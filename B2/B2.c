#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 10
#define DIM 33






char rand_lett(); //generatore di lettere random
void str_gen(char **array, int**mask, int user);//genera le stringhe random
void print_str(char **array, int **mask, int user, int mode);//stampa le stringhe, può essere chiamato in diversi modi in base al caso
void free_all(char **array, int **mask, int user, FILE *x);//funzione che libera tutta la memoria occupata e chiude il file
void read_file(FILE *x, char *name);//funzione che legge e stampa un file
void confronta(char **array, int** mask, int user, FILE *x); //algoritmo che confronta ogni lettera di ogni parola del file con tutte le stringhe random
void mask_changer(int **mask, char **array, int user, int mode); //modifica una "maschera" di numeri, creata in parallelo con le stringhe, per verificare lo status di ogni lettera











int main(int argc, char **argv){

  int x = 0; //user input NUMERO STRINGHE
  if(argc!=3){
    printf("Inserire tre argomenti, in ordine : \"name programma\"  \"numero stringhe\" \"name file\"\n");
    return 0;
    }

  FILE *fp; //puntatore al file
  fp = fopen(argv[2], "r"); //apro il file, con il nome ricevuto da linea di comando
  if(fp == NULL){
    printf("Impossibile aprire il file\n");
    return 0;
    }

  read_file(fp, argv[2]);

  x = atoi(argv[1]); //converto il parametro in int, in quanto se usato senza conversione avrebbe preso il valore ASCII
  char** arr = malloc(x*(sizeof(char*)));//creazione array di puntatori a char, ogni elemento conterrà il primo carattere di una diversa stringa
  int** check = malloc(x*(sizeof(int*)));//creazione maschera parallela di puntatori ad  int

  str_gen(arr,check,x); //genero le strighe random
  print_str(arr,check,x,1);//printo le stringhe random
  confronta(arr, check, x, fp); //confronto le parole con le stringhe, e stampo le parole possibili
  printf("\n");
  print_str(arr, check, x, 2); //printo le lettere degli array di stringhe rimaste

  free_all(arr, check, x, fp); // libero tutta la memoria occupata e chiudo il file
  return 0;
}


















char rand_lett() {  //funzione per la creazione di un nummero corrispondente al valore ascii dell'alfabeto
    char val = rand() % 52;
    if (val < 26) {
        val += 'a';
    } else {
        val -= 26;
        val += 'A';
    }
    return val;
}





void str_gen(char **array, int**mask, int user){
  int n = 0; //random lunghezza stringa
  for(int i = 0; i < user; i++){
    n = rand() %SIZE + 4;
    char* str = malloc(n*(sizeof(char))+1);
    int* num = malloc(n*(sizeof(int))+1);//maschera creata per verificare lo status dei caratteri 0) il carattere è utilizzabile
    //1) il carattere è stato utilizzato per una parola non ancora completata 2) il carattere è stato utilizzato per completare una parola, quindi mai più utilizzabile
    for(int j = 0; j < n; j++){
      num[j] = 0;
      if(j==n-1){
        str[j] = '\0';
      }
      else{
      str[j] = rand_lett(); //numero random compreso tra 65 e 90 e compreso tra 97 e 122
      }
    }
    array[i] = str; //all'elemento i dell'array di puntatori, do il puntatore alla prima lettera dell'array di caratteri random
    mask[i] = num; //stessa cosa qua
  }
}





void print_str(char **array, int **mask, int user, int mode){
    if (mode == 1){ //chimaando la funzione con il parametro mode = 1, la funzione stamperà le stringhe appena create
     printf("Il programma genera le stringhe:\n\n");
   }
   if (mode == 2){ //chiamando la funzione con mode = 2 la funzione stamperà i caratteri rimasti
     printf("Caratteri rimasti: \n");
   }
    for (int i = 0; i < user; i++){
      char *p = array[i];
       int *c = mask[i];
      for(int j = 0; j < strlen(p); j++){
        if(mode == 2 && c[j] == 0){
         printf("%c", p[j]);
         printf(" ");
        }
       if(mode == 1){ //indentazione a seconda dei casi
         printf("%c", p[j]);
         printf(" ");
       }
     }
      if(mode == 1)
      printf("\n");
    }

  printf("\n\n");
}





void free_all(char **array,int **mask, int user, FILE *x){
  for(int i = 0; i < user; i++){
    free(*(array+i));
    free(*(mask+i));
  }
 free(mask);
 free(array);
 fclose(x);
}





void read_file(FILE *x, char *name){

  printf("IL file %s contiene le parole:", name); //name è il nome del file inserito dall'utente
  printf("\n\n");

  char file_str [DIM];
  while(fscanf(x, "%[^\n]\n", file_str)!=EOF){ //leggo ogni parola fino a \n
    printf("%s\n", file_str);
  }
  rewind(x); //riporto il puntatore del file all'inizio
  printf("\n\n\n");
}




