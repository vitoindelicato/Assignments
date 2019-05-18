#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM 30
#define MENU 3



struct grid{   //struttura della lista contenente i piloti sulla griglia di partenza 
    char* pilot_grid;
    char* constructor;
    int pos;
    struct grid *next;
};
typedef struct grid grid;
typedef grid* gridptr;



struct pos_const{ //struttura di cui mi avvalgo per ritornare il nome del costruttore e la posizione in griglia di partenza
    char* constructor;
    int position;
};
typedef struct pos_const pos_const;



struct gen_lead{ //struttura della lista contenente la classifica generale definitiva
    char* pilot_lead;
    char* constructor;
    int pos;
    int hrs;
    int min;
    int sec;
    int mill;
    struct gen_lead* next;
};
typedef struct gen_lead gen_lead;
typedef gen_lead* gen_leadptr;



void podio(int x);
void best_pilot(int x);

void write_grid(FILE* fp1); //la funzione inserisce in lista i piloti in ordine di partenza
void insert_node_grid(gridptr *head_grid, char *a, char *b, int c);//questa sarà chiamata all'interno della soprascritta funzione
char *best_pil(FILE* fp2);
void read_times(FILE* fp3);
int confront(gen_leadptr new, gen_leadptr curr); //funzione che si occupa del confronto dei tempi per inserimento ordinato in lista
void print_file(FILE* fp4, gen_leadptr head_gen_lead);

void insert_node_gen_lead(gen_leadptr *head_gen_lead, char* name, int a, int b, int c, int d);
pos_const returner(gridptr* head_grid, char* pilot);

gridptr head_grid = NULL;
gen_leadptr head_gen_lead = NULL;





int main(int argc, char **argv){
int choice = 0;
 
 if(argc != 4){
    printf("Errore, inserire 3 argomenti : \"Nome programma\" \"Griglia di partenza\" \"Velocità\" \"Tempi dei piloti\" \n");
    return 0;
  }
  FILE* fp1; //griglia di partenza
  FILE* fp2; //topspeed
  FILE* fp3; //tempi
  FILE* fp4; //file csv da creare
  fp1 = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "r");
  fp3 = fopen(argv[3], "r");
  fp4 = fopen("D2.out", "w");


 void (*menu[DIM]) (int) = {podio, best_pilot, exit};
 while(choice == 0 || choice !=3){
    printf("Scegli un'opzione:\n\t1)Stampa il podio.\n\t2)Stampa il nome del miglior pilota.\n\t3)Esci dal programma.");

    while(scanf("%d", &choice) != 1 || choice != 1 || choice != 2){
        printf("Errore! Inserisci un numero valido!");
        scanf("%*[^\n]%*c");
    }
    (*menu[choice-1]) (choice-1);
 }





 if (fp1 == NULL || fp2 == NULL || fp3 == NULL){
        printf("Non è stato possibile aprire i file!\n");
        return 0;
    }



 write_grid(fp1);
 printf("%s", "The best pilot is:\n \t");
 char *name = best_pil(fp2);
 printf("%s\n", name);
 free(name);

 read_times(fp3);
 print_file(fp4, head_gen_lead);
 
 
 fclose(fp1);
 fclose(fp2);
 fclose(fp3);
 fclose(fp4);
    return 0;
}


void write_grid(FILE* fp){
    char p_name[DIM]; //pilot name
    char c_name[DIM]; //constructor name
    int i = 1; //counter for position
    while(fscanf(fp, "%[^\n]\n %[^\n]\n", c_name, p_name)!=EOF){
        insert_node_grid(&head_grid, c_name, p_name, i);
        i++;
    }
    
}





void insert_node_grid(gridptr *head_grid, char *a, char *b, int c){
    
    gridptr new_grid = malloc(sizeof(grid));
    if(new_grid == NULL){
       printf("Memoria non disponibile\n");
       exit(EXIT_FAILURE);
    }
    new_grid->constructor = malloc((strlen(a))+1);
    strcpy(new_grid->constructor, a);
    new_grid->pilot_grid = malloc((strlen(b))+1);
    strcpy(new_grid->pilot_grid, b);
    new_grid->pos = c;
    new_grid->next = NULL;

    gridptr tmp = *head_grid;


    if(*head_grid == NULL){
        *head_grid = new_grid;
    }
    else{
        while(tmp->next!= NULL){
            tmp = tmp->next; 
        }
        tmp->next = new_grid;
    }

}



char* best_pil(FILE* fp){
    char tmp_name [DIM];
    float a = 0.0;
    float b = 0.0;
    float c = 0.0;
    float d = 0.0;
    float top_speed = 0.0;
    float tmp_top_speed = 0.0;
    char* best_name = malloc(DIM);

    fscanf(fp, "%*[^\n]\n"); //skip first line of file


    while(fscanf(fp, "%s %f %f %f %f\n", tmp_name, &a, &b, &c, &d)!= EOF){
        
        if(a > b && a > c && a > d){
            tmp_top_speed = a;
        }
        if(b > a && b > c && b > c){
            tmp_top_speed = b;
        }
        if(c > a && c > b && c > d){
            tmp_top_speed = c;
        }
        if(d > a && d > b && d > c){
            tmp_top_speed = d;
        }

        if(tmp_top_speed > top_speed){
            top_speed = tmp_top_speed;
            best_name = realloc(best_name,strlen(tmp_name)+1);
            strcpy(best_name, tmp_name);
        }
    }
    return best_name;
}


