#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "helpheader.h"

int main(int argc, char *argv[]){

    // printf("Number of arguments: %d",argc); printf("\n");
    // printf("Argument passed: %s", argv[1]); printf("\n");
    // printf("Size of argument passed: %lu", strlen(argv[1])); printf("\n");
    // time_t t = time(NULL);
    // struct tm tm = *localtime(&t);
    // printf("%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    // printf("\n");
    
    if(argv[1]==NULL){
        time_t currentTime;
        time(&currentTime);
        printf("%s", ctime(&currentTime)); //printf("\n");
        return 0;
    }

    //char *nullWOrd = malloc(100); memset(nullWOrd, 0, 100); "Studio"
    char *inputCopy = malloc(100); memset(inputCopy, 0, 100);
    //strcpy(inputCopy, argv[1]);


    if(argv[2]==NULL){
        // printf("in here\n");
        printf("(Through fork)\n");
        strcpy(inputCopy, argv[1]);
        // printf("input is %s\n", inputCopy);
        // printf("length of input is %lu\n", strlen(inputCopy));
    }
    else{
        printf("(Through thread)\n");
        int i=4;
        // printf("argv[0] is %s\n",argv[0]);
        // printf("argv[1] is %s\n",argv[1]);
        while(argv[i]!=NULL){
            // printf("argv[%d] is %s\n",i, argv[i]);
            strcat(inputCopy, argv[i]);
            strcat(inputCopy, " ");
            i++;
        }
        inputCopy[strlen(inputCopy)]='\0';
        //inputCopy[strlen(inputCopy)+1]='\0';
        // printf("IN HERE\n");
        // printf("input is %s\n", inputCopy);
        // printf("length of input is %lu\n", strlen(inputCopy));
    }


    //printf("Here is: %s", firstWord); printf("\n");
    //printf("Length of firstWord: %lu", strlen(firstWord)); printf("\n");

    //count number of nonblank characters in input
    int nonBlankCharacters=0;
    for(int i=0; i<strlen(inputCopy); i++){
        if(inputCopy[i]!=' ' && inputCopy[i]!='\0'){
            nonBlankCharacters++;
        }
    }
    if(nonBlankCharacters==0){
        time_t currentTime;
        time(&currentTime);
        printf("%s", ctime(&currentTime)); //printf("\n");
        return 0;
    }


    if(strcmp(inputCopy," ")==0 || strcmp(inputCopy,"")==0 || inputCopy==NULL){
        time_t currentTime;
        time(&currentTime);
        printf("%s", ctime(&currentTime)); //printf("\n");
        return 0;
    }

    char *firstWord = malloc(100); memset(firstWord, 0, 100);
    calculateFirstWord(inputCopy,firstWord);

    if(strcmp(inputCopy,"-u")==0 || strcmp(inputCopy,"-u  ")==0 || strcmp(inputCopy,"-u ")==0){
        //print UTC time
        time_t utctime;
        time(&utctime);
        printf("%s", asctime(gmtime(&utctime))); //printf("\n");
        return 0;
    }
    // else if(strcmp(firstWord,"-r")==0){
    //     //print time of last modification of file
    //     struct stat fileStat;
    //     stat("try.c", &fileStat);
    //     printf("Last modified time: %s", ctime(&fileStat.st_mtime)); //printf("\n");
    //     return 0;
    // }
    else if(strcmp(inputCopy,"-I")==0 || strcmp(inputCopy,"-I  ")==0 || strcmp(inputCopy,"-I ")==0){
        //print todays date in YYYY/MM/DD format
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        printf("%d/%d/%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
        printf("\n");
        return 0;
    }
    else{
        printf("%s: Flag not recognised.",inputCopy); printf("\n");
    }

    // struct tm *utc;
    // utc = gmtime();
    // printf("%s", asctime(&utc));



    return 0;

}
