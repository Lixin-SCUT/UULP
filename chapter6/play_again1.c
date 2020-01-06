//play_again1.c
//Coded by Lixin on 2020/01/05

#include<stdio.h>
#include<termios.h>
#include<stdlib.h>

#define QUESTION "Do you want another transaction?"

int get_response(char *);

int main(){
	int response;
	tty_mode(0);
	set_crmode();
	response=get_response(QUESTION);
	tty_mode(1);
	return response;
}

int get_response(char *question){
	int input;
	printf("%s (y/n)?",question);
	while(1){
		switch(input=getchar()){
			case'y':
			case'Y':return 0;break;
			case'n':
			case'N':return 1;break;
			case EOF:return 1;
			default:
				printf("\ncannot understand %c",input);
				printf("Please type y or n\n");
		}
	}
}

set_crmode()
{
	struct termios ttystate;
	tcgetattr(0,&ttystate);
	ttystate.c_lflag &=~ICANON;
	ttystate.c_cc[VMIN]=1;
	tcsetattr(0,TCSANOW,&ttystate);
}

tty_mode(int how){
	static struct termios original_mode;
	if(how==0)
		tcgetattr(0,&original_mode);
	else
		return tcsetattr(0,TCSANOW,&original_mode);
}