void confronta(char **array, int** mask, int user, FILE *x){
  int len = 0; //lunghezza della parola del file
  int count = 0; // conteggio lettere che hanno una corrispondenza
  int flag = 0; //flag per uscita dai cicli
  int word_count = 0; //conteggio parole compiute trovate
  char file_str[DIM]; //arry che conterrà parola del file
  char **list = malloc(DIM*sizeof(char*)); //array di puntatori che immagazzinerà ogni parola compiuta, per stampare tutto alla fine del confronto


  while(fscanf(x, "%[^\n]\n", file_str)!=EOF){ //prende ogni parola dal file
    len = strlen(file_str); // prende la lunghezza della parola selezionata
    count = 0; //conteggio delle lettere trovate
    for(int i = 0; i < len; i++){ // questo ciclo seleziona ogni lettera della parola presa dal file

      for(int n = 0; n < user; n ++){ // prende ogni elemento dell'array di puntatori per le stringhe random
        if(flag == 1){ //se il flag del ciclo successivo si è attivato, ovvero si è trovata una corrispondenza, riporto il flag a 0 e rompo questo ciclo, passando così alla lettera successiva
            flag = 0;
            break;
        }
        char *p = array[n]; //creo un ptr a char, e passo passo, gli do le stringhe generate random
        int *a = mask[n]; //idem per la maschera

        for(int j = 0; j < strlen(p); j++){ //questo ciclo esamina ogni lettera di una stringa generata random fino all'ultimo carattere
          if(file_str[i] == p[j]&& a[j] == 0){ //confornto la lettera della parola del file con ogni lettera di una stringa
            count++; //se trovo una corrispondenza incremento il counter delle corrispondenze trovate
            flag++; //trovata una corrispondenza, do il valore uno al flag che serve a rompere i cicli, e passare alla lettera della parola successiva
            a[j] = 1; // imposto il numero della maschera corrispondente ad 1 (ovvero lettera utilizzata per parola non compiuta)
            break; //rompo questo ciclo e ritorno a quello in cui do a p la stringa successiva
          }
        } // fine del ciclo che confronta una lettera della parola,  con tutte le lettere dela stringa random
      } // fine del ciclo che percorre tutto l'array di puntatori
      //controllata ogni stringa random con la lettera della parola...
      if(count == 0){ //...se una lettera di una parola non trova corrispondenza, è inutile verificare le altre
        mask_changer(mask, array, user, 2); //la funzione ripristina la mascher di int a seconda del modo in cui viene chiamata, chiamata con mode 2 riporta gli int di valore 1 a 0
        count = 0; //azzero il conteggio delle lettere che hanno trovato corrispondenza
        break; // rompo quindi il ciclo e ottengo una nuova parola
      }
    } // fine del ciclo che passa alla lettera successiva
    if(count == len){ //se vedo che ogni lettera ha trovato una corrispondenza
      word_count++; //incremento il numero di parole possibili
      mask_changer(mask, array, user, 1); //faccio un update della maschera, con mode = 1, porto gli int da 1 a 2
      char *word = malloc(len*(sizeof(char))+1); //creo una stringa della stessa lungheza della parola trovata
      strcpy(word, file_str); // e copio la parola trovata dentro essa
      list[word_count-1] = word; //uso il numero delle parole trovate -1 per scorrere gli elementi dell'array di puntatori, partendo da 0
      count = 0; //azzero il conteggio delle lettere trovate

    }
  } //fine del while che prende ogni parola
  if(word_count == 0){
    printf("Non è stato possibile generare nessuna parola\n");

  }
  else{
    printf("Si possono generare %d parole:\n", word_count);
    for(int i = 0; i < word_count; i++){ //stampo tutti gli elementi dell'array contenente le parole generate
      printf("%s\n", *(list+i));
    }
  }
  for(int i = 0; i < word_count; i++){ //libero ogni cella di memoria utiizzata per stampare
    free(list[i]);
  }
  free(list);
}





void mask_changer(int **mask, char **array, int user, int mode){ //chimata con il parametro mode = 1 aggiorna i numeri da 1 a 2, chimata con mode = 2 riporta i numeri con valore 1 a 0
  for (int i = 0; i < user; i++){
    int  *num = mask[i];
    for(int j = 0; j < (sizeof(num)/sizeof(int)); j++){
      if(num[j] == 1){
        if(mode == 1)
        num[j] = 2;
        }
        else if(mode == 2){
          num[j] = 0;
        }
      }
    }
  }
