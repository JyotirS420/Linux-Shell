#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <dirent.h>
#include "helpheader.h"

void removeFile(char filename[]){
    //check if file exists
    int checkIfFileExists = access(filename, F_OK);
    if(checkIfFileExists!=0){printf("%s: No such file or directory",filename);
    printf("\n"); return;}

    checkIfFileExists = remove(filename);
    if(checkIfFileExists==0){
        //printf("File %s removed successfully",filename); 
        //printf("\n");
        }
    else{
        printf("Unable to remove file %s",filename); printf("\n");
    }
}

void removeFileV(char filename[]){
    //check if file exists
    int checkIfFileExists = access(filename, F_OK);
    if(checkIfFileExists!=0){printf("%s: No such file or directory",filename);
    printf("\n"); return;}

    checkIfFileExists = remove(filename);
    if(checkIfFileExists==0){
        printf("File %s removed successfully",filename); 
        printf("\n");
        }
    else{
        printf("Unable to remove file %s",filename); printf("\n");
    }
}



int main(int argc, char *argv[]){

    //remove first character from argv[1]
    // char *input = malloc(100);
    // int i=0;
    // while(argv[1][i]!='\0'){
    //     input[i]=argv[1][i+1];
    //     i++;
    // };

    argv[1][strlen(argv[1])]=' ';
    argv[1][strlen(argv[1])+1]='\0';

    char *input = malloc(100);
    if(argv[2]==NULL){
        //printf("in here\n");
        printf("(Through fork)\n");
        strcpy(input, argv[1]);
        //printf("input is %s\n", input);
        //printf("length of input is %lu\n", strlen(input));
    }
    else{
        int i=4;
        // printf("argv[0] is %s\n",argv[0]);
        // printf("argv[1] is %s\n",argv[1]);
        printf("(Through thread)\n");
        while(argv[i]!=NULL){
            // printf("argv[%d] is %s\n",i, argv[i]);
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
    
    char *firstWord = malloc(100);
    calculateFirstWord(input,firstWord);
    // printf("First word: %s", firstWord); printf("\n");
    // printf("Length of firstWord: %lu", strlen(firstWord)); printf("\n");
    //count number of words in input
    int numberOfWords=0;
    calculateNumberOfWordsInString(input, &numberOfWords);
    // printf("Number of words: %d", numberOfWords); printf("\n");

    // if(strcmp(firstWord," ")==0 || strcmp(firstWord,"")==0 || firstWord==NULL || strcmp(firstWord,"rm")==0 || strcmp(firstWord,"\0")==0){
    //     printf("No file name provided"); printf("\n");
    //     return 0;
    // }
    //count non blank characters
    int nonBlankCharacters=0;
    for(int i=0; i<strlen(input); i++){
        if(input[i]!=' ' && input[i]!='\0'){
            nonBlankCharacters++;
        }
    }
    if(nonBlankCharacters==0){
        printf("No file name provided"); printf("\n");
        return 0;
    }

    //inputCopy
    char *inputCopy = malloc(100);
    //find string except first word
    
    if(firstWord[0]=='-'){
        if(strcmp(firstWord,"-i")==0 || strcmp(firstWord,"-v")==0){
        }
        else{
            printf("Invalid option: %s",firstWord); printf("\n");
            exit(1);
        }
        // if(firstWord[1]=='i' || firstWord[1]=='v'){

        // }
        // else{
        //     printf("%s: Invalid flag", firstWord); printf("\n");
        //     return 0;
        // }
    }


    if(strcmp(firstWord,"-i")==0){
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        //set input copy to string except first word
        calculateStringExceptForFirstWord(input, inputCopy);
        for(int i=0; i<strlen(inputCopy); i++){
            if(inputCopy[i]==' ' || inputCopy[i]=='\0'){
                int checkIfFileExists = access(word, F_OK);
                if(checkIfFileExists!=0){
                    printf("%s: No such file or directory",word); printf("\n"); 
                    memset(word, 0, 100); j=0; 
                    continue;
                }
                DIR *dir = opendir(word);
                if(dir){
                    printf("rm: %s: is a directory", word); printf("\n");
                    closedir(dir);
                    memset(word, 0, 100); j=0; 
                    continue;
                }

                printf("remove file \'%s\'? ", word); char *answer = malloc(100); scanf("%s", answer);
                if(strcmp(answer,"y")==0 || strcmp(answer,"Y")==0){
                    removeFile(word);
                }
                //char *word = malloc(100);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=inputCopy[i];
                j++;
            }
        }
        return 0;
    }

    if(strcmp(firstWord,"-v")==0){
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        //set input copy to string except first word
        calculateStringExceptForFirstWord(input, inputCopy);
        for(int i=0; i<strlen(inputCopy); i++){
            if(inputCopy[i]==' ' || inputCopy[i]=='\0'){
                int checkIfFileExists = access(word, F_OK);
                if(checkIfFileExists!=0){
                    printf("%s: No such file or directory", word); printf("\n"); 
                    memset(word, 0, 100); j=0; 
                    continue;
                }
                DIR *dir = opendir(word);
                if(dir){
                    printf("rm: %s: is a directory", word); printf("\n");
                    closedir(dir);
                    memset(word, 0, 100); j=0; 
                    continue;
                }
                
                removeFileV(word);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=inputCopy[i];
                j++;
            }
        }
        return 0;
    }

    else{
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        //set input copy to string except first word
        //calculateStringExceptForFirstWord(input, inputCopy);

        strcpy(inputCopy, input);
        for(int i=0; i<strlen(inputCopy); i++){
            if(inputCopy[i]==' ' || inputCopy[i]=='\0'){
                int checkIfFileExists = access(word, F_OK);
                if(checkIfFileExists!=0){
                    printf("%s: No such file or directory",word); printf("\n"); 
                    memset(word, 0, 100); j=0; 
                    continue;
                }
                DIR *dir = opendir(word);
                if(dir){
                    printf("rm: %s: is a directory", word); printf("\n");
                    closedir(dir);
                    memset(word, 0, 100); j=0; 
                    continue;
                }
                removeFile(word);
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=inputCopy[i];
                j++;
            }
        }
        return 0;
    }

    // if(strcmp(firstWord,"-r")==0){
    //     char *word = malloc(100); memset(word, 0, 100);
    //     int j=0;
    //     for(int i=0; i<strlen(inputCopy); i++){
    //         if(inputCopy[i]==' ' || inputCopy[i]=='\0'){
    //             printf("remove file \'%s\'?", word); char *answer = malloc(100); scanf("%s", answer);
    //             if(strcmp(answer,"y")==0 || strcmp(answer,"Y")==0){
    //                 removeFile(word);
    //             }
    //             //char *word = malloc(100);
    //             memset(word, 0, 100); j=0;
    //         }
    //         else{
    //             word[j]=inputCopy[i];
    //             j++;
    //         }
    //     }
    //     return 0;
    // }



    //find words by iterating through argv[1] and finding spaces
    // char *word = malloc(100); memset(word, 0, 100);
    // int j=0;
    // for(int i=0; i<strlen(inputCopy); i++){
    //     if(inputCopy[i]==' ' || inputCopy[i]=='\0'){
    //         removeFile(word);
    //         //char *word = malloc(100);
    //         memset(word, 0, 100); j=0;
    //     }
    //     else{
    //         word[j]=inputCopy[i];
    //         j++;
    //     }
    // }







    return 0;
}
