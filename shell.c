#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	pid_t id;
	while(1)
	{
		printf("[jf@bogon ~]$");
		fflush(stdout);
		char cmd_str[1024] = {0};
		ssize_t size = read(0, cmd_str, sizeof(cmd_str) - 1);
		char cmd[32] = {0};
		char* my_argv[32];
		memset(my_argv, 0, sizeof(char*)*32);
		int length = strlen(cmd_str)-2;
		printf("%s", cmd_str);
		if(size != -1)
		{
			int index = 0;
			while(length >= 0)
			{
				while(length >= 0 && cmd_str[length] == ' ')
				{
					cmd_str[length--] = 0;
				}
				while(length >= 0 && cmd_str[length] != ' ')
				{
					length--;
				}
				my_argv[index++] = cmd_str + length+1;
			}
			my_argv[index] = NULL;
			int i = 0;
			index--;
			for(; i<index; ++i,--index)
			{
				char* tmp = my_argv[i];
				my_argv[i] = my_argv[index];
				my_argv[index] = tmp;
			}
			if(strcmp(argv[0], "cd") == 0)
			{
				chdir(my_argv[1]);
				continue;
			}
		}
		id = fork();
		if(id < 0)
		{
			perror("fork");
		}
		else if(id == 0)
		{
			execvp(my_argv[0], my_argv);
			exit(1);
		}
		else if(id > 0)
		{
			pid_t waitPid = waitpid(id, NULL, 0);
		}
	}
	return 0;
}
