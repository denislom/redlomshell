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
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
} t_redircmd;

typedef struct s_pipecmd {
	int type;
	struct cmd *left;
	struct cmd *right;
} t_pipecmd;

typedef struct s_listcmd {
	int type;
	struct cmd *left;
	struct cmd *right;
} t_listcmd;

typedef struct s_backcmd {
	int type;
	struct cmd *cmd;
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
struct cmd	*parse_cmd(char *s);
int			get_token(char **ps, char *es, char **q, char **eq);
int			peek(char **ps, char *es, char *toks);

// construct.c
struct cmd	*exec_cmd(void);
struct cmd	*redir_cmd(struct cmd *subcmd, char *file, char *efile, int mode, int fd);
struct cmd	*pipe_cmd(struct cmd *left, struct cmd *right);
struct cmd	*list_cmd(struct cmd *left, struct cmd *right);
struct cmd	*back_cmd(struct cmd *subcmd);

/*** EXECUTOR ***/

/*** OTHER FUNCTIONS ***/

#define MAX_INPUT_SIZE 1024

#endif