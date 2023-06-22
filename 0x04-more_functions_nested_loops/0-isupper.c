#include "main.h"

/**
 * _isupper - uppercase letters
 * @c: character to check
 * Return: 1 for uppercase and 0 for anything else
 */

int _isupper(int c)
{
	if (c >= 65 && c <= 90)
		return (1);
	else
		return (0);
}
