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


float StringHandler(char *s){
	float result;
	float temp[50];
	float f;
	char flt[50];
	char operand[50];
	char opt;
	int idxa = 0;
	int idxc = 0;
	int idx = 0;
	int count;

	while(*s != '\0'){
		if(*s == '('){
			temp[idx] = ParenthesesHandler(s);
			count = 1;
			s++;

			while(count != 0){
				if(*s == ')'){
					count--;
				} else  if(*s == '('){
					count++;
				}
				s++;
			}
		} else {
			if(idxa != 0){
				idxa--;
				while(idxa >= 0){
					flt[idxa] = '\0';
					idxa--;
				}
				idxa = 0;
			}
			while ((*s != '\0') && (*s != '+') && (*s != '-') && (*s != '*') && (*s != '/')){
				flt[idxa] = *s;
				idxa++;
				s++;
			}
			temp[idx] = StringToFloat(flt);
		}
		if(*s != '\0'){
			opt = *s;
			while(opt == '*' || opt == '/'){
				s++;
				if(*s == '('){
					f = ParenthesesHandler(s);
					count = 1;
					s++;

					while(count != 0){
						if(*s == '('){
							count++;
						} else if(*s == ')'){
							count--;
						}
						s++;
					}
				} else {
					if(idxa != 0){
						idxa--;
						while(idxa >= 0){
							flt[idxa] = '\0';
							idxa--;
						}
						idxa = 0;
					}
					while ((*s != '\0') && (*s != '+') && (*s != '-') && (*s != '*') && (*s != '/')){
						flt[idxa] = *s;
						idxa++;
						s++;
					}
					f = StringToFloat(flt);
				}
				if(opt == '*'){
					temp[idx] *= f;
				} else if(opt == '/'){
					temp[idx] /= f;
				}
				opt = *s;
			}

			if(((opt == '+') || (opt == '-')) && (*s != '\0')){
				operand[idxc] = opt;
				OneElmt = false;
				idxc++;
				s++;
			}
			idx++;
		}
	}

	if(OneElmt){
		result = temp[0];
	} else {
		for(int i = 0; i < idx; i++){
			if(i == 0){
				if(operand[i] == '+'){
					result = result + temp[i] + temp[i+1];
				} else if(operand[i] == '-'){
					result = result + temp[i] - temp[i+1];
				}	
			} else {
				if(operand[i] == '+'){
					result += temp[i+1];
				} else if(operand[i] == '-'){
					result -= temp[i+1];
				}
			}
		}
	}
	return result;
}


float ParenthesesHandler(char *s){
	float tabfl[50];
	float result = 0;
	float temp;
	char flt[50];
	char operand[50];
	char opt;
	int count;
	int idx = 0;
	int idxc = 0;
	int idxa = 0;

	boolean OneElmt = true;
	boolean Minus = false;
	boolean FirstElmt = true;

	s++;
	if(*s == '-'){ 
		flt[idxc] = *s;
		idxc++;
		s++;
		Minus = true;
	}
	while(*s != ')'){
		if((!Minus) || (!FirstElmt)){
			if(idxc != 0){
				idxc--;
				while(idxc >= 0){
					flt[idxc] = '\0'
					idxc--;
				}
				idxc = 0;
			}
		}

		if(*s == '('){
			tabfl[idx] = ParenthesesHandler(s);
			if(Minus){
				tabfl[idx] *= -1;
			}
			count = 1; //merupakan jumlah ')' yang dibutuhkan 
			s++;
			while (hit != 0){
				if(*s == ')'){
					count--;
				} else if(*s == '('){
					count++;
				}
				s++;

			}			
		} else {
			while((*s != ')') && (*s != '*') && (*s != '/') && (*s != '+') && (*s != '-')){
				flt[idxc] = *s;
				idxc++;
				s++;
 			}
 			tabfl[idx] = StringToFloat(flt);
		}

		FirstElmt = false;

		if(*s != ')'){
			opt = *s;
			while(opt == '*' || opt == '/'){
				s++;
				if(*s == '('){
					temp = ParenthesesHandler(s);
					count = 1;
					s++;
					while(count != 0){
						if(*s == ')'){
							count--;
						} else if(*s == '('){
							count++;
						}
						s++;
					}
				} else {
					if (idxc != 0){
						idxc--;
						while(idxc >= 0){
							flt[idxc] = '\0';
							idxc--;
						}
						idxc = 0;
					}
					while((*s != ')') && (*s != '*') && (*s != '/') && (*s != '+') && (*s != '-')){
						flt[idxc] = *s;
						idxc++;
						s++;
					}
					temp = StringToFloat(flt);
				}

				if(opt == '*'){
					tabfl[idx] *= temp;
				} else if(opt == '/'){
					tabfl[idx] /= temp;
				}
				opt = *s;
			}

			if (((opt == '+') || (opt == '-')) && (*s != ')')){
				operand[idxa] = opt;
				OneElmt = false;
				idxa++;
				s++;
			}
			idx++;
		}
	}


	if(OneElmt){
		result = tabfl[0];
	} else {
		for(int i = 0; i <= idx; i++){
			if(i == 0){

				if(operand[i] == '+'){
					result = result + tabfl[i] + tabfl[i+1];
				} else if (operand[i] == '-'){
					result = result + tabfl[i] - tabfl[i+1];
				}

			} else {
				if(operand[i] == '+'){
					result = result + tabfl[i+1];
				} else if(operand[i] == '-'){
					result = result - tabfl[i+1];
				}
			}
		}
	}

	return result;
}

