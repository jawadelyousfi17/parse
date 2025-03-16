#include "../include/minishell.h"

char *ft_join_after_redir(t_token *t)
{
    char *r;

    r = NULL;
    if (t && t->type == SPACES)
        t = t->next;
    while (t && !ft_is_op_space(t))
    {
        r = ft_strjoin(r, t->value, GB_C);
        if (!r)
            return NULL;
        if (t)
            t = t->next;
    }
    return ft_strtrim(r, " \t", GB_C);
}

int ft_is_ambs(char *s)
{
    char qt;

    if (ft_strlen(s) == 0)
        return 1;
    while (*s)
    {
        if (*s != ' ' && *s != '\t')
        {
            qt = *s;
            while (*s && *s != qt)
                s++;
            if (*s)
                s++;
        }
        else if (*s == ' ' || *s == '\t')
            return 1;
        else
            s++;
    }
    return 0;
}

int check_ambs(t_token *tokens)
{
    t_token *t;

    t = tokens;
    while (t)
    {
        if (t->type == REDIRECT_INPUT || t->type == REDIRECT_OUTPUT || t->type == APPEND)
        {
            char *r = ft_join_after_redir(t->next);
            if (!r)
                return 0;
            if (ft_is_ambs(r))
                t->is_ambs = 1;
        }
        if (t) 
            t = t->next;
    }
    return 1;
}