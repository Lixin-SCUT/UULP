#include<stdio.h>
#include<stdlib.h>
#include<utmp.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

//#define SHOWHOST

void show_info(struct utmp*);
void showtime(long);

int main(){
	struct utmp *utbufp,*utmp_next();
	if(open(UTMP_FILE,O_RDONLY)==-1){
		perror(UTMP_FILE);
		exit(1);
	}	
	while((utbufp=utmp_next())!=((struct utmp*)NULL))
		show_info(utbufp);
	utmp_close();
	return 0;
}

void show_info(struct utmp *utbufp){
	if(utbufp->ut_type!=USER_PROCESS)
		return;
	printf("%-8.8s",utbufp->ut_name);
	printf(" ");
	printf("%-8.8s",utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_time);
#ifdef SHOWHOST
	if(utbufp->ut_host[0]!="\0")
		printf("(%s)",utbufp->ut_host);
#endif
	printf("\n");		
}

void showtime(long timeval){
	char *cp;
	cp=ctime(&timeval);
	printf("%16.16s",cp);
}
