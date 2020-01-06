//sigdemo1.c
//Coded by Lixin on 2020/01/06

#include<stdio.h>
#include<signal.h>

main(){
	void f(int);
	int i;
	signal(SIGINT,f);
	for(i=0;i<5;i++){
		printf("hallo!\n");
		sleep(1);
	}
}

void f(int signum){
	printf("OUCH!\n");
}
