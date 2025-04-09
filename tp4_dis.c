#include <stdio.h>
#include <stdlib.h>

struct Tarea{
    int TareaID; //Numerico autoincremental comenzando en 1000
    char *Descripcion;
    int Duracion; // entre 10 - 100
}typedef Tarea;

struct Nodo{
    Tarea T;
    Nodo *Siguiente;

}typedef Nodo;

int main(){
    

    return 0;
}