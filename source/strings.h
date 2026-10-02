/// @file strings.h

#ifndef STRINGS_H_
#define STRINGS_H_

#include <stddef.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#pragma pack(4)

typedef struct string_t {
	char *cstr;
	size_t len, alloc;
} str_t;

#pragma pack()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

str_t str_init	(const char *cstr);
str_t str_n_init(const char *cstr, const size_t len);

void str_pack(str_t *str);
void str_free(str_t *str);

/* —— strlen() —————————————————————————————————————————————————— */

size_t str_len	(const str_t *str);
size_t str_n_len(const str_t *str, size_t len);

/* —— strcpy() —————————————————————————————————————————————————— */

str_t *str_cpy	(str_t *dst, const str_t *src);
str_t *str_n_cpy(str_t *dst, const str_t *src, size_t len);
size_t str_l_cpy(str_t *dst, const str_t *src, size_t len);

/* —— strdup() —————————————————————————————————————————————————— */

str_t *str_dup	(const str_t *str);
str_t *str_n_dup(const str_t *str, size_t len);

/* —— strcmp() —————————————————————————————————————————————————— */

int str_cmp	 (const str_t *str1, const str_t *str2);
int str_n_cmp(const str_t *str1, const str_t *str2, size_t len);

/* —— strchr() —————————————————————————————————————————————————— */

str_t *str_chr	  (const str_t *str, int c);
str_t *str_r_chr  (const str_t *str, int c);
str_t *str_chr_nul(const str_t *str, int c);

/* —— strstr() —————————————————————————————————————————————————— */

str_t *str_str		(const str_t *haystack, const str_t *needle);
str_t *str_n_str	(const str_t *haystack, const str_t *needle, size_t len);
str_t *str_case_str	(const str_t *haystack, const str_t *needle);

/* —— strcat() —————————————————————————————————————————————————— */

str_t *str_cat	(str_t *dst, const str_t *src);
str_t *str_n_cat(str_t *dst, const str_t *src, size_t len);
size_t str_l_cat(str_t *dst, const str_t *src, size_t len);

/* —— strspn() —————————————————————————————————————————————————— */

size_t str_spn	(const str_t *str, const str_t *charset);
size_t str_c_spn(const str_t *str, const str_t *charset);

/* —— strsep() —————————————————————————————————————————————————— */

str_t *str_sep(str_t **pstr, const str_t *delim);

/* —— strpbrk() ————————————————————————————————————————————————— */

str_t *str_p_brk(const str_t *str, const str_t *charset);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRINGS_H_ */

// spell:ignore ccstr_t
