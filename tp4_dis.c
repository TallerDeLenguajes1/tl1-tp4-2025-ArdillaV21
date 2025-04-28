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
void mostrar_lista(Nodo *lista, char* titulo);

int pedir_id_transferencia();
void transferir_tarea(Nodo **pendiente, Nodo **realizado);

Nodo *buscar_tarea_por_palabra(Nodo *lista, char *palabra);
Nodo* buscar_tarea_por_id(Nodo *lista, int id);

void liberar_lista(Nodo *lista);

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
            int opcion1;
            do
            {
                cargar_tarea(&listasPendientes, &ultimoID);
                printf("Desea agregar una nueva tarea pendiente?(0:Si, 1:NO)");
                scanf("%d",&opcion1);      
            } while (opcion1!=1);
        break;    
        case 1:
                if(listasPendientes == NULL){
                    printf("No hay tareas pendientes para transferir.\n");
                    break;
                }
                mostrar_lista(listasPendientes,"Pendientes");

                transferir_tarea(&listasPendientes, &listasRealizadas);
        break;
        case 2:
            int opcion2;
            do
            {
                printf("Desea ver las tareas pendientes?[0]\n");
                printf("Desea ver las tareas Realizadas?[1]\n");
                printf("Desea ver ambas listas?[2]\n");
                printf("Volver al menu[3]\n");
                scanf("%d",&opcion2);
                
                switch (opcion2)
                {
                    case 0:
                        mostrar_lista(listasPendientes,"Pendientes");
                    break;
                    case 1:
                        mostrar_lista(listasRealizadas,"Realizadas");
                    break;
                    case 2:
                        printf("---Listas de tareas pendientes y realizadas---\n");
                        mostrar_lista(listasPendientes,"Pendientes");
                        mostrar_lista(listasRealizadas,"Realizadas");
                    break;
                    default:

                    break;
                }
            } while (opcion2 !=3);
        break;
        case 3:
            int opcionBusqueda;
            printf("Como desea buscar?\n");
            printf("[0] Buscar por ID\n");
            printf("[1] Buscar por palabra clave\n");
            scanf("%d",&opcionBusqueda);

            if(opcionBusqueda == 0){
                int id;
                printf("Ingrese el ID a buscar: ");
                scanf("%d",&id);

                Nodo *encontrado = buscar_tarea_por_id(listasPendientes, id);
                if( encontrado != NULL){
                    printf("Tarea encontrada en listas PENDIENTES:\n");
                    mostrar_tarea(encontrado->T);
                }else{
                    encontrado = buscar_tarea_por_id(listasRealizadas, id);
                    if( encontrado != NULL){
                        printf("Tarea encontrada en listas REALIZADAS:\n");
                        mostrar_tarea(encontrado->T);
                }else{
                    printf("No se encontro ninguna tarea con ese ID.\n");
                }
            }
        }
        else if(opcionBusqueda == 1){
            char palabra[100];
            printf("Ingrese la palabra clave a buscar: ");
            getchar();
            fgets(palabra,sizeof(palabra),stdin);
            palabra[strcspn(palabra, "\n")] = 0;

            Nodo *encontrado = buscar_tarea_por_palabra(listasPendientes, palabra);
            if(encontrado != NULL){
                printf("Tarea encontrada en listas pendientes:\n");
                mostrar_tarea(encontrado->T);
            }else{
                encontrado = buscar_tarea_por_palabra(listasRealizadas,palabra);
                if(encontrado != NULL){
                    printf("Tarea encontrada en la lista de Realizadas:\n");
                    mostrar_tarea(encontrado->T);
                }else{
                    printf("No se encontro ninguna tarea que contenga esa palabra: \n");
                }
            }
        }else{
            printf("Opcion invalida.\n");
        }
        break;
        case 4:
            printf("Liberando memoria...\n");
            liberar_lista(listasPendientes);
            liberar_lista(listasRealizadas);
            printf("Memoria liberada correctamente. Fin del programa.\n");
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
    return nuevaTarea;
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

void mostrar_lista(Nodo *lista, char* titulo){
    if(lista == NULL){
        printf("La lista %s esta vacia\n", titulo);
        return;
    }

    Nodo *actual = lista;
    printf("La lista que muestra corresponde a %s\n",titulo);
    while (actual != NULL)
    {
        mostrar_tarea(actual->T);
        actual = actual->Siguiente;
    }
}

int pedir_id_transferencia(){
    int id;
    printf("Ingrese el ID de la tarea que desea transferir a realizadas: ");
    scanf("%d",&id);
    return id;
}

void transferir_tarea(Nodo **pendiente, Nodo **realizado){
    int idBuscado = pedir_id_transferencia();

    Nodo *actual = *pendiente;
    Nodo *anterior = NULL;

    while (actual !=NULL && actual->T.TareaID != idBuscado)
    {
        anterior = actual;
        actual = actual->Siguiente;
    }
    if(actual == NULL){
        printf("Tarea con ID %d no encontrada en la lista de pendientes.\n", idBuscado);
        return;
    }

    if(anterior == NULL){
        *pendiente = actual->Siguiente;
    }

    actual->Siguiente = *realizado;
    *realizado = actual;

    printf("Tarea transferida correctamente.\n");
}

Nodo* buscar_tarea_por_id(Nodo *lista, int id){
    Nodo *actual = lista;
    while (actual != NULL)
    {
        if(actual->T.TareaID == id){
            return actual;
        }
        actual= actual->Siguiente;
    }
    return NULL;
    
}

Nodo *buscar_tarea_por_palabra(Nodo *lista, char *palabra){
    Nodo *actual = lista;

    while (actual != NULL)
    {
        if(strstr(actual->T.Descripcion,palabra) != NULL){
            return actual;
        }
        actual = actual->Siguiente;
    }
    return NULL;
    
}

void liberar_lista(Nodo *lista){
    Nodo *aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->Siguiente;

        if(aux-> T.Descripcion !=NULL){
            free(aux->T.Descripcion);
        }
        free(aux);
    }
}