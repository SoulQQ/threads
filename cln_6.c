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
        int serv_sock, clnt_sock;
       // char messages[BUF_SIZE];
      //  int str_len, i=0;
	FILE *fp;
        struct sockaddr_in serv_adr, clnt_adr;
       // socklen_t clnt_adr_sz;
	char read_buf[100];	
	int  read_cnt;
	char file_name[30];
       // if(argc != 2)
      //  {
    //            printf("Usage : %s <port>\n", argv[0]);
  //              exit(1);
//        }

	printf("Input your file name:\n");
	scanf("%s",file_name);
	fp=fopen(file_name,"wb");

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sock == -1)
                error_handling("socket() error");

        memset(&serv_adr, 0, sizeof(serv_adr));
        serv_adr.sin_family = AF_INET;
        serv_adr.sin_addr.s_addr = inet_addr("127.0.0.1");
        serv_adr.sin_port = htons(5188);

	if(connect(serv_sock,(const struct sockaddr *)(&serv_adr),sizeof(serv_adr))==-1){
	error_handling("connect() error!");
	}

       // clnt_adr_sz = sizeof(clnt_adr);
	write(serv_sock,file_name,strlen(file_name)+1);
	printf("write name successful");
	while(read_cnt=read(serv_sock,read_buf,BUF_SIZE) !=0)
		fwrite((void*)read_buf,1,read_cnt,fp);

	fclose(fp);



		close(clnt_sock);        
	//	close(serv_sock);
	

        return 0;
}

void error_handling(char *messages)
{
        fputs(messages, stderr);
        fputc('\n', stderr);
        exit(1);
}

