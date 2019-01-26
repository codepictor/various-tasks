#pragma pack (push, 1)

#include "stdio.h"
#include "stdlib.h"

typedef unsigned char      uint8;
typedef unsigned short int uint16;
typedef unsigned int       uint32;

#define CR0_PE 0x1         // 0x00000001
#define CR0_PG (1 << 31)   // 0x80000000
#define MY_EXCEPTION_N 13

const char* format = "%s\n";
const char* msg = "### Hello from my handler!";
uint16 old_segment = 0;    //segment of previous interrupt handler
uint32 old_offset = 0;     //offset of previous interrupt handler

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


void generate_my_exception(void) {
    //#GP - trying to disable PM and enable paging simultaneously
    uint32 _cr0 = 0;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);
    _cr0 = sysinfo.cr0;
    _cr0 = (_cr0 | CR0_PG) & (~CR0_PE);

    __asm {
        mov eax, _cr0
        mov cr0, eax
    }
}


void generate_my_wrong_exception(void) {
    //#GP - trying to disable PM and enable paging simultaneously
    uint32 _cr0 = 0;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);
    _cr0 = sysinfo.cr0;
    _cr0 = (_cr0 | CR0_PG) & (~CR0_PE);

    __asm {
        mov eax, _cr0
        mov cr0, eax
    }
}


void __declspec(naked) handle_my_exception(void) {
    __asm {
        push eax
        push ebx
        pushfd

        mov eax, offset generate_my_exception
        mov ebx, [esp+4]
        cmp eax, ebx
        jge unknown_src
        sub ebx, 80
        cmp eax, ebx
        jle unknown_src

        mov ax, seg generate_my_exception
        mov bx, [esp+8]
        cmp ax, bx
        jne unknown_src

        pusha
        push msg             //"### Hello from my handler!"
        push format          //"%s\n"
        call printf          //print greeting
        add esp, 8           //printf had 2 arguments
        popa

        popfd
        pop ebx
        pop eax

        add esp, 4           //pop error code
        mov eax, [esp]
        add eax, 3           //size(mov cr0, eax0) = 3 bytes
        mov [esp], eax
        iretd

    unknown_src:             //calling old handler
        popfd
        pop ebx
        pop eax
        add esp, 4
        push old_segment
        push old_offset
        retf
    }
}


void set_idt_desc(void) {
    uint32 new_offset = 0;
    uint16 new_segment = 0;
    PIDTENTRY idt_table = NULL;
    SYSINFO sysinfo;
    get_sysinfo(&sysinfo);
    idt_table = (PIDTENTRY)sysinfo.idt.base;

    old_offset = (idt_table[MY_EXCEPTION_N].offset_h << 16) | (idt_table[MY_EXCEPTION_N].offset_l);
    old_segment = idt_table[MY_EXCEPTION_N].seg_sel;
    //old_offset = (idt_table[14].offset_h << 16) | (idt_table[14].offset_l);
    //old_segment = idt_table[14].seg_sel;

    __asm {
        mov edx, offset handle_my_exception
        mov new_offset, edx
        mov ax, seg handle_my_exception
        mov new_segment, ax
    }

    idt_table[MY_EXCEPTION_N].offset_l = new_offset & 0xFFFF;
    idt_table[MY_EXCEPTION_N].offset_h = (new_offset >> 16) & 0xFFFF;
    idt_table[MY_EXCEPTION_N].seg_sel = new_segment;
    idt_table[MY_EXCEPTION_N].zero = 0;
    idt_table[MY_EXCEPTION_N].flags = idt_table[MY_EXCEPTION_N].flags;
}


void main() {
    set_idt_desc();
    printf("main: IDT desc has been set\n");

    generate_my_exception();
    printf("*********************************\n");

    printf("DEBUG: old_segment = %04x   old_offset = %08x\n", old_segment, old_offset);
    generate_my_wrong_exception();
    printf("main: Returning from main\n");
}

