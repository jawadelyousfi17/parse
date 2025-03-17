
#include <string.h>
#include <stdlib.h>

// Garbage collector
#define GB_C 0
#define GB_NC 1
#define GB_CLEAR 2
void *ft_malloc(size_t size, int flag);

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
    EXPORT,
} t_token_type;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// token struct
typedef struct s_token
{
    char            *value;
    t_token_type    type;
    int             is_quoted;
    int             is_ambs;
    struct s_token  *next;
    struct s_token  *prev;
} t_token;

typedef struct s_minishell
{
    char **env;
} t_minishell;


char	*ft_strtrim(char const *s1, char const *set, int flag);
char	*ft_substr(char const *s, unsigned int start, size_t len, int flag);
char	*ft_strdup(const char *s, int flag);
char	*ft_strjoin(const char *s1, const char *s2, int flag);
size_t 	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strndup(char *s, size_t len, int flag);
int is_equal(char *s, char *p);

// lists
t_list	*ft_lstnew(void *content);
int	ft_lstadd_back(t_list **lst, t_list *new);
char *ft_join_list(t_list *t);

// tokens
void ft_remove_double_spaces(t_token **tokens);




// utils/tokens.c
t_token *ft_new_token(char *value, t_token_type type);
int ft_add_token(t_token **tokens, char *value, t_token_type type);
t_token *ft_add_token_front(t_token **tokens, char *value, t_token_type type);
void ft_remove_token(t_token **tokens, t_token *node);
t_token *ft_remove_token_and_get_previous(t_token **tokens, t_token *node);
t_token *ft_add_token_after(t_token **head, t_token *node, t_token *new);

char *ft_getenv(char *name, t_minishell *m);
int ft_is_operator(t_token *token);
int ft_is_op_space(t_token *token);
void ft_remove_double_spaces(t_token **tokens);

int check_valid_export(char *s);
