#pragma pack (push, 1)

#include "stdio.h"
#include "assert.h"
#include "stdlib.h"

#define CR0_PE 0x1
#define CR0_PG (1 << 31) //0x80000000

typedef unsigned int       uint32;
typedef unsigned short int uint16;
typedef unsigned char      uint8;

typedef struct _DTR {
    uint16 limit;
    uint32 base;
    uint16 _padding;
} DTR, *PDTR;

typedef union _SELECTOR {
    uint16 raw;
    struct {
        uint16 pl:2;
        uint16 table:1;
        uint16 index:13;
    };
} SELECTOR, *PSELECTOR;

typedef struct _SYSINFO {
    SELECTOR cs;
    uint32 cr0;
    DTR gdt;
    DTR idt;
    SELECTOR ldt;
    SELECTOR tr;
} SYSINFO, *PSYSINFO;

typedef enum _TABLETYPE {
    TABLETYPE_GDT     = 0,
    TABLETYPE_LDT     = 1,
    TABLETYPE_IDT     = 2,
    TABLETYPE_UNKNOWN = 3
} TABLETYPE, *PTABLETYPE;

typedef enum _DESCTYPE {
    DESCTYPE_RESERVED0        = 0,
    DESCTYPE_TSS16            = 1,
    DESCTYPE_LDT              = 2,
    DESCTYPE_TSS16_BUSY       = 3,
    DESCTYPE_CALLGATE16       = 4,
    DESCTYPE_TASKGATE         = 5,
    DESCTYPE_INTERRUPTGATE16  = 6,
    DESCTYPE_TRAPGATE16       = 7,
    DESCTYPE_RESERVED8        = 8,
    DESCTYPE_TSS32            = 9,
    DESCTYPE_RESERVED10       = 10,
    DESCTYPE_TSS32_BUSY       = 11,
    DESCTYPE_CALLGATE32       = 12,
    DESCTYPE_RESERVED13       = 13,
    DESCTYPE_INTERRUPTGATE32  = 14,
    DESCTYPE_TRAPGATE32       = 15,
    DESCTYPE_DATA_R           = 16,
    DESCTYPE_DATA_RA          = 17,
    DESCTYPE_DATA_RW          = 18,
    DESCTYPE_DATA_RWA         = 19,
    DESCTYPE_DATA_RD          = 20,
    DESCTYPE_DATA_RDA         = 21,
    DESCTYPE_DATA_RWD         = 22,
    DESCTYPE_DATA_RWDA        = 23,
    DESCTYPE_CODE_E           = 24,
    DESCTYPE_CODE_EA          = 25,
    DESCTYPE_CODE_ER          = 26,
    DESCTYPE_CODE_ERA         = 27,
    DESCTYPE_CODE_EC          = 28,
    DESCTYPE_CODE_ECA         = 29,
    DESCTYPE_CODE_ERC         = 30,
    DESCTYPE_CODE_ERCA        = 31,
    DESCTYPE_UNKNOWN          = 32
} DESCTYPE, *PDESCTYPE;

typedef struct _DESC {
    DESCTYPE type;
    uint32 base;      // for segment desc
    uint32 limit;     // for segment desc
    uint32 g;         // for segment desc
    uint32 db;        // for segment desc
    uint32 l;         // for segment desc
    uint32 avl;       // for segment desc
    uint32 p;         // for segment desc
    uint32 dpl;       // for segment desc
    uint32 seg_sel;   // for gates
    uint32 offset;    // for gates
    uint32 param;     // for callgate
} DESC, *PDESC;

typedef struct _TSS {
    uint16 backlink, _backlink;
    uint32 esp0;
    uint16 ss0, _ss0;
    uint32 esp1;
    uint16 ss1, _ss1;
    uint32 esp2;
    uint16 ss2, _ss2;
    uint32 cr3;
    uint32 eip;
    uint32 eflags;
    uint32 eax;
    uint32 ecx;
    uint32 edx;
    uint32 ebx;
    uint32 esp;
    uint32 ebp;
    uint32 esi;
    uint32 edi;
    uint16 es, _es;
    uint16 cs, _cs;
    uint16 ss, _ss;
    uint16 ds, _ds;
    uint16 fs, _fs;
    uint16 gs, _gs;
    uint16 ldt, _ldt;
    uint16 trace, bitmap;
} TSS, *PTSS;


