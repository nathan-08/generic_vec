#ifndef VEC_INCLUDE
#define VEC_INCLUDE

#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> // memcpy

#define CAP_INIT 0x20

#define DECLARE_VEC(tag, T) \
	struct tag { \
		size_t nitems, cap; \
		T     *data; \
	}; \
	typedef struct tag * tag ## _t; \
	\
	/* <tag>_new: Create a new instance of the vector */ \
	\
	tag ## _t tag ## _new(void) { \
		tag ## _t ptr = malloc(sizeof(struct tag)); \
		ptr->nitems = 0; \
		ptr->cap    = CAP_INIT; \
		ptr->data   = calloc(CAP_INIT, sizeof(T)); \
		return ptr; \
	} \
	\
	/* <tag>_push: Adds an item to the end of the vector. */ \
	\
	void tag ## _push(tag ## _t vec, T item) { \
		assert(vec); \
		if (vec->nitems == vec->cap) { \
			size_t new_cap = 2 * vec->cap; \
			T *new_data = calloc(new_cap, sizeof(T)); \
			memcpy(new_data, vec->data, vec->nitems); \
			free(vec->data); \
			vec->data = new_data; \
			vec->cap = new_cap; \
		} \
		vec->data[vec->nitems++] = item; \
	} \
	\
	/* <tag>_free: Takes a pointer to a <tag>_t,
	 * 				(that is, a `struct <tag>**`);
	 * 				deallocates the vector and sets
	 * 				the <tag>_t pointer to NULL,
	 * 				in order to protect against
	 * 				accessing freed memory. 
	 * 				*/ \
	\
	void tag ## _free(tag ## _t * vec_ptr) { \
		free ((*vec_ptr)->data); \
		free (*vec_ptr); \
		*vec_ptr = NULL; \
	} \
	\
	/* <tag>_count: Returns the number of items
	 * 				in the vector */ \
	\
	size_t tag ## _count(tag ##_t vec) { \
		return vec->nitems; \
	} \
	\
	/* <tag>_get: Returns the element at the provided index. */ \
	\
	T tag ## _get (tag ## _t vec, size_t index) { \
		assert(vec); \
		assert(index < vec->nitems); \
		return vec->data[index]; \
	} \
	\
	/* <tag>_pop: Removes the last element of the vector. */ \
	\
	void tag ## _pop (tag ## _t vec) { \
		assert(vec); \
		assert(vec->nitems > 0); \
		--vec->nitems; \
	} \


#endif
