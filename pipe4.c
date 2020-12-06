#include<stdio.h> 
#include<unistd.h>  
#include<string.h> 
#include<stdlib.h> 

int main(void) 
{ 
	int fd1[2], nbytes=1,fd2[2],a=0; 
	pid_t pid; 
	char string[80]; 
	char readbuffer[80];
	char ch='a',ch1='\n';
	FILE *fp; 
	
	pipe(fd1);
	pipe(fd2); 


	if((pid = fork()) == -1) 
	{ 
		perror("fork"); 
		exit(1); 
	} 

	if(pid == 0) 
	{  
		close(fd1[1]);           
		read(fd1[0], readbuffer, sizeof(readbuffer));     
		printf("\nFilename '%s' is being read by Child Process through Pipe 1...\n",readbuffer);
		fp=fopen(readbuffer,"r");
		close(fd1[0]);         
		close(fd2[0]);      
		printf("\nContents of %s are being sent to Parent Process through Pipe 2...\n",readbuffer);
		while(a!=-1)
		{
			a=fscanf(fp,"%c",&ch);
			write(fd2[1], &ch, sizeof(ch));  
		} 
		close(fd2[1]); 
		exit(0); 
	} 
	else 
	{  
		close(fd1[0]); 
		printf("IN PARENT PROCESS\n" );
		printf("\nEnter name of file:");
		scanf("%s",string); 
		printf("Filename is being sent by Parent Process to Child Process through Pipe 1...\n"); 
		write(fd1[1], string, (strlen(string)+1));  
		wait();
		close(fd1[1]); 
		close(fd2[1]);  

		printf("\nContents of %s are being received by Parent Process through Pipe 2...\n\n",string);
		printf("IN PARENT PROCESS\n" );
		printf("\nReceived Message:\n");

		while(nbytes!=0) 
		{
			printf("%c",ch1);
			nbytes = read(fd2[0], &ch1, sizeof(ch1));   
		} 
		close(fd2[0]); 
	} 
	return(0); 
} 
