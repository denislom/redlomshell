/* ************************************************************************** */
/*																																						*/
/*																												:::			::::::::	 */
/*	 redlomshell.h																			:+:			:+:		:+:	 */
/*																										+:+ +:+				 +:+		 */
/*	 By: dlom <dlom@student.42prague.com>					 +#+	+:+			 +#+				*/
/*																								+#+#+#+#+#+	 +#+					 */
/*	 Created: 2024/01/29 00:18:00 by dlom							#+#		#+#						 */
/*	 Updated: 2024/02/27 00:06:28 by dlom						 ###	 ########.fr			 */
/*																																						*/
/* ************************************************************************** */

#ifndef	REDLOMSHELL_H
# define REDLOMSHELL_H

# include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
# include "./libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>


#define EXEC	1
#define REDIR	2
#define PIPE	3
#define LIST	4
#define BACK	5

#define MAXARGS 10

typedef struct s_cmd
{
	int type;
} t_cmd;

typedef struct s_execcmd {
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
} t_execcmd;

typedef struct s_redircmd {
	int type;
	t_cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
} t_redircmd;

typedef struct s_pipecmd {
	int type;
	t_cmd *left;
	t_cmd *right;
} t_pipecmd;

typedef struct s_listcmd {
	int type;
	t_cmd *left;
	t_cmd *right;
} t_listcmd;

typedef struct s_backcmd {
	int type;
	t_cmd *cmd;
} t_backcmd;

/* typedef enum e_return
{
	RETURN_ERR = -1,
	RETURN_SUCCESSFUL = 0,
	RETURN_FALSE = 1,
	RETURN_TRUE = 2,
	RETURN_EXIT = 3,
	RETURN_PIPE = 4
}			t_return;

typedef struct s_simple_command
{
	char **args; // Array of strings for arguments, including the command as args[0]
} t_simple_command;

typedef struct s_command
{
	t_simple_command **simple_commands; // Array of simple commands
	char *infile;
	char *outfile;
	int append; // Boolean indicating if output redirection should append
	int background; // Boolean indicating if the command should run in the background
} t_command; */

/*** PARSER ***/

//parsing.c
t_cmd		*parse_cmd(char *s);
t_cmd		*parse_line(char **ps, char *es);
t_cmd		*parse_pipe(char **ps, char *es);
int			get_token(char **ps, char *es, char **q, char **eq);
int			peek(char **ps, char *es, char *toks);
t_cmd		*nul_terminate(t_cmd *cmd);

// construct.c
t_cmd	*exec_cmd(void);
t_cmd	*redir_cmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd	*pipe_cmd(t_cmd *left, t_cmd *right);
t_cmd	*list_cmd(t_cmd *left, t_cmd *right);
t_cmd	*back_cmd(t_cmd *subcmd);

/*** EXECUTOR ***/
// run_cmd.c
void	run_cmd(t_cmd *cmd);

/*** OTHER FUNCTIONS ***/
// error_handling.c
void	print_error(const char *error);

#define MAX_INPUT_SIZE 1024

#endif