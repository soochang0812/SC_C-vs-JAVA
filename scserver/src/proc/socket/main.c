/**************************************************************************
* Filename : main.c
* Author : Chang Soo Kim <soochang0812@gmail.com>
* description : 데이터 전송을 위한 Socket Server File
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char* message);

int main(int argc, char** argv) {
	// serv_sock : 서버 소켓 변수, clnt_sock : 클라이언트 소켓 변수
	int serv_sock, clnt_sock;
	// serv_adr : 서버 주소값 변수, clnt_adr : 클라이언트 주소값 변수
	struct sockaddr_in serv_adr, clnt_adr;
	int clnt_adr_sz;
	char message[BUF_SIZE];

	if (argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*) &serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");

	if (listen(serv_sock, 5) == -1)
		error_handling("listen() error");

	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	if (clnt_sock == -1)
		error_handling("accept() error");

	// 클라이언트가 연결되면 메시지 출력
	while (1) {
		int str_len = read(clnt_sock, message, BUF_SIZE - 1);
		if (str_len == 0)
			break;

		message[str_len] = 0;
		printf("Message from client: %s \n", message);
	}
	
	printf("Test [%d]\n",clnt_sock);

	close(clnt_sock);
	close(serv_sock);
	return 0;
}

void error_handling(char* message) {
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
