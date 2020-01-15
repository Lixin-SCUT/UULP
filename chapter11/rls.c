//rls.c
//Code by Lixin on 2020/01/15

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>

#define oops(msg) {perror(msg);exit(1);}
#define PORTNUM 15000

main(int ac,char *av[]){
	struct sockaddr_in servaddr;
	struct hostent *hp;
	int sock_id,sock_fd;
	char buffer[BUFSIZ];
	int n_read;

	if(ac!=3) exit(1);

	sock_id=socket(AF_INET,SOCK_STREAM,0);
	if(sock_id==-1)
		oops("socket");
	
	bzero(&servaddr,sizeof(servaddr));
	hp=gethostbyname(av[1]);
	bcopy(hp->h_addr,(struct sockaddr*)&servaddr.sin_addr,hp->h_length);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORTNUM);

	if(connect(sock_id,(struct sockaddr *)&servaddr,sizeof(servaddr))!=0)
		oops("connect");

	write(sock_id,av[2],strlen(av[2]));
	write(sock_id,"\n",1);
	
	while((n_read=read(sock_id,buffer,BUFSIZ))>0)
		write(1,buffer,n_read)==-1;

	close(sock_id);
			
}
