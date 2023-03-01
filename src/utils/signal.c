#include "../../minishell.h"

void	sigint_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// g_errno = 1;
}

void	init_signal(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(1);
	}
	termios_current.c_lflag &= ~ECHOCTL; // Turning off ECHO for Ctrl key pressed
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(1);
	}
	signal(SIGINT, sigint_handler); // handles Ctrl-C
	signal(SIGQUIT, SIG_IGN); // ignores Ctrl-\' SIG_IGN = signal ignore
}
