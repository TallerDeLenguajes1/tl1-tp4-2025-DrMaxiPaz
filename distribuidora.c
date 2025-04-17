#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
};

typedef struct Tarea Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
};

typedef struct Nodo Nodo;
typedef struct Nodo *Lista;

Lista crearlistaVacia();

Nodo *CrearNodo(Tarea T);

void InsertarNodo(Lista* L, Nodo *Nodo);

bool esListaVacia(Lista L);

void mostrar(Lista L);

int longitud(Lista L);

int main()
{
    Lista TPendientes = crearlistaVacia();
    Lista TRealizadas = crearlistaVacia();
    int orden = 1000;
    char opc[10];
    char Buff[50];
    do
    {
        orden++;
        Tarea nuevaTarea;
        nuevaTarea.TareaID = orden; // asigno el ID
        printf("\n\tIngrese una tarea:");
        gets(Buff);
        nuevaTarea.Descripcion = (char *)malloc(strlen(Buff) + 1);
        strcpy(nuevaTarea.Descripcion, Buff); // asigno la descripcion
        do
        {
            printf("\n\tIngrese la duracion de la tarea (10-100):");
            scanf("%d", &nuevaTarea.Duracion); // asigno la duracion
        } while (nuevaTarea.Duracion < 10 || nuevaTarea.Duracion > 100);
        

        Nodo *TNodo;
        TNodo = CrearNodo(nuevaTarea);// $ creo un nuevo nodo con la tarea ingresada
        InsertarNodo(&TPendientes, TNodo);// ingreso el nodo en la lista
        do // control de si se ingresa otra tarea o no
        {
            fflush(stdin);
            printf("\n\tDesea ingresar otra tarea(si/no):");
            gets(opc);
        } while (strcmp(opc, "si") != 0 && strcmp(opc, "no") != 0);

    } while (strcmp(opc, "si") == 0);
    printf("Finalizando ingreso de tareas...\n");
    printf("\n\tcantidad de tareas:%d", longitud(TPendientes));

    mostrar(TPendientes);
    // libero la memoria
    for (int i = 0; i < longitud(TPendientes); i++)
    {
        free(TPendientes->T.Descripcion);
        free(TPendientes);
    }
    return 0;
}

Lista crearlistaVacia()
{
    Lista L;
    L = NULL;
    return L;
}

Nodo *CrearNodo(Tarea T)
{
    Nodo *NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T = T;
    NNodo->Siguiente = NULL;
    return NNodo;
}

void InsertarNodo(Lista* L, Nodo *Nodo)
{
    Nodo->Siguiente = *L;
    *L = Nodo;
}

bool esListaVacia(Lista L)
{
    return (L == NULL);
}

void mostrar(Lista L)
{

    while (!esListaVacia(L))
    {
        printf("\n\tTarea: ");
        printf("\n\tID: %d ", L->T.TareaID);
        printf("\n\tDescripcion: %s ", L->T.Descripcion);
        printf("\n\tDuracion %d ", L->T.Duracion);
        L = L->Siguiente;
    }
}

int longitud(Lista L)
{
    int cantidad = 0;
    while (L != NULL) // controla si es el ultimo elemento
    {
        cantidad++;
        L = L->Siguiente;
    }
    return cantidad;
}