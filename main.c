#include <stdio.h>
#include <stdbool.h>
#include <string.h>

long int findSize(char* fileName);
long int getNumLines(char* fileName);
long int getNumWords(char* fileName);
long int getNumChars(char* fileName);
bool validFile(char* fileName);
bool validCommand(int argc, char* argv[]);

int main(int argc, char* argv[]){
    if (validCommand(argc, argv) == false){
        printf("test\n");
        return 1;
    }
    if (validFile(argv[argc-1]) == false){
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0){
        long int result = findSize(argv[2]);
        printf("%ld %s", result, argv[2]);
    }

    if (strcmp(argv[1], "-l") == 0){
        long int result = getNumLines(argv[2]);
        printf("%ld %s", result, argv[2]);
    }

    if (strcmp(argv[1], "-w") == 0){
        long int result = getNumWords(argv[2]);
        printf("%ld %s", result, argv[2]);
    }

    if (strcmp(argv[1], "-m") == 0){
        long int result = getNumChars(argv[2]);
        printf("%ld %s", result, argv[2]);
    }

    return 0;
}


long int getNumChars(char* fileName){
    FILE* file = fopen(fileName, "r");

    if (file == NULL){
        printf("File not found\n");
        return -1;
    }

    long int size = findSize(fileName);
    char fileData[size+1];

    size_t characters = fread(fileData, 1, size, file);
    
    if (ferror(file)){
        printf("Error reading file\n");
        fclose(file);
        return -1;
    }

    fclose(file);
    return characters;
}

long int getNumWords(char* fileName){
    FILE* file = fopen(fileName, "r");

    if (file == NULL){
        printf("File not found\n");
        return -1;
    }

    int inWord = 0;
    int c;
    long unsigned int count = 0;

    while ((c = fgetc(file)) != EOF){
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

    if (ferror(file)){
        printf("Error reading file\n");
        fclose(file);
        return -1;
    }

    fclose(file);

    return count;

}


long int getNumLines(char* fileName){
    FILE* file = fopen(fileName, "r");

    if (file == NULL){
        printf("File not found\n");
        return -1;
    }

    long int size = findSize(fileName);
    long int count = 0;
    char fileData[size+1];

    while (fgets(fileData, size+1, file) != NULL){      // use getline from glibc instead of fgets but I can't get it working
        count++;
    }

    if (ferror(file)){
        printf("Error reading file\n");
        fclose(file);
        return -1;
    }

    fclose(file);

    return count;
}


long int findSize(char* fileName){

    FILE* file = fopen(fileName, "r");
    if (file == NULL){
        printf("File not found\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);

    long int size = ftell(file);

    fclose(file);

    return size;
}


bool validCommand(int argc, char* argv[]){
    // check if the number of arguments is valid
    if (!(argc >= 1 && argc <= 4)){
        printf("Invalid command\n");
        return false;
    }

    char* seen[] = {};
    
    // check if the options are valid and not repeated
    for (int i = 1; i < (argc-1); i++){
        int seenLen = sizeof(seen)/sizeof(seen[0]);
        for (int j = seenLen-1; j > -1; j--){
            if ((strcmp(argv[i], seen[j]) == 0) && (
                (strcmp(argv[i], "-c") != 0) ||
                (strcmp(argv[i], "-l") != 0) ||
                (strcmp(argv[i], "-w") != 0) ||
                (strcmp(argv[i], "-m") != 0))){
                    printf("Invalid command\n");
                    return false;
            }
            seen[j] = argv[i];
        }
    }

    return true;
}

bool validFile(char* fileName){
    int fileNameLen = strlen(fileName);
    
    // check if a file was provided
    if (fileNameLen < 5){
        printf("Invalid file\n");
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
        printf("Invalid file\n");
        return false;
    }

    return true;
}