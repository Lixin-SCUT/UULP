//whotofile.c
//Code by Lixin on 2020/01/14

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

main(){
	int pid;
	int fd;
	printf("About to run who into a file\n");

	if((pid=fork())==-1){
		perror("fork");
		exit(1);
	}
	if(pid==0){
		close(1);
		fd=creat("uselist",0644);
		execlp("who","who",NULL);
		perror("execlp");
		exit(1);
	}
	if(pid!=0){
		wait(NULL);
		printf("Done running who,results in userlist\n");
	}
}
