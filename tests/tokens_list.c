#include "../include/minishell.h"

int main()
{
    t_token *tokens = NULL;
    ft_add_token(&tokens, "hello", TEXT);
    ft_add_token(&tokens, "world", TEXT);
    ft_add_token(&tokens, "!", TEXT);
    ft_add_token(&tokens, "end", TEXT);

    ft_add_token_front(&tokens, "start", TEXT);

    return 0;
}