section .data
    format db 'Hello, Holberton', 0

section .text
    global main
    extern printf

main:
    mov edi, format     ; Load the address of the format string into the EDI register
    xor eax, eax        ; Clear the EAX register (set it to 0)
    call printf         ; Call the printf function to print the formatted string
    mov eax, 0          ; Set the return value to 0
    ret                 ; Return from the main function
