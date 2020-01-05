//setecho.c
//Coded by Lixin on 2020/1/4

#include<stdio.h>
#include<stdlib.h>
#include<termios.h>

main(int ac,char *av[])
{
	struct termios info;
	if(ac==1)
		exit(0);
	if((tcgetattr(0,&info))==-1)
		perror("tcgetattr");
	if(av[1][0]=='y')
		info.c_lflag!=ECHO;
	else
		info.c_lflag&=~ECHO;
	if((tcsetattr(0,TCSANOW,&info))==-1)
		perror("tcgetattr");
}
