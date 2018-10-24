#include <stdio.h>    // puts(), printf(), perror(), getchar()
#include <stdlib.h>   // exit(), EXIT_SUCCESS, EXIT_FAILURE
#include <unistd.h>   // getpid(), getppid(),fork()
#include <sys/wait.h> // wait()
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#define READ  0
#define WRITE 1
/*
void child(int fd[]) {
	printf("i am CHILD ..\n");
	dup2(fd[READ],STDIN_FILENO);
	close(fd[READ]);
	execl("nl",NULL);
}
void parent(int fd[]) {
	printf("i am parent..\n");
	dup2(fd[WRITE],STDOUT_FILENO);
	close(fd[WRITE]);
	execl("/bin/ls","ls","-F","1",NULL);
}
*/
int main(void) {
  int fd[2];
  int pid;
  pipe(fd);
  pid=fork();
  if (pid>0)
  {
	  printf("i am parent..\n");
	  dup2(fd[WRITE],STDOUT_FILENO);
	  close(fd[WRITE]);
	  execl("/bin/ls","ls","-F","1",NULL);

  }
  else if(pid==0)
  {
	  printf("i am child..\n");
	  dup2(fd[READ],STDIN_FILENO);
	  close(fd[READ]);
	  execl("nl",NULL);
  }
  return 0;
}

