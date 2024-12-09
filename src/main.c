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
				 // and demonstrates the _for_each functionality
	example_3(); // demonstrates the vec_from_array and vec_reduce functionality
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

typedef struct {
	unsigned int id;
	char name[100];
} User;

void print_user(User *user);

void example_2(void) {
	DECLARE_VEC(uvec, User);

	uvec_t v = uvec_new();
	uvec_push(v, (User){ 125, "Bob" });
	uvec_push(v, (User){ 300, "Alice" });

	uvec_for_each(v, &print_user);

	uvec_free(&v);
}

int sum(int a, int b);

void example_3(void) {
	DECLARE_VEC(ivec, int);

	int ns[0x100] = { 32, 17, 5, 286, 114, 0, 2, 7 };
	ivec_t v = ivec_from_array(ns, ARR_LEN(ns));

	printf("Sum: %d\n", ivec_reduce(v, &sum, 0));


	ivec_free(&v);
}

void print_user(User *user) {
	printf("User's name: %s\n", user->name);
}
int sum(int a, int b) {
	return a + b;
}
