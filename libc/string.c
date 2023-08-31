
#include "string.h"

int strlen(char str[]) {
    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    return i;
}

int strcmp(char src[], char dest[]) {
    for (int i = 0; src[i] == dest[i]; i++) {
        if (src[i] == '\0')
            return 0;
    }

    return src[i] - dest[i];
}

void int_to_ascii(int num, char dest[]) {
    int i, sign;

    if ((sign = n) < 0) n = -n;

    i = 0;

    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';

    str[i] = '\0';
}

void append(char src[], char data) {
    int len = strlen(src);

    src[len] = data;
    src[len + 1] = '\0';
}
