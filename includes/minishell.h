/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingjimen <ingjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:51:55 by ingjimen          #+#    #+#             */
/*   Updated: 2025/06/24 11:01:36 by ingjimen         ###   ########.fr       */
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
# define SHELLPRMPT	"[shellmi] "

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
}   t_data;


/* TOKENIZER */
int validate_token_syntax(t_data *data);

#endif