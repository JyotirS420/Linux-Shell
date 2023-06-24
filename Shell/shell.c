#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include "helpheader.h"

char* returnFirstWord(char[]);
char* returnSecondWord(char input[]);
void echoFunction(char[]);
char* returnStringExceptForFirstWord(char input[]);

char* returnFirstWord(char input[]){
    char *firstWord = malloc(100);
    int i=0;
    while(input[i]!=' '){
        firstWord[i]=input[i];
        i++;
    };
    return firstWord;
}

char* returnSecondWord(char input[]){
    char *secondWord = malloc(100);
    int i=0;
    while(input[i]!=' '){
        i++;
    };
    i++;
    int j=0;
    while(input[i]!='\0'){
        secondWord[j]=input[i];
        i++;
        j++;
    };
    return secondWord;
}

char* returnStringExceptForFirstWord(char input[]){
    char *stringExceptForFirstWord = malloc(100);
    int i=0;
    while(input[i]!=' '){
        i++;
    };
    i++;
    int j=0;
    int quoteCounter=0;
    while(input[i]!='\0'){
        if(input[i]=='"'){
            i++;
            quoteCounter++;
        }
        stringExceptForFirstWord[j]=input[i];
        i++;
        j++;
        // if(quoteCounter%2!=0 && input[i]=='\0'){
        //     //stringExceptForFirstWord[j]=' ';
        //     //j++;
        //     printf("dquote>");
        //     scanf("%c",&input[i]);
        //     if(input[i]=='"'){quoteCounter++;}
        // }
    };
    return stringExceptForFirstWord;
}



void echoFunction(char input[]){
    
    //printf("%s", input); printf("\n");
    
    char *firstWord = malloc(100); memset(firstWord, 0, 100);
    char *inputCopy = malloc(100); memset(inputCopy, 0, 100);
    strcpy(inputCopy,input);
    //add ' ' to the end of the string inputCopy
    // int i=0;
    // while(inputCopy[i]!='\0'){
    //     i++;
    // };
    // inputCopy[i]=' ';
    // inputCopy[i+1]='\0';
    
    calculateFirstWord(inputCopy,firstWord);
    //return;
    //printf("Here is the first word: %s\n",firstWord);
    if(firstWord[0]=='-'){
        if(firstWord[1]=='n' && strlen(firstWord)==2){
            printf("%s",returnStringExceptForFirstWord(input)); //printf("%c"); printf("\n");
            //printf("No newline");printf("\n");
            return;
        }
        // if(firstWord[1]=='E' && strlen(firstWord)==2){
        //     printf("%s",returnStringExceptForFirstWord(input)); printf("\n");
        //     return;
        // }
        else{
            printf("%s: Not a valid flag",firstWord); printf("\n");
            return;
        }

    }
    printf("%s", input); printf("\n");

    return;
}

void pwdFunction(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("%s", cwd);
}

void cdFunction(char input[]){
    //chdir(input);
    //printf("%s", input);
    if(input==NULL){chdir("/home/js"); return;}
    if(strcmp(input,"~")==0 || strcmp(input,"")==0){chdir("/home/js"); return;}
    if(chdir(input)==-1){printf("%s: No such file or directory",input); printf("\n");return;}
    //else{printf("Directory changed");printf("\n"); return;}
    
}

void *helpersystem(void * arg){
    //type caste the argument to a char*
    printf("(In helper system)\n");

    char *input = (char*)arg;
    //printf("Input in helper is: %s\n", input);
    //print each character of the input 
    // int i=0;
    // while(input[i]!='\0'){
    //     printf("\'%c\' ",input[i]);
    //     i++;
    // };
    //printf("\n");
    system(input);
    return NULL;
}



