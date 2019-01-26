#pragma pack (push, 1)

#include "stdio.h"
#include "stdlib.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

#define CR0_PE        0x1      // 0x00000001
#define CR0_PG        (1<<31)  // 0x80000000
#define CR4_PSE       (1<<4)   // 0x00000010
#define PF_EXCEPTION  14
#define PAGE_SIZE     4096
#define ENTRY_SIZE    4

#define PDE_TRIVIAL_PRESENT     0x007  //0000 0000 0111 //present read-write user 4Kb
#define PDE_TRIVIAL_NONPRESENT  0x000  //0000 0000 0000 //not present
#define PTE_TRIVIAL_PRESENT     0x007  //0000 0000 0111 //present read-write user 4Kb
#define PTE_TRIVIAL_NONPRESENT  0xBA4  //1011 1010 0100 //not present

uint16 old_segment = 0;  //segment selector of old PF handler
uint32 old_offset  = 0;  //offset to old PF handler
char*  pf_addr     = 0;  //address generating PF
uint32 pte_addr    = 0;  //address of PTE containing ref to pf_addr
uint32 pf_counter  = 0;  //PF counter


typedef union _PDE {
    uint32 raw;
    struct {
        uint32 p:1;
        uint32 rw:1;
        uint32 us:1;
        uint32 xx:4; //PCD,PWT,A,D
        uint32 ps:1;
        uint32 ign:4;
        uint32 pfn:20;
    };
} PDE, *PPDE;

typedef union _PTE {
    uint32 raw;
    struct {
        uint32 p:1;
        uint32 rw:1;
        uint32 us:1;
        uint32 xx:4; //PCD,PWT,A,D
        uint32 ps:1;
        uint32 g:1;
        uint32 avl:3;
        uint32 pfn:20;
    };
} PTE, *PPTE;

typedef struct _IDTENTRY {
    uint16 offset_l;
    uint16 seg_sel;
    uint8  zero;
    uint8  flags;
    uint16 offset_h;
} IDTENTRY, *PIDTENTRY;

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


void get_sysinfo(PSYSINFO psysinfo) {
    uint16 _cs = 0;
    uint32 _cr0 = 0;
    DTR* _gdt = &psysinfo->gdt;
    DTR* _idt = &psysinfo->idt;
    uint16 _ldt = 0;
    uint16 _tr = 0;

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


void idt_set_gate(PIDTENTRY idt, uint8 num, uint32 offset, uint16 seg_sel, uint8 flags) {
    idt[num].offset_l = offset & 0xFFFF;
    idt[num].offset_h = (offset >> 16) & 0xFFFF;
    idt[num].seg_sel = seg_sel;
    idt[num].zero = 0;
    idt[num].flags = flags;
}


void __declspec( naked ) pf_handler(void) {
    __asm {
        //cli
        push eax
        push edx
        mov edx, cr2
        cmp edx, pf_addr        //"my" address
        jnz pf
        mov eax, pte_addr       //pde/pte corresponding to "my" unpresent address
        or dword ptr [eax], 1h  //restore P bit
        invlpg [eax]            //invalidate all paging caches for "my" address
        lea eax, pf_counter
        add [eax], 1            //inc counter of "my" #PF
        jmp done
    pf:
        pop edx
        pop eax
        push old_segment
        push old_offset
        retf
    done:
        pop edx
        pop eax
        //sti
        add esp, 4
        iretd
    }
}


void paging_task() {
    const int entries_num = 1024;
    const int present_entries_num = 256;
    int i = 0;
    int j = 0;
    char* addr = (char*)0x1FC00000;
    uint32 pt = (uint32)malloc(1024 * PAGE_SIZE + PAGE_SIZE);
    uint32 pt_aligned = (pt & 0xFFFFF000) + PAGE_SIZE;
    PPTE page_tables = (PPTE)pt_aligned;
    uint32 pd = (uint32)malloc(2 * PAGE_SIZE);
    uint32 pd_aligned = (pd & 0xFFFFF000) + PAGE_SIZE;
    PPDE page_dir = (PPDE)pd_aligned;

    for (i = 0; i < entries_num; i++) {
        page_dir[i].raw = pt_aligned + i * PAGE_SIZE;
        page_dir[i].raw |= (i < present_entries_num) ? PDE_TRIVIAL_PRESENT : PDE_TRIVIAL_NONPRESENT;
    }
    page_dir[0x3C0].raw = pd_aligned | PDE_TRIVIAL_PRESENT;  //self-mapped to 0xF0000000

    for (i = 0; i < present_entries_num; i++) {
        for (j = 0; j < entries_num; j++) {
            page_tables[i * entries_num + j].raw = (i * entries_num + j) << 12;
            page_tables[i * entries_num + j].raw |= PTE_TRIVIAL_PRESENT;
        }
    }
    page_tables[0x7F * entries_num + 0].raw &= 0xFFFFFFFE;
    page_tables[0x7F * entries_num + 1].raw &= 0xFFFFFFFE;

    __asm {
        pushfd
        cli
        mov eax, pd_aligned
        mov cr3, eax         //this also resets instruction cache
        mov eax, cr4
        or eax, 0x80
        mov cr4, eax         //set CR4.PGE
        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax         //set CR0.PG
        popfd
    }

    pf_addr = addr + 13;
    pte_addr = 0xF007F000;
}


void pf_test(void) {
    uint32 new_offset = 0;
    uint16 new_segment = 0;
    PIDTENTRY idt_table = NULL;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);

    idt_table = (PIDTENTRY)sysinfo.idt.base;
    old_offset = idt_table[PF_EXCEPTION].offset_h << 16 | idt_table[PF_EXCEPTION].offset_l;
    old_segment = idt_table[PF_EXCEPTION].seg_sel;

    __asm {
        mov edx, offset pf_handler
        mov new_offset, edx
        mov ax, seg pf_handler
        mov new_segment, ax
    }

    idt_set_gate(idt_table, PF_EXCEPTION, new_offset, new_segment, idt_table[PF_EXCEPTION].flags);

    printf("PF counter: %d\n", pf_counter);
    printf("1. I am memory %d\n", *pf_addr);  //recovering page
    printf("PF counter: %d\n", pf_counter);
    printf("2. I am memory %d\n", *pf_addr);
    printf("PF counter: %d\n", pf_counter);
    printf("3. I am memory %d\n", *(pf_addr + PAGE_SIZE));  //#PF
}


void main() {
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);
    printf("0x%08X - %s, %s \n",
        sysinfo.cr0,
        sysinfo.cr0 & CR0_PE ? "Protected mode" : "Real mode",
        sysinfo.cr0 & CR0_PG ? "Paging on" : "Paging off"
    );
    printf("========================== \n");

    paging_task();
    pf_test();

    get_sysinfo(&sysinfo);
    printf("========================== \n");
    printf("0x%08X - %s, %s \n",
        sysinfo.cr0,
        sysinfo.cr0 & CR0_PE ? "Protected mode" : "Real mode",
        sysinfo.cr0 & CR0_PG ? "Paging on" : "Paging off"
    );
}

