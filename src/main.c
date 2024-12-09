#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vec.h"

#define ARR_LEN(a) sizeof(a)/sizeof(a[0])
#define RAND_FLOAT(a,b) a+(b-a)*((float) rand() / (float) RAND_MAX)

void example_1(void);
void example_2(void);
void example_3(void);

int main (int argc, char* argv[]) {
	example_1(); // creates a large array of floats
	example_2(); // creates an array of user defined structs
	example_3(); // uses the _from_array functionality
	return 0;
}

void example_1(void) {
	srand(time(NULL));
	DECLARE_VEC(fvec, float);
	fvec_t v = fvec_new();

	for (int i = 0; i < 0x1000; ++i) {
		fvec_push(v, RAND_FLOAT(-1.f, 1.f));
	}

	printf("nitems: %ld\n", fvec_count(v));
	for (size_t i = 32; i < 37; i++) {
		printf("%f\n", fvec_get(v, i));
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

	for (size_t i = 0; i < uvec_count(v); ++i)
		printf("User's name: %s\n", uvec_get(v, i).name);

	uvec_free(&v);
}

void example_3(void) {
	DECLARE_VEC(ivec, int);

	int ns[0x100] = { 32, 17, 5, 286, 114, 0, 2, 7 };
	ivec_t v = ivec_from_array(ns, ARR_LEN(ns));

	printf("nitems: %ld\n", ivec_count(v));
	printf("arrlen: %ld\n",   ARR_LEN(ns));

	for (size_t i = 0; i < 5; ++i)
		printf("%d\n", ivec_get(v, i));

	ivec_free(&v);
}
