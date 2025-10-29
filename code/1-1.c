#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main() {
  pid_t pid, pid1;//存储进程ID
  int flag; //全局变量  
  pid = fork(); //通过fork()创建子进程
  if (pid < 0) {// fork失败时输出错误信息，并返回值1
    fprintf(stderr, "fork failed");
    return 1;
  } else if (pid==0) {  // pid=0表示当前在子进程，将id赋值给pid1
    pid1 = getpid();
    flag = 10;

    // 使用system函数调用system_call
    printf("Using system to call system_call:\n");
    system("./system_call");

    // 使用exec函数族调用system_call
    printf("Using exec to call system_call:\n");
    execlp("./system_call", "./system_call", NULL);

    // 如果execlp成功，进程已经被替换，以下代码不会执行
    printf("child: pid = %d\n", pid);// 打印子进程中fork()的返回值（0）
    printf("child: pid1 = %d\n", pid1);// 打印子进程的ID
    printf("child: flag = %d\n", flag);// 打印子进程中flag的值（10）
  } else {  // 父进程
    pid1 = getpid();
    flag = 20;
    printf("parent: pid = %d\n", pid);// 打印父进程中fork()的返回值（子进程ID）
    printf("parent: pid1 = %d\n", pid1);// 打印父进程的ID
    printf("parent: flag = %d\n", flag);// 打印父进程中flag的值（20）
    wait(NULL); // 父进程等待子进程结束
  }
  printf("pid = %d program before end: flag = %d\n", pid, flag);
  return 0;
}