void get_sysinfo(SYSINFO* psysinfo) {
    uint16 _cs = 0;
    uint32 _cr0 = 0;
    DTR* _gdt = &psysinfo->gdt;
    DTR* _idt = &psysinfo->idt;
    uint16 _ldt = 0;
    uint16 _tr = 0;

    assert(psysinfo);

    __asm {
        mov eax, cr0
        mov _cr0, eax
        mov ax, cs
        mov _cs, ax
        mov eax, _gdt
        sgdt [eax]
        mov eax, _idt
        sidt [eax]
        sldt _ldt
        str _tr
    }

    psysinfo->cr0 = _cr0;
    psysinfo->cs.raw = _cs;
    psysinfo->ldt.raw = _ldt;
    psysinfo->tr.raw = _tr;
}


void get_descinfo(DESC* pdesc, uint32 desc_addr) {
    uint32 desc_second = 0;
    uint32 desc_first = 0;

    assert(pdesc);

    __asm {
        mov eax, desc_addr
        mov ebx, [eax]
        mov desc_first, ebx
        mov ebx, [eax+4]
        mov desc_second, ebx
    }

    pdesc->param = 0;
    pdesc->p = (0x00008000 & desc_second) >> 15;
    pdesc->dpl = (0x00006000 & desc_second) >> 13;
    pdesc->type = (0x00001f00 & desc_second) >> 8;

    if (pdesc->type >= DESCTYPE_DATA_R || pdesc->type == DESCTYPE_LDT
            || pdesc->type == DESCTYPE_TSS16 || pdesc->type == DESCTYPE_TSS16_BUSY
            || pdesc->type == DESCTYPE_TSS32 || pdesc->type == DESCTYPE_TSS32_BUSY) {
        pdesc->offset   = 0;
        pdesc->seg_sel  = 0;
        pdesc->g        = (0x00800000 & desc_second) >> 23;
        pdesc->db       = (0x00400000 & desc_second) >> 22;
        pdesc->l        = (0x00200000 & desc_second) >> 21;
        pdesc->avl      = (0x00100000 & desc_second) >> 20;
        pdesc->limit    = (0x000f0000 & desc_second) + (0x0000ffff & desc_first);
        pdesc->base     = (0xff000000 & desc_second) + ((0x000000ff & desc_second) << 16)
                          + ((0xffff0000 & desc_first) >> 16);
    }
    else {
        pdesc->g     = 0;
        pdesc->db    = 0;
        pdesc->db    = 0;
        pdesc->l     = 0;
        pdesc->avl   = 0;
        pdesc->limit = 0;
        pdesc->base  = 0;
        if (pdesc->type == DESCTYPE_CALLGATE16 || pdesc->type == DESCTYPE_CALLGATE32) {
            pdesc->param = 0x0000000f & desc_second;
        }
        pdesc->offset  = (0xffff0000 & desc_second) + (0x0000ffff & desc_first);
        pdesc->seg_sel = (0xffff0000 & desc_first) >> 16;
    }
}


