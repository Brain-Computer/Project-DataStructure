#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	FILE* fStream;
	char 格废[1000000] = { 0 };
	fStream = fopen("c:\\word.txt", "r");

	if (fStream)
	{
		fread(格废, 1000000, 1, fStream);
		printf("格废 : \n%s\n", 格废);
	}
	fclose(fStream);
	return 0;
}