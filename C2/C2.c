#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define DIM 100

struct Words{
  int len;
  char *word;
  int count;
  struct Words *next;
};
typedef struct Words words;
typedef words *wordsptr;

void read_file (FILE *x);
void insert_node(wordsptr *head, char file_str[]);
void len_calc(wordsptr head);
void star(wordsptr head);


FILE *fp; //puntatore al file
wordsptr head = NULL;
char file_str[DIM];
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
  star(head);
  fclose(fp);


 return 0;
}




//strip

void read_file(FILE *x){
  while(fscanf(x, "%[a-zA-Z]%*[^\"]%*[^a-zA-Z]", file_str)!=EOF){
    for(int i = 0; file_str[i] != '\0'; i++){
      file_str[i] = tolower(file_str[i]);
    }
    word_count++;
    insert_node(&head, file_str);
  }

}


void insert_node(wordsptr *head, char file_str[DIM]){
  wordsptr new = malloc(sizeof(words));
  new->len = strlen(file_str);
  new->count = 1;
  if(new->len > max_len){
    max_len = new->len;
  }
  new->word = malloc((strlen(file_str))*sizeof(char)+1);
  strcpy(new->word, file_str);
  new->next = NULL;

  wordsptr prev = NULL;
  wordsptr curr = *head;


  //leggendo le parole da file, si inseriscono già in ordine alfabetico in lista
  while(curr != NULL && strcmp(new->word, curr->word)>=0){
    prev = curr;
    curr = curr->next;
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
  int counter = 0;
  int i = 0;
  double freq = 0;
  wordsptr tmp = NULL;
  printf("\tLunghezza\tFrequenza(%%)\n");
  for (i = 0; i < max_len; i ++){
    counter = 0;
    tmp = head;
    while(tmp->next != NULL){
      if(tmp->len == i+1){
        counter++;
      }
      tmp = tmp->next;
    }
    freq = (double)(counter*100)/word_count;
    printf("\t%9d", i+1);
    printf("%18.02f%%\n", freq);

  }
}




void star(wordsptr head){
  wordsptr tmp = head;
  wordsptr tmp2 = tmp->next;
  while(tmp2->next!= NULL){
    while(strcmp(tmp->word, tmp2->word)==0){
      tmp->count++;
      wordsptr tmp3 = tmp2;
      tmp2 = tmp2->next;
      tmp->next = tmp3->next;
      free(tmp3->word);
      free(tmp3);
    }
    printf("%17s  ", tmp->word);
    for(int i = 0; i < tmp->count; i++){
      printf("*");
    }
    printf("\n");
    wordsptr tmp3 = tmp;
    tmp = tmp->next;
    free(tmp3->word);
    free(tmp3);
    tmp2 = tmp2->next;
  }
  free(tmp->word);
  free(tmp);
  free(tmp2->word);
  free(tmp2);

}
