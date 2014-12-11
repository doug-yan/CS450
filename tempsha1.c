#include <openssl/sha.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i;
	int bufferCounter = 0;
	unsigned char rbuff[4000];
	unsigned char wbuff[20];
	clock_t begin, end;
	double time_spent;
	begin = clock();

	//File i/o
	FILE *fp;
	char *filename = argv[1];
	fp = fopen(filename, "r");

	if(fp == NULL)
	{
		printf("Error opening file. \n");
		return 0;
	}

	char ch;
	while( (ch = fgetc(fp) ) != EOF)
	{
		rbuff[bufferCounter] = ch;
		bufferCounter++;
	}
	fclose(fp);

	SHA_CTX	c;

	memset(wbuff,0,sizeof(wbuff));

	SHA1_Init(&c);
	SHA1_Update(&c,rbuff,sizeof(rbuff));
	SHA1_Final(wbuff,&c);

	printf("Clear text: %s\n",rbuff);
	printf("SHA-1 digest:");
	for (i=0;i<sizeof(wbuff);i++)
		printf("%x",wbuff[i]);
	printf("\n");
	end = clock();
	time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("Time spent: %f", time_spent);
}
