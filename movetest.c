#include <string.h>
#include <stdio.h>

int main()
{
	char str[] = "BOM DIA";

	printf("antes  -> %s\n", str);

	memmove(str + 3, str + 4, strlen(str + 4) + 1);
	printf("depois -> %s\n", str);
}