#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
    int fd2,fd1,i,j,k,chars,words,s;
    char buf[512],str[512];
    fd1=open("myfifo1",O_RDONLY); //1
    read(fd1,buf,sizeof(buf)); //1
    
    //2
    printf("\nData received is:\n");
    for(i=0;i<strlen(buf);i++)
        printf("%c",buf[i]);

    close(fd1);
    s=0;
    
    //2 Count characters, words , lines
    for(i=0;i<strlen(buf);i++)
        if(buf[i]==' ')
            s++;

    words = s + 1;
    chars=strlen(buf)-s;
    fd2=open("myfifo1",O_WRONLY); //3
    
    //4
    sprintf(str, "\nNumber of lines:%d\nNumber of words:%d\nNumber of characters: %d .", s , words, chars);
    
    //5
    write(fd2,str,strlen(str));
    close(fd2);
}