#ifndef pdacalculator_H
#define pdacalculator_H

#include "boolean.h"
#include "string.h"
#include "stack.h"
#include <stdio.h>

float StringTofloat(char *s);
/* Mengubah string dari sebuah bilangan ke bentuk float
I.S : s terdefinisi sebagai sebuah string berbentuk bilangan dan tidak kosong,
minimal adalah 2 karakter untuk bilangan negatif dan 1 karakter untuk bil. positif
F.S : mengembalikan hasil konversi dari string s
*/
void Transition(int *State, char Symbol, Stack *S,boolean *stuck);
/* Prosedur transisi PDA
State terdefinisi 0,1,2,3. Symbol merupakan karakter yang sedang dibaca. S merupakan Stack yang digunakan. stuck bernilai true jika Symbol tidak valid
*/

boolean PDA(char *s);
/* Validasi apakah string merupakan ekspresi matematika yang valid?
I.S : str terdefinisi sebagai sebuah string
F.S : jika str merupakan ekspresi matematika, output true. Jika tidak, output false
*/

float StringHandler(char *s);
/* Menghitung operasi matematika dari string yang diinputkan
Prekondisi  : Sintaks string harus benar
F.S         : Mengeluarkan hasil dari operasi matematika string tersebut
Operasi yang ada (+,-,*,/,()) 
*/

float ParenthesesHandler(char *s);
/* Algoritma khusus menghitung operasi dalam kurung
Prekondisi  : Sintaks merupakan operasi dalam kurung
F.S         : Menghasilkan hasil operasi dalam kurung
*/

#endif