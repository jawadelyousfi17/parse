# include "../include/minishell.h"
# include <readline/readline.h>

char *_trs(t_token_type t)
{
    if (t == TEXT)
        return "TEXT";
    if (t == S_QUOTE)
        return "S_QUOTE";
    if (t == D_QUOTE)
        return "D_QUOTE";
    if (t == VAR)
        return "VAR";
    if (t == EXPAND)
        return "EXPAND";
    if (t == PIPE)
        return "PIPE";
    if (t == REDIRECT_INPUT)
        return "REDIRECT_INPUT";
    if (t == REDIRECT_OUTPUT)
        return "REDIRECT_OUTPUT";
    if (t == HERE_DOC)
        return "HERE_DOC";
    if (t == APPEND)
        return "APPEND";
    if (t == SPACES)
        return "SPACES";
    return "UNKNOWN";
}

void _print_tokens(t_token *tokens)
{   
    printf("\n");
    while (tokens)
    {
        printf("value: %s, type: %10s", tokens->value, _trs(tokens->type));
        if (tokens->type == HERE_DOC)
            printf("  is_quoted: %d", tokens->is_quoted);
        if (tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT || tokens->type == APPEND)
            printf("   is_ambs: %d", tokens->is_ambs);
        printf("\n");
        tokens = tokens->next;
    }
    printf("\n");
}

int main()
{
    while (TRUE)
    {
        char *line = readline("minishell$ ");
        if (!line)
            break;
        add_history(line);
        t_token *tokens = ft_tokenize_input(line, NULL);
        if (!tokens)
            break;
        if (!ft_expand_vars(&tokens, tokens, NULL))
            break;
        if (!check_ambs(tokens))
            break;
        _print_tokens(tokens);
    }
    
}


