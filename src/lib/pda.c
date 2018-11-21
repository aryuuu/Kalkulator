#include "pda.h"
#include "boolean.h"
#include <math.h>
#include <stdio.h>

float StringTofloat(char *s){ //mengubah array of char menjadi float
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

		if(temp >= 0 && temp <= 9){
			if(point){
				SignDec = SignDec *10; //menghitung jumlah digit di belakang koma
									   //dimana jumlah digit di belakang koma = log(abs(SignDec)
			}
			result = result * 10 + (float) temp; 
		}

	}
	return result / SignDec;
}

void trans_state(int *State, char Symbol, Stack *S,boolean *stuck){ //menangani state transition untuk PDA
	infotype temp;

	switch (*State){
		case 0: //State 0, menangani angka, buka kurung, dan tanda negatif
			switch (Symbol) {
				case '(':
					if(InfoTop(*S) == 'Z' || InfoTop(*S) == 'X'){
						Push(S,'X');
						break;
					}
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
				case '-':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 1;
						break;
					}
				default : //selain kondisi diatas maka stuck
					*stuck = true;

			}
			break;

		case 1: //State 1, menangani ekspresi setelah tanda '-', bisa berupa angka atau '('
			switch (Symbol){
				case '(':
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						Push(S,'X');
						*State = 0;
						break;
					}
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
				default :
					*stuck = true;
			}
			break;

		case 2: //menangani state 2, penambahan digit angka atau adanya operator atau ada ')'
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
				case '.':	
					if(InfoTop(*S) == 'X' || InfoTop(*S) == 'Z'){
						*State = 2;
						break;
					}
				case '^':
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

		case 3: //menangani ekspresi setelah ada ')' atau operator lain
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


boolean PDA(char *s){//menangani transisi antar state dan manajemen stack
	Stack S;
	infotype temp;
	boolean stuck = false;
	int state = 0;
	CreateEmpty(&S);

	Push(&S,'Z');

	while(*s){
		if(*s != '\n' && !stuck){
			trans_state(&state, *s, &S, &stuck);
		}
		s++;
	}

	if(InfoTop(S) == 'Z' && state == 2 && !stuck){
		Pop(&S,&temp);
	}

	return IsEmpty(S);
}

void proc_in_parentheses(char **s, boolean *error, float temp[], int idx){
	float tempres;
	int count;
	
	proc_parentheses(*s, error, &tempres);
	if(*error){
	}
	else {
		temp[idx] = tempres; 
		//printf("parenth res in %f\n", temp[idx]);
		count = 1;
	} //mengembalikan angka/ekspresi yang ada di parentheses

}


