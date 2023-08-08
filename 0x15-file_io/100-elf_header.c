#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_elf_info(const Elf64_Ehdr *header);
void close_elf(int elf);

/**
* check_elf - Checks if a file is an ELF file.
* @e_ident: A pointer to an array containing the ELF magic numbers.
*
* Description: If the file is not an ELF file, exit code 98.
*/

void check_elf(unsigned char *e_ident)
{
int index;

for (index = 0; index < 4; index++)
{
if (e_ident[index] != 127 &&
e_ident[index] != 'E' &&
e_ident[index] != 'L' &&
e_ident[index] != 'F')
{
dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
exit(98);
}
}
}

/**
* print_elf_info - Prints various information from the ELF header.
* @header: A pointer to the ELF header structure.
*/

void print_elf_info(const Elf64_Ehdr *header)
{
int index;

printf("ELF Header:\n");

printf(" Magic:");
for (index = 0; index < EI_NIDENT; index++)
{
printf(" %02x", header->e_ident[index]);
}
printf("\n");

printf(" Class: ");
switch (header->e_ident[EI_CLASS])
{
// ... (other cases)
}

printf(" Data: ");
switch (header->e_ident[EI_DATA])
{
// ... (other cases)
}

// ... (other cases)

printf(" Entry point address: ");
if (header->e_ident[EI_DATA] == ELFDATA2MSB)
{
// ... (conversion for big endian)
}
if (header->e_ident[EI_CLASS] == ELFCLASS32)
{
printf("%#x\n", (unsigned int)header->e_entry);
}
else
{
printf("%#lx\n", header->e_entry);
}
}

/**
* close_elf - Closes an ELF file.
* @elf: The file descriptor of the ELF file.
*
* Description: If the file cannot be closed, exit code 98.
*/

void close_elf(int elf)
{
if (close(elf) == -1)
{
dprintf(STDERR_FILENO,
"Error: Can't close fd %d\n", elf);
exit(98);
}
}

/**
* main - Displays the information contained in the
* ELF header at the start of an ELF file.
* @argc: The number of arguments supplied to the program.
* @argv: An array of pointers to the arguments.
*
* Return: 0 on success.
*
* Description: If the file is not an ELF File or
* the function fails, exit code 98.
*/

int main(int __attribute__((__unused__)) argc, char *argv[])
{
Elf64_Ehdr *header;
int o, r;

o = open(argv[1], O_RDONLY);
if (o == -1)
{
dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
exit(98);
}
header = malloc(sizeof(Elf64_Ehdr));
if (header == NULL)
{
close_elf(o);
dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
exit(98);
}
r = read(o, header, sizeof(Elf64_Ehdr));
if (r == -1)
{
free(header);
close_elf(o);
dprintf(STDERR_FILENO, "Error: `%s`: No such file\n", argv[1]);
exit(98);
}

check_elf(header->e_ident);
print_elf_info(header);

free(header);
close_elf(o);
return (0);
}
