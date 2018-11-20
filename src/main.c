#include <stdio.h>
#include <string.h>
#include "lib/pda.c"
#include "lib/stack.c"

int main()
{
	// Stack S;
	char input[1000];

	// fgets(input, 1000, stdin);
	printf("Ketik EXIT untuk keluar program\n\n"); 
	do
	{
		scanf("%s",input);
		if (PDA(input))
		{
			float result = StringHandler(input);
			if(result != result)
			{
				printf("Math Error\n");
			} 
			else 
			{
				printf("-> ");
				printf("%.2f\n\n", StringHandler(input));
			}
		} 
		else if (strcmp(input,"EXIT") != 0)
		{
			printf("Syntax Error\n\n");
		}
	}
	while (strcmp(input,"EXIT") != 0);
}
