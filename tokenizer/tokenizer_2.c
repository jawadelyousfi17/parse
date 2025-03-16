
#include "../include/minishell.h"

int ft_tokenize_redir_in(char **s, t_token **head, t_minishell *m)
{
     t_token *token;
    char *r;

    if (*(*s + 1) == '<')
    {
        r = ft_strndup(*s, 2, GB_C);
        if (!r)
            return (0);
        (*s) += 2;
        return ft_add_token(head, r, HERE_DOC);
    }
    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_add_token(head, r, REDIRECT_INPUT);
}

int ft_tokenize_redir_out(char **s, t_token **head, t_minishell *m)
{
    t_token *token;
    char *r;

    if (*(*s + 1) == '>')
    {
        r = ft_strndup(*s, 2, GB_C);
        if (!r)
            return (0);
        (*s) += 2;
        return ft_add_token(head, r, APPEND);
    }
    r = ft_strndup(*s, 1, GB_C);
    if (!r)
        return (0);
    (*s)++;
    return ft_add_token(head, r, REDIRECT_OUTPUT);
}

int ft_tokenize_variable(char **s, t_token **head, t_minishell *m)
{
    char *start;
    char *r;

    start = *s;
    (*s)++;
    if (!**s)
        return ((*s)--, ft_tokenize_txt(s, head, m));
    if (**s == DOUBLE_QUOTE)
        return ft_tokenize_dquote(s, head, m);
    else if (**s == SINGLE_QUOTE)
        return ft_tokenize_squote(s, head, m);
    if (**s != '_' && !ft_isalpha(**s) && **s != '?')
        return ((*s)--, ft_tokenize_txt(s, head, m));
    while (**s && **s != '?' && (ft_isalnum(**s) || **s == '_'))
        (*s)++;
    if (**s == '?')
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (0);
    return ft_add_token(head, r, VAR);
}