/// @file strings.h

#ifndef STRINGS_H_
#define STRINGS_H_

#include <stddef.h>

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

typedef size_t len_t;
typedef ssize_t	idx_t, count_t;

#pragma pack(4)

typedef struct string_t {
	char *cstr;
	len_t len, _alloc;
} str_t;

#pragma pack()

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

str_t str_init	(const char *cstr);
str_t str_n_init(const char *cstr, const len_t len);

void str_pack(str_t *str);
void str_free(str_t *str);

/* —— strlen() —————————————————————————————————————————————————— */

len_t str_len  (const str_t *str);
len_t str_n_len(const str_t *str, len_t len);

/* —— strcpy() —————————————————————————————————————————————————— */

void str_cpy  (str_t *dst, const str_t *src);
void str_n_cpy(str_t *dst, const str_t *src, len_t len);

/* —— strdup() —————————————————————————————————————————————————— */

str_t str_dup  (const str_t *str);
str_t str_n_dup(const str_t *str, len_t len);

/* —— strcmp() —————————————————————————————————————————————————— */

int str_cmp	 (const str_t *str1, const str_t *str2);
int str_n_cmp(const str_t *str1, const str_t *str2, len_t len);

/* —— strchr() —————————————————————————————————————————————————— */

idx_t str_chr	 (const str_t *str, char chr);
idx_t str_r_chr	 (const str_t *str, char chr);
idx_t str_chr_nul(const str_t *str, char chr);
idx_t str_n_chr	 (const str_t *str, char chr, const len_t len);

/* —— strstr() —————————————————————————————————————————————————— */

idx_t str_str	  (const str_t *haystack, const str_t *needle);
idx_t str_n_str	  (const str_t *haystack, const str_t *needle, len_t len);
idx_t str_case_str(const str_t *haystack, const str_t *needle);

/* —— strcat() —————————————————————————————————————————————————— */

void str_cat  (str_t *dst, const str_t *src);
void str_n_cat(str_t *dst, const str_t *src, len_t len);

/* —— strspn() —————————————————————————————————————————————————— */

count_t str_spn	 (const str_t *str, const str_t *charset);
count_t str_c_spn(const str_t *str, const str_t *charset);

/* —— strsep() —————————————————————————————————————————————————— */

str_t *str_sep(str_t **pstr, const str_t *delim);

/* —— strpbrk() ————————————————————————————————————————————————— */

str_t *str_p_brk(const str_t *str, const str_t *charset);

/* ————————————————————————————————————————————————————————————————————————————————————————————————————————————————— */

#endif /* !STRINGS_H_ */

// spell:ignore ccstr_t
