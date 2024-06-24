#include <stdio.h>
#include <string.h>

long int findSize(char* fileName);
int validFile(char* fileName);
int validCommand(int argc);

int main(int argc, char* argv[]){
    if (validCommand(argc) == 1){
        printf("Invalid command\n");
        return 1;
    }

    if (validFile(argv[2]) == 1){
        printf("Invalid file\n");
        return 1;
    }

    if (strcmp(argv[1], "-c") == 0){
        long int result = findSize(argv[2]);
        printf("Size of file: %ld\n", result);
    }

    return 0;
}

int validCommand(int argc){
    if (argc < 2){
        return 1;
    }
    else {
        return 0;
    }
}

int validFile(char* fileName){
    int fileNameLen = strlen(fileName);
    int extension = fileName[fileNameLen - 4] + fileName[fileNameLen - 3] + fileName[fileNameLen - 2] + fileName[fileNameLen - 1];  // extension = 398 because .txt = 398 in ASCII

    if (extension == 398){
        return 0;
    }
    else {
        return 1;
    }

}

long int findSize(char* fileName){

    FILE* file = fopen(fileName, "r");
    if (file == NULL){
        printf("File not found\n");
        return -1;
    }

    fseek(file, 0, SEEK_END);

    long int size = ftell(file);
    printf("%ld\n", size);

    fclose(file);

    return size;
}
