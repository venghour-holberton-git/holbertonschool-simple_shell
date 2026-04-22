#include "simple_shell.h"

void child_parent_recur(int *status, pid_t *)
{

}
int main(void)
{
	int status;
	pid_t m_pid, w;
	char *new_argv[] = { NULL };
	char *new_env[] = { NULL };
	int child_count = 0;

	while (child_count < 5)
	{
		m_pid = fork();
		if (m_pid == -1)
			return (0);
		if (m_pid == 0)
		{
			printf("this is a child\n");
			if (execve("./ls_script", new_argv, new_env) == -1)
				printf("err load file\n");
		}
		if (m_pid > 0)
		{
			/* kill(m_pid, SIGKILL); */
			w = waitpid(m_pid, &status, WUNTRACED | WCONTINUED);

			if (w == -1)
				perror("waitpid");
		/* if (WIFSIGNALED(status))
		*	printf("killed by signaled");
		* if (WIFSTOPPED(status))
		*	printf("child stopped");
		*/
			printf("this is a parent\n");
		}
		child_count++;

	}
		return (0);
}
