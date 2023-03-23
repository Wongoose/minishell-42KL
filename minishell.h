#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "ft_printf/includes/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <termios.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <term.h>

struct s_vars;
typedef int	(*t_func)(struct s_vars *vars, char **args);

typedef enum s_redirect
{
	IN = 1,		 // <
	OUT = 2,	 // >
	HEREDOC = 3, // <<
	APPEND = 4,	 // >>
}	t_redirect;

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0,
}	t_bool;

typedef enum e_function
{
	E_ECHO = 0,
	E_CD = 1,
	E_PWD = 2,
	E_EXPORT = 3,
	E_UNSET = 4,
	E_ENV = 5,
	E_EXIT = 6,
}	t_function;

typedef struct s_pipe
{
	char		*infile;
	char		*outfile;
	char		*delim;
	char		*cmd;
	char		**arg;
	t_redirect	*rdr_list;
}				t_pipe;

typedef struct s_vars
{
	char	**envp;
	char	**functions;
	char	**path;
	t_pipe	*cmdlst;
	t_func	func[7];
}			t_vars;

void	print_startup(void);
void	init_signal(void);
char	**dup_envp(char **envp);

// built_in_functions
int		func_echo(t_vars *vars, char **argv);
int		func_cd(t_vars *vars, char **args);
int		func_pwd(t_vars *vars, char **args);
int		func_exit(t_vars *vars, char **args);
int		func_env(t_vars *vars, char **args);
int		func_export(t_vars *vars, char **args);
int		export_unset_error(int condition, char *var, char *name);
void	print_envp(t_vars *vars);
char	**equal_split(char *str);
t_bool	verify_variable(char *variable);

int		func_unset(t_vars *vars, char **args);
t_bool	verify_variable(char *variable);
int		export_unset_error(int condition, char *var, char *name);
t_bool	validate_unset(char *variable);
char	*get_envp_value(char **envp, char *key);
void	free_doublearray(char **data);

// piping
void	test_piping(t_vars *vars);
void	ft_dup_inoutfile(t_pipe cmdlst, int *fd_in, int *fd_out);
void	ft_dup(char *cmd, int fd_one, int fd_two);
void	ft_close_pipe(int index, int n_cmds, int pipefd[2][2]);
int		first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		middle_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		last_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		error(char *cmd, char *str);

// execution
int		execution(t_vars *vars, t_pipe cmdlst);

#endif