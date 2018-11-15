#include "pda.h"

float StringToFloat(char *s){
	float result = 0;
	float SignDec = 1;

	if(*s == '-'){//menangani bilangan negatif
		s++;
		SignDec = -1;
	}

	boolean point = false;

	for(; *s; s++){
		
		if(*s == '.'){//menandai mulainya koma
			point = true;
		}

		int	temp = *s - '0'; //menampung hasil konversi karaker ke bilangan

		if(temp >= 0 && d <= 9){
			if(point){
				SignDec = SignDec *10; //menghitung jumlah digit di belakang koma
									   //dimana jumlah digit di belakang koma = log(abs(SignDec)
			}
			result = result * 10 + (float) temp; 
		}

	}
	return result / SignDec;
}

void Transition(int *State, char Symbol, Stack *S,boolean *stuck){
	infotype temp;

	switch (*State){
		case 0:
			switch (Symbol) {
				case '(':
					if(InfoTop(*S) == 'Z' || InfoTop(*S) == 'X'){
						Push(S,'X');
						break;
					}

				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 2;
						break;
					}
				case '-':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 1;
						break;
					}
				default :
					stuck = true;

			}
			break;

		case 1:
			switch (Symbol){
				case '(':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						Push(S,'X');
						break;
					}
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 2;
						break;
					}
				default :
					*stuck = true;
			}
			break;

		case 2:
			switch (Symbol){
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 2;
						break;
					}
				case '*':
				case '/':
				case '+':
				case '-':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 3;
						break;
					}
				case ')':
					if(InfoTop(*S) == 'X'){
						Pop(S,&temp);
						*State = 2;
						break;
					}
				default :
					*stuck = true;
			}
			break;

		case 3:
			switch (Symbol){
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 2;
						break;
					}
				case '(':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						Push(S,'X');
						*State = 0;
						break;
					}
				default :
					*stuck = true;
			}
			break;


	}

}

boolean PDA(char *s){
	Stack S;
	infotype temp;
	boolean stuck = false;
	int state = 0;
	CreateEmpty(&S);

	Push(&S,'Z');

	while(*s){
		if(*s != '\n' && !stuck){
			Transition(&state, *s, &S, &stuck);
		}
		s++;
	}

	if(InfoTop(S) == 'Z' && state == 2 && !stuck){
		Pop(&S,&temp);
	}

	return IsEmpty(S);

}

float ParenthesesHandler(char *s){
	float tabfl[50];
	float result = 0;
	float temp;
	int hit;
}