void callShell(){
    
    // char str[100];
    // clear str
    // for(int i=0;i<100;i++){
    //     str[i]='\0';
    // }
    char *str=malloc(100);memset(str,0,100);
    char *firstWord=malloc(100);memset(firstWord,0,100);

    while(strcmp(str,"exit")!=0){

        char str[100];
        // clear str
        for(int i=0;i<100;i++){str[i]='\0';};
        char *firstWord=malloc(100);memset(firstWord,0,100);
        char *secondWord=malloc(100);memset(secondWord,0,100);
        char *stringExceptForFirstWord=malloc(100);memset(stringExceptForFirstWord,0,100);


        //memset(str,0,strlen(str));
        //memset(firstWord,0,strlen(firstWord));

        // for(int i=0;i<100;i++){
        //     str[i]='\0';
        //     firstWord[i]='\0';
        // };
        
        //printf("\n");
        pwdFunction();
        printf(" >>> ");

        

        //scanf("%s", str);
        //scan till first space
        //scanf("%[^\n]s",str);

        //scan a string until newline
        fgets(str,100,stdin);
        str[strlen(str)-1]='\0';
        //fflush(stdin);

        //printf("Hello4");
        
        //firstWord=returnFirstWord(str);
        calculateFirstWord(str,firstWord);
        if(strcmp(firstWord,"exit")==0){break;}

        // printf("First word: %s",firstWord); printf("\n");
        // printf("String: %s",str); printf("\n");
        if(strcmp(firstWord,"ls&t")==0){
            //call tryls file using fork() process
            //printf("Inside ls&t"); printf("\n");
            pthread_t p1;
            char *passString=malloc(100);memset(passString,0,100);
            
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));

            // char *secondWord=malloc(100);
            // memset(secondWord,0,strlen(secondWord));
            // secondWord=returnSecondWord(str);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            calculateSecondWord(str,secondWord);
            strcat(passString,"/home/js/A_2F/C/tryls"); strcat(passString," "); strcat(passString,"try"); strcat(passString," ");
            strcat(passString,"A"); strcat(passString," ");strcat(passString,"B"); strcat(passString," ");strcat(passString,stringExceptForFirstWord);
            pthread_create(&p1,NULL,helpersystem,(void *)passString);
            pthread_join(p1,NULL);
        }
        else if(strcmp(firstWord,"mkdir&t")==0){
            //call tryls file using fork() process
            //printf("Inside mkdir&t"); printf("\n");
            pthread_t p1;
            char *passString=malloc(100);memset(passString,0,100);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //add a space and a \0 to the end of the stringExceptForFirstWord
            stringExceptForFirstWord[strlen(stringExceptForFirstWord)]=' ';
            stringExceptForFirstWord[strlen(stringExceptForFirstWord)+1]='\0';

            strcat(passString,"/home/js/A_2F/C/trymkdir"); strcat(passString," "); strcat(passString,"try"); strcat(passString," ");
            strcat(passString,"A"); strcat(passString," ");strcat(passString,"B"); strcat(passString," ");strcat(passString,stringExceptForFirstWord);
            pthread_create(&p1,NULL, helpersystem, (void *)passString);
            pthread_join(p1,NULL);
        }
        else if(strcmp(firstWord,"cat&t")==0){
            //printf("Inside cat&t"); printf("\n");
            pthread_t p1;
            char *passString=malloc(100);memset(passString,0,100);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //add a space and a \0 to the end of the stringExceptForFirstWord
            // stringExceptForFirstWord[strlen(stringExceptForFirstWord)]=' ';
             stringExceptForFirstWord[strlen(stringExceptForFirstWord)+1]='\0';

            strcat(passString,"/home/js/A_2F/C/trycat"); strcat(passString," "); strcat(passString,"try"); strcat(passString," ");
            strcat(passString,"A"); strcat(passString," ");strcat(passString,"B"); strcat(passString," ");strcat(passString,stringExceptForFirstWord);
            pthread_create(&p1,NULL, helpersystem, (void *)passString);
            pthread_join(p1,NULL);
        }
        else if(strcmp(firstWord,"rm&t")==0){
            //printf("Inside rm&t"); printf("\n");
            pthread_t p1;
            char *passString=malloc(100);memset(passString,0,100);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //add a space and a \0 to the end of the stringExceptForFirstWord
            //stringExceptForFirstWord[strlen(stringExceptForFirstWord)]=' ';
            //stringExceptForFirstWord[strlen(stringExceptForFirstWord)+1]='\0';

            //strcat(passString,"/Users/jyotir/C/tryrm"); strcat(passString," "); strcat(passString,stringExceptForFirstWord); strcat(passString,"rm"); strcat(passString," ");
            strcat(passString,"/home/js/A_2F/C/tryrm"); strcat(passString," "); strcat(passString,"try"); strcat(passString," ");
            strcat(passString,"A"); strcat(passString," ");strcat(passString,"B"); strcat(passString," ");strcat(passString,stringExceptForFirstWord);
            pthread_create(&p1,NULL, helpersystem, (void *)passString);
            pthread_join(p1,NULL); // strcat(passString," "); strcat(passString," ");
        }
        else if(strcmp(firstWord,"date&t")==0){
            //printf("Inside date&t"); printf("\n");
            pthread_t p1;
            char *passString=malloc(100);memset(passString,0,100);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //add a space and a \0 to the end of the stringExceptForFirstWord
            stringExceptForFirstWord[strlen(stringExceptForFirstWord)]=' ';
            stringExceptForFirstWord[strlen(stringExceptForFirstWord)+1]='\0';

            // printf("firstWord: %s",firstWord); printf("\n");
            // printf("length of firstWord: %lu",strlen(firstWord)); printf("\n");
            // printf("String is: %s",str); printf("\n");
            // printf("length of string is: %lu",strlen(str)); printf("\n");
            if(strcmp(firstWord,str)==0){
                //overwrite stringExceptForFirstWord with a space and a \0
                memset(stringExceptForFirstWord,0,strlen(stringExceptForFirstWord));
                // stringExceptForFirstWord[0]=' ';
                // stringExceptForFirstWord[1]='\0';
                strcpy(stringExceptForFirstWord,"");
            }

            strcat(passString,"/home/js/A_2F/C/trydate"); strcat(passString," "); strcat(passString,"try"); strcat(passString," ");
            strcat(passString,"A"); strcat(passString," ");strcat(passString,"B"); strcat(passString," ");strcat(passString,stringExceptForFirstWord);
            pthread_create(&p1,NULL, helpersystem, (void *)passString);
            pthread_join(p1,NULL);
        }

        

        else if(strcmp(firstWord,"ls")==0){
            //call tryls file using fork() process

            pid_t pid = fork();
            char cwd[1024];
            getcwd(cwd, sizeof(cwd));

            // char *secondWord=malloc(100);
            // memset(secondWord,0,strlen(secondWord));
            // secondWord=returnSecondWord(str);
            calculateSecondWord(str,secondWord);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);

            if(pid==0){
                execlp("/home/js/A_2F/C/tryls","tryls",stringExceptForFirstWord,NULL);
            }
            else{wait(NULL);}
        }
        else if(strcmp(firstWord,"echo")==0){
            //printf("echo"); printf("\n");
            //call tryecho file using fork() process

            // char *stringExceptForFirstWord=malloc(100);
            // memset(stringExceptForFirstWord,0,strlen(stringExceptForFirstWord));
            // stringExceptForFirstWord=returnStringExceptForFirstWord(str);
            if(strcmp(str,"echo --help")==0){
                //read the echohelp file and print it
                    FILE *fp;
                    fp = fopen("echohelp.txt", "r");
                    if(fp == NULL){
                        printf("echohelp.txt: File not found."); printf("\n");
                        return;
                    }
                    //printf("%s: ", path);
                    char c;
                    while((c = fgetc(fp)) != EOF){
                        printf("%c", c);
                    }
                    printf("\n");
                    fclose(fp);
                    continue;
            }

            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);

            //printf("%s",stringExceptForFirstWord); printf("\n");

            echoFunction(stringExceptForFirstWord);

            // pid_t pid = fork();
            // if(pid==0){
            //     char *stringExceptForFirstWord=malloc(100);
            //     memset(stringExceptForFirstWord,0,strlen(stringExceptForFirstWord));
            //     stringExceptForFirstWord=returnStringExceptForFirstWord(str);
            //     int ret = execlp("/Users/jyotir/C/tryecho","tryecho",stringExceptForFirstWord,NULL);
            //     if(ret==-1){
            //         perror("Error executing tryecho");
            //     }
            // }
            // else{
            //     //wait for child process to complete execution and then resume immediately
            //     wait(NULL);
            // }
        }
        else if(strcmp(firstWord,"cd")==0){
            // char *stringExceptForFirstWord=malloc(100);
            // memset(stringExceptForFirstWord,0,strlen(stringExceptForFirstWord));
            // stringExceptForFirstWord=returnStringExceptForFirstWord(str);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //chdir(stringExceptForFirstWord);
            cdFunction(stringExceptForFirstWord);

            
        }
        else if(strcmp(firstWord,"pwd")==0){
            pwdFunction(); printf("\n");
        }
        // else if(strcmp(firstWord,"exit")==0){
        //     printf("");
        // }
        else if(strcmp(firstWord,"cat")==0){
            //call trycat file using fork() process
            pid_t pid = fork();

            // char *secondWord=malloc(100);
            // memset(secondWord,0,strlen(secondWord));
            // secondWord=returnSecondWord(str);
            calculateSecondWord(str,secondWord);
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //add '\0' at the end of stringExceptForFirstWord
            // int j=0;
            // while(stringExceptForFirstWord[j]!='\0'){
            //     j++;
            // }
            // stringExceptForFirstWord[j]='\0';

            if(pid==0){
                execlp("/home/js/A_2F/C/trycat","trycat",stringExceptForFirstWord,NULL);
            }
            else{wait(NULL);}
            
        }
        else if(strcmp(firstWord,"mkdir")==0){
            //call trymkdir file using fork() process
            pid_t pid = fork();
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            if(pid==0){
                execlp("/home/js/A_2F/C/trymkdir","trymkdir",stringExceptForFirstWord,NULL);
            }
            else{wait(NULL);}
        }
        else if(strcmp(firstWord,"date")==0){
            //call trydate file using fork() process
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            //calculateFirstWord(str,firstWord);
            if(strcmp(firstWord,str)==0){
                pid_t pid = fork();
                if(pid==0){
                    execlp("/home/js/A_2F/C/trydate","trydate"," ",NULL);
                }
                else{wait(NULL);}
            }
            else{
                pid_t pid = fork();
                if(pid==0){
                    execlp("/home/js/A_2F/C/trydate","trydate",stringExceptForFirstWord,NULL);
                }
                else{wait(NULL);}
            }

        }
        else if(strcmp(firstWord,"rm")==0){
            pid_t pid = fork();
            calculateStringExceptForFirstWord(str,stringExceptForFirstWord);
            if(pid==0){
                execlp("/home/js/A_2F/C/tryrm","tryrm",stringExceptForFirstWord,NULL);
            }
            else{wait(NULL);}
        }

        else if(strcmp(firstWord,"exit")==0){
            break;
        }
        else if(strcmp(firstWord,"")==0){
            printf("");
        }
        else{
            printf("%s: Invalid command",firstWord); printf("\n");
        }
    }

    return;

}




int main(){

    callShell();

    return 0;
}
