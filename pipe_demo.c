#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int file_pipes[2], data_pro;
	const char data[] = "HELLO, WORLD!";
	char buffer[20];
	if (pipe(file_pipes) == 0)
	{
		data_pro = write(file_pipes[1], data, strlen(data));
		printf("\nWrote %d bytes \n", data_pro);
		data_pro = read(file_pipes[0], buffer, 20);
		printf("\nRead %d bytes : %s\n", data_pro, buffer);
	}
	return 0;
}
