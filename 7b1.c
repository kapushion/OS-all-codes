#include <stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdlib.h>
int main () {
    int fd1, fd2, i, j, k;
    char buf[512];
    
    int res = mkfifo("myfifo1",0777); //1
    
    if(res != 0)
        printf("\nError in creating FIFO\n");
    
    printf("Accept Sentences:");
    gets(buf);
    
    fd1 = open("myfifo1", O_WRONLY);
    write(fd1, buf, strlen(buf));
    close(fd1);
    
    res = mkfifo("myfifo1",0777);
    if(res != 0)
        printf("\nError in creating FIFO\n");
    
    fd2=open("myfifo1",O_RDONLY);
    read(fd2, buf, sizeof(buf));
    printf("\nData received from pipe2 is:");
    
    for(i=0;i<strlen(buf);i++)
        printf("%c",buf[i]);
    printf("\n"); 
    close(fd2);
    return 0;
}