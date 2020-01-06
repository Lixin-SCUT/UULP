//play_again0.c
//Coded by Lixin on 2020/01/05

#include<stdio.h>
#include<termios.h>
#include<stdlib.h>

#define QUESTION "Do you want another transaction?"

int get_response(char *);

int main(){
	int response;
	response=get_response(QUESTION);
	return response;
}

int get_response(char *question){
	printf("%s (y/n)?",question);
	while(1){
		switch(getchar()){
			case'y':
			case'Y':return 0;break;
			case'n':
			case'N':return 1;break;
			case EOF:return 1;
		}
	}
}

