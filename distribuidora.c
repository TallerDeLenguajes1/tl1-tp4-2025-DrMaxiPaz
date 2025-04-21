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

void insertarNodo(Lista *L, Nodo *Nodo);

bool esListaVacia(Lista L);

void mostrar(Lista L);

int longitud(Lista L);

void mostrarListas(Lista LP, Lista LR);

Lista realizarTarea(Lista LP, Lista LR, int ID);

Nodo *buscarNodo(Nodo *Start, int IdBuscado);

void QuitarNodo(Nodo *Start, int ID);

int main()
{
    Lista TPendientes = crearlistaVacia();
    Lista TRealizadas = crearlistaVacia();
    int orden = 999;
    char opc[10];
    char Buff[50];
    Tarea nuevaTarea;
    do
    {
        orden++;
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
        TNodo = CrearNodo(nuevaTarea);     // creo un nuevo nodo con la tarea ingresada
        insertarNodo(&TPendientes, TNodo); // ingreso el nodo en la lista
        do                                 // control de si se ingresa otra tarea o no
        {
            fflush(stdin);
            printf("\n\tDesea ingresar otra tarea(si/no):");
            gets(opc);
        } while (strcmp(opc, "si") != 0 && strcmp(opc, "no") != 0);

    } while (strcmp(opc, "si") == 0);

    printf("Finalizando ingreso de tareas...\n");
    printf("\n\tcantidad de tareas:%d", longitud(TPendientes));

    fflush(stdin);
    int idTarea;
    do
    {
        mostrar(TPendientes);
        printf("\n\n\tMarcando las tareas realizadas");
        do
        {
            printf("\n\tIngrese el ID de la tarea realizada(>=1000): ");
            scanf("%d", &idTarea);
        } while (idTarea < 1000);
        Nodo *nuevo = buscarNodo(TPendientes, idTarea);
        if (nuevo == NULL)
        {
            printf("\n\tNo existe la tarea con el ID ingresado\n");
        }
        else
        {
            QuitarNodo(TPendientes, idTarea);
            insertarNodo(&TRealizadas, nuevo);
            printf("\n\tTarea marcada como realizada...\n");
        }

        /*printf("hola");
        TPendientes = realizarTarea(TPendientes, TRealizadas, idTarea);
        printf("papa");*/

        do // control de si se ingresa marca otra tarea como realizada o no
        {
            fflush(stdin);
            printf("\n\tDesea marcar como realizada otra tarea(si/no):");
            gets(opc);
        } while (strcmp(opc, "si") != 0 && strcmp(opc, "no") != 0);
    } while (strcmp(opc, "si") == 0);

    //    mostrar(TPendientes);
    mostrarListas(TPendientes, TRealizadas);

    for (int i = 0; i < longitud(TPendientes); i++) // libero la memoria de lista de tareas pendientes
    {
        free(TPendientes->T.Descripcion);
        free(TPendientes);
    }
    for (int i = 0; i < longitud(TRealizadas); i++) // libero la memoria de lista de tareas realizadas
    {
        free(TRealizadas->T.Descripcion);
        free(TRealizadas);
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

void insertarNodo(Lista *L, Nodo *Nodo)
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
    if (esListaVacia(L))
    {
        printf("\n\tNo hay tareas pendientes");
    }
    else
    {
        while (!esListaVacia(L))
        {
            printf("\nTarea: ");
            printf("\n\tID: %d ", L->T.TareaID);
            printf("\n\tDescripcion: %s ", L->T.Descripcion);
            printf("\n\tDuracion %ds", L->T.Duracion);
            L = L->Siguiente;
        }
    }
}

void mostrarListas(Lista LP, Lista LR)
{
    if (esListaVacia(LP))
    {
        printf("\n\tNo hay tareas pendientes...\n");
    }
    else
    {
        printf("\n******Lista de tareas pendientes******\n");
        while (!esListaVacia(LP))
        {
            printf("\nTarea: ");
            printf("\n\tID: %d ", LP->T.TareaID);
            printf("\n\tDescripcion: %s ", LP->T.Descripcion);
            printf("\n\tDuracion %ds", LP->T.Duracion);
            LP = LP->Siguiente;
        }
    }
    printf("\n");
    if (esListaVacia(LR))
    {
        printf("\n\tNo hay tareas realizadas...\n");
    }
    else
    {
        printf("\n\t******Lista de tareas realizadas******\n");
        while (!esListaVacia(LR))
        {
            printf("\nTarea: ");
            printf("\n\tID: %d", LR->T.TareaID);
            printf("\n\tDescripcion: %s", LR->T.Descripcion);
            printf("\n\tDuracion %ds", LR->T.Duracion);
            LR = LR->Siguiente;
        }
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

Nodo *buscarNodo(Nodo *Start, int IdBuscado)
{
    Nodo *Aux = Start;
    while (Aux && Aux->T.TareaID != IdBuscado)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

void QuitarNodo(Nodo *Start, int ID)
{
    Nodo **aux = &Start;
    while (*aux != NULL && (*aux)->T.TareaID != ID)
    {
        aux = &(*aux)->Siguiente;
    }
    if (*aux)
    {
        Nodo *temp = *aux;
        *aux = (*aux)->Siguiente;
        temp->Siguiente = NULL;
    }
}
