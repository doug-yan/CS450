#include <openssl/crypto.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <time.h>

int main(int argc, char *argv[])
{
	clock_t begin, end;
	double time_spent;
	begin = clock();

	RSA *key;
	unsigned char rbuff[4000];
	unsigned char wbuff[4000];
	unsigned char exbuff[4000];
	int num,i, bufferCounter = 0;
	static const char rnd_seed[] = "string to make the random number generator think it has entropy";

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

	printf("Clear Text: %s\n",rbuff);

	memset(wbuff,0,sizeof(wbuff));
	memset(exbuff,0,sizeof(exbuff));
	RAND_seed(rnd_seed, sizeof rnd_seed);
	if( (key = RSA_generate_key(2048,3,NULL,NULL)) == NULL)
		printf("\nerror generating key\n");

    	num = RSA_public_encrypt(sizeof(rbuff),rbuff,wbuff,key,RSA_PKCS1_PADDING);

	printf("RSA Encryption:");
	for(i=0;i<num;i++)
		printf("%x",wbuff[i]);	
	printf("\n");

    	num = RSA_private_decrypt(sizeof(wbuff),wbuff,exbuff,key,RSA_PKCS1_PADDING);

    	RSA_free(key);

   	end = clock();
	time_spent = (double)(end-begin) / CLOCKS_PER_SEC;
	printf("Time spent: %f", time_spent);
}
