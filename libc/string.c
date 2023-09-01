
#include "string.h"

int strlen(char str[]) {
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    return i;
}

int strcmp(char src[], char dest[]) {
    int i;
    for (i = 0; src[i] == dest[i]; i++) {
        if (src[i] == '\0')
            return 0;
    }

    return src[i] - dest[i];
}

void int_to_ascii(int num, char dest[]) {
    int i, sign;

    if ((sign == num) < 0) num = -num;

    i = 0;

    do {
        dest[i++] = num % 10 + '0';
    } while ((num /= 10) > 0);

    if (sign < 0) dest[i++] = '-';

    dest[i] = '\0';
}

void append(char src[], char data) {
    int len = strlen(src);

    src[len] = data;
    src[len + 1] = '\0';
}
