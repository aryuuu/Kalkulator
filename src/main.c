#include "pda.h"
#include <stdio.h>
#include <string.h>
#include "stack.h"

int main(){
	Stack S;
	char input[1000];
	boolean matherr;
	float result;

	printf("Ketik EXIT untuk keluar program\n\n"); 
	do
	{
		scanf("%s",input);
		if (PDA(input))
		{
			proc_string(input, &matherr, &result);
			if(matherr)
			{
				printf("Math Error\n\n");
			} 
			else 
			{
				printf("-> ");
				printf("%.2f\n\n", result);
			}
		} 
		else if (strcmp(input,"EXIT") != 0)
		{
			printf("Syntax Error\n\n");
		}
	}
	while (strcmp(input,"EXIT") != 0);

}


