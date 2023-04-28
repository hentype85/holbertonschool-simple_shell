#include "main.h"

/**
 * _strdup - duplicate a string
 * @s: pointer to string to duplicate
 * Return: duplicated string or NULL if fails
 */
char *_strdup(char *s)
{
	char *p = NULL;
	int i = 0, len = 0;

	if (s == NULL)
		return (NULL);
	while (s[len])
		len++;
	p = malloc(sizeof(char) * len + 1);

	if (p == NULL)
		return (NULL);

	while (i < len)
	{
		p[i] = s[i];
		i++;
	}

	p[len] = '\0';

	return (p);
}

