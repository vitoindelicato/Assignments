#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define DIM 100 


int stato0(char input, int stato, int* flag_b);
int stato1(char input, int stato, int* flag_b);
int stato2(char input, int stato, int* flag_b);
int stato3(char input, int stato, int* flag_b);
int stato4(char input, int stato, int* flag_b);



int sottostr0(char x, int stato);
int sottostr1(char x, int stato);
int sottostr2(char x, int stato);
int sottostr3(char x, int stato);





char input[DIM] = {""};

int main(){
int stato = 0;
int i = 0;
int flag_b = 0;
char c;
int counter = 0;
printf("Stringa:\n");
while(( c = getchar())!= '\n' && counter < 98){
    input [counter] = c;
    counter ++;
}
input[counter +1] = '\0';

int (*array[10]) (char x, int stato, int* flag_b) = {stato0, stato0, stato0, stato0, stato1, stato2, stato3, stato4, stato4, stato4};
    while(input[i] != '\0' ){
      stato = array[stato](input[i], stato, &flag_b);
        i++;
        if(stato == -1 || stato > 9){
            break;
        }
    }
    if (stato == -1 || stato > 9){
        printf("stringa non appartenente al linguaggio\n");
    }
    else if (stato == 9 || (stato==8 && flag_b >= 1) || (stato==7 && flag_b >= 2) || (stato==6 && flag_b >= 3)){
        printf("stringa appartenente al linguaggio\n");
        int(*sottostr[4])(char x, int stato) = {sottostr0, sottostr1, sottostr2,sottostr3}; 
        stato = 0;
        for(int j = 4; input[j]!='\0'; j++){
            stato = sottostr[stato] (input[j], stato);
            if (stato >= 3 || stato == -1){
                break;
            }
        }
        if(stato != 3){
            printf("nessuna sottostringa abDD\n");
        }
        else{
            printf("sottostringa abDD presente\n");
        }
    }
    else{
        printf("stringa non appartenente al linguaggio\n");
    }


    return 0;
}




int stato0(char input, int stato, int* flag_b){
    if (isupper((int)input)==0){
        return -1;
    }
    
    return stato+1;
}




int stato1(char input, int stato, int* flag_b){
    if(input == 'a'){
        return stato+1;
    }

    return -1;
}



int stato2(char input, int stato, int* flag_b){
    if(input == 'b'){
        return stato +1;
    }
    return -1;
}


int stato3(char input, int stato, int* flag_b){
    if(input == 'b'){
        *flag_b += 1;
        return stato;
    }
    else if (input == 'd'){
        return -1;
    }
    else{
        return stato +1;
    }
 
}


int stato4(char input, int stato, int* flag_b){
    if (input == 'd'){
        return -1;
    }
    else{
        return stato +1;
    }
}
    



int sottostr0(char x, int stato){
    if(x =='a'){
        return stato +1;
    }
    else{
        return -1;
    }

    
}



int sottostr1(char x, int stato){
    if(x == 'b'){
        return stato +1;
    }
    else{
        return -1;
    }
    
    
}



int sottostr2(char x, int stato){
    if(x == 'D'){
        return stato + 1;
    }
    
    else{
        return -1;
        }
}



int sottostr3(char x, int stato){
    if(x == 'D'){
        return stato;
    }
    
    else{
        return -1;
        }
}