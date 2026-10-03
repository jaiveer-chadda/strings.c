/// @file strings.c

#include <stdlib.h> // malloc(), free()
#include <string.h> // memcpy(), strlen()
#include <stdbool.h> // bool, true, false

#include "strings.h"

/* —— Definitions —————————————————————————————————————————————————————————————————————————————————————————————————— */

#define public
#define private static inline

/* ——————————————————————————————————————————————————————————— */

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

#define MULT_BY_1_5(var) \
	((var) += (var) <= 1 ? 1 : (var) >> 1)

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— Private Functions ———————————————————————————————————————————————————————————————————————————————————————————— */

private void str_resize(str_t *const str, const len_t new_len) {
	// the +1 is for the extra nullbyte
	if (str->_alloc >= ( str->len = new_len ) + 1) return;

	str->cstr = reallocf(str->cstr, MULT_BY_1_5(str->_alloc));

	if (str->cstr == NULL) exit(-1);
	str->cstr[new_len + 1] = '\0';
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— str_init() ——————————————————————————————————————————————————————————————————————————————————————————————————— */

public str_t str_init(const char *const cstr) {
	return str_n_init(cstr, strlen(cstr));
}

public str_t str_n_init(const char *const cstr, const len_t len) {
	return (str_t){
		.cstr = memcpy(calloc(1, len + 1), cstr, len),
		.len = len, ._alloc = len
	};
}

/* —— str_pack() ————————————————————————————————————————————— */

public void str_pack(str_t *const str) {
	str->cstr = realloc(str->cstr, ( str->_alloc = str->len ));
}

/* —— str_free() ————————————————————————————————————————————— */

public void str_free(str_t *const str) {
	free(str->cstr);
	*str = (str_t){0};
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
/* —— strlen() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

public len_t str_len(const str_t *const str) {
	return str->len;
}

public len_t str_n_len(const str_t *const str, len_t len) {
	return MIN(str->len, len);
}

/* —— strcpy() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

public void str_cpy(str_t *const dst, const str_t *const src) {
	str_n_cpy(dst, src, src->len);
}

public void str_n_cpy(str_t *dst, const str_t *src, len_t len) {
	if (dst == NULL) exit(-1);

	str_resize(dst, len);
	memcpy(dst->cstr, src, len);
}

/* —— strdup() ——————————————————————————————————————————————— */

public str_t str_dup(const str_t *str) {
	return str_n_dup(str, str->len);
}

public str_t str_n_dup(const str_t *str, len_t len) {
	str_t string = {0};
	str_n_cpy(&string, str, len);
	return string;
}

/* —— strcmp() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

public int str_cmp(const str_t *str1, const str_t *str2) {
	return str_n_cmp(str1, str2, str1->len);
}

public int str_n_cmp(const str_t *str1, const str_t *str2, const len_t len) {
	const size_t iter_len = MIN(len, MIN(str1->len, str2->len));

	for (size_t i = 0; i < iter_len; i++) {
		if (str1->cstr[i] < str2->cstr[i]) return -1;
		if (str1->cstr[i] > str2->cstr[i]) return  1;
	}

	return 0;
}

/* —— strchr() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

private idx_t s__strchr(const str_t *str, char chr, const len_t maxlen, const idx_t on_failure) {
	const idx_t max_idx = MIN(maxlen, str->len);

	for (idx_t idx = 0; idx < max_idx; idx++) {
		if (str->cstr[idx] == chr) return idx;
	}

	return on_failure;
}

/* ——————————————————————————————————————————————————————————— */

public idx_t str_chr(const str_t *str, char chr) {
	return s__strchr(str, chr, str->len, -1);
}

public idx_t str_chr_nul(const str_t *str, char chr) {
	return s__strchr(str, chr, str->len, str->len);
}

public idx_t str_n_chr(const str_t *str, char chr, const len_t len) {
	return s__strchr(str, chr, len, str->len);
}

/* ——————————————————————————————————————————————————————————— */

public idx_t str_r_chr(const str_t *str, char chr) {
	for (idx_t idx = str->len - 1; idx >= 0; idx--) {
		if (str->cstr[idx] == chr) return idx;
	}
	return -1;
}

/* —— strstr() ————————————————————————————————————————————————————————————————————————————————————————————————————— */

#define TOLOWER_IF(chr, cond) (				 \
	((cond) && 'A' <= (chr) && (chr) <= 'Z') \
		? (chr) + ('a' - 'A')				 \
		: (chr)								 \
)

/* ——————————————————————————————————————————————————————————— */

private bool s__strstr_from_idx(const str_t *haystack, const str_t *needle, const idx_t hsi, const bool igncase) {
	for (idx_t i = 0; i < (idx_t)needle->len; i++) {
		const char hay = haystack->cstr[hsi + i];
		const char ned = needle->cstr[i];

		if (TOLOWER_IF(hay, igncase) != TOLOWER_IF(ned, igncase)) return false;
	}

	return true;
}

private bool s__strnstr(const str_t *haystack, const str_t *needle, const len_t len, const bool igncase) {
	const idx_t max_idx = MIN(len, haystack->len - needle->len);

	for (idx_t i = 0; i < max_idx; i++) {
		if (s__strstr_from_idx(haystack, needle, i, igncase)) return i;
	}

	return -1;
}

/* ——————————————————————————————————————————————————————————— */

public idx_t str_str(const str_t *haystack, const str_t *needle) {
	return s__strnstr(haystack, needle, haystack->len, false);
}

public idx_t str_n_str(const str_t *haystack, const str_t *needle, const len_t len) {
	return s__strnstr(haystack, needle, len, false);
}

public idx_t str_case_str(const str_t *haystack, const str_t *needle) {
	return s__strnstr(haystack, needle, haystack->len, true);
}

public idx_t str_n_case_str(const str_t *haystack, const str_t *needle, const len_t len) {
	return s__strnstr(haystack, needle, len, true);
}

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */
