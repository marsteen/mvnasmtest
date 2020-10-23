;
;
; Parameter-Reihenfolge (int):
; rdi, rsi, rdx, rcx, r8, r9
;
; Reihenfolge (ARM64 ABI):
; RDI, RSI, RDX, RCX, R8, R9 
; Reihenfolge (Windows 64 ABI):
; RCX, RDX, R8, and R9
;
; https://en.wikipedia.org/wiki/X86_calling_conventions

section .text
global cpuid0
global cpuid1
global ASM_rdrand

cpuid0:
    mov rax, 0
    
    push rbx
    push rdx
    push rcx
    CPUID
    
    ;mov  rbx, 65
    mov  [rdi], ebx
    mov  [rdi + 4], edx   
    mov  [rdi + 8], ecx
    
    pop  rcx
    pop  rdx
    pop  rbx
    
    mov  eax, 0
    
    ret

;
;
;

cpuid1:
    mov rax, 1
    
    push rbx
    push rdx
    push rcx
    CPUID
        
    mov  [rdi + 0],  eax
    mov  [rdi + 4],  ebx   
    mov  [rdi + 8],  ecx
    mov  [rdi + 12], edx
    
    pop  rcx
    pop  rdx
    pop  rbx
    
    mov  eax, 0
    
    ret
    
ASM_rdrand:

    mov    rax, 0
    rdrand rax
    ret
    
