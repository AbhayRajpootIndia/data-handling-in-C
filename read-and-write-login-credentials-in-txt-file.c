#include <stdio.h>
#include <string.h>



int main() {

    FILE *file ;
    char letter, contents[100];

    char user_names[100][100], passwords[100][100];

    file = fopen("accounts.txt", "r");  // open the file

    int i = 0,        // letter position variable
        count = 0;    // accounts count

    while(1) {
        letter = fgetc(file);

        if (letter == EOF) {
            break;
        }
        else if (letter == ':') {
            contents[i] = '\0';
            strcpy(user_names[count], contents);
            i = 0;
        }
        else if (letter == ';') {
            contents[i] = '\0';
            strcpy(passwords[count], contents);
            i = 0;
            count++;
        }
        else {
            if (isalpha(letter) || isdigit(letter))
                contents[i++] = letter;
        }

    }

    for(i = 0; i <= count; i++) {
        printf("%s %s\n", user_names[i], passwords[i]);
    }


    fclose(file);

    return 0;
}
