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
# include <limits.h>
# include <string.h>

struct s_vars;
struct s_token;
typedef int	(*t_func)(struct s_vars *vars, char **args);

#define MAX_TOKENS 1024

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0,
}	t_bool;

typedef enum e_operator
{
	UNDEFINED = 0,
	AND = 1,
	OR = 2,
}	t_operator;

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

typedef enum s_rdrtype
{
	IN = 1,		 // <
	OUT = 2,	 // >
	HEREDOC = 3, // <<
	APPEND = 4,	 // >>
}	t_rdrtype;

typedef struct s_rdrinfo
{
    char		*rdr_str;
    t_rdrtype	rdr_type;
}	t_rdrinfo;

typedef struct s_pipe
{
    char		*cmd;
    char		**arg;
	int			rdr_count;
    t_rdrinfo	*rdr_info;
}	t_pipe;

typedef struct s_token
{
	struct s_token	*parent;
	struct s_token	*left;
	struct s_token	*right;
	char			*value; // raw value (e.g. "echo z")
	int				exit_status;
	int				pipe_num;
	t_pipe			*cmdlst;
	t_operator		operator;
}	t_token;

typedef struct s_vars
{
	char			**envp;
	char			**functions;
	char			**path;
	int				last_errno;
	t_token			*tokens;
	t_func			func[7];
}	t_vars;

void		print_startup(void);
void		init_signal(void);
char		**dup_envp(char **envp);

// built_in_functions
int			func_echo(t_vars *vars, char **argv);
int			func_cd(t_vars *vars, char **args);
int			func_pwd(t_vars *vars, char **args);
int			func_exit(t_vars *vars, char **args);
int			func_env(t_vars *vars, char **args);
int			func_export(t_vars *vars, char **args);
int			export_unset_error(int condition, char *var, char *name);
void		print_envp(t_vars *vars);
char		**equal_split(char *str);
t_bool		verify_variable(char *variable);

int			func_unset(t_vars *vars, char **args);
t_bool		verify_variable(char *variable);
int			export_unset_error(int condition, char *var, char *name);
t_bool		validate_unset(char *variable);
char		*get_envp_value(char **envp, char *key);
void		free_doublearray(char **data);

// tokenization
t_token		*tokenize_input(t_vars *vars, char *input);
int 		is_operator(char *token);
int 		is_left_paren(char *token);
int 		is_right_paren(char *token);
int 		count_paren(char *input);
void		print_token_tree(t_token *token, int level, char *direction); // temporary
t_operator	get_operator_type(char *value);
char		*expand_env_dollar(t_vars *vars, char *str);

// parsing
t_pipe		create_new_pipe(char *value);
int			get_pipe_num(t_pipe *pipe_list);
t_token 	*build_token_tree(char **tokens, int start, int end);
t_pipe		*generate_pipe_list(char *value, t_token *token);
int			count_pipes(char *value);
void		print_pipe_info(t_pipe pipe);
int			handle_rdr_out(int i, char *value, t_rdrinfo *rdr_info);
int			handle_rdr_in(int i, char *value, t_rdrinfo *rdr_info);
void		filter_exceptions(t_pipe *pipe);

// piping
int		cmdgroup(t_vars *vars, t_token group);
int		first_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		middle_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		last_child(t_vars *vars, t_pipe cmdlst, int pipefd[2][2], pid_t *pid);
int		error(char *cmd, char *str);
void	ft_dup_inoutfile(t_pipe cmdlst, int fd_inout[2], int std_fd[2]);
void	ft_dup(char *cmd, int fd_one, int fd_two);
void	ft_open(char *cmd, t_rdrinfo info, int fd_inout[2], int std_fd[2]);
void	ft_close_pipe(int index, int n_cmds, int pipefd[2][2]);

// heredoc utils in piping
int		do_heredoc(char *cmd, t_rdrinfo info, int std_fd[2]);
void	dup_heredoc(char *cmd, int curr_fd[2], int std_fd[2], int situation);

// execution
int		execution(t_vars *vars, t_pipe cmdlst);
int		wait_for_pid(t_vars *vars, t_token group, int *pid);

#endif
