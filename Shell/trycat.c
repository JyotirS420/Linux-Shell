#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "helpheader.h"


void catFile(char *path){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(path, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    printf("%s: \n", path);

    while ((read = getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }

    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);
}


void printfile(char *filename){

    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("%s: File not found.",filename); printf("\n");
        return;
    }
    printf("%s: \n", filename);
    char c;
    while((c = fgetc(fp)) != EOF){
        printf("%c", c);
    }
    printf("\n");
    fclose(fp);

}


void catFilen(char *path){
    
    FILE *fp;
    fp = fopen(path, "r");
    if(fp == NULL){
        printf("%s: File not found.",path); printf("\n");
        return;
    }
    printf("%s: \n", path);
    char c;
    int lineCounter=1;
    printf("%d ", lineCounter); lineCounter++; 
    while((c = fgetc(fp)) != EOF){
        if(c=='\n'){
            printf("\n%d ", lineCounter);
            lineCounter++;
            continue;
        }
        printf("%c", c);
    }
    printf("\n");
    fclose(fp);
    return;
}

void catFilee(char *path){
    //print $ at the end of each line
    FILE *fp;
    fp = fopen(path, "r");
    if(fp == NULL){
        printf("%s: File not found.",path); printf("\n");
        return;
    }
    printf("%s: \n", path);
    char c;
    //int lineCounter=1;
    //printf("%d ", lineCounter); lineCounter++;
    while((c = fgetc(fp)) != EOF){
        if(c=='\n'){
            printf("$\n");
            //printf("$\n%d ", lineCounter);
            //lineCounter++;
            continue;
        }
        printf("%c", c);
    }
    printf("$\n");
    fclose(fp);
    return ;

}



