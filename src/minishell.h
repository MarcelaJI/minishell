/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:51:55 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/26 09:05:25 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>

# define RED		"\x1b[31m"
# define GREEN		"\x1b[32m"
# define YELLOW		"\x1b[33m"
# define BLUE		"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN		"\x1b[36m"
# define WHITE		"\x1b[0;37m"
# define BOLD		"\x1b[1m"
# define RESET		"\x1b[0m"
# define SHELLNAME	"[shellmi]: "
# define SHELLPRMPT	"[shellmi]$ "

/* FLAGS FOR TOKEN TYPES */
enum e_type
{
	CMD = 0,
	PARAM = 1,
	PIPE = 2,
	FILENAME = 3,
	INF = 4,
	OUTF = 5,
	OUTF_APD = 6,
	HERE_DOC = 7,
	LIMITER = 8,
	UNKNOWN = 9,
	NA = -1
};

/* DOUBLY LINKED LIST STRUCTURE */
typedef struct s_dlist
{
	char			*str;
	enum e_type		token;
	int				index;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

typedef struct s_data
{
    t_dlist	*tokens;
	t_dlist	*env;
	char	*input;
	int		exit_status;
}   t_data;


/*  TOKENIZER  */
int validate_token_syntax(t_data *data);
void assign_token_type_ext(t_dlist *temp);
void assign_token_types(t_dlist **tokens);
void tokenize_input_string(char *input, t_data *data);
int is_valid_token_char(char c);
int is_redirection_token(t_dlist *node);
int has_command_before_pipe(t_dlist *node);

/* PARSER */
int	check_quotes(char *input);
void	expand_all_tokens(t_data *data);
int	check_empty_input(char *input);
int	parse_input(t_data *data);
int	check_valid_char(int c);
int	check_redir(char *c);
int	is_whitespace(char c);
int	checkfornum(char *s);
int	cmp_up_to_equal(const char *s1, const char *s2);
void	copy_full_word(char *input, char *str, size_t *a, size_t *b);
char	*fix_input(char *input, t_data *data);

/*  ENV  */
char	*get_env_var_str(char *str, t_data *data);
t_dlist	*get_env_var(char *var, t_dlist *env);
char	*find_path_in_env(char **env);
char	*search_path(char *cmd, char **env, t_data *data);
char	**convert_env_to_strings(t_data *data);
void	copy_env_var(char *env_str, size_t *j, char *exp);
void	expand_env_vars_loop(char *str, char *exp, char *env_str, t_data *data);
char	*expand_env_vars(char *str, t_data *data);
void	get_exp_len_extension(char *str, t_data *data, size_t *len);
size_t	get_exp_len(char *str, t_data *data);
int	check_invalid_chars_env_var(char c);
size_t	env_var_name_len(char *str);


/*  QUOTES  */
void	update_double_quote_flag(char *str, int *dquote, int *squote, size_t *i);
void	update_single_quote_flag(char *str, int *squote, int *dquote, size_t *i);
void	skip_quoted_single_block(char *str, int *dquote, int *squote, size_t *i);
char	*strip_quotes_from_string(char *str, t_data *data);
void	strip_all_token_quotes(t_data *data);

/*  UTILS  LISTS */
char	*ms_substr(char const *s, unsigned int start, size_t len, t_data *data);
char	*ms_strdup(const char *s, t_data *data);
char	*ms_strjoin(char *s1, char *s2, int f, t_data *data);
t_dlist	*newnode(char *str);
void	node_addfront(t_dlist **list, t_dlist *node);
void	node_addback(t_dlist **list, t_dlist *new);
t_dlist	*skip_instructions(t_dlist *node, int n);
void	refreshindex(t_dlist **list);
int	listsize(t_dlist *list);
t_dlist	*lastnode(t_dlist *list);

/*  ERROR  */
void	ms_perror(t_data *data);
int     error(char *str, char *token, t_data *data);

/*  FREE MEMORY */
void	free_all(t_data *data);
void	check_memory_failure(t_data *data, void *ptr, char **dptr, int f);
void	freelist(t_dlist *list);
void	free_str_array(char **arr, size_t n);


#endif