/************************************************************************
    > File Name: fork_test.c
    > Author: 圆
    > Mail:18678902738@163.com 
    > Created Time: Mon 27 Apr 2020 11:11:14 AM UTC
************************************************************************/

#include<stdio.h>
#include<sys/types.h>

int main(void){
    int var;
    pid_t pid;
    printf("Before fork.\n");
    pid = fork();
    printf("After fork.\n");
    if (pid == 0){
        printf("son.");
    } else {
        sleep(2);
        printf("father.");
    }
    printf("pid:%d\n", getpid());
    return 0;
}
