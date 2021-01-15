#include "minicrt.h"


void string_test()
{
	long i;
	FILE* fp;

	fp	= fopen("test.txt","w");
	
	{
	  char* buf = "hello how are you \n";
	  long len = strlen(buf);
	  fwrite(buf ,1,len,fp);
	  write(0,"c",1);
	  printf("hello world\n");
	  printf("%d  %s\n",len,buf);
	}
	
	fclose(fp);

	char test[100] = {0};
	vsnprintf(test,"test%d%s%d\n",100,"-----",100);
	printf(test);

}
void malloc_test(){
	char* p = malloc(sizeof(char)*10);
	const char *s = "test-test";
	memcpy(p,s,strlen(s));
	printf(p);
}

int main(long argc,char *argv[])
{
    string_test();
    malloc_test();
	return 0;

}

