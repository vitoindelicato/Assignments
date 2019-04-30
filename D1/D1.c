#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DIM 6
#define SIZE 35
#define RAND 100

struct Prod{
  int code;
  char *name;
  float price;
  int qty;
  struct Prod *next;
};
typedef struct Prod prods;
typedef prods *prodsptr;



void print_menu();
void qty_var();
void price_var();
void insert_prod();
void delete_prod();
void search_prod();
void under_lim_prod();
void read_file(FILE *fp);
void insert_node(prodsptr *head ,int a, char b[], float c, int mode, int d);
void free_list(prodsptr head);
void print_list(prodsptr head);
void reverse_list(prodsptr *head);
void write_file(int limit);
FILE *fp;

prodsptr head = NULL;

int limit = 10;

int main(){
  srand(10);
  int choice = 0;
  fp = fopen("elencoProdotti.csv","r");

  if(fp==NULL){
    printf("Impossibile aprire il file, non vi è alcun prodotto memorizzato\n");
    return 0;
  }
  read_file(fp);
  print_list(head);
  void (*menu[DIM]) (int) = {qty_var, price_var, insert_prod, delete_prod, search_prod, under_lim_prod};

  do{
    printf("%d\n", limit);
    print_menu();
    while(scanf("%d", &choice)!=1 || choice <= 0){
      printf("Errore. Inserisci un numero intero positivo\n");
      scanf("%*[^\n]%*c");
    }
    if(choice == 7){
      break;
    }
    while(choice > 7){
      printf("Errore. Inserisci un numero compreso tra 1 e 7\n");
      scanf("%*[^\n]%*c");
      scanf("%d\n", &choice);
    }
    (menu[choice-1])(choice-1);
  }
  while(choice > 0 && choice <= 6);
  printf("Bye!\n");

  printf("\n\n\n");
  print_list(head);
  write_file(limit);
  free_list(head);



  return 0;
}








void read_file(FILE *fp){


  int code = 0;
  char name [SIZE];
  float price = 0;
  while(fscanf(fp, "%d;%[^;];%f\n", &code, name, &price)!=EOF){
    insert_node(&head,code, name, price, 0, 0);
  }
  fclose(fp);
}


void insert_node(prodsptr *head, int code, char name[], float price, int qty, int mode){
  prodsptr new = malloc(sizeof(prods));
  if(new == NULL){
    printf("Memoria non disponibile\n");
    exit(EXIT_FAILURE);
  }
  new->code = code;
  new->name = malloc((strlen(name))*sizeof(char)+1);
  strcpy(new->name, name);
  new->price = price;
  if(mode == 0){
    new->qty = rand() % RAND +1;
  }
  if(mode == 1){
    new->qty = qty;
  }
  prodsptr prev = NULL;
  prodsptr curr = *head;


  while(curr!=NULL && new->code > curr->code){
    prev = curr;
    curr = curr->next;
  }

  if(prev == NULL){
    new->next = *head;
    *head = new;
  }
  else{
    prev->next = new;
    new->next = curr;
  }

}


void print_list(prodsptr head){
   while(head!=NULL){
      printf("%-4d\t\t%-8s\t\t%-4.2f\t\t%-4d\n",head->code, head->name, head->price, head->qty);
      head = head->next;
   }


}





void print_menu(){
  printf("Scegliere un’opzione:\n 1 - variazione della quantità di un prodotto.\n 2 - variazione del prezzo di un prodotto.\n 3 - inserimento di un nuovo prodotto.\n 4 - eliminazione di un prodotto.\n 5 - Ricerca di un prodotto.\n 6 - Stampa prodotti sotto alla soglia.\n 7 - Esci):\n");
}



void qty_var(){
  int code = 0;
  prodsptr tmp;
  printf("Inserisci il codice del prodotto del quale vuoi modificare la quantità\n");
  do{
    tmp = head;
    while(scanf("%d", &code)!=1){
      printf("Errore. Il codice è formato solo da cifre!\n");
      scanf("%*[^\n]%*c");
    }
    while(tmp != NULL && code != tmp->code){
      tmp = tmp->next;
    }
    if(tmp == NULL){
      printf("Il codice inserito non appartiene a nessun prodotto memorizzato, ritentare\n");
    }
  }
  while(tmp == NULL);

  printf("Immetti la nuova quantità \n");
  while(scanf("%d", &(tmp->qty))!=1){
    printf("Errore. Inserisci una quantità\n");
    scanf("%*[^\n]%*c");
  }

}


void price_var(){
  int code = 0;
  prodsptr tmp;
  printf("Inserisci il codice del prodotto del quale vuoi modificare il prezzo\n");
  do{
    tmp = head;
    while(scanf("%d", &code)!=1){
      printf("Errore. Il codice è formato solo da cifre!\n");
      scanf("%*[^\n]%*c");
    }
    while(tmp != NULL && code != tmp->code){
      tmp = tmp->next;
    }
    if(tmp == NULL){
      printf("Il codice inserito non appartiene a nessun prodotto memorizzato, ritentare\n");
    }
  }
  while(tmp == NULL);
  printf("Immetti il nuovo prezzo \n");
  while(scanf("%f", &(tmp->price))!=1){
    printf("Errore. Inserisci una quantità\n");
    scanf("%*[^\n]%*c");
  }
}


