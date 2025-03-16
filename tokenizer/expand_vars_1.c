#include "../include/minishell.h"

t_token *ft_ttokenize_nrm_txt(char **s, t_token *t, t_minishell *m, t_token **head)
{
    t_token *token;
    char *start;
    char *r;

    start = *s;
    while (**s && !ft_strchr(" \t\"'", **s))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (NULL);
   return ft_add_token_after(head, t, ft_new_token(r, TEXT));
}

t_token *ft_tokenize_quote_as_txt(char **s, t_token *t, t_minishell *m, char quote_type, t_token **head)
{
    t_token *token;
    char *start;
    char *r;

    start = (*s);
    (*s)++;
    while (**s && **s != quote_type)
        (*s)++;
    (*s) += **s == quote_type;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (NULL);
    return ft_add_token_after(head, t, ft_new_token(r, TEXT));
}

t_token *ft_tokenize_espaces(char **s, t_token *t, t_minishell *m, t_token **head)
{
    t_token *token;
    char *start;
    char *r;

    start = *s;
    while (**s && ft_strchr(" \t", **s))
        (*s)++;
    r = ft_strndup(start, *s - start, GB_C);
    if (!r)
        return (NULL);
    return ft_add_token_after(head, t, ft_new_token(r, SPACES));
}

int ft_expand_expand(t_token **head, t_token *t, t_minishell *m)
{
    char *s;
    int c;

    while (t)
    {
        if (t->type == EXPAND)
        {
            c = 0;
            s = t->value;
            t = ft_remove_token_and_get_previous(head, t);
            printf("expand: %s\n", s);
            while (*s)
            {
                if (*s == ' ' || *s == '\t')
                    t = ft_tokenize_espaces(&s, t, m, head);
                else if (*s == DOUBLE_QUOTE || *s == SINGLE_QUOTE)
                    t = ft_tokenize_quote_as_txt(&s, t, m, *s, head);
                else
                    t = ft_ttokenize_nrm_txt(&s, t, m, head);
                if (!t)
                    return (0);
            }
        }
        if (t)
            t = t->next;   
    }
    return (1);
}


