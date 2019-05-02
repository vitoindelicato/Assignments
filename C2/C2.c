#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#define FILTER " / . ( ) * + - = \n #  \\ ' ; , ? ! @ \" "
#define MAX_LEN 27

struct Words{
  int len;
  char *word;
  int count;
  struct Words *next;
};
typedef struct Words words;
typedef words *wordsptr;

void read_file (FILE *x);
void insert_node(wordsptr *head, char *token);
void len_calc(wordsptr head);
void print_star(wordsptr head);


FILE *fp; //puntatore al file
wordsptr head = NULL;
long int word_count = 0;
int max_len = 0;


int main(int argc, char **argv){

  if(argc != 2){
    printf("Errore, inserire due argomenti : \"Nome programma\" \"Nome file\" \n");
    return 0;
  }

  fp = fopen(argv[1], "r");

  if(fp == NULL){
    printf("Impossibile aprire il file %s\n", argv[1]);
    return 0;
  }

  read_file(fp);
  len_calc(head);
  print_star(head);



 return 0;
}





void read_file(FILE *x){
  int size = 0;
  fseek(x,0,SEEK_END);//Returns the file size
  size = ftell(x);
  rewind(x);
  char assets[size]; //assets originariamente era usato dinamicamente, ma con la funzione fread, anche usando il free su di esso, rimaneva comunque allocato in memoria, usarlo staticamente era unica soluzione possibile per non avere leak
  //char *assets = malloc(size +1); //per verificare veridicità di quanto detto, basta commentare la riga sopra a questa e decommentare questa
  fread(assets, sizeof(char), size, x);
  assets[size] = '\0';
  fclose(x);
  char *token = strtok(assets,FILTER);



  while (token!= NULL){
    for(int i = 0; token[i] != '\0'; i++){
      token[i] = tolower(token[i]);
    }
    insert_node(&head, token);
    word_count++;
    token = strtok(NULL,FILTER);

    if(token == NULL){
      return;
    }
  }
  //free(assets); //decommentare anche questa, e girare con valgrind
  free(token);

}





void insert_node(wordsptr *head, char *token){
  wordsptr new = malloc(sizeof(words));
  new->len = strlen(token);
  new->count = 1;
  if(new->len > max_len){
    max_len = new->len;
  }
  new->word = malloc((strlen(token))*(sizeof(char))+1);
  strcpy(new->word, token);
  new->next = NULL;

  wordsptr prev = NULL;
  wordsptr curr = *head;


  //leggendo le parole da file, si inseriscono già in ordine alfabetico in lista
  while(curr != NULL && strcmp(new->word, curr->word)>0){
    prev = curr;
    curr = curr->next;
  }
  if(curr != NULL && (strcmp(new->word, curr->word)==0)){
    curr->count++;
    free(new->word);
    free(new);
    return;
  }
  if(prev == NULL){
    new->next = *head;  //faccio puntare il next alla struttura testa aka null
    *head = new; //e alla testa do i valori den new node
  }
  else{
    prev->next = new;
    new->next = curr;
  }

}






void len_calc(wordsptr head){
  float freq = 0.0;
  int length[MAX_LEN] = {0};
  printf("\tLunghezza\tFrequenza(%%)\n");

  while (head != NULL) {
    length[head->len] += head->count;
    head = head->next;
  }
  for(int i = 0; i < MAX_LEN;i++){
    if(length[i] != 0){
      printf("\t%9d", i);
      freq =((float)length[i]/(float)word_count)*100;
      printf("%18.02f%%\n", freq);
    }
  }
}





void print_star(wordsptr head){
  while(head != NULL){
    printf("%17s  ", head->word);
    for(int i = 0; i < head->count; i++){
      printf("*");
    }
    printf("\n");

    wordsptr tmp = head;
    head = head->next;
    free(tmp->word);
    free(tmp);
  }
}
