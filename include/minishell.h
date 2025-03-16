#include "../libft/libft.h"

# include <stdio.h>

// Garbage collector
#define GB_C 0
#define GB_NC 1
#define GB_CLEAR 2
void *ft_malloc(size_t size, int flag);

# define DOUBLE_QUOTE '\"'
# define SINGLE_QUOTE '\''

# define FALSE 0
# define TRUE 1

// token type
typedef enum e_token_type
{
    TEXT,
    S_QUOTE,
    D_QUOTE,
    VAR,
    EXPAND,
    TOKEN,
    PIPE,
    REDIRECT_INPUT,
    REDIRECT_OUTPUT,
    HERE_DOC,
    APPEND,
    SPACES,
} t_token_type;

// token struct
typedef struct s_token
{
    char            *value;
    t_token_type    type;
    int             is_quoted;
    int             is_ambs;
    struct s_token  *next;
} t_token;

// minishell
typedef struct s_minishell
{
    char **env;
} t_minishell;

// utils/tokens.c
t_token *ft_new_token(char *value, t_token_type type);
int ft_add_token(t_token **tokens, char *value, t_token_type type);
int ft_add_token_front(t_token **tokens, char *value, t_token_type type);
void ft_remove_token(t_token **tokens, t_token *node);
t_token *ft_remove_token_and_get_previous(t_token **tokens, t_token *node);
t_token *ft_add_token_after(t_token **head, t_token *node, t_token *new);
int ft_is_operator(t_token *token);
int ft_is_op_space(t_token *token);

// tokenizer/
t_token *ft_tokenize_input(char *s, t_minishell *m);
int ft_tokenize_txt(char **s, t_token **head, t_minishell *m);
int ft_tokenize_dquote(char **s, t_token **head, t_minishell *m);
int ft_tokenize_squote(char **s, t_token **head, t_minishell *m);
int ft_tokenize_pipe(char **s, t_token **head, t_minishell *m);
int ft_tokenize_space(char **s, t_token **head, t_minishell *m);
int ft_tokenize_redir_in(char **s, t_token **head, t_minishell *m);
int ft_tokenize_redir_out(char **s, t_token **head, t_minishell *m);
int ft_tokenize_variable(char **s, t_token **head, t_minishell *m);

// utils
char *ft_strndup(char *s, size_t len, int flag);
int is_equal(char *s, char *p);
void ft_remove_double_spaces(t_token **tokens);

// env
char *ft_getenv(char *name, t_minishell *m);

// handle expan vars
void ft_handle_here_doc_var(t_token *token, t_minishell *m);
int ft_handle_redirection_var(t_token *t, t_minishell *m);
int check_valid_export(char *s);
int ft_handle_export_var(t_token *t, t_minishell *m);
int ft_expand_vars(t_token **head, t_token *t, t_minishell *m);
int ft_expand_expand(t_token **head, t_token *t, t_minishell *m);


// check ambs
int check_ambs(t_token *tokens);
