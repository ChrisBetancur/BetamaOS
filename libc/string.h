
#ifndef STRING_H
#define STRING_H

void int_to_ascii(int n, char str[]);

void reverse(char s[]);

int strlen(char s[]);

int strcmp(char s1[], char s2[]);

void append(char s[], char n);

void backspace(char s[]);

char** split_str(char input[], char delimiter, int max_tokens);

#endif
