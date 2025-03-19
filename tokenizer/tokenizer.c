#include "../include/minishell.h"


t_token *ft_tokenize_input(char *s, t_minishell *m)
{
    t_token *tokens;
    t_token *current;
    t_token *new;
    tokens = NULL;
    s = ft_strtrim(s, " \t", GB_C);
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == ' ' || *s == '\t')
            new = ft_tokenize_space(&s, &tokens, m);
        else if (*s == DOUBLE_QUOTE)
            new = ft_tokenize_dquote(&s, &tokens, m);
        else if (*s == SINGLE_QUOTE)
            new = ft_tokenize_squote(&s, &tokens, m);
        else if (*s == '|')
            new = ft_tokenize_pipe(&s, &tokens, m);
        else if (*s == '<')
            new = ft_tokenize_redir_in(&s, &tokens, m);
        else if (*s == '>')
            new = ft_tokenize_redir_out(&s, &tokens, m);
        else if (*s == '$')
            new = ft_tokenize_variable(&s, &tokens, m);
        else
            new = ft_tokenize_txt(&s, &tokens, m);
        if (!new)
            return (NULL);
        current = ft_add_token_current(&tokens, current, new);
    }
    return (tokens);
}


