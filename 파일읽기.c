#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	FILE* fStream;
	char ���[1000000] = { 0 };
	fStream = fopen("c:\\word.txt", "r");

	if (fStream)
	{
		fread(���, 1000000, 1, fStream);
		printf("��� : \n%s\n", ���);
	}
	fclose(fStream);
	return 0;
}