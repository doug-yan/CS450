#include <openssl/des.h>
#include <stdio.h>

#define ENC 1
#define DEC 0

int main(int argc[], char *argv[])
{
	int k;
	char rbuff[4000];
	char in1[1000];
	char in2[1000];
	char in3[1000];
	char in4[1000];

	//File i/o
	FILE *fp;
	char *filename = argv[3];
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

	int counter = bufferCounter / 4, i;
	for(i = 0; i < counter; i++)
		in1[i] = rbuff[i];
	for(i = 0; i < counter; i++)


	static unsigned char cbc_key[16] = argv[2];
	des_key_schedule key;

	if ((k = des_set_key_checked(&cbc_key,key)) != 0)
		printf("\nkey error\n");



	printf("DES Clear Text: %s\n",rbuff);
	
	des_encrypt1(in,key,ENC);

	printf("DES Encryption: %u%u\n",in[0],in[1]);

    	des_encrypt1(in,key,DEC);
}