int main(int argc, char *argv[]){

    //printf("%s", argv[1]); printf("\n"); //printf("\n");
    FILE *fp;

    char *inputCopy = malloc(100); memset(inputCopy, 0, 100);
    if(argv[2]==NULL){
        //printf("in here\n");
        printf("(Through fork)\n");
        strcpy(inputCopy, argv[1]);
        // printf("input is %s\n", inputCopy);
        // printf("length of input is %lu\n", strlen(inputCopy));
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
        //input[strlen(input)]=' ';
        inputCopy[strlen(inputCopy)]='\0';
        // printf("IN HERE\n");
        // printf("input is %s\n", inputCopy);
        // printf("length of input is %lu\n", strlen(inputCopy));
    }



    // strcpy(inputCopy, argv[1]);
    // inputCopy[strlen(inputCopy)]=' ';
    // inputCopy[strlen(inputCopy)+1]='\0';

    int numberOfWords;
    //printf("Number of words: %d", numberOfWords); printf("\n");
    calculateNumberOfWordsInString(inputCopy, &numberOfWords);
    // numberOfWords=2;
    // if(numberOfWords==1){
    //     fp = fopen(inputCopy, "r");
    //     if(fp == NULL){
    //         printf("File not found."); printf("\n");
    //         return 0;
    //     }
    //     char c;
    //     while((c = fgetc(fp)) != EOF){
    //         printf("%c", c);
    //     }
    //     fclose(fp);
    //     return 0;
    // }



    char *firstWord = malloc(100); memset(firstWord, 0, 100);
    calculateFirstWord(inputCopy,firstWord);
    //add '\0' to the end of the string firstWord
    //add a blank space to beginning of string newfirstWord and then copy firstWord
    // char *newfirstWord = malloc(100); memset(newfirstWord, 0, 100);
    // newfirstWord[0]=' ';
    // strcat(newfirstWord,firstWord);
    // if(strcmp(newfirstWord,inputCopy)==0){
    //     printf("here");
    // }



    char *secondWord = malloc(100); memset(secondWord, 0, 100);
    calculateSecondWord(inputCopy,secondWord);


    char *stringExceptFirstWord = malloc(100); memset(stringExceptFirstWord, 0, 100);
    //copy first word into stringExceptFirstWord
    strcpy(stringExceptFirstWord,inputCopy);
    //calculate stringExceptFirstWord
    calculateStringExceptForFirstWord(inputCopy,stringExceptFirstWord);

    //printf("Here is: %s", firstWord); printf("\n"); printf("Lenght of first word: %lu", strlen(firstWord)); printf("\n");
    //printf("Here is: %s", inputCopy); printf("\n"); printf("Lenght of inputCopy: %lu", strlen(inputCopy)); printf("\n");
    //printf("Here is: %s", secondWord); printf("\n"); printf("Lenght of second word: %lu", strlen(secondWord)); printf("\n");


    //strcmp(secondWord,"Studio")==0 || 
    // if(strcmp(firstWord,"Studio")==0){
    //     printf("File not specified"); printf("\n");
    //     return 0;
    // }
    
    if(firstWord[0]=='-'){
        if(strcmp(firstWord,"-n")==0 || strcmp(firstWord,"-e")==0){
        }
        else{
            printf("Invalid option: %s",firstWord); printf("\n");
            exit(1);
        }
        // if(firstWord[1]=='n' || firstWord[1]=='e'){

        // }
        // else{
        //     printf("%s: Invalid flag",firstWord); printf("\n");
        //     return 0;
        // }
    }
    int nonBlankCharacters=0;
    for(int i=0; i<strlen(inputCopy); i++){
        if(inputCopy[i]!=' ' && inputCopy[i]!='\0'){
            nonBlankCharacters++;
        }
    }
    if(nonBlankCharacters==0){
        printf("No file name provided"); printf("\n");
        return 0;
    }

    char *currentWorkingDirectory = malloc(100); memset(currentWorkingDirectory, 0, 100);
    getcwd(currentWorkingDirectory, 100);

    //if(strcmp(firstWord,inputCopy)==0){
    if(strcmp(firstWord,"-n")!=0 && strcmp(firstWord,"-e")!=0){
        // char *firstWord = malloc(100); memset(firstWord, 0, 100);
        // calculateFirstWord(inputCopy,firstWord);
        // char *stringExceptFirstWord = malloc(100); memset(stringExceptFirstWord, 0, 100);
        // calculateStringExceptFirstWord(inputCopy,stringExceptFirstWord);
        // //set inputCopy equal to stringExceptFirstWord
        // char *inputCopy = malloc(100); memset(inputCopy, 0, 100);
        // strcpy(inputCopy, stringExceptFirstWord);
        // calculateNumberOfWordsInString(inputCopy, &numberOfWords);

        // printf("In here\n");
        // char *firstWord = malloc(100); memset(firstWord, 0, 100);
        // calculateFirstWord(stringExceptFirstWord,firstWord);
        // calculateNumberOfWordsInString(stringExceptFirstWord, &numberOfWords);
        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        int slashcounter = 0;
        for(int i=0; i<strlen(inputCopy); i++){
            
            if(inputCopy[i]=='/'){slashcounter++;}
            if(inputCopy[i]==' ' || inputCopy[i]=='\0' || inputCopy[i]=='/'){


                //int checkIfFileExists = access(word, F_OK);
                // if(checkIfFileExists!=0){
                //     printf("%s: No such file or directory", word); printf("\n"); 
                //     memset(word, 0, 100); j=0; 
                //     continue;
                // }
                if(chdir(word)!=0){
                    // printf("inside this if\n");
                    // printf("%s: is the file", word); printf("\n");
                    
                    printfile(word);
                    memset(word, 0, 100); j=0; 
                    //continue;
                }

                //printf("In here too\n");
                
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=inputCopy[i];
                j++;
            }
            if(inputCopy[i]==' '){
                // while(slashcounter>0){
                //     chdir("..");
                //     slashcounter--;
                // }
                chdir(currentWorkingDirectory);
            }
        }


    }
    else if(strcmp(firstWord,"-n")==0){
        // fp = fopen(secondWord, "r");
        // if(fp == NULL){
        //     printf("File not found."); printf("\n");
        //     return 0;
        // }
        // char c;
        // int lineCounter=1;
        // printf("%d ", lineCounter); lineCounter++; 
        // while((c = fgetc(fp)) != EOF){
        //     if(c=='\n'){
        //         printf("\n%d ", lineCounter);
        //         lineCounter++;
        //         continue;
        //     }
        //     printf("%c", c);
        // }
        // printf("\n");
        // fclose(fp);
        // return 0;
        //printf("In here\n");

        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        int slashcounter = 0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(inputCopy[i]=='/'){slashcounter++;}
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0'){
                if(chdir(word)!=0){
                    catFilen(word);
                    memset(word, 0, 100); j=0; 
                    //continue;
                }
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=stringExceptFirstWord[i];
                j++;
            }
            if(inputCopy[i]==' '){
                // while(slashcounter>0){
                //     chdir("..");
                //     slashcounter--;
                // }
                chdir(currentWorkingDirectory);
            }
        }
    }

    else if(strcmp(firstWord,"-e")==0){
        // //print $ at the end of each line
        // fp = fopen(secondWord, "r");
        // if(fp == NULL){
        //     printf("File not found."); printf("\n");
        //     return 0;
        // }
        // char c;
        // //int lineCounter=1;
        // //printf("%d ", lineCounter); lineCounter++;
        // while((c = fgetc(fp)) != EOF){
        //     if(c=='\n'){
        //         printf("$\n");
        //         //printf("$\n%d ", lineCounter);
        //         //lineCounter++;
        //         continue;
        //     }
        //     printf("%c", c);
        // }
        // printf("$\n");
        // fclose(fp);
        // return 0;

        char *word = malloc(100); memset(word, 0, 100);
        int j=0;
        int slashcounter = 0;
        for(int i=0; i<strlen(stringExceptFirstWord); i++){
            if(inputCopy[i]=='/'){slashcounter++;}
            if(stringExceptFirstWord[i]==' ' || stringExceptFirstWord[i]=='\0'){
                if(chdir(word)!=0){
                    catFilee(word);
                    memset(word, 0, 100); j=0; 
                    //continue;
                }
                memset(word, 0, 100); j=0;
            }
            else{
                word[j]=stringExceptFirstWord[i];
                j++;
            }
            if(inputCopy[i]==' '){
                // while(slashcounter>0){
                //     chdir("..");
                //     slashcounter--;
                // }
                chdir(currentWorkingDirectory);
            }
        }
    }
    else{
        printf("Flag not identified."); printf("\n");
        return 0;
    }





    // fp = fopen(argv[1], "r");
    // //if file opened successfully, then show message
    // if(fp){
    //     printf(" (File opened successfully)"); printf("\n");
    // }
    // else{
    //     printf(" (File not opened)"); printf("\n");
    //     return -1;
    // }
    // char c;
    // while((c = fgetc(fp)) != EOF){
    //     printf("%c", c);
    // }
    // printf("\n");
    // fclose(fp);
    

    return 0;

}
