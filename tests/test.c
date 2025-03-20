#include "../include/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <time.h>

// Text Colors
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

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
        printf("value: " GREEN "{%s}" RESET "\ntype:" GREEN " %s" RESET, tokens->value, _trs(tokens->type));
        if (tokens->type == HERE_DOC)
            printf(BLUE "\nis_quoted: %d" RESET, tokens->is_quoted);
        if (tokens->type == REDIRECT_INPUT || tokens->type == REDIRECT_OUTPUT || tokens->type == APPEND)
            printf(BLUE "\nis_ambs: %d" RESET, tokens->is_ambs);
        printf("\n\n");
        tokens = tokens->next;
    }
    printf("\n\n");
}

void _print_data(t_data *d)
{
    if (!d->pipe)
    {
        if (d->_t_files)
        {
            t_list *f = d->_t_files;
            while (f)
            {
                t_files *file = f->content;
                printf("file: "BLUE"%s" RESET "\ntype: " BLUE "%s" RESET "\nis_ambs: " BLUE "%s" RESET "\n", file->file, _trs(file->redirect_type), file->is_ambs ? "true" : "false");
                f = f->next;
            }
        } else {
            printf("No files\n");
        }
        if (d->_t_cmd)
        {
            t_list *c = d->_t_cmd;
            printf("cmds: ");
            while (c)
            {
                printf(GREEN "{%s} " RESET,(char *) c->content);
                c = c->next;
            }
            printf("\n");
        } else {
            printf("No cmds\n");
        }
        return;
    }

    t_list *p = d->pipe_cmd;
    printf("pipes: \n");
    while (p)
    {
        t_data *d = p->content;
        _print_data(d);
        p = p->next;
        printf("\n");
    }
}

int main()
{

    {
        // t_token *tokens = ft_new_token("first", TEXT);
        // ft_add_token(&tokens, "second", TEXT);
        // ft_add_token(&tokens, "third", TEXT);
        // ft_add_token(&tokens, "fourth", TEXT);
        // ft_add_token(&tokens, "fifth", TEXT);
        // ft_add_token(&tokens, "sixth", TEXT);

        // t_token *t = tokens;
        // while (t)
        // {
        //     if (is_equal(t->value, "first"))
        //     {
        //         t = ft_remove_token_and_get_previous(&tokens, t);
        //         if (!t)
        //             t = tokens;
        //         printf("removed new val = %s\n", t->value);
        //     }
        //     else
        //         t = t->next;
        // }

        // t = tokens;
        // while (t)
        // {
        //     printf("%s\n", t->value);
        //     t = t->next;
        // }
    }

    char *err;
    while (TRUE)
    {
        clock_t start = clock(); // Start time

        char *line = readline("minishell$ ");
        if (!line)
            break;
        
        add_history(line);
        if (check_unclosed_quotes(line))
        {
            printf("unclosed quotes\n");
            continue;
        }
        t_token *tokens = ft_tokenize_input(line, NULL);
        if (!tokens)
            break;
        if ((err = check_syntax_error(tokens)) != NULL)
        {
            printf("syntax error '%s'\n", err);
            continue;
        }
        if (!ft_expand_vars(&tokens, tokens, NULL))
            break;
        if (!check_ambs(tokens))
            break;
        if (!ft_expand_quoted(tokens, NULL))
        {
            printf("error expanding quotes\n");
            break;
        }
        if (!ft_join_tokens(&tokens, NULL))
            break;
        if (ft_execute_heredoc(tokens, NULL) == 0)
        {
            printf("error executing here doc\n");
            break;
        }
        t_data *d = init_data(tokens, NULL);
        if (!d)
            break;
        _print_data(d);
        // _print_tokens(tokens);
        clock_t end = clock(); // End time

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", elapsed_time);
    free(line);
    ft_malloc(1, GB_CLEAR);
    }
}
