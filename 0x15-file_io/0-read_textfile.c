#include "main.h"
#include <stdlib.h>

/**
 * read_textfile - Read text file and print to STDOUT.
 * @filename: Text file being read.
 * @letters: Number of letters to be read.
 *
 * Return: The actual number of bytes read and printed,
 *         0 when the function fails or filename is NULL.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
ssize_t w;
int fd;
char *buf;

if (filename == NULL)
return (0);

/*
 * Open file in read-only mode
 */
fd = open(filename, O_RDONLY);
if (fd == -1)
return (0);

/*
 * Allocate memory for the buffer
 */
buf = malloc(sizeof(char) * letters);
if (buf == NULL)
{
close(fd);
return (0);
}

/*
 * * Read from the file into the buffer
 */
ssize_t t = read(fd, buf, letters);
w = write(STDOUT_FILENO, buf, t);

/*
 * Free the buffer and close the file descriptor
 */
free(buf);
close(fd);

return (w);
}
