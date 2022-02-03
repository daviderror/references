#include <stdio.h>
#include <limits.h>
#include <float.h>

#include "chapter_3.h"

void exercise_3_1(void) {
	int int_max = INT_MAX;
	unsigned int u_int_max = UINT_MAX;
	float float_max = FLT_MAX;

	printf("int_max: %d int_max + 1: %d\n", int_max, int_max + 1);
	printf("u_int_max: %d u_int_max + 1: %d\n", u_int_max, u_int_max + 1);
	printf("float_max: %f float_max + 1: %f\n", float_max, float_max + 1);
}

void exercise_3_2(void) {

	unsigned int ch_value = 0;

	printf("Please push some value at an arrange 0 - 127:");
	scanf("%d", &ch_value);
	printf("\nThe value equals: %c", (char) ch_value);
}

void exercise_3_3(void) {

	printf("\a Hello\n\"What happen!\"");
}

void exercise_3_4(void) {

	float f_value = 0.0;

	printf("Please push some float value:");
	scanf("%f", &f_value);
	printf("\nThe value:\nIn dec %d\nIn exp %e\nIn just float %.10f\nIn binary %a", (int) f_value, f_value,f_value, f_value);
}

void exercise_3_5(void) {
	unsigned int ages = 0;

	const float c_sec_per_year = 3.156e7;

	printf("Please push your age:");
	scanf("%u", &ages);
	printf("\nYour age in seconds: %e", ages * c_sec_per_year);
}

void exercise_3_6(void) {
	unsigned int quart_number = 0;

	const float c_mol_per_quart = 3e-23, c_quart_mass = 0.950;

	printf("Please push number of quarts:");
	scanf("%u", &quart_number);
	printf("\nMass of the quarts: %e", (quart_number * c_quart_mass) / c_mol_per_quart);
}

void exercise_3_7(void) {
	unsigned int height = 0;

	const float c_sm_in_inch = 2.54;

	printf("Please push your height in inches:");
	scanf("%u", &height);
	printf("\nYou height in inches: %e", height / c_sm_in_inch);
}

void exercise_3_8(void) {
	unsigned int cups_number = 0;

	const float c_pints_in_cup = 0.5;
	const unsigned int c_ounce_in_cup = 8, c_tablespoon_in_ounce = 2, c_teaspoon_in_tablespoon = 3;

	printf("Please push cup number:");
	scanf("%u", &cups_number);

	printf("\nThe cups number equals:");
	printf("\n%f pints", (float) (cups_number * c_pints_in_cup) );
	printf("\n%u ounces", cups_number * c_ounce_in_cup);
	printf("\n%u tablespoons", cups_number * c_ounce_in_cup * c_tablespoon_in_ounce);
	printf("\n%u teaspoons", cups_number * c_ounce_in_cup * c_tablespoon_in_ounce * c_teaspoon_in_tablespoon);
}
