#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>

void swap(char *str1, char *str2) {
    char *temp = (char *) malloc((strlen(str1) + 1) * sizeof(char));
    strcpy(temp, str1);
    strcpy(str1, str2);
    strcpy(str2, temp);
    free(temp);
}

void force_str1_large(char *str1, char *str2) {
    int str1_len = strlen(str1);
    int str2_len = strlen(str2);
    bool str1_is_large = true;
    if (str1_len < str2_len) {
        str1_is_large = false;
    } else if (str1_len == str2_len) {
        int i = 0;
        while (i < str1_len) {
            if (str1[i] != str2[i]) {
                str1_is_large = str1[i] > str2[i] ? true : false;
                break;
            }
            i++;
        }
    }
    if (!str1_is_large) {
        swap(str1, str2);
    }
}

bool is_divisible_by2(char *str) {
    if (str[strlen(str) - 1] % 2 == 0) return true;
    return false;
}

void long_str_division(char *str, int divisor) {
    int str_len = strlen(str);
    if (str_len > 1) {
        int p = 0;
        int temp = str[p] - 48;
        while (temp < divisor) {
            temp = temp * 10 + (str[++p] - 48);
        }
        int q = 0;
        while (p < str_len) {
            str[q++] = temp / divisor + 48;
            temp = (temp % divisor) * 10 + (str[++p] - 48);
        }
        str[q] = '\0';
    } else {
        str[0] = (str[0] - 48) / divisor + 48;
    }
}

void long_str_subtraction(char  *str1, char  *str2) {
    int p = strlen(str1) - 1;
    int q = strlen(str2) - 1;
    int difference;
    while (q >= 0) {
        difference = str1[p] - str2[q--];
        if (difference < 0) {
            str1[p - 1]--;
            str1[p--] = difference + 10 + 48;
        } else {
            str1[p--] = difference + 48;
        }
    }
    while (p > 0 && str1[p] - 48 < 0) {
        str1[p - 1]--;
        str1[p--] = 57;
    }
}

void trim_zeros(char *str) {
    int str_len = strlen(str);
    int p = 0;
    while (str[p] == 48 && p < str_len) p++;
    if (p == str_len) {
        str[1] = '\0';
    } else {
        int q = 0;
        while (p <= str_len) {
            str[q++] = str[p++];
        }
    }
}

void long_str_multiplication_by2(char *str) {
    int str_len = strlen(str);
    int p = str_len - 1;
    bool carry = false;
    int temp;
    while (p >= 0) {
        temp = (str[p] - 48) * 2;
        str[p--] = carry ? temp % 10 + 48 + 1 : temp % 10 + 48;
        carry = temp >= 10 ? true : false;
    }
    if (carry) {
        for (int i = str_len; i > 0; i--) str[i] = str[i - 1];
        str[0] = 49;
        str[str_len + 1] = '\0';
    }
}

int main( )
{
    char str1[256];
    char str2[256];
    scanf("%s%s", str1, str2);
    force_str1_large(str1, str2);
    int time = 0;
    while (str1[0] != 48 && str2[0] != 48) {
        if (is_divisible_by2(str1) && is_divisible_by2(str2)) {
            long_str_division(str1, 2);
            long_str_division(str2, 2);
            time++;
        } else if (is_divisible_by2(str1)) {
            long_str_division(str1, 2);
        } else if (is_divisible_by2(str2)) {
            long_str_division(str2, 2);
        }
        force_str1_large(str1, str2);
        long_str_subtraction(str1, str2);
        trim_zeros(str1);
    }
    while (time-- > 0) {
        long_str_multiplication_by2(str2);
    }
    printf("%s", str2);
    return 0;
}
