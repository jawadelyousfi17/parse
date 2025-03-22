// #include "../libft/libft.h"

#include "../utils/utils.h"

#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
# include <stdio.h>
#include <readline/readline.h>


# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

# define FALSE 0
# define TRUE 1





// minishell





// tokenizer/
t_token *ft_tokenize_input(char *s);
t_token* ft_tokenize_txt(char **s);
t_token* ft_tokenize_dquote(char **s);
t_token* ft_tokenize_squote(char **s);
t_token* ft_tokenize_pipe(char **s);
t_token* ft_tokenize_space(char **s);
t_token* ft_tokenize_redir_in(char **s);
t_token* ft_tokenize_redir_out(char **s);
t_token* ft_tokenize_variable(char **s);

// utils





// handle expan vars
int ft_handle_redirection_var(t_token *t, t_minishell *m);
int ft_handle_export_var(t_token *t, t_minishell *m);
int ft_expand_vars(t_token **head, t_token *t, t_minishell *m);
int ft_expand_expand(t_token **head, t_token *t);
int ft_expand_quoted(t_token *t, t_minishell *m);

// check ambs
int check_ambs(t_token *tokens);

// check syntax
char *check_syntax_error(t_token *t);
int check_unclosed_quotes(char *s);

// join tokens
int ft_join_tokens(t_token **tokens);



// init data
t_data *init_data(t_token *t);

// expand here doc
char *ft_expand_here_doc(char *s, t_minishell *m);
int ft_execute_heredoc(t_token *t, t_minishell *m);

// initialize the data
t_data *ft_initialize_data(char *line, t_minishell *m);