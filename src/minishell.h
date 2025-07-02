/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:51:55 by ingjimen          #+#    #+#             */
/*   Updated: 2025/07/02 09:11:08 by ingjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../Libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <string.h>

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
# define SHELL_SUFFIX "/shellmi> "

/* GLOBAL VARIABLE FOR SIGNAL */
extern int	exit_nbr;

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
	t_dlist	*env;
	char	*input;
	t_dlist	*tokens;
	char	**instructions;
	int		*in_fds;
	int		*out_fds;
	pid_t	*pids;
	int		cmd_count;
	int		exit_status;
	int		pipe_fds[2];
	int		prev_pipe_fd;
	int		open_fail;
}	t_data;


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

/* INIT */
void	add_to_env(char *str, t_data *data);
void	update_oldpwd(t_dlist *env, t_data *data);
void	update_pwd(t_dlist *env, t_data *data);
void	update_shlvl(t_dlist *env, t_data *data);
void	create_env(t_data *data, char **env);
void	reset_input(t_data *data);
char	*get_dynamic_prompt(void);
void	take_input(t_data *data);

/*  QUOTES  */
void	update_double_quote_flag(char *str, int *dquote, int *squote, size_t *i);
void	update_single_quote_flag(char *str, int *squote, int *dquote, size_t *i);
void	skip_quoted_single_block(char *str, int *dquote, int *squote, size_t *i);
char	*strip_quotes_from_string(char *str, t_data *data);
void	strip_all_token_quotes(t_data *data);
void	reset_data(t_data *data);

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

/*  EXECUTION */
void    set_cmd_count(t_data *data);
char    **create_exec_array(t_data *data, int n);
void    convert_tokens(t_data *data);
void    exit_status(pid_t pid, t_data *data);
void    alloc_fd_pid_arrays(t_data *data);
void    execve_fail(char *cmd, char **execve_arr, char **env, t_data *data);
void    exec_single_cmd(t_data *data, int n);
void	exec_external_cmd(t_data *data, int n);
void    execution_child(t_data *data, int i);
void    execution_parent(t_data *data, int i);
void    execution(t_data *data);
int		is_directory(const char *path);

/* HEREDOC */
void    exit_heredoc(t_data *data, char *limiter, char *line);
void    heredoc_child(t_data *data, t_dlist *node);
int heredoc(t_data *data, t_dlist *node);
int heredoc_check(t_dlist *node, int n);
void    open_heredoc(t_data *data, t_dlist *node, int n);

/* REDIR & PIPES */
void    open_error(t_data *data, int in_fd, int out_fd, int n);
int open_outfile(t_data *data, t_dlist *node, int out_fd, int apd);
int open_infile(t_data *data, t_dlist *node, int in_fd);
void    open_files_extension(t_data *data, int in_fd, int out_fd, int n);
void    open_files(t_data *data, t_dlist *node, int n);
void    close_error(int fd, t_data *data);
int dup_close(int oldfd, int newfd, t_data *data);
void    dupdup(t_data *data, int n);


/* SIGNAL */
void    heredoc_signal(int sig);
void    do_nothing(int sig);
void    readline_sig(int sig);
void	ignore_sigquit(int sig);

/* BUILT IN */
int is_builtin(t_data *data, int n);
void    exec_builtin(t_data *data, int n);
void    exec_single_builtin(t_data *data);
void    builtin_exit(t_data *data, int exit_status);
void    ft_pwd(t_data *data);
void    ft_cd(t_data *data, int n);
void    ft_cd_utils(char **params, char *dir, t_data *data);
void    ft_echo(t_data *data, int n);
size_t  ft_echo_newline(char **params, int *newline);
void    ft_unset(t_data *data, int n);
void    ft_env(t_data *data);
void    ft_exit(t_data *data, int n);
int    ft_exit_invalid_params(t_data *data, char **params);
void    ft_exit_builtin_no_params(t_data *data, char **params);
void    ft_export(t_data *data, int n);
int ft_export_utils(char *str, t_data *data);
void    ft_export_list(t_data *data);
void    sort_export_list(char **export_arr);
void    print_export_list(char **export_arr, int fd);

#endif