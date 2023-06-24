#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
//#include <conio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include "helpheader.h"

void createDirectoryV(char filename[]){
    int checkIfDirExists = mkdir(filename, 0777);
    if(checkIfDirExists==0){
        printf("Directory %s created successfully",filename); printf("\n");
        }
    else{
        printf("Unable to create directory %s",filename); printf("\n");
    }
}
void createDirectory(char filename[]){
    int checkIfDirExists = mkdir(filename, 0777);
    if(checkIfDirExists==0){
        //printf("Directory %s created successfully",filename); printf("\n");
        }
    else{
        printf("Unable to create directory %s",filename); printf("\n");
    }
}

void createDirectoryP(char filename[], char path[]){

    //printf("path is %s\n", path);
    if(chdir(path)==-1){printf("No such file or directory"); printf("\n");return;}

    int checkIfDirExists = mkdir(filename, 0777);
    if(checkIfDirExists==0){
        //printf("Directory %s created successfully",filename); printf("\n");
        }
    else{
        printf("Unable to create directory %s",filename); printf("\n");
    }
}


int main(int argc, char *argv[]){
    
    // printf("Argument passed: %s", argv[1]); printf("\n");
    // printf("Size of argument passed: %lu", strlen(argv[1])); printf("\n");
    // int numberOfWords; calculateNumberOfWordsInString(argv[1],&numberOfWords);
    // printf("Number of words: %d", numberOfWords); printf("\n");

    if(strcmp(argv[1]," ")==0 || strcmp(argv[1],"")==0 || argv[1]==NULL ||  strcmp(argv[1],"\0")==0){
        printf("No directory name provided"); printf("\n");
        return 0;
    }
    char *inputCopy = malloc(100); memset(inputCopy, 0, 100);
    if(argv[2]==NULL){
        //printf("in here\n");
        strcpy(inputCopy, argv[1]);
        printf("(Through fork)\n");
        //printf("input is %s\n", inputCopy);
        //printf("length of input is %lu\n", strlen(inputCopy));
        inputCopy[strlen(inputCopy)]=' ';
        inputCopy[strlen(inputCopy)+1]='\0';
    }
    else{
        int i=4;
        printf("(Through thread)\n");
        // printf("argv[0] is %s\n",argv[0]);
        // printf("argv[1] is %s\n",argv[1]);
        while(argv[i]!=NULL){
            //printf("argv[%d] is %s\n",i, argv[i]);
            strcat(inputCopy, argv[i]);
            strcat(inputCopy, " ");
            i++;
        }
        //inputCopy[strlen(inputCopy)]=' ';
        inputCopy[strlen(inputCopy)]='\0';
        // printf("IN HERE\n");
        // printf("input is %s\n", inputCopy);
        // printf("length of input is %lu\n", strlen(inputCopy));
    }


    //count non blank characters
    int nonBlankCharacters=0;
    for(int i=0; i<strlen(inputCopy); i++){
        if(inputCopy[i]!=' ' && inputCopy[i]!='\0'){
            nonBlankCharacters++;
        }
    }
    if(nonBlankCharacters==0){
        printf("No directory name provided"); printf("\n");
        return 0;
    }


    // printf("Argument passed: %s", argv[1]); printf("\n");
    // printf("Size of argument passed: %lu", strlen(argv[1])); printf("\n");
    //char *dirName = argv[1];

    // inputCopy[strlen(inputCopy)]=' ';
    // inputCopy[strlen(inputCopy)+1]='\0';

    char *stringExceptFirstWord = malloc(100); memset(stringExceptFirstWord, 0, 100);
    calculateStringExceptForFirstWord(inputCopy,stringExceptFirstWord);

    char *firstWord = malloc(100); memset(firstWord, 0, 100);
    calculateFirstWord(inputCopy,firstWord);
    //printf("Input copy: %s", inputCopy); printf("\n");
    //printf("Size of input copy: %lu", strlen(inputCopy)); printf("\n");

    int numberOfWords; 
    calculateNumberOfWordsInString(inputCopy,&numberOfWords);
    // printf("Number of words: %d", numberOfWords); printf("\n");

    // char *firstWord = malloc(100); memset(firstWord, 0, 100);
    // calculateFirstWord(inputCopy,firstWord);
    // int checkIfDirExists = mkdir(firstWord, 0777);
    // if(checkIfDirExists==0){
    //     printf("Directory created successfully"); printf("\n");
    // }
    // else{
    //     printf("Unable to create directory"); printf("\n");
    // }
    // if(strcmp(firstWord,inputCopy)==0){
    //     printf("here");
    //     return 0;
    // }
    if(firstWord[0]=='-'){
        if(strcmp(firstWord,"-v")==0 || strcmp(firstWord,"-p")==0){
        }
        else{
            printf("Invalid option: %s",firstWord); printf("\n");
            exit(1);
        }
        // if(firstWord[1]=='v' || firstWord[1]=='p'){
        // }
        // else{
        //     printf("%s: Invalid option",firstWord); printf("\n");
        //     return 0;
        // }
    }


    //int x=0;
    if(numberOfWords>=1 && strcmp(firstWord,"-v")==0){
        //find words by iterating through argv[1] and finding spaces

        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0'){
                createDirectoryV(word);
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=stringExceptFirstWord[i];
                j++;
            }
        }


    }
    else if(numberOfWords>=1 && strcmp(firstWord,"-p")==0){
        //find words by iterating through argv[1] and finding spaces

        char *word = malloc(100); memset(word, 0, 100);
        char *path = malloc(100); memset(path, 0, 100);
        int j=0; //int k=0;
        //int flag=0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0' || stringExceptFirstWord[i]=='/'){
                //check if directory exist
                DIR *dir = opendir(word);
                if(dir){
                    chdir(word);
                    memset(word, 0, 100); j=0;
                }
                else{
                    createDirectory(word);
                    chdir(word);
                    memset(word, 0, 100); j=0;
                }
                //createDirectory(word);

                //chdir(word);
                // if(flag == 1){
                //     createDirectoryP(word,path);
                //     // path[k] = stringExceptFirstWord[i];
                //     // k++;
                //     //concatenate word to path
                //     printf("Word is %s\n", word);
                //     printf("Word length is %lu\n", strlen(word));
                //     printf("Path is %s\n", path);
                //     printf("Path length is %lu\n", strlen(path));
                //     strcat(path,word);
                //     //concatenate / to path
                //     strcat(path,"/");
                // }
                // if(flag==0){
                //     flag=1;
                //     createDirectory(word);
                //     printf("Word is %s\n", word);
                //     printf("Word length is %lu\n", strlen(word));
                //     printf("Path is %s\n", path);
                //     printf("Path length is %lu\n", strlen(path));
                //     //concatenate word to path
                //     strcat(path,word);
                //     //concatenate / to path
                //     strcat(path,"/");
                // }
                
                //char *word = malloc(100);
                //memset(word, 0, 100); j=0;
            }
            else{

                // path[k] = stringExceptFirstWord[i];
                // k++;
                word[j]=stringExceptFirstWord[i];
                j++;
                
            }
        }


    }
    else{
        //find words by iterating through argv[1] and finding spaces

        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        for(int i=0; i<strlen(inputCopy); i++){
            if(inputCopy[i]==' ' || inputCopy[i]=='\0' || inputCopy[i]=='/'){
                createDirectory(word);
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=inputCopy[i];
                j++;
            }
        }


    }


    return 0;
}
