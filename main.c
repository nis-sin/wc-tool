#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

void readStream(FILE* fp, int result[4]);

int main(int argc, char* argv[]){
    // Set locale to the user's default locale
    setlocale(LC_ALL, "");

    int result[4] = {-1, -1, -1, -1};       // size, char, word, sentence counts
    bool cflag = false, wflag = false, lflag = false, mflag = false, fileflag = false;
    FILE* fp = stdin;   // default to stdin
    char* filename;
    int option;

    // Use getopt to parse the command line arguments. Specify a hyphen prefix so that non-option arguments are treated as arguments
    // if non-option arguments are present, getopt returns 1
    while ((option = getopt(argc, argv, "-cwml")) != -1){
        switch (option){
            case 'c':
                cflag = true;
                break;
            case 'w':
                wflag = true;
                break;
            case 'm':
                mflag = true;
                break;
            case 'l':
                lflag = true;
                break;
            case 1:
                fileflag = true;
                filename = optarg;
                break;
            case '?':
                printf("Invalid option\n");
                return -1;
        }
    }

    // check if file argument if given and open the file
    if (fileflag == true){
        fp = fopen(filename, "r");
        if (fp == NULL){
            printf("File not found\n");
            return -1;
        }
    }

    // Default command execution if no options are specified
    if (cflag == false && wflag == false && lflag == false && mflag == false){
        cflag = true;
        wflag = true;
        lflag = true;
    }

    readStream(fp, result);

    if (cflag == true){
        printf("size: %d ", result[0]);
    }
    if (wflag == true){
        printf("word: %d ", result[2]);
    }
    if (lflag == true){
        printf("sentence: %d ", result[3]);
    }
    if (mflag == true){
        printf("char: %d ", result[1]);
    }
    printf("\n");

    return 0;
}


void readStream(FILE* fp, int result[4]){
    /*
    we need to read in wide characters since characters can be multibyte, utf-8 etc. Thus write the program
    to handles wide characters. We will use the wint_t type to store the wide characters.
    */
    wint_t wc;
    char buffer[8];
    bool inWord = false, space = false, inSentence = false;
    long int charCount = 0, wordCount = 0, sentenceCount = 0, size = 0;

    while ((wc = fgetwc(fp)) != WEOF){
        charCount++;
        size += wctomb(buffer, wc);

        space = iswspace(wc);
        if (inWord == true && space == true){
            inWord = false;
        }
        else if (inWord == false && space == false){
            wordCount++;
            inWord = true;
        }

        if (wc == L'\n'){
            sentenceCount++;
        }

    }
    result[0] = size;
    result[1] = charCount;
    result[2] = wordCount;
    result[3] = sentenceCount;
}