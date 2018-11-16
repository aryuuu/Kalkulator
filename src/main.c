#include "lib/pda.h"
#include <stdio.h>

int main(){
	Stack S;
	char input[1000];

	// fgets(input, 1000, stdin);
	scanf("%s", input);

	if(PDA(input)){
		float result = StringHandler(input);
		if(result != result){
			printf("Math Error\n");
		} else {
			printf("%.2f\n", result);
		}
	} else {
		printf("Syntax Error\n");
	}
}