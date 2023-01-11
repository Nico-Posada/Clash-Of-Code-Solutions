// First assembly solution lol
// RDI
// RSI
// RDX
// RCX
__attribute__((naked)) long solve(char* letters, int strlen)
{
    __asm__(".intel_syntax noprefix;\
    push rbx;\
    push r8;\
    mov rax, 1;\
    loop%=:\
    movzx rbx, byte ptr [rdi+r8];\
    shl ebx, 1;\
    xor ebx, 0x82;\
    mul ebx;\
    inc r8;\
    cmp r8, rsi;\
    jl loop%=;\
    pop r8;\
    pop rbx;\
    ret;\
    .att_syntax;" : :);
}

int main()
{
    char letters[11];
    scanf("%[^\n]", letters);
    printf("%ld\n", solve(letters, strlen(letters)));
}
