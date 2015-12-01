#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int i;
  printf(1,"parent:%d\n", getpid());
  for(i=1; i<4; i++){
  	int pid = fork();
  	if(pid == 0){
  		setprio(i*20);
  		printf(1, "child:%d\n", getpid());
  		int j;
  		for(j=1;j<10000000;j++);
  		break;
  	}
  	else{
  		//wait();
  	}
  }

  exit();
}
