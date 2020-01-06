//sigdemo1.c
//Coded by Lixin on 2020/01/06

#include<stdio.h>
#include<signal.h>

main(){
	signal(SIGINT,SIG_IGN);
	printf("you can't stop me!\n");
	while(1)
	{
		sleep(1);
		printf("haha\n");
	}
}

