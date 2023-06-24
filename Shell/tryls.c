#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "helpheader.h"

#define GREEN  "\x1B[32m"
#define BLUE  "\x1B[34m"

int lsCommand(char *path);
int lsaCommand(char *path);

int lsCommand(char *path){

    DIR *folder;
    struct dirent *entry;
    //set entry to not null
    //entry = malloc(sizeof(struct dirent));
    //entry->d_name = malloc(100);
    int numberOfFiles = 0;

    folder = opendir(path);

    if(folder == NULL)
    {
        printf("%s: Unable to open directory",path); printf("\n");
        return 1;
    }
    //printf("%s:\n", path);
    //printf("Length of path: %lu\n", strlen(path));

    printf("%s:\n", path);
    entry=readdir(folder);

    while( (entry!=NULL) )
    {
        
        if(entry == NULL){break;}

        // || entry->d_type == DT_DIR
        if(entry->d_type == DT_REG) { // If the entry is a regular file
            numberOfFiles++;
            printf("File %d: %s\n", numberOfFiles, entry->d_name);
            //printf("File %d: %s%s\n", numberOfFiles,BLUE, entry->d_name);
        }
        entry=readdir(folder);
    }

    closedir(folder);
    return 0;

}

int lsrCommand(char *path){

    DIR *folder;
    struct dirent *entry;
    int numberOfFiles = 0;

    folder = opendir(path);

    if(folder == NULL)
    {
        printf("%s: Unable to open directory",path); printf("\n");
        return 1;
    }
    printf("%s:\n", path);
    entry=readdir(folder);

    //char *bigString = (char *)malloc(1000*sizeof(char));
    char ** stringArray = (char **)malloc(1000*sizeof(char *));
    //char *filenumber = (char *)malloc(100*sizeof(char));
    while( (entry!=NULL) )
    {
        
        if(entry == NULL){break;}

        // || entry->d_type == DT_DIR
        if(entry->d_type == DT_REG) { // If the entry is a regular file
            numberOfFiles++;
            stringArray[numberOfFiles-1] = entry->d_name;
            //add newline to string Array
            //clear bigString
            //memset(bigString, 0, 1000);
            //printf("File %d: %s\n", numberOfFiles, entry->d_name);
            //printf("File %d: %s%s\n", numberOfFiles,BLUE, entry->d_name);
        }
        entry=readdir(folder);
    }
    //print out stringArray backwards
    for(int i=numberOfFiles-1; i>=0; i--){
        int number = i - numberOfFiles;
        printf("File %d: %s\n", number,stringArray[i]);
    }
    //printf("%s\n", bigString);

    closedir(folder);
    return 0;

}

int lsaCommand(char *path){

    DIR *folder;
    struct dirent *entry;
    int numberOfFiles = 0;

    folder = opendir(path);

    if(folder == NULL)
    {
        printf("%s: Unable to open directory",path); printf("\n");
        return 1;
    }
    printf("%s:\n", path);
    entry = readdir(folder);
    while( (entry!=NULL) )
    {
        
        if(entry == NULL){break;}

        numberOfFiles++;
        printf("File %d: %s\n", numberOfFiles, entry->d_name);
        entry=readdir(folder);
        
    }

    closedir(folder);
    return 0;
    
}


int main(int argc, char *argv[])
{
    // DIR *folder;
    // struct dirent *entry;
    // int numberOfFiles = 0;

    //add a blank space and a null character to the end of the string
    //argv[1][strlen(argv[1])]=' ';
    //argv[1][strlen(argv[1])+1]='\0';

    ///Users/jyotir/C++ Programs
    char *input = malloc(100); memset(input, 0, 100);
    
    //strcpy(input, argv[1]);
    //add a blank space and a null character to the end of the string
    // input[strlen(input)]=' ';
    // input[strlen(input)+1]='\0';

    if(argv[2]==NULL){
        // printf("in here\n");
        printf("(Through fork)\n");
        strcpy(input, argv[1]);
        // printf("input is %s\n", input);
        // printf("length of input is %lu\n", strlen(input));
        input[strlen(input)]=' ';
        input[strlen(input)+1]='\0';
    }
    else{
        int i=4;
        printf("(Through thread)\n");
        // printf("argv[0] is %s\n",argv[0]);
        // printf("argv[1] is %s\n",argv[1]);
        while(argv[i]!=NULL){
            //printf("argv[%d] is %s\n",i, argv[i]);
            strcat(input, argv[i]);
            strcat(input, " ");
            i++;
        }
        //input[strlen(input)]=' ';
        input[strlen(input)]='\0';
        // printf("IN HERE\n");
        // printf("input is %s\n", input);
        // printf("length of input is %lu\n", strlen(input));
    }



    char *firstWord; firstWord = malloc(100); memset(firstWord, 0, 100);
    calculateFirstWord(input,firstWord);
    char *stringExceptFirstWord; stringExceptFirstWord = malloc(100); memset(stringExceptFirstWord, 0, 100);
    calculateStringExceptForFirstWord(input,stringExceptFirstWord);
    //char *newStringExceptFirstWord; newStringExceptFirstWord = malloc(100); memset(newStringExceptFirstWord, 0, 100);
    //remove first character from stringExceptFirstWord
    // int i;
    // for(i=0;i<strlen(stringExceptFirstWord);i++){
    //     newStringExceptFirstWord[i] = stringExceptFirstWord[i+1];
    // }
    // newStringExceptFirstWord[strlen(stringExceptFirstWord)-1] = '\0';
    // //copy newStringExceptFirstWord to stringExceptFirstWord
    // memset(stringExceptFirstWord, 0, 100);
    // strcpy(stringExceptFirstWord, newStringExceptFirstWord);
    
    //folder = opendir(argv[1]);

    if(strcmp(input,"\0")==0 || input==NULL || strcmp(input," ")==0){
        lsCommand(".");
        exit(1);
    }

    //second word
    // char *secondWord=malloc(100);
    // secondWord = argv[2];
    // //printf("Second word: %s",secondWord); printf("\n");
    if(firstWord[0]=='-'){
        if(strcmp(firstWord,"-a")==0 || strcmp(firstWord,"-r")==0){

        }
        else{
            printf("Invalid option: %s",firstWord); printf("\n");
            exit(1);
        }
        // if(firstWord[1]!='a' && firstWord[1]!='r'){
        //     printf("%s: Invalid command\n", firstWord);
        //     return 0;
        // }
    }

    if(strcmp(input,"-a")==0 || strcmp(input,"-a ")==0){
        lsaCommand(".");
        exit(1);
    }
    if(strcmp(input,"-r")==0 || strcmp(input,"-r ")==0){
        lsrCommand(".");
        exit(1);
    }

    char *currentWorkingDirectory = malloc(100); memset(currentWorkingDirectory, 0, 100);
    getcwd(currentWorkingDirectory, 100);


    if(strcmp(firstWord,"-a")==0){
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0'){
                // word[j]=' ';
                // word[j+1]='\0';
                lsaCommand(word);
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=stringExceptFirstWord[i];
                j++;
            }
        }
    }
    else if(strcmp(firstWord,"-r")==0){
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        int slashcounter = 0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(input[i]=='/'){slashcounter++;}
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0'){
                // chdir(word);
                // printf("%s:\n", word);
                // lsrCommand(".");
                // // while(slashcounter>=0){
                // //     chdir("..");
                // //     slashcounter--;
                // // }
                // //char *word = malloc(100);
                // chdir(currentWorkingDirectory);
                // memset(word, 0, 100); j=0;

                lsrCommand(word);
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=stringExceptFirstWord[i];
                j++;
            }
        }
    }
    else{
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        int slashcounter = 0;
        for(int i=0; i<strlen(input); i++){
            if(input[i]=='/'){slashcounter++;}
            if(input[i]==' ' || input[i]=='\0'){
                //word[j]=' ';
                //word[j+1]='\0';
                // if(chdir(word)!=0){
                //     printf("%s: Invalid location\n", word);
                //     slashcounter--;
                // }
                // else{
                //     printf("%s:\n", word);
                //     lsCommand(".");
                // }
                // // while(slashcounter>0){
                // //     chdir("..");
                // //     slashcounter--;
                // // }
                // //char *word = malloc(100);
                // chdir(currentWorkingDirectory);
                // memset(word, 0, 100); j=0;



                lsCommand(word);
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=input[i];
                j++;
            }
        }
    }

    // if(folder == NULL)
    // {
    //     perror("Unable to read directory");
    //     return(1);
    // }

    // if(strcmp(secondWord,"-a")==0){
    //     lsaCommand(argv[1]);
    // }
    // else if(strcmp(secondWord,"-r")==0){
    //     lsrCommand(argv[1]);
    // }
    // else{
    //     lsCommand(argv[1]);
    // }

    // if(folder == NULL)
    // {
    //     perror("Unable to read directory");
    //     return(1);
    // }

    // while( (entry!=NULL) )
    // {
    //     entry=readdir(folder);
    //     if(entry == NULL){break;}

    //     if(entry->d_type == DT_REG) { // If the entry is a regular file
    //         numberOfFiles++;
    //         printf("File %d: %s\n", numberOfFiles, entry->d_name);
    //     }
    // }
    //closedir(folder);

    return 0;
}
