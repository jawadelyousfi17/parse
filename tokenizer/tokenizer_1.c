#include "../include/minishell.h"




int ft_tokenize_space(char **s, t_token **head, t_minishell *m)
{
    char *start;
    char *r;

    start = *s;
    while (**s && (**s == ' ' || **s == '\t'))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    if (!ft_add_token(head, r, SPACES))
        return (0);
    return (1);
}

int ft_tokenize_txt(char **s, t_token **head, t_minishell *m)
{
    char *start;
    char *r;

    start = *s;
    if (**s == '$')
        (*s)++;
    while (**s && !ft_strchr(" \t|<>$\"'", **s))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    if (!ft_add_token(head, r, TEXT))
        return (0);
    return (1);
}


int ft_tokenize_dquote(char **s, t_token **head, t_minishell *m)
{
    char *start;
    char *r;

    start = *s;
    (*s)++;
    while (**s && **s != DOUBLE_QUOTE)
        (*s)++;
    if (**s == DOUBLE_QUOTE)
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_add_token(head, r, D_QUOTE);
}

int ft_tokenize_squote(char **s, t_token **head, t_minishell *m)
{
    char *start;
    char *r;

    start = (*s);
    (*s)++;
    while (**s && **s != SINGLE_QUOTE)
        (*s)++;
    (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_add_token(head, r, S_QUOTE);
}

int ft_tokenize_pipe(char **s, t_token **head, t_minishell *m)
{
    char *r;

    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_add_token(head, r, PIPE);
}
