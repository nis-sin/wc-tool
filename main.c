#include <stdio.h>
#include <stdbool.h>
#include <string.h>

long int findSize(FILE* fp);
long int getNumLines(FILE* fp);
long int getNumWords(FILE* fp);
long int getNumChars(FILE* fp);
bool checkFile(char* fileName);
bool checkOption(int argc, char* argv[]);

int main(int argc, char* argv[]){

    if (argc > 3 || argc < 2){
        printf("Invalid command\n");
        return 1;
    }

    bool fileProvided = false;
    FILE* fp;
    if (checkFile(argv[argc-1]) == true){
        printf("File provided\n");
        fp = fopen(argv[argc-1], "r");
        fileProvided = true;
    }
    else {
        fp = stdin;
    }

    if (fp == NULL){
        printf("File not found\n");
        return -1;
    }

    if (checkOption(argc, argv) == false){
        printf("Invalid command\n");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0){
        long int result = findSize(fp);
        printf("%ld %s", result, argv[2]);
    }

    else if (strcmp(argv[1], "-l") == 0){
        long int result = getNumLines(fp);
        printf("%ld %s", result, argv[2]);
    }

    else if (strcmp(argv[1], "-w") == 0){
        long int result = getNumWords(fp);
        printf("%ld %s", result, argv[2]);
    }

    else if (strcmp(argv[1], "-m") == 0){
        long int result = getNumChars(fp);
        printf("%ld %s", result, argv[2]);
    }

    fclose(fp);
    return 0;
}


long int getNumChars(FILE* fp){

    long int size = findSize(fp);
    char fileData[size+1];

    fseek(fp, 0, SEEK_SET); // set the file pointer to the beginning of the file
    size_t characters = fread(fileData, 1, size, fp);
    
    if (ferror(fp)){
        printf("Error reading file\n");
        return -1;
    }

    return characters;
}

long int getNumWords(FILE* fp){

    int inWord = 0;
    int c;
    long unsigned int count = 0;

    while ((c = fgetc(fp)) != EOF){
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
            if (inWord == 0){
                inWord = 1;
                count++;
            }
        }
        else {
            inWord = 0;
        }
    }

    if (ferror(fp)){
        printf("Error reading file\n");
        return -1;
    }

    return count;
}


long int getNumLines(FILE* fp){

    long int size = findSize(fp);
    long int count = 0;
    char fileData[size+1];

    fseek(fp, 0, SEEK_SET); // set the file pointer to the beginning of the file
    while (fgets(fileData, size+1, fp) != NULL){      // use getline from glibc instead of fgets but I can't get it working
        count++;
    }

    if (ferror(fp)){
        printf("Error reading file\n");
        return -1;
    }

    return count;
}


long int findSize(FILE* fp){

    fseek(fp, 0, SEEK_END);

    long int size = ftell(fp);

    return size;
}


bool checkOption(int argc, char* argv[]){

    char* options[] = {"-c", "-l", "-w", "-m"};
    for (int i = 0; i < 4; i++){
        if (strcmp(argv[1], options[i]) == 0){
            return true;
        }
    }

    return false;
}

bool checkFile(char* fileName){
    int fileNameLen = strlen(fileName);
    
    // check if a file was provided
    if (fileNameLen < 5){
        return false;
    }
    // retrieve the extension of the file
    char extension[5];
    extension[0] = (char) fileName[fileNameLen - 4];
    extension[1] = (char) fileName[fileNameLen - 3];
    extension[2] = (char) fileName[fileNameLen - 2];
    extension[3] = (char) fileName[fileNameLen - 1];

    // check if the file is a .txt file
    if (strncmp(extension, ".txt", 4) != 0){
        return false;
    }

    return true;
}