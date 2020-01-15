//rlsd.c
//Code by Lixin on 2020/01/15

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>
#include<strings.h>

#define PORTNUM 15000
#define HOSTLEN 256
#define oops(msg) {perror(msg);exit(1);}

int main(int ac,char *av[]){
	struct sockaddr_in saddr;
	struct hostent *hp;
	char hostname[HOSTLEN];
	int sock_id,sock_fd;
	FILE *sock_fpi,*sock_fpo;
	FILE *pipe_fp;
	char dirname[BUFSIZ];
	char command[BUFSIZ];
	int dirlen,c;

	sock_id=socket(PF_INET,SOCK_STREAM,0);
	if(sock_id==-1)
		oops("socket");

	bzero((void*)&saddr,sizeof(saddr));
	gethostname(hostname,HOSTLEN);
	hp=gethostbyname(hostname);
	
	bcopy((void*)hp->h_addr,(void*)&saddr.sin_addr,hp->h_length);
	saddr.sin_port=htons(PORTNUM);
	saddr.sin_family=AF_INET;

	if(bind(sock_id,(struct sockaddr*)&saddr,sizeof(saddr))!=0)
		oops("bind");
	
	if(listen(sock_id,1)!=0)
		oops("listen");
	
	while(1){
		sock_fd=accept(sock_id,NULL,NULL);
		if(sock_fd==-1)
			oops("accept");
		
		if((sock_fpi=fdopen(sock_fd,"r"))==NULL)
			oops("fdopen");

		fgets(dirname,BUFSIZ-5,sock_fpi);
		sanitize(dirname);

		sock_fpo=fdopen(sock_fd,"w");
		sprintf(command,"ls %s",dirname);
		pipe_fp=popen(command,"r");

		while((c=getc(pipe_fp))!=EOF)
			putc(c,sock_fpo);
		pclose(pipe_fp);
		fclose(sock_fpi);
		fclose(sock_fpo);
	}
}

sanitize(char *str)
{
	char *src,*dest;

	for(src=dest=str;*src;src++)
		if(*src=='/'||isalnum(*src))
			*dest++=*src;
	*dest='\0';
}
