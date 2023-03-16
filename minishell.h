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

typedef struct s_vars
{
	char	**envp;
	char	**functions;
	char	**path;
	t_func	func[7];
}	t_vars;

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

#endif