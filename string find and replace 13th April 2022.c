// my second attemp at making a fairly quick program to find and replace a given word from a source string

#include <stdio.h>
#include <stdlib.h>

char src[1000], pat[500], rep[500];

int compare(char str1[], char str2[])
{
    int i;

    for (i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) return 0;
    }

    if ((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
        return 0;

    return 1;
}

char words[50][1000];

int split(char str[])
{
    int j = 0;

    for (int i = 0, k = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') {
            k = 0;
            j++;
        }
        else {
            words[j][k++] = str[i];
        }
    }

    return j + 1;
}


char* replace(char src[], char pat[], char rep[])
{
    char* newString = (char *) malloc(1000 * sizeof(char));

    int numberOfWords = split(src);

    int i, j, k;

    for (i = 0, j = 0; i < numberOfWords; i++) {
        if (compare(words[i], pat)) {
            for (k = 0; rep[k] != '\0'; k++) {
                newString[j++] = rep[k];
            }
        }
        else {
            for (k = 0; words[i][k] != '\0'; k++) {
                newString[j++] = words[i][k];
            }
        }
        newString[j++] = ' ';
    }

    newString[j] = '\0';

    return newString;
}



void menu() {
    printf("Enter the main string: \n");
    gets(src);

    printf("Enter the pattern string: \n");
    gets(pat);

    printf("Enter the replacement string: \n");
    gets(rep);

    char* newString = replace(src, pat, rep);

    printf("%s", newString);

    return;
}



int main() {
    menu();
    return 0;
}
