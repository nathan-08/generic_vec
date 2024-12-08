#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vec.h"

void example_1(void);
void example_2(void);

int main (int argc, char* argv[]) {
	example_1();
	example_2();
	return 0;
}

void example_1(void) {
	srand(time(NULL));
	DECLARE_VEC(fvec, float);
	fvec_t v = fvec_new();
	for (int i = 1; i <= 100; i++) {
		fvec_push(v, (float) rand() / (float) RAND_MAX);
	}
	printf("nitems: %ld\n", fvec_count(v));
	for (int i = 0; i < 5; i++) {
		printf("%f\n", fvec_get(v, (size_t) i));
	}
	fvec_free(&v);
}

void example_2(void) {
	typedef struct {
		unsigned int id;
		char name[100];
	} User;

	DECLARE_VEC(uvec, User);

	uvec_t v = uvec_new();
	uvec_push(v, (User){ 125, "Bob" });
	uvec_push(v, (User){ 300, "Alice" });

	for (int i = 0; i < uvec_count(v); ++i)
		printf("User's name: %s\n", uvec_get(v, (size_t) i).name);

	uvec_free(&v);
}
