#include <stdio.h>

#include "chapter_2.h"

static void jolly (void) {
	printf("He is good fellow!\n");
}

static void br (void) {
	printf("Brazil, Russia");
}

static void ic (void) {
	printf("India, China");
}

static void deny (void) {
	printf("Which nobody can deny!\n");
}

static void smile (void) {
	printf("smile!");
}

static void two (void) {
	printf("two");
}

static void one_three (void) {
	printf("one\n");
	two();
	printf("\n");
	printf("three\n");
}

void exercise_2_1(void) {

    printf("Darth Vader\n");
    printf("Darth\nVader\n");
    printf("Darth ");
    printf("Vader\n");
}

void exercise_2_2(void) {
    printf("First name: Vader\n"
    	   "Secon name: Darth\n");
    printf("Address:    Tatooine\n");
}

void exercise_2_3(void) {
	const unsigned int age = 32, days_per_year = 365;

	printf("Age %d equal %d days\n", age, age * days_per_year);
}

void exercise_2_4(void) {
	unsigned int jolly_num = 3;

    while (jolly_num--) {
	   jolly();
	}

	deny();
}

void exercise_2_5(void) {
	br();
	printf(", ");
	ic();
	printf("\n");
	ic();
	printf(",\n");
	br();
}

void exercise_2_6(void) {
	const unsigned int toes = 10;

	printf("An origin value of the toes: %d\n"
		   "The doubled toes: %d\n"
		   "A squad of the toes: %d", toes, 2 * toes, toes * toes);

}

void exercise_2_7(void) {
	unsigned int i = 6;

	for (i = 6; i > 0; i--) {
		smile();

		if((2 == i) || (4 == i)) {
			printf("\n");
		}
	}
}

void exercise_2_8(void) {
	printf("begin:\n");
	one_three();
	printf("ok!\n");
}




































