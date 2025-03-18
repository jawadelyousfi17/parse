#include "../include/minishell.h"



t_files *ft_init_files(t_token *t, t_token_type type, int is_ambs)
{
    t_files *f;

    f = ft_malloc(sizeof(t_files), GB_C);
    if (!f)
        return (NULL);
    f->redirect_type = type;
    f->file = t->next->value;
    f->is_ambs = is_ambs;
    return (f);
}

void process_tokens(t_token **t, t_list **c, t_list **f)
{
    while (*t && (*t)->type != PIPE)
    {
        if ((*t)->type == TEXT)
            ft_lstadd_back(c, ft_lstnew((*t)->value));
        else if ((*t)->type == REDIRECT_INPUT || (*t)->type == REDIRECT_OUTPUT || 
                 (*t)->type == APPEND || (*t)->type == HERE_DOC)
        {
            ft_lstadd_back(f, ft_lstnew(ft_init_files(*t, (*t)->type, (*t)->is_ambs)));
            *t = (*t)->next;
        }
        *t = (*t)->next;
    }
}


t_data *init_no_pipe(t_token **tk, t_minishell *m)
{
    t_token *t;
    t_data *d;
    t_list *f;
    t_list *c;

    (1) && (c = NULL, f = NULL, t = *tk);
    d = ft_malloc(sizeof(t_data), GB_C);
    if (!d)
        return (NULL);
    d->pipe = 0;
    process_tokens(&t, &c, &f);
    d->_t_cmd = c;
    d->_t_files = f;
    d->files = ft_list_to_files(f);
    d->cmd = ft_list_to_array(c);
    d->n_of_cmds = c != NULL;
    *tk = t;
    return (d);
}


t_list *init_pipes(t_token **tk, t_minishell *m)
{
    t_token *t;
    t_list *p;
    t_data *d;

    p = NULL;
    t = *tk;
    while (t)
    {
        d = init_no_pipe(&t, m);
        if (!d)
            return (NULL);
        ft_lstadd_back(&p, ft_lstnew(d));
        if (t)
            t = t->next;
    }
    return (p);
}

t_data *init_data(t_token *t, t_minishell *m)
{
    t_data *d;
    int count_pipe;

    count_pipe = ft_count_token(t, PIPE);
    if (count_pipe == 0)
    {
        d = init_no_pipe(&t, m);
        if (!d)
            return (NULL);
        d->pipe = 0;
        return (d);
    }
    d = ft_malloc(sizeof(t_data), GB_C);
    if (!d)
        return (NULL);
    d->pipe = 1;
    d->pipe_cmd = init_pipes(&t, m);
    if (!d->pipe_cmd)
        return (NULL);
    d->n_of_cmds = ft_lstsize(d->pipe_cmd);
    return (d);
}