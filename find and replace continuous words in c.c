#include <stdio.h>
#include <string.h>

char STR[1000], split_string[999][999], PAT[100], REP[100], TEMP[1000], puncts[1000];   // declare all the strings


// function to remove punctuations from string

void remove_punct(char* string) {

    for (int i = 0; string[i] != '\0'; i++) {
        if (ispunct(string[i])) string[i] = ' ';
    }

}


// function to split string into different words (will treat punctuations as letters)

int string_split(char* string) {

    int i = 0, word_count = 0, k = 0, punct_count = 0, new_word;

    while (string[i] == ' ') i++;   // remove spaces in beginning

    for ( ; string[i] != '\0'; i++) {      // i = i

        new_word = 0;

        if (string[i] != ' ') {                    
            if (ispunct(string[i]) || isdigit(string[i])) {
                puncts[word_count] = string[i];
                new_word = 1;
            }
            else {
                split_string[word_count][k] = tolower(string[i]);
                k++;
            }

        }
        else {
            if (string[i + 1] != ' ') {
                puncts[word_count] = ' ';

                new_word = 1;
            }
        }

        if (new_word) {
            split_string[word_count][k] = '\0';
            word_count++;
            k = 0;
        }

    }

    if (split_string[word_count - 1] == ' ') word_count--;

    return word_count + 1;          // function will return the number of words in the string

}


// function to combine words into a string

void combine_string(int word_count) {

    int i, j, k = 0, new_word = 1;

    for (i = 0; i < word_count; i++) {        // each word of string

        if (split_string[0] == ' ') {
            TEMP[k] = puncts[i];
        }

        for (j = 0; split_string[i][j] != '\0'; j++) {     // each letter of word

            if (new_word) {
                TEMP[k] = toupper(split_string[i][j]);
                new_word = 0;
            }
            else {
                TEMP[k] = split_string[i][j];
            }

            k++;
        }

        if (puncts[i] == '!' || puncts[i] == '.' || puncts[i] == '?') {
            new_word = 1;
        }

        TEMP[k] = puncts[i];
        k++;

    }

}


// function to replace words of string with another word of choice

void string_replace(char* STR, char* PAT, char* REP) {

    //Abhay is great! 34Abhay12 is 19 years old. "Abhay" loves coffee, abhay hates noise. JSS is abhay's college.

    int word_count = string_split(STR);    // split the string into words

    int i, rep_count = 0, same;

    // perform word replacement:

    for(i = 0; i < word_count; i++) {        // each word

            int word_len = strlen(split_string[i]);  // length of word

            int pat_len = strlen(PAT);               // length of pattern

            int rep_len = strlen(REP);               // length of replacement

            int same_count = 0, j, j_temp = 0, k = 0;

            for (j = 0; j < word_len; j++) {    // each letter

                if (split_string[i][j] == PAT[k]) {
                    same_count++;
                    k++;
                }
                else {
                    same_count = k = 0;
                }

                if (same_count == pat_len) {

                    j_temp = j;

                    int diff;    // the difference between lengths of replacement and pattern

                    if (rep_len > pat_len) {          // if replacement is longer than the pattern
                                                          
                        diff = rep_len - pat_len;

                        // replace all the letters till length of pattern is reached

                        for (j = j - pat_len + 1, k = 0; k < pat_len; j++, k++) {
                            split_string[i][j] = REP[k];
                        }

                        // now, we insert the remaining letters of replacement while shifting the other letters of the word to the right

                        for ( ; k < rep_len; j++, k++) {     // j = j
                            split_string[i][j + diff] = split_string[i][j];
                            split_string[i][j] = REP[k];
                        }

                        j = j_temp + diff;

                    }
                    else if (rep_len < pat_len){                           // if replacement is shorter than the pattern

                        diff = pat_len - rep_len;

                        // replace all the letters till length of pattern is reached

                        for (j = j - pat_len + 1, k = 0; k < rep_len; j++, k++) {
                            split_string[i][j] = REP[k];
                        }

                        // now, we shift the other letters of the word to the left

                        for ( ; j < word_len; j++, k++) {     // j = j
                            split_string[i][j] = split_string[i][j + diff];
                        }

                        split_string[i][j] = ' ';
                        j = j_temp - diff;

                    }
                    else {
                        // replace all the letters till length of pattern is reached

                        for (j = j - pat_len + 1, k = 0; k < rep_len; j++, k++) {
                            split_string[i][j] = REP[k];
                        }

                        j = j_temp;

                    }

                    rep_count++;            // count no. of replacements made
                    same_count = k = 0;     // reset scanning variables

                }

            }

         split_string[i][j] = '\0';

    }

    combine_string(word_count);      // recombine the words into one string

    strcpy(STR, TEMP);       // assign value to old string

    printf("\n%d words replaced.\n", rep_count);

}

int main() {

    printf("Enter the main string: \n");
    scanf("%[^\n]%*c", STR);

    int i = 0, word_count = string_split(STR);

    // Abhay is great! 34Abhay12 is 19 years old. "Abhay" loves coffee, abhay hates noise. JSS is abhay's college.

    printf("\nEnter the string to replace: \n");
    scanf("%[^\n]%*c", PAT);

    // Jack Miller

    printf("\nEnter the replacement string: \n");
    scanf("%[^\n]%*c", REP);

    string_replace(STR, PAT, REP);

    printf("\nString has been updated: \n%s\n", STR);

    return 0;
}
