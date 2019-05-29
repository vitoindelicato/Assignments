#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 100 

int stato = 0;

//funzioni per verificare l'appartenenza allo stato
int stato0(char x);
int stato1(char x);
int stato2(char x);
int stato3(char x);
int stato4(char x);



//funzioni per la presenza della sottostringa abDD
int sottostr0(char x);
int sottostr1(char x);
int sottostr2(char x);
int sottostr3(char x);


int main(){
 int counter = 0;
 int flag = 0;
 char input [DIM]= {'\0'}; //inizializzo la stringa a vuota per evitare undefined behaviours
 input[DIM-1] = '\0';
 int(*array[5])(char) = {stato0, stato1, stato2, stato3, stato4}; 
 printf("Stringa:");

 while(char c = getchar() && c != '\n' && counter != 98){
    input[counter] = c;
    counter++;
 }
 input[counter+1] = '\0';
 
 for(int i = 0; input[i]!='\n'; i++){
    flag = array[stato] (input[i]);
    if (flag == 1){
        break;
    }
 }
    if (flag == 0){
        printf("stringa non appartente al linguaggio\n");
    }
    else{
        printf("stringa appartenente al linguaggio\n");
        flag = 0;
        int(*sottostr[4])(char) = {sottostr0, sottostr1, sottostr2,sottostr3}; 
        for(int i = 0; input[i]!='\n'; i++){
            flag = sottostr[flag] (input[i]);
            if (flag == 4){
                break;
            }
        }
        if(flag != 4){
            printf("nessuna sottostringa abDD\n");
        }
        else{
            printf("sottostringa abDD presente\n");
        }
    }
    return 0;    
}


int stato0(char x){

}


int stato1(char x){
    if (x >= 'A' && x <= 'Z'){
        stato = 2;
    }
    return 0;
}

int stato2(char x){
    if (x >= 'A' && x <= 'Z'){
        stato = 3;
    }
    return 0;
}


int stato3(char x){
    if (x >= 'A' && x <= 'Z'){
        stato = 4;
    }
    return 0;
}


int stato4(char x){
    if (x == 'a'){
        stato = 5;
    }
    else if((x >= 'A' && x <= 'Z')){
        stato = 1;
    }
    else{
        stato = 0;
    }
    return 0;
}



 



int sottostr0(char x){
    if(x =='a'){
        return 1;
    }
    else{
        return 0;
    }

    
}



int sottostr1(char x){
    if(x == 'b'){
        return 2;
    }
    else if(x == 'a'){
        return 1;
    }
    else{
        return 0;
    }
    
    
}



int sottostr2(char x){
    if(x == 'D'){
        return 3;
    }
    else if(x == 'a'){
        return 1;
    }
    else{
        return 0;
    }
    
    
}



int sottostr3(char x){
    if(x == 'D'){
        return 4;
    }
    else if(x == 'a'){
        return 1;
    }
    else{
        return 0;
    }
    
    
}