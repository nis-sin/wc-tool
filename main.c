#include <stdio.h>
#include <string.h>

long int findSize(char* fileName);
long int getNumLines(char* fileName);
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

    if (strcmp(argv[1], "-l") == 0){
        long int result = getNumLines(argv[2]);
        printf("Number of lines: %ld\n", result);
    }

    return 0;
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
    // retrieve the extension of the file
    char extension[5];
    extension[0] = (char) fileName[fileNameLen - 4];
    extension[1] = (char) fileName[fileNameLen - 3];
    extension[2] = (char) fileName[fileNameLen - 2];
    extension[3] = (char) fileName[fileNameLen - 1];

    if (strcmp(extension,".txt") == 0){
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

    fclose(file);

    return size;
}