void print_desc(FILE* out, DESC* pdesc, uint32 entry_index) {
    assert(out);
    assert(pdesc);

    fprintf(out, "-------------------%04d--------------------\n", entry_index);
    if (pdesc->type == DESCTYPE_CALLGATE16 || pdesc->type == DESCTYPE_CALLGATE32) {
        fprintf(out, "CALLGATE\nseg_sel = %04x\noffset = %08x\n", pdesc->seg_sel, pdesc->offset);
        fprintf(out, "param_count = %d\n", pdesc->param);
    }
    else if (pdesc->type == DESCTYPE_TASKGATE) {
        fprintf(out, "TASKGATE\nseg_sel = %04x\n", pdesc->seg_sel);
    }
    else if (pdesc->type == DESCTYPE_INTERRUPTGATE16 || pdesc->type == DESCTYPE_INTERRUPTGATE32) {
        fprintf(out, "INTERRUPTGATE\nseg_sel = %04x\noffset = %08x\n", pdesc->seg_sel, pdesc->offset);
    }
    else if (pdesc->type == DESCTYPE_TRAPGATE16 || pdesc->type == DESCTYPE_TRAPGATE32) {
        fprintf(out, "TRAPGATE\nseg_sel = %04x\noffset = %08x\n", pdesc->seg_sel, pdesc->offset);
    }
    else {
        if (pdesc->type == DESCTYPE_LDT) {
            fprintf(out, "LDT\n");
        }
        else if (pdesc->type == DESCTYPE_TSS16 || pdesc->type == DESCTYPE_TSS16_BUSY
                    || pdesc->type == DESCTYPE_TSS32 || pdesc->type == DESCTYPE_TSS32_BUSY) {
            fprintf(out, "TSS\n", pdesc->type);
        }
        else if (DESCTYPE_DATA_R <= pdesc->type && pdesc->type <= DESCTYPE_DATA_RWDA) {
            fprintf(out, "DATA  (E = %d W = %d A = %d)\n",
                    4 & pdesc->type, 2 & pdesc->type, 1 & pdesc->type
            );
        }
        else if (DESCTYPE_CODE_E <= pdesc->type && pdesc->type <= DESCTYPE_CODE_ERCA) {
            fprintf(out, "CODE  (C = %d R = %d A = %d)\n",
                    4 & pdesc->type, 2 & pdesc->type, 1 & pdesc->type
            );
        }
        else {
            fprintf(out, "RESERVED\n");
        }

        if (pdesc->p) {
            fprintf(out, "base = %08x\nlimit = %d (in bytes)\ng = %d\nD/B = %d\nL = %d\nAVL = %d\n",
                    pdesc->base, pdesc->limit * (pdesc->g ? 4096 : 1), pdesc->g, pdesc->db, pdesc->l, pdesc->avl
            );
        }
    }

    fprintf(out, "Presence = %d\nDPL = %d\n", pdesc->p, pdesc->dpl);
    fprintf(out, "-------------------------------------------\n");
}


void print_table(FILE* out, TABLETYPE table_type) {
    uint32 i = 0;
    uint32 table_limit = 0;
    uint32 table_base = 0;
    DESC desc;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);

    assert(out);
    assert(0 <= table_type && table_type < TABLETYPE_UNKNOWN);

    switch (table_type) {
        case TABLETYPE_GDT:
            table_limit = (sysinfo.gdt.limit + 1) / 8;
            table_base = sysinfo.gdt.base;
            fprintf(out, "\n\n************* GDT *************\n");
            break;
        case TABLETYPE_IDT:
            table_limit = (sysinfo.idt.limit + 1) / 8;
            table_base = sysinfo.idt.base;
            fprintf(out, "\n\n************* IDT *************\n");
            break;
        case TABLETYPE_LDT:
            assert(!(sysinfo.ldt.raw & 0x0004));
            get_descinfo(&desc, sysinfo.gdt.base + (sysinfo.ldt.raw & 0xfff8));
            assert(desc.type == DESCTYPE_LDT);
            table_limit = (desc.limit + 1) / 8;
            table_base = desc.base;
            fprintf(out, "\n\n************* LDT *************\n");
            break;
        default:
            assert(0);
    }

    for (i = 0; i < table_limit; i++) {
        get_descinfo(&desc, table_base + i * 8);
        print_desc(out, &desc, i);
    }

    fprintf(out, "*******************************\n");
}


void print_tss(FILE* out) {
    TSS* ptss = NULL;
    DESC desc;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);

    assert(out);
    assert(!(0x0004 & sysinfo.tr.raw));

    get_descinfo(&desc, sysinfo.gdt.base + (0xfff8 & sysinfo.tr.raw));
    assert(!desc.db);
    assert(!desc.l);
    assert(!(desc.type & (1 << 5)));
    assert(desc.type == DESCTYPE_TSS16 || desc.type == DESCTYPE_TSS16_BUSY
               || desc.type == DESCTYPE_TSS32 || desc.type == DESCTYPE_TSS32_BUSY);

    ptss = (TSS*)desc.base;

    fprintf(out, "\n\n************* TSS *************\n");
    fprintf(out, "backlink = %u\n", ptss->backlink);
    fprintf(out, "esp0 = %u\nss0 = %u\n", ptss->esp0, ptss->ss0);
    fprintf(out, "esp1 = %u\nss1 = %u\n", ptss->esp1, ptss->ss1);
    fprintf(out, "esp2 = %u\nss2 = %u\n", ptss->esp2, ptss->ss2);
    fprintf(out, "cr3 = %u\neip = %u\neflags = %u\n", ptss->cr3, ptss->eip, ptss->eflags);
    fprintf(out, "eax = %u\necx = %u\nedx = %u\nebx = %u\n", ptss->eax, ptss->ecx, ptss->edx, ptss->ebx);
    fprintf(out, "esp = %u\nebp = %u\nesi = %u\nedi = %u\n", ptss->esp, ptss->ebp, ptss->esi, ptss->edi);
    fprintf(out, "es = %u\ncs = %u\nss = %u\n", ptss->es, ptss->cs, ptss->ss);
    fprintf(out, "ds = %u\nfs = %u\ngs = %u\n", ptss->ds, ptss->fs, ptss->gs);
    fprintf(out, "ldt = %u\n", ptss->ldt);
    fprintf(out, "trace = %u\niobitmap = %u\n", ptss->trace, ptss->bitmap);
    fprintf(out, "*******************************\n");
}


