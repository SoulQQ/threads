#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *messages);
int main(int argc, char *argv[])
{
        int option;
       int  serv_sock, clnt_sock;
       // char messages[BUF_SIZE];
        int  i=0;
	int optlen;	
	int read_cnt;
        struct sockaddr_in serv_adr, clnt_adr;
        socklen_t clnt_adr_sz;
	char read_buf[100];	
	char file_name[300];
	FILE * fp;
       // if(argc != 2)
      //  {
    //            printf("Usage : %s <port>\n", argv[0]);
  //              exit(1);
//        }

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sock == -1)
                error_handling("socket() error");
	optlen=sizeof(option);
	option=1;
	setsockopt(serv_sock,SOL_SOCKET, SO_REUSEADDR,(void *)&option,optlen);

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serv_adr.sin_port = htons(5188);

	

        if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
                error_handling("bind() error");
        if(listen(serv_sock, 10) == -1)
                error_handling("listen() error");

        clnt_adr_sz = sizeof(clnt_adr);
	
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
           if(clnt_sock == -1)
                        error_handling("accept() error");
           else
                        printf("Connected client %d \n", i + 1);
	read(clnt_sock,file_name,BUF_SIZE);
	fp=fopen(file_name,"r");
	printf("receive file name");
	if (fp != NULL){
		while(1){
			read_cnt=fread((void *)read_buf,1,BUF_SIZE,fp);
			if (read_cnt < BUF_SIZE){
				write(clnt_sock,read_buf,read_cnt);
				break;
			}				
			write(clnt_sock,read_buf,BUF_SIZE);
			}
		}
		fclose(fp);
		close(clnt_sock);        
		close(serv_sock);
	

        return 0;
}

void error_handling(char *messages)
{
        fputs(messages, stderr);
        fputc('\n', stderr);
        exit(1);
}