void insert_prod(){
  int code = 0;
  char name[SIZE];
  float price = 0;
  int qty = 0;
  printf("Inserisci le caratteristiche del prodotto come segue:   #CODICE #NOME #PREZZO #QUANTIÀ\n");
  while(scanf("%d", &code)!=1){
    printf("Errore. Il codice è formato solo da cifre!\n");
    scanf("%*[^\n]%*c");
  }
  scanf("%s", name);
  while(scanf("%f", &price)!=1){
    printf("Errore. Nel prezzo non vanno inserite lettere!\n");
    scanf("%*[^\n]%*c");
  }
  while(scanf("%d", &qty)!=1){
    printf("Errore. Nella quantità non vanno inserite lettere!\n");
    scanf("%*[^\n]%*c");
  }
  insert_node(&head,code, name, price, qty, 1);
}


void delete_prod(){
  int code = 0;
  printf("Inserisci il codice del prodotto da eliminare\n");
  prodsptr curr;
  prodsptr prev;
    do{
      curr = head;
      while(scanf("%d", &code)!=1){
        printf("Errore. Il codice è formato solo da cifre!\n");
        scanf("%*[^\n]%*c");
      }
      while(curr != NULL && code != curr->code){
        prev = curr;
        curr = curr->next;
      }
      if(curr == NULL){
        printf("Il codice inserito non appartiene a nessun prodotto memorizzato, ritentare\n");
      }
    }
    while(curr == NULL);
    prev->next = curr->next;
    free(curr);
  }



void search_prod(){
  int code = 0;
  prodsptr tmp;
  printf("Inserire il codice del prodotto da cercare\n");
  do{
    tmp = head;
    while(scanf("%d", &code)!=1){
      printf("Errore. Il codice è formato solo da cifre!\n");
      scanf("%*[^\n]%*c");
    }
    while(tmp != NULL && code != tmp->code){
      tmp = tmp->next;
    }
    if(tmp == NULL){
      printf("Il codice inserito non appartiene a nessun prodotto memorizzato, ritentare\n");
    }
  }
  while(tmp == NULL);
  printf("%-4d\t\t%-8s\t\t%-4.2f\t\t%-4d\n",tmp->code, tmp->name, tmp->price, tmp->qty);

}



void under_lim_prod(){
  int flag = 0;
  prodsptr tmp = NULL;
  printf("Inserisci la soglia di riordino\n");
  while(scanf("%d", &limit)!=1){
    printf("Errore. Inserisci un intero\n");
    scanf("%*[^\n]%*c");
  }
  reverse_list(&head);
    tmp = head;
    while(tmp != NULL){
      if(tmp->qty < limit){
        printf("%-4d\t\t%-8s\t\t%-4.2f\t\t%-4d\n",tmp->code, tmp->name, tmp->price, tmp->qty);
        flag++;
      }
      tmp = tmp->next;
    }
    if(flag == 0){
      printf("Non vi è nessun prodotto sotto la soglia di riordino!\n");
    }
  reverse_list(&head);
}

void reverse_list(prodsptr *head){
  prodsptr curr = *head;
  prodsptr prev = NULL;
  prodsptr next = NULL;
  while (curr != NULL){
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
    *head = prev;

}




void write_file(int limit){
  int count = 0;
  int count_und = 0;
  prodsptr tmp = head;
  FILE *fp;
  FILE *fp1;
  fp = fopen("numeroTotale.txt", "w");
  fp1 = fopen("daORDINARE.bin", "w");
  if(fp == NULL || fp1 == NULL){
    printf("Non è stato possibile creare il file\n");
    exit(EXIT_FAILURE);
  }
  else{
    fprintf(fp1, "DI SEGUITO VI È LA LISTA DI PRODOTTI SOTTO LA SOGLIA DI RIORDINO:\n\nCODICE\t\tNOME\t\tUNITÀ DA RIORDINARE\n");
    while(tmp!=NULL){
      count++;
      if (tmp->qty < limit){
        count_und++;
        fprintf(fp1, "%-4d\t\t%-8s\t\t%-4d\n", tmp->code, tmp->name, limit-tmp->qty);
      }
      tmp = tmp->next;
    }
    fprintf(fp,"IN MAGAZZINO VI SONO:\n\n");
    fprintf(fp, "%-d\tProdotti diversi.\n%-d\tProdotti sotto la soglia di riordino.", count, count_und);
  }
  fclose(fp);
  fclose(fp1);

}


void free_list(prodsptr head){
  while(head != NULL){
    prodsptr tmp = head;
    head = head->next;
    free(tmp->name);
    free(tmp);

  }
}
