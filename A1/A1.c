#include <stdio.h>
#include <limits.h>
#define DIM 4 //dimensione dell'array

void insert(int choice);
void visc2(int choice);
void opposite(int choice);
void oppositec2(int choice);
void printmenu();
void display(int a);
void error();

const int BITS = sizeof(int)*CHAR_BIT; //costante intera necessaria a gestire il for per la stampa dei bit, si usa "CHAR_BIT" per una migliore portabilità
int x = 0;
int choice = 0;

int main(){

  void (*menu[DIM]) (int) = {insert, visc2, opposite, oppositec2}; //array di puntatori a funzioni
  error();
  printmenu(); // menu testuale
  while (choice > 0 && choice < 5){ //se il numero inserito è maggiore di 0 e minore di 5, il loop va avanti, richiamando la funzione nell'array
    (*menu[choice-1]) (choice-1); //nel paramentro vi è choice -1 in quanto nell'array la funzione corrispondente al numero 1 verà immagazzinata al posto 0, stessa cosa per le altre funzioni
    printmenu();
  }
  if(choice == 5){ //se la scelta inserita equivale a 5, si stampa un saluto
  printf("Bye\n");
 }
  return 0;
}

void display(int a){ //la funzione stampa a video direttamnete il complemento a 2 del numero
  int mask = 1 << BITS-1; //si crea una maschera per i bit
  for(short i = 1; i <= BITS; ++i){ // for che va da 1 al numero di bits
    putchar(a & mask ? '1' : '0');// se l'unione tra il valore a e la maschera è falsa, ritorna 0 altrimenti 1
    a <<= 1; //si fa scorrere il valore di un bit a destra
    if(i%4 == 0){ //condizione necessaria per formattare i bit in sequenze di 4
      putchar(' ');
    }
  }
  printf("\n");
}


void insert(int choice){ //inserisce un intero nella variabile x
  error();
}

void visc2(int choice){
  printf("La rappresentazione di %d in complemento a due (MSB) è: ", x); //stampa il numero inserito e successivamente il suo complemento a 2 tramite la funzione display
  display(x);
  printf("\n");

}

void opposite(int choice){
  printf("L'opposto di %d è %d", x, -(x)); //stampa il numero opposto
  printf("\n");

}

void oppositec2(int choice){
  int tmp = 0;
  tmp = -(x); //si affida l'opposto di x a una variabile temporanea per la stampa del c2 dell'opposto, in quanto l'input dell'utente non deve essere intaccato
  printf("La rappresentazione dell'opposto di %d in complemento a due (MSB) è: ", x); // stessa modalità di stampa delle altre funzioni
  display(tmp);
  printf("\n");

}

void printmenu(){ //menu testuale
  printf("Scegli un'opzione:\n\t1) Inserisci un nuovo numero.\n\t2) Stampa rappresentazione in complemento a due.\n\t3) Calcola opposto.\n\t4) Stampa rappresentazione in complemento a due dell'opposto.\n\t5) Esci.\n");
  printf("Scelta:  ");
  scanf("%d", &choice);
}


void error(){
  printf("Inserisci un numero intero: ");//primo input con pulzia del buffer e reinserimento in caso di errore
  while(scanf("%d", &x)!=1){
    printf("Errore. Inserisci un numero intero\n");
    scanf("%*[^\n]%*c");
  }
}
