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
; https://www.sandpile.org/x86/cpuid.htm

section .text
global cpuid0
global cpuid1
global cpuid7
global cpuid0_win
global cpuid1_win
global cpuid7_win
global ASM_rdrand

cpuid0:
    mov rax, 0    
    push rbx
    push rdx
    push rcx
    CPUID    
    mov  [rdi], ebx
    mov  [rdi + 4], edx   
    mov  [rdi + 8], ecx    
    pop  rcx
    pop  rdx
    pop  rbx    
    mov  eax, 0    
    ret

cpuid0_win:
    mov rax, 0
    
    push rbx
    push rdx
    push rcx
	push rdi
	mov  rdi, rcx
    CPUID
    
    ;mov  rbx, 65
    mov  [rdi], ebx
    mov  [rdi + 4], edx   
    mov  [rdi + 8], ecx
    
	pop  rdi
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
	push rdi
    CPUID        
    mov  [rdi + 0],  eax
    mov  [rdi + 4],  ebx   
    mov  [rdi + 8],  ecx
    mov  [rdi + 12], edx    
	pop  rdi
    pop  rcx
    pop  rdx
    pop  rbx    
    mov  eax, 0    
    ret

cpuid1_win:
    mov rax, 1    
    push rbx
    push rdx
    push rcx
    push rdi
	mov  rdi, rcx
    CPUID        
    mov  [rdi + 0],  eax
    mov  [rdi + 4],  ebx   
    mov  [rdi + 8],  ecx
    mov  [rdi + 12], edx    
    pop  rdi
    pop  rcx
    pop  rdx
    pop  rbx    
    mov  eax, 0    
    ret

cpuid7_win:
    mov   rax, 7   
    push  rbx
    push  rdx
    push  rcx
    push  rdi
    mov   rdi, rcx
	mov   ecx, 0	
    CPUID        
    mov   [rdi + 0],  eax
    mov   [rdi + 4],  ebx   
    mov   [rdi + 8],  ecx
    mov   [rdi + 12], edx
    pop   rdi
    pop   rcx
    pop   rdx
    pop   rbx    
    mov   eax, 0    
    ret

ASM_rdrand:
    mov    rax, 0
    rdrand rax
    ret
