/// @file strings.c

#include <stdlib.h> // malloc(), free()
#include <string.h> // memcpy(), strlen()

#include "strings.h"

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define public
#define private static inline

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define zalloc(size) calloc(1, (size))

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MULT_BY_1_5(var) \
	((var) += (var) <= 1 ? 1 : (var) >> 1)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

private void str_resize(str_t *const str, const len_t new_len) {
	// the +1 is for the extra nullbyte
	if (str->alloc >= ( str->len = new_len ) + 1) return;

	str->cstr = reallocf(str->cstr, MULT_BY_1_5(str->alloc));

	if (str->cstr == NULL) exit(-1);
	str->cstr[new_len + 1] = '\0';
}

private void str_cset(const str_t *const dst, const char *const src) {
	str_resize(dst, strlen(src));
	memcpy(dst->cstr, src, dst->len);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

public str_t str_init(const char *const cstr) {
	return str_n_init(cstr, strlen(cstr));
}

public str_t str_n_init(const char *const cstr, const len_t len) {
	return (str_t){
		.cstr = memcpy(zalloc(len + 1), cstr, len),
		.len = len, .alloc = len
	};
}

public void str_pack(str_t *const str) {
	str->cstr = realloc(str->cstr, ( str->alloc = str->len ));
}

public void str_free(str_t *const str) {
	free(str->cstr);
	*str = (str_t){0};
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

public len_t str_len(const str_t *const str) { return str->len; }
public len_t str_n_len(const str_t *const str, len_t len) { return MIN(str->len, len); }

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
