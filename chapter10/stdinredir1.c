//stdinredir1.c
//Code by Lixin on 2020/01/14

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

main(){
	int fd;
	char line[100];
	fgets(line,100,stdin);printf("%s",line);
	fgets(line,100,stdin);printf("%s",line);
	fgets(line,100,stdin);printf("%s",line);

	close(0);
	fd=open("/etc/passwd",O_RDONLY);
	if(fd!=0){
		fprintf(stderr,"Could not open data as fd 0\n");
		exit(1);
	}

	fgets(line,100,stdin);printf("%s",line);
	fgets(line,100,stdin);printf("%s",line);
	fgets(line,100,stdin);printf("%s",line);
}