void set_gdt_desc(void* pdata, uint32 data_size, uint8 access, uint8 gran) {
    uint32 i = 0;
    uint32 desc_second = 0;
    uint32 desc_first = 0;
    uint32 table_limit = 0;
    uint32 table_base = 0;
    uint32 desc_addr = 0;
    uint16 tr_sel = 0;
    DESC desc;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);
    table_limit = (sysinfo.gdt.limit + 1) / 8;
    table_base = sysinfo.gdt.base;

    assert(pdata);
    assert(data_size < 1048576); // 1Mb == 2^20 bytes

    for (i = 0; i < table_limit; i++) {
        get_descinfo(&desc, table_base + i * 8);
        if (!desc.p && i && (desc.type == DESCTYPE_RESERVED0 || desc.type == DESCTYPE_RESERVED8
                || desc.type == DESCTYPE_RESERVED10 || desc.type == DESCTYPE_RESERVED13)) {
            desc_addr = table_base + i * 8;
            tr_sel = i << 3;
            break;
        }
    }

    desc_second = 0xff000000 & (uint32)pdata;
    desc_second += ((gran ? (uint32)1 : 0) << 23);
    desc_second += ((uint32)1 << 20);
    desc_second += ((0x000f0000 & (data_size - 1)) << 16);
    desc_second += ((uint32)access << 8);
    desc_second += ((0x00ff0000 & (uint32)pdata) >> 16);
    desc_first = (0x0000ffff & (uint32)pdata) << 16;
    desc_first += 0x0000ffff & (data_size / (gran ? 4096 : 1) - 1);

    __asm {
        mov eax, desc_addr
        mov ebx, desc_first
        mov [eax], ebx
        mov ebx, desc_second
        mov [eax+4], ebx
        mov ax, tr_sel
        ltr ax
    }
}


void main() {
    SYSINFO sysinfo;
    FILE* out = NULL;
    TSS* ptss = calloc(1, sizeof(TSS));
    assert(ptss);

    ptss->eax = 13;
    ptss->backlink = 1234;
    set_gdt_desc(ptss, sizeof(TSS), 0x89, 0);

    out = fopen("out.txt", "w");
    if (!out) {
        perror("Can't open file for writing");
        return;
    }

    get_sysinfo(&sysinfo);
    fprintf(out, "\n\n******** General info *********\n");
    fprintf(out, "GDT: base=0x%08X limit=0x%04X (%d entries)\n",
        sysinfo.gdt.base, sysinfo.gdt.limit, (sysinfo.gdt.limit + 1) / 8
    );
    fprintf(out, "IDT: base=0x%08X limit=0x%04X (%d entries)\n",
        sysinfo.idt.base, sysinfo.idt.limit, (sysinfo.idt.limit + 1) / 8
    );
    fprintf(out, "LDT: selector=0x%04X \n", sysinfo.ldt.raw);
    fprintf(out, "TR : selector=0x%04X \n", sysinfo.tr.raw);
    fprintf(out, "*******************************\n");

    print_table(out, TABLETYPE_GDT);
    print_table(out, TABLETYPE_IDT);
    print_table(out, TABLETYPE_LDT);
    print_tss(out);

    if (fclose(out)) {
        perror("Can't close file");
        return;
    }

    free(ptss);
    ptss = NULL;
}
