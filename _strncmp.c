#include "main.h"

/**
 * _strncmp - compare two srings to "n" chars len
 * @s1: pointer to string
 * @s2: pointer to other string
 * @n: len of characters to compare
 * Return: if the string are equal return 0
 * or the difference between characters that do not match
 */
int _strncmp(char *s1, char *s2, int n)
{
	int i = 0;

	while (s1[i] == s2[i] && i < n)
	{
		if (s1[i] == '\0')
			return (0);
		i++;
	}

	if (i == n)
		return (0);
	else
		return (s1[i] - s2[i]);
}
