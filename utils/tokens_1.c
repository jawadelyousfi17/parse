#include "utils.h"

void ft_remove_token(t_token **tokens, t_token *node)
{
    if (!*tokens || !node)
        return;
    if (*tokens == node)
    {
        *tokens = node->next;
        return;
    }
    t_token *tmp = *tokens;
    while (tmp->next && tmp->next != node)
        tmp = tmp->next;
    if (tmp->next)
        tmp->next = node->next;
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