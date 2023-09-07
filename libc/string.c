#include "string.h"
#include "../drivers/graphics.h"
#include "types.h"

void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    s32 tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');}

void reverse(char s[]) {
    int j, c;
    for (int i = 0; j = strlen(s) - 1; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int strlen(char s[]) {
    int i = 0;

    while (s[i] != '\0') i++;

    return i;
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

void append(char s[], char n) {
    int len = strlen(s);

    s[len] = n;
    s[len + 1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len - 1] = '\0';
}

char** split_str(char input[], char delimiter, int max_tokens) {
    int token_count = 0;
    int len = strlen(input);

    if (len == 0)
        return NULL;

    int start = 0;
    int end = 0;
    int in_token = 0;

    char* tokens[max_tokens];


    for (int i = 0; i < len; i++) {
        if (input[i] == delimiter) {
            if (token_count < max_tokens) {

                char str[end-start];

                mem_copy(input, str, end - start);
                tokens[token_count] = str;

                //tokens[token_count][end - start] = '\0';
                kprint(*tokens[token_count]);
                kprint("\n");

                token_count++;
                start = i + 1;
            }
            else
                return NULL; // EXCEEDED MAX TOKEN COUNT
        }
        else {
            end = i + 1;
            in_token = 1;
        }
        kprint("start=");

        char s1[3];
        int_to_ascii(start, s1);
        kprint(s1);

        kprint(", ");

        char s2[3];
        int_to_ascii(end, s2);
        kprint(s2);

        kprint("\n");
        kprint("\n");
    }

    if (in_token && token_count < max_tokens) {
        mem_copy(input, tokens[token_count], end - start);
        tokens[token_count][end - start] = '\0';
        token_count++;
    }
    else if (in_token && token_count >= max_tokens) {
        return NULL;
    }

    kprint(tokens[0]);
    return tokens;
}
