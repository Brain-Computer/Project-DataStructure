#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main()
{
	FILE* fStream;
	char ¸목록[1000000] = { 0 };
	fStream = fopen("c:\\word.txt", "r"); // word.txt , user.txt, friend.txt 파일로 변경해서 모두 읽을 수 있음

	if (fStream)
	{
		fread(¸목록, 1000000, 1, fStream);
		printf("¸목록 : \n%s\n", ¸목록);
	}
	fclose(fStream);
	return 0;
}
