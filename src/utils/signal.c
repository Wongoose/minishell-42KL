#include "../minishell.h"

// NEXT: Fix echo, need to hide ^C?
void	ms_init_signal(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(1);
	}
	termios_current.c_lflag &= ~ECHOE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(1);
	}
	// signal(SIGINT, ms_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}