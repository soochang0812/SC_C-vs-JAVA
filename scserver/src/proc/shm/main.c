
/**************************************************************************
* Filename : main.c
* Author : Chang Soo Kim <soochang0812@gmail.com>
* description : 공유메모리 생성을 위한 SHM File
**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x1111


int main(int argc, char** argv) {

	int shmid;
	char *str;

	/* 공유 메모리 생성
     int shmget(key_t key, size_t size, int shmflg);
     key -> SHM Segment 구분
     size -> SHM Segment 크기
     shmflg -> SHM Segment 속성
     성공 id반환, 실패시 -1반환. */
	if((shmid = shmget(SHM_KEY, 1024, IPC_CREAT | 0666)) == -1) {
		perror("shmget failed : ");
		exit(0);
	}

	// 공유 메모리 사용하기
	if((str = (char*)shmat(shmid, (void *)0, 0)) == (char*)-1) {
		perror("shmat failed : ");
		exit(0);
	}

	printf("Input a string : ");
	scanf("%s", str);

	printf("Done!\n");

	// 공유 메모리 종료
	if(shmdt(str) == -1) {
		perror("shmdt failed : ");
		exit(0);
	}

	return 0;

}
