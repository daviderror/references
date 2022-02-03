#include <stdio.h>
#include <float.h>

#include "chapter_4.h"

#define STRING_LIMITE 100

void exercise_4_1(void) {
	char name[STRING_LIMITE] = {}, surname[STRING_LIMITE] = {};

	printf("Insert your name and surname please: ");
	scanf("%s%s", name, surname);
	printf("Here are both your surname and name: %s %s\n", surname, name);
}

void exercise_4_2(void) {
	char name[STRING_LIMITE] = {};

	printf("Insert your name please: ");
	scanf("%s", name);
	printf("a.It is your \"name\": %s\n", name);
	printf("b.It is your name: \"%20s\"\n", name);
	printf("c.It is your name: \"%-20s\"\n", name);
}

void exercise_4_3(void) {
	float float_var = 0.0;

	printf("Insert a float number please: ");
	scanf("%f", &float_var);
	printf("The value in dec: %.3f\n", float_var);
	printf("The value in exp: %.3e\n", float_var);
}

void exercise_4_4(void){
	const float inch_coef = 12.0;

	char name[STRING_LIMITE] = {};
	float height = 0.0;

	printf("Insert you name and height: ");
	scanf("%s%f", name, &height);

	printf("%s: %.3f", name, height / inch_coef);
}

void exercise_4_5(void){
	float rate = 0, file_size = 0;

	const unsigned int c_bit_in_byte = 9;

    printf("Insert rate in Mb/s: ");
    scanf("%f", &rate);
    printf("Insert a file  size in MB: ");
    scanf("%f", &file_size);

    printf("Rate: %2.2fMB/s, size: %2.2fMB, loading: %2.2f seconds", rate, file_size, (file_size * c_bit_in_byte) / rate);
}

void exercise_4_6(void) {

}

void exercise_4_7(void) {
    double d = 1.0 / 3.0;
    float f = 1.0 / 3.0;

    printf("4: d:%.4f f:%.4f\n", d, f);
    printf("4: d:%.12f f:%.12f\n", d, f);
    printf("4: d:%.16f f:%.16f\n", d, f);

    printf("DBL_DIG:%d FLT_DIG:%d", DBL_DIG, FLT_DIG);
}


void exercise_4_8(void) {
	float gasoline = 0.0, miles = 0.0;

	const float c_km_coef = 1.609, c_lt_coef = 3.785;

	printf("Insert gasoline gallons: ");

	scanf("%f", &gasoline);

	printf("Insert miles: ");
	scanf("%f", &miles);

	printf("Insert gallons per mile: %.1f\n", gasoline / miles);
	printf("Insert litters per kilometer: %.1f\n", (gasoline * c_lt_coef) / (miles * c_km_coef));

}





































