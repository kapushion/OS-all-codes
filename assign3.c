#include<pthread.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int matrix1[10][10],matrix2[10][10],row1,col1,col2,row2;

void *multiply(void *arg);
void input(int matrix[10][10],int row,int col) {
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            scanf("%d", &matrix[i][j]);
}

void print(int matrix[10][10],int row,int col) {
    for(int i=0;i<row;i++) {
        for(int j=0;j<col;j++)
            printf("%d ",matrix[i][j]);
        printf("\n");
    }
}

int main()
{
    int res;
    void *tres;

    printf("Enter number of rows in matrix 1: ");
    scanf("%d",&row1);

    printf("Enter number of columns in matrix 1: ");
    scanf("%d",&col1);
    printf("Enter number of rows in matrix 2: ");
    scanf("%d",&row2);
    printf("Enter number of columns in matrix : ");
    scanf("%d",&col2);
    
    if(col1==row2) {
        pthread_t thread[row1];
        printf("\nENTER ELEMENTS FOR MATRIX 1:\n");
        input(matrix1,row1,col1);
        printf("\nENTER ELEMENTS FOR MATRIX 2:\n");
        input(matrix2,row2,col2);
        printf("MATRIX 1\n");
        print(matrix1,row1,col1);
        printf("MATRIX 2\n");
        print(matrix2,row2,col2);
        printf("RESULTANT MULTIPLICATION MATRIX\n");

        for(int i=0;i<row1;i++)
            res = pthread_create(&thread[i],NULL,multiply,(void *)i);
        for(int j=0;j<row1;j++) {
            res = pthread_join(thread[j],&tres);
            int *p=(int *)tres;
            printf("\n");
            for(int i=0;i<col2;i++)
            printf("%d ",*(p+i));
        }
    }
    else
        printf("MULTIPLICATION NOT POSSIBLE");
}

void * multiply(void *arg) {
    int result;
    int p=(int )arg;
    printf("INSIDE MULT THREAD %d\n",p+1);
    printf("Thread ID is:- %ld\n", pthread_self());
    int *q =(int *)malloc(sizeof(int)*col2);
    
    for(int i=0;i<col2;i++) {
        result=0;
        for(int j=0;j<col1;j++)
        result = result + matrix1[p][j]*matrix2[j][i];
        q[i]=result;
    }
    pthread_exit(q);
}