void read_times(FILE* fp3){
    char file_name[DIM];
    int hrs = 0;
    int min = 0;
    int sec = 0;
    int mill = 0;
    while(fscanf(fp3, "%[^\n]\n %d:%d:%d.%d\n", file_name, &hrs, &min, &sec, &mill)!=EOF){
        insert_node_gen_lead(&head_gen_lead, file_name, hrs, min, sec, mill);
    }


}


void insert_node_gen_lead(gen_leadptr *head_gen_lead, char* file_name, int a, int b, int c, int d){
    gen_leadptr new = malloc(sizeof(gen_lead));
    if(new == NULL){
       printf("Memoria non disponibile\n");
       exit(EXIT_FAILURE);
    }
    else{
        new->pilot_lead = malloc(strlen(file_name)+1);
        strcpy(new->pilot_lead, file_name);
        new->hrs = a;
        new->min = b;
        new->sec = c;
        new->mill = d;
        pos_const data = returner(&head_grid, new->pilot_lead);
        new->constructor = malloc(strlen(data.constructor)+1);
        strcpy(new->constructor, data.constructor);
        free(data.constructor);
        new->pos = data.position;
        new->next = NULL;

        gen_leadptr curr = *head_gen_lead;
        gen_leadptr prev = NULL;
        if(*head_gen_lead == NULL){
            *head_gen_lead = new;
        }
        else{
            while(curr != NULL  && confront(new, curr) == 1){
               prev = curr;
               curr = curr->next;
            }
            if(prev == NULL){ // caso in cui nuovo nodo vad in testa
                new->next = curr;
                *head_gen_lead = new;
            }         
            else if (curr == NULL){ //caso in cui nuovo nodo deve andare in coda
                prev->next = new;
            
            }
            else{
                new->next = curr;
                prev->next = new;
            
            }
        } 
    }    
}


pos_const returner(gridptr* head_grid, char* pilot_lead){
    pos_const values;
    gridptr tmp = NULL;


    
    if((*head_grid) == NULL){
        printf("La lista contenente la griglia di partenza è vuota!");
        exit(EXIT_FAILURE);
    }



    if(strcmp((*head_grid)->pilot_grid, pilot_lead) == 0){
        values.constructor = malloc(strlen((*head_grid)->constructor)+1);
        strcpy(values.constructor, (*head_grid)->constructor);
        values.position = (*head_grid)->pos;

        tmp = (*head_grid);
        (*head_grid) = (*head_grid)->next;

        free(tmp->constructor);
        free(tmp->pilot_grid);
        free(tmp);
        
    }
    else{
        gridptr curr = (*head_grid);
        gridptr prev = NULL;
        while (curr != NULL && strcmp(curr->pilot_grid, pilot_lead)!=0){
            prev = curr;
            curr = curr->next;
        }
        if(curr != NULL){
            values.constructor = malloc(strlen(curr->constructor)+1);
            strcpy(values.constructor, curr->constructor);
            values.position = curr->pos;
            tmp = curr;
            prev->next = curr->next;
            free(tmp->constructor);
            free(tmp->pilot_grid);
            free(tmp);
            
        }
        
            
        
    }

    return values;
}



int confront(gen_leadptr new, gen_leadptr curr){
    
    if(curr->hrs == 0 && curr->min == 0 && curr->sec == 0 && curr->mill == 0){
        return 1;
    }

    if(new->hrs == 0 && new->min == 0 && new->sec == 0 && new->mill == 0){
        return 2;
    }



    if(new->hrs > curr->hrs){
        return 2;
    }
    else if (new->hrs < curr->hrs){
        return 1;
    }
    else{
        if (new->min > curr->min){
            return 2;
        }
        else if (new->min < curr->min){
            return 1;
        }
        else{
            if(new->sec > curr->sec){
                return 2;
            }
            else if (new->sec < curr->sec){
                return 1;
            }
            else{
                if(new->mill > curr->mill){
                    return 2;
                }
                else if(new->mill < curr->mill){
                    return 1;
                }
                else{
                  return 1;
                }
            }
        }    
    }
}



void print_file(FILE* fp4,gen_leadptr head_gen_lead){

   fprintf(fp4, "Pilota \t\t\t\t\t Costruttore \t\t Griglia \t\t\t Tempi\n\n");

   gen_leadptr tmp = head_gen_lead;

   while(head_gen_lead!=NULL){
      tmp = head_gen_lead;
      fprintf(fp4, "%-20s \t %-20s \t %-4d \t\t\t %02d:%02d:%02d.%03d\n", tmp->pilot_lead, tmp->constructor, tmp->pos, tmp->hrs, tmp->min, tmp->sec, tmp->mill);
      head_gen_lead = head_gen_lead->next;
      free(tmp->constructor);
      free(tmp->pilot_lead);
      free(tmp);
   }
}


      
void podio(int x){




}
void best_pilot(int x){



}