void proc_string(char *s, boolean *error, float *res){
	float result;
	float temp[50];
	float f;
	float tempres;
	char flt[50];
	char *temps;
	char operand[50];
	char opt;
	int idxa = 0;
	int idxc = 0;
	int idxpow = 0;
	int idx = 0;
	int count;
	boolean OneElmt = true;
	boolean preopt;
	boolean Minus = false;
	boolean firstopt = true;
	boolean multiplied = false;
	*error = false;

	while((*s != '\0') && !*error){
		if(*s == '('){
			 
			temps = s;
 			proc_in_parentheses(&temps, error, temp, idx);
			if(*error) break;
			else{
				s = temps;
				count = 1;
			s++;
			while(count != 0){
				//melanjutkan pembacaan sampai akhir kurung
				if(*s == ')'){
					count--;
				} else  if(*s == '('){
					count++;
				}
				s++;
			} 
			}
		} 
		else {
			//menangani bila yang muncul langsung angka
			if(*s == '-'){ 
				flt[idxc] = *s;
				idxc++;
				s++;
				Minus = true;
			}
			if(idxa != 0){
				//mengosongkan array flt yang akan diisi angka
				idxa--;
				while(idxa >= 0){
					flt[idxa] = '\0';
					idxa--;
				}
				idxa = 0;
			}
			while ((*s != '\0') && (*s != '+') && (*s != '-') && (*s != '*') && (*s != '/') && (*s != '^')){
				//memasukkan digit-digit angka ke array flt
				flt[idxa] = *s;
				idxa++;
				s++;
			}
			temp[idx] = StringTofloat(flt);//mengubah isi array flt menjadi float
			if(Minus) temp[idx] *= -1;
			//printf("temp[%d] %f\n", idx, temp[idx]);
		}

		if(*s != '\0'){
			//menangani munculnya operator
			if (firstopt){
				preopt = *s;
				firstopt = false;
			}  //mengeset firstopt (operator pertama)
			else preopt = opt; 
			
			opt = *s;
			while(opt == '*' || opt == '/' || opt == '^'){
				multiplied = true;
				if (idxc == 0) OneElmt = true;

				s++;
				if(*s == '('){
					//menangani tanda kurung
					proc_parentheses(s, error, &tempres);
					if(*error){
						break;
					}
					else {
						f= tempres; //printf("parenth res %f\n", temp[idx]);}
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
					}
				} 
				else {
					//menangani angka
					if(idxa != 0){
						//loop buat mengosongkan array flt yang dipake buat menyimpan angka
						idxa--;
						while(idxa >= 0){
							flt[idxa] = '\0';
							idxa--;
						}
						idxa = 0;
					}
					while ((*s != '\0') && (*s != '+') && (*s != '-') && (*s != '*') && (*s != '/') && (*s != '^')){
							//loop buat menangkap semua angka dan mengkonversi jadi float
							flt[idxa] = *s;
							idxa++;
							s++;
					}
					f = StringTofloat(flt);
				}

				if(opt == '^'){//menangani perpangkatana
					if((temp[idx] < 0) && ((f < 1) && (f > 0))){ //bilangan negatif dipangkat dengan bilangan kurang dari 1
						*error = true;
						break;
					}
					else{
						idx++;
						temp[idx] = f;
						idxpow++;
					}
				}
				else if(opt == '*'){//menangani perkalian
					temp[idx] *= f;
				} 
				else if(opt == '/'){//menangani pembagian
					if(f == 0){//bila bilangan yang baru dibaca berupa 0, maka error karena division by zero
						*error = true;
						break;
					} 
					else temp[idx] /= f;
				}
				
				preopt = opt;
				opt = *s;

				//printf("preopt %c\n", preopt);
				//printf("opt %c\n", opt);
				//printf("temp[%d] %f\n", idx, temp[idx]);

				if((preopt == '^') && (opt != '^') && (idxpow != 0)){
					//menangani perpangkatan yang lebih dari satu berturut turut, dan setelahnya ada perkalian
					//atau pembagian
					//printf("inloop 1\n");
					//printf("idxpow %d\n", idxpow);
					for (int k = 0; k < idxpow; k++){
						idx--;
						temp[idx] = pow(temp[idx], temp[idx+1]);
						//printf("temp[%d] %f\n", idx, temp[idx]);
					}
					idxpow = 0;
				}
			}

			if((preopt == '^') && (opt != '^') && (idxpow != 0)){
				//menangani perpangkatan lebih dari satu kali berturut turut, dan setelahnya ada
				//karakter break atau tambah atau
				//printf("inloop 2\n");
				//printf("idxpow %d\n", idxpow);
				for (int k = 0; k < idxpow; k++){
					idx--;
					temp[idx] = pow(temp[idx], temp[idx+1]);
					//printf("temp[%d] %f\n", idx, temp[idx]);
				}
				idxpow = 0;
			}
			
			//printf("outofloop\n");
			//printf("temp[%d] %f\n", idx, temp[idx]);

			if(((opt == '+') || (opt == '-')) && (*s != '\0')){
				//menandai berapa banyak tanda + dan - yang ada, dan dimana letaknya
				operand[idxc] = opt;
				//printf("operand[%d] %c\n", idxc, operand[idxc]);
				OneElmt = false;
				idxc++;
				s++;
			}
			idx++;
			//printf("loopidx %d\n", idx);
		}
	}

	if(OneElmt){
		//kondisi isi array bilangan hanya 1
		//printf("case 1 idx%d\n", idx);
		result = temp[0];
	} 
	else {
		/* if(multiplied) idx--; */
		//printf("case 2 idx %d\n", idx);
		result = 0;
		for(int i = 0; i < idx; i++){
			//printf("sumloop\n");
			//printf("temp[%d] %f\n", i, temp[i]);
			//printf("temp[%d] %f\n", i+1, temp[i+1]);
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
	*res = result;
}


float proc_parentheses(char *s, boolean *error, float *res){
	float tabfl[50];
	float result = 0;
	float temp;
	float tempres;
	char flt[50];
	char operand[50];
	char opt;
	char preopt;
	int count;
	int idx = 0;
	int idxc = 0;
	int idxa = 0;
	int idxpow = 0;

	boolean OneElmt = true;
	boolean Minus = false;
	boolean FirstElmt = true;
	boolean firstopt = false;
	boolean multiplied = false;
	*error = false;

	s++;
	if(*s == '-'){ 
		flt[idxc] = *s;
		idxc++;
		s++;
		Minus = true;
	}
	while(*s != ')'){
		if((!Minus) || (!FirstElmt)){
			//kalo  !(minus dan first element), maka kosongkan array flt yang buat menyimpan angka
			if(idxc != 0){
				idxc--;
				while(idxc >= 0){
					flt[idxc] = '\0';
					idxc--;
				}
				idxc = 0;
			}
		}

		if(*s == '('){
			proc_parentheses(s, error, &tempres);
			if(*error){
				break;
			}
			else tabfl[idx] = tempres; 
			////printf("tabfl[%d] %f\n", idx, tabfl[idx]);
			
			if(Minus){
				tabfl[idx] *= -1;
			}
			count = 1; //merupakan jumlah ')' yang dibutuhkan 
			s++;
			while (count != 0){
				if(*s == ')'){
					count--;
				} else if(*s == '('){
					count++;
				}
				s++;

			}			
		} 
		else {
			while((*s != ')') && (*s != '*') && (*s != '/') && (*s != '+') && (*s != '-') && (*s != '^')){
				flt[idxc] = *s;
				idxc++;
				s++;
 			}
 			tabfl[idx] = StringTofloat(flt);
			//printf("tabfl[%d] %f\n", idx, tabfl[idx]);

		}

		FirstElmt = false;

		if(*s != ')'){
			if (firstopt){
				preopt = *s;
				firstopt = false;
			}  //mengeset firstopt (operator pertama)
			else preopt = opt; 

			opt = *s;
			while(opt == '*' || opt == '/' || (opt == '^')){
				if(idxa == 0) OneElmt = true;
				multiplied = true;
				s++;
				if(*s == '('){
					proc_parentheses(s, error, &tempres);
					if(*error){
						break;
					}
					else temp = tempres; 

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
					while((*s != ')') && (*s != '*') && (*s != '/') && (*s != '+') && (*s != '-') && (*s != '^')){
						flt[idxc] = *s;
						idxc++;
						s++;
					}
					temp = StringTofloat(flt);
				}

				if(opt == '^'){
					if((tabfl[idx] < 0) && (temp < 1)){
						*error = true;
						break;
					}
					else{
						idx++;
						tabfl[idx] = temp;
						idxpow++;
					}
				}
				else if(opt == '*'){
					tabfl[idx] *= temp;
				} 
				else if(opt == '/'){
					if(temp == 0){
						*error = true;
						break;
					}
					else{
						tabfl[idx] /= temp;
					}
				}
				preopt = opt;
				opt = *s;

				if((preopt == '^') && (opt != '^') && (idxpow != 0)){
					//printf("inloop 1\n");
					//printf("idxpow %d\n", idxpow);
					for (int k = 0; k < idxpow; k++){
						idx--;
						tabfl[idx] = pow(tabfl[idx], tabfl[idx+1]);
						//printf("tabfl[%d] %f\n", idx, tabfl[idx]);
					}
					idxpow = 0;
				}
			}

			//pemrosesan pangkat(diulang)
			if((preopt == '^') && (opt != '^') && (idxpow != 0)){
					//printf("inloop 2\n");
					//printf("idxpow %d\n", idxpow);
					for (int k = 0; k < idxpow; k++){
						idx--;
						tabfl[idx] = pow(tabfl[idx], tabfl[idx+1]);
						//printf("tabfl[%d] %f\n", idx, tabfl[idx]);
					}
					idxpow = 0;
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
		//printf("case 1 idx%d\n", idx); 
		//printf("result %f\n", result);
		
	} else {
		/* if(multiplied) idx--; */
		//pemrosesan tab(diulang)
		//printf("case 2 idx%d\n", idx); 
		result = 0;
		for(int i = 0; i < idx; i++){
			if(i == 0){
				//printf("sumloop\n");
				//printf("tabfl[%d] %f\n", i, tabfl[i]);
				//printf("tabfl[%d] %f\n", i+1, tabfl[i+1]);
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
			//printf("result %d %f\n", i, result);
		}
	}
	
	*res = result;
}

