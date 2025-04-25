#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Tarea{
    int TareaID; ;//Numérico autoincremental comenzando en 1000
    char *Descripcion; 
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;    
    struct Nodo *Siguiente;
}Nodo;

Nodo* crear_nodo(Tarea t){
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    if(nuevo == NULL) return NULL;
    nuevo->T.TareaID = t.TareaID;
    nuevo->T.Descripcion = t.Descripcion;
    nuevo->T.Duracion = t.Duracion;

    nuevo->Siguiente = NULL;

    return nuevo;
}

void insertar_nodo(Nodo **head, Tarea tarea){
    Nodo *nuevo = crear_nodo(tarea);
    if(nuevo == NULL) return;
    nuevo->Siguiente = *head;
    *head = nuevo;
}

Tarea pedir_datos_tarea(int *ultimoID);
void cargar_tarea(Nodo **listasPendientes, int *ultimoID);

void mostrar_tarea(Tarea t);
void mostrar_lista(Nodo *lista);

int main(){
    Nodo *listasPendientes = NULL;
    Nodo *listasRealizadas = NULL;
    int valor;
    int ultimoID = 1000;
    
    
    do
    {
        printf("---------------INTERFAZ TAREAS---------------------\n");
        printf("[0] Para cargar una tarea a pendientes.\n");
        printf("[1] Para transferir una tarea pendiente a realizada.\n");
        printf("[2] Ver listas de tareas.\n");
        printf("[3] Buscar una tarea por su id o palabra clave.\n");
        printf("[4] Para finalizar la ejecucion.\n");
        scanf("%d", &valor);
        switch (valor)
        {
        case 0:
            int opcion;
            do
            {
                cargar_tarea(&listasPendientes, &ultimoID);
                printf("Desea agregar una nueva tarea pendiente?(0:Si, 1:NO)");
                scanf("%d",&opcion);      
            } while (opcion!=1);
            break;    
        case 1:
                int opcion;
                pritf("Desea ver las tareas pendientes?[0]");
                pritf("Desea ver las tareas Realizadas?[1]");
                pritf("Desea ver ambas listas?[2]");
                scanf("%d",&opcion);
            break;
        case 2:
            /* code */
            break;
        case 3:
    
            break;
        default:
            break;
        };
    } while (valor!=4);
    

    return 0;
}

Tarea pedir_datos_tarea(int *ultimoID){
    Tarea nuevaTarea;
    char buffer[100];

    //Pedir Descripcion
    printf("Ingrese la descripcion de la tarea: ");
    getchar();
    fgets(buffer, sizeof(buffer),stdin);

    nuevaTarea.Descripcion = (char *)malloc(strlen(buffer) + 1);
    if(nuevaTarea.Descripcion != NULL){
        strcpy(nuevaTarea.Descripcion, buffer);
    }

    //Pedir duracion
    printf("Ingrese la duracion de la tarea(entre 10 y 100 minutos): ");
    scanf("%d",&nuevaTarea.Duracion);

    //Asignar ID
    nuevaTarea.TareaID = (*ultimoID)++;
}

void cargar_tarea(Nodo **listasPendientes, int *ultimoID){
    Tarea nuevaTarea = pedir_datos_tarea(ultimoID);
    insertar_nodo(listasPendientes, nuevaTarea);
    
}

void mostrar_tarea(Tarea t){
    printf("Tarea ID: %d\n", t.TareaID);
    printf("Descripcion: %s\n", t.Descripcion);
    printf("Duracion: %d\n", t.Duracion);
    printf("------------------------------------\n");
}

void mostrar_lista(Nodo *lista){
    if(lista == NULL){
        printf("La lista esta vacia\n");
        return;
    }

    Nodo *actual = lista;
    while (actual != NULL)
    {
        mostrar_tarea(actual->T);
        actual = actual->Siguiente;
    }
}