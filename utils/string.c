#include "../include/minishell.h"

// compare two strings
// return 1 if the strings are equal
// return 0 if the strings are not equal
int is_equal(char *s, char *p)
{
    if (ft_strlen(s) != ft_strlen(p))
        return 0;
    return ft_strncmp(s, p, ft_strlen(p)) == 0;
}

// extract a string from a string and return a pointer to the extracted string
// len is the length of the extracted string
// flag is a flag to indicate if the extracted string should be added to the garbage collector
char *ft_strndup(char *s, size_t len, int flag)
{
    char *r;
    int i;

    i = 0;
    r = ft_malloc(len + 1, flag);
    if (!r)
        return NULL;
    while (s[i] && i < len)
    {
        r[i] = s[i];
        i++;
    }
    r[i] = 0;
    return r;
}