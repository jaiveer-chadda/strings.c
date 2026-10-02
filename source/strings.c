/// @file strings.c

#include <stdlib.h> // malloc(), free()
#include <string.h> // memcpy(), strlen()

#include "strings.h"

#define public
#define private static inline

#define zalloc(size) calloc(1, (size))

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

public str_t str_init(const char *const cstr) {
	return str_n_init(cstr, strlen(cstr));
}

public str_t str_n_init(const char *const cstr, const size_t len) {
	return (str_t){
		.cstr = memcpy(zalloc(len + 1), cstr, len),
		.len = len, .alloc = len
	};
}

public void str_pack(str_t *str) {
	str->cstr = realloc(str->cstr, ( str->alloc = str->len ));
}

public void str_free(str_t *str) {
	free(str->cstr);
	*str = (str_t){0};
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
