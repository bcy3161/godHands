#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE	1024

void error_handling(char *message);

int main(int argc, char *argv[]){
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len, i;

	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_adr_sz;

	if(argc!=2){
		printf("Usage:%s <port>\n", argv[0]);
		exit(1);
	}
	
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		error_handling("socket() error");
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)
		error_handling("bind() error");

	if(listen(serv_sock, 5)==-1)
		error_handling("listen() error");
	
	clnt_adr_sz=sizeof(clnt_addr);

	while(1){
		clnt_sock=accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_adr_sz);
		if(clnt_sock==-1)
			error_handling("accept() error");
		else
			printf("Connected client IP : %s, num : %d\n", inet_ntoa(clnt_addr.sin_addr),i+1);
		switch(fork()){
			case 0:
				close(serv_sock);
				int flag2=1;
				while((str_len=read(clnt_sock, message,1))!=0){
					printf("flag : %d, %s\n",flag2,message);
					if((flag2==0)&&(message[0]=='1')){
						printf("door open! %d\n",flag2);
						flag2=1;
						system("./pushServer");
					}
					else if((flag2==1)&&(message[0]=='0')){
						printf("door close%d\n",flag2);
						flag2=0;
					}
				}
				close(clnt_sock);
		}
	}
//	close(serv_sock);
	return 0;

}

void error_handling(char *message){
	fputs(message, stderr);
	fputc("\n",stderr);
	exit(1);
}
