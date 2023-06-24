void calculateFirstWord(char input[], char firstWord[]){
    int i=0;
    while(input[i]!=' ' && input[i]!='\0'){
        firstWord[i]=input[i];
        i++;
    };
    firstWord[i]='\0';
}


void calculateSecondWord(char input[], char secondWord[]){
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
    secondWord[j]='\0';
}

void calculateStringExceptForFirstWord(char input[], char stringExceptForFirstWord[]){
    int i=0;
    while(input[i]!=' '){
        if(input[i]=='\0'){
            stringExceptForFirstWord[0]='\0';
            return;
        }
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
    //stringExceptForFirstWord[j]=' ';
    stringExceptForFirstWord[j]='\0';
}



void calculateNumberOfWordsInString(char input[], int *numberOfWords){
    int i=0;
    int wordCounter=0;
    while(input[i]!='\0'){
        if(input[i]==' '){
            wordCounter++;
        }
        i++;
    };
    *numberOfWords=wordCounter+1;
}