#include "../include/minishell.h"

char *ft_getenv(char *name, t_minishell *m)
{
    char *value;

    value = getenv(name);
    if (!value)
        return ft_strdup("", GB_C);
    return ft_strdup(value, GB_C);
}
int ft_is_operator(t_token *token)
{
    if (token->type == PIPE || token->type == REDIRECT_INPUT || token->type == REDIRECT_OUTPUT || token->type == APPEND || token->type == HERE_DOC)
        return 1;
    return 0;
}

int ft_is_op_space(t_token *token)
{
    if (token->type == PIPE || token->type == REDIRECT_INPUT || token->type == REDIRECT_OUTPUT || token->type == APPEND || token->type == HERE_DOC || token->type == SPACES)
        return 1;
    return 0;
}

void ft_remove_double_spaces(t_token **tokens)
{
    t_token *t;
    t_token *p;

    t = *tokens;
    if (t && t->type == SPACES)
    {
        *tokens = t->next;
        t = *tokens;
    }
    while (t)
    {
        if (t->type == SPACES)
        {
            p = t;
            t = t->next;
            while (t && t->type == SPACES)
            {
                p->next = t->next;
                t = p->next;
            }
        }
        if (t)
            t = t->next;
    }
}
