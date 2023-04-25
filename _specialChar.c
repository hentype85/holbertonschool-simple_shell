#include "main.h"

/**
 * SpecialChar - check if the string contains special chars
 * @s: pointer to the string to be checked
 * Return: 1 if the string contains the special char or 0
 */
int SpecialChar(char *s)
{
	int i = 0, j = 0, len = 0;
	char special[] = "\"'\\*&#^[[C";

	while (special[len])
		len++;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (s[i] == special[j])
			{
				return (1);
			}
		}
	}

	return (0);
}
