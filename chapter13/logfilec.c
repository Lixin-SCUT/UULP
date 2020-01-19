//logfilec.c
//Code by Lixin on 2020.01.18

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<time.h>
#include<string.h>
#include<unistd.h>

#define oops(m,x){perror(m);exit(x);}
#define SOCKET "/tmp/logfilesock"

int main(int ac,char *av[])
{
	int sock;
	struct sockaddr_un addr;
	socklen_t addrlen;
	char sockname[]=SOCKET;
	char *msg=av[1];

	if(ac!=2){
		fprintf(stderr,"usage:logfilec 'message'\n");
		exit(1);
	}

	sock=socket(PF_UNIX,SOCK_DGRAM,0);
	if(sock==-1)
		oops("socket",2);
	
	addr.sun_family=AF_UNIX;
	strcpy(addr.sun_path,sockname);
	addrlen=strlen(sockname)+sizeof(addr.sun_family);

	if(sendto(sock,msg,strlen(msg),0,(struct sockaddr*)&addr,addrlen)==-1)
		oops("sendto",3);
}
