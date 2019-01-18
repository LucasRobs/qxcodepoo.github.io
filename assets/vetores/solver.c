#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 10000
#define read(ptr) strsep(&ptr, " ")

//funcoes auxiliares, definidas apos a main
bool eq(const char * a, const char * b);
void readline(char * line);


void vet_show(int *vet, size_t size){
    printf("[ ");
    for(size_t i = 0; i < size; i++)
        printf("%d ", vet[i]);
    printf("]\n");
}

void vet_add(int *vet, size_t *size, int value){
    vet[*size] = value;
    *size += 1;
}

int vet_find(int * vet, size_t size, int value){
    for(size_t i = 0; i < size; i++)
        if(vet[i] == value)
            return i;
    return -1;
}

void vet_rmi(int * vet, size_t *size, int ind){
    if(ind < 0 || ind >= *size){
        puts("fail");
        return;
    }
    for(int i = ind; i < *size - 1; i++)
        vet[i] = vet[i + 1];
    *size -= 1;
}

void vet_rma(int * vet, size_t *size, int value){
    for(int i = (*size - 1); i >= 0; i--)
        if(vet[i] == value)
            vet_rmi(vet, size, i);
}


int main(){
    int vet[MAX];
    size_t size = 0;


    char buffer[MAX];
    char * ptr;               //como vou navegar pela linha
    char * token = NULL;      //onde vou guardar os token
    char * cmd = NULL;        //onde vou guardar o comando
    while(true){
        readline(buffer);
        ptr = buffer;
        printf("$%s\n", ptr);
        cmd = read(ptr);
        if(eq(cmd, "end")){
            break;
        }else if(eq(cmd, "add")){
            while((token = read(ptr))){ //enquanto conseguir retirar tokens
                vet_add(vet, &size, atoi(token)); //converte pra inteiro e imprime
            }
        }else if(eq(cmd, "show")){
            vet_show(vet, size);
        }else if(eq(cmd, "find")){
            printf("[ ");
            while((token = read(ptr))){ //enquanto conseguir retirar tokens
                printf("%d ", vet_find(vet, size, atoi(token))); //converte pra inteiro e imprime
            }
            printf("]\n");
        }else if(eq(cmd, "rmi")){
            int ind = atoi(read(ptr));
            vet_rmi(vet, &size, ind);
        }else if(eq(cmd, "rma")){
            int value = atoi(read(ptr));
            vet_rma(vet, &size, value);
        }else{
            puts("Comando invalido");
        }
    }
    return 0;
}

bool eq(const char * a, const char * b){
    return strcmp(a, b) == 0;
}

void readline(char * line){
    fgets(line, MAX, stdin);
    line[strcspn(line, "\n")] = '\0'; //tirar o \n
}
