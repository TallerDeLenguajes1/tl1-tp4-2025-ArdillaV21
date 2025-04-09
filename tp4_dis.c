#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_DESC 100

struct Tarea{
    int TareaID; //Numerico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 - 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;

}typedef Nodo;


Tarea PedirTareas(){
    int ID_incremental = 1000;
    Tarea nueva;
    nueva.TareaID = ID_incremental++;

    char buffer[TAM_DESC];
    printf("Ingrese la descripcion de la tarea: \n");
    getchar();
    fgets(buffer,TAM_DESC,stdin);
    buffer[strcspn(buffer,"\n")] = 0;

    nueva.Descripcion = (char *) malloc(strlen(buffer + 1) * sizeof(char));

    do{
        printf("Ingrese la duracion de la tarea: ");
        scanf("%d", &nueva.Duracion);
    }while(nueva.Duracion<10 || nueva.Duracion>100);
    
    return nueva;
}

int main(){
    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;

    PedirTareas();

    return 0;
}