#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 1000

int stato = 0;

int stato0(char x);
int stato1(char x);
int stato2(char x);
int stato3(char x);
int stato4(char x);
int stato5(char x);
int stato6(char x);
int stato7(char x);
int stato8(char x);
int stato9(char x);



int sottostr0(char x);
int sottostr1(char x);
int sottostr2(char x);
int sottostr3(char x);


int main(){
 int flag = 0;
 char input [DIM] = "";
 scanf("%s", input);
 int(*array[10])(char) = {stato0, stato1, stato2, stato3, stato4, stato5, stato6, stato7, stato8, stato9}; 
 for(int i = 0; input[i]!='\n'; i++){
    flag = array[stato] (input[i]);
    if (flag == 1){
        break;
    }
 }
    if (flag == 0){
        puts("Stringa non appartente al linguaggio");
    }
    else{
        puts("Stringa appartenente al linguaggio");
        flag = 0;
        int(*sottostr[4])(char) = {sottostr0, sottostr1, sottostr2,sottostr3}; 
        for(int i = 0; input[i]!='\n'; i++){
            flag = sottostr[flag] (input[i]);
            if (flag == 4){
                break;
            }
        }
        if(flag != 4){
            puts("Sottostringa abDD non presente");
        }
        else{
            puts("Sottostringa abDD presente");
        }
    }
    return 0;    
}


int stato0(char x){
    if (x >= 'A' && x <= 'Z'){
        stato = 1;
    }
    return 0;
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



int stato5(char x){
    if (x == 'b'){
        stato = 6;
    }
    else if((x >= 'A' && x <= 'Z')){
        stato = 1;
    }
    else{
        stato = 0;
    }
    return 0;
}



int stato6(char x){
    if (x != 'd'){
        stato = 7;
    }
    else{
        stato = 0;
    }
    return 0;
}



int stato7(char x){
    if (x != 'd'){
        stato = 8;
    }
    else{
        stato = 0;
    }
    return 0;
}






int stato8(char x){
    if (x != 'd'){
        stato = 9;
    }
    else{
        stato = 0;
    }
    return 0;
}


int stato9(char x){
    return 1;
}







int sottostr0(char x){
    if(x=='a'){
        return 1;
    }

    return 0;
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