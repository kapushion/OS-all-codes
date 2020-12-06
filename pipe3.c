#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int file_pipe1[2], file_pipe2[2], fork_result, data_pro, count;
	char buffer[20];
	const char data[] = "pipe.txt";
	count = 0;
	FILE *fp;
	
	pipe(file_pipe2);
	if (pipe(file_pipe1) == 0)
		fork_result = fork();
	
	if (fork_result == 0)
	{
		data_pro = write(file_pipe1[1], data, sizeof(data));
		printf("\nWrote %d bytes \n", data_pro);
		read(file_pipe2[0], buffer, 1024);
		printf("\nChild process contents are: %s ", buffer);
	}
	else
	{
		data_pro = read(file_pipe1[0], buffer, sizeof(buffer));
		printf("\nPARENT PROCESS: Read filename %s .....\n", buffer);
		fp = fopen(buffer, "r");
		while (!feof(fp))
		{
			buffer[count] = fgetc(fp);
			count++;
		}
		fclose(fp);
		write(file_pipe2[1], buffer, sizeof(buffer));
		printf("\nPARENT PROCESS: The contents are written .....\n");
	}
	return 0;
}
