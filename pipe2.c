#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int file_pipes[2], data_pro, pid;
	const char data[] = "Hello this is utkarsh";
	char buffer[20];
	
	pipe(file_pipes);
	pid = fork();
	
	if (pid == 0)
	{
		data_pro = write(file_pipes[1], data, strlen(data));
		printf("\nWrote %d bytes\n", data_pro);
	}
	else
	{
		data_pro = read(file_pipes[0], buffer, 20);
		printf("\n Read %d bytes: %s \n", data_pro, buffer);
	}
	return 0;
}
