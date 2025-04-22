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

Nodo *buscarNodoPorId(Nodo *Start, int IdBuscado);

Nodo *buscarNodoPorPalabra(Nodo *Start, char palabra[]);

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
        Nodo *nuevo = buscarNodoPorId(TPendientes, idTarea);
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

        do // control de si se ingresa marcar otra tarea como realizada o no
        {
            fflush(stdin);
            printf("\n\tDesea marcar como realizada otra tarea(si/no):");
            gets(opc);
        } while (strcmp(opc, "si") != 0 && strcmp(opc, "no") != 0);
    } while (strcmp(opc, "si") == 0);

    mostrarListas(TPendientes, TRealizadas);

    fflush(stdin);
    printf("\n\tBuscar tarea por 'palabra' o por 'ID': ");
    fgets(opc, sizeof(opc), stdin);
    opc[strcspn(opc, "\n")] = 0; // Eliminar el salto de línea

    while (strcmp(opc, "palabra") != 0 && strcmp(opc, "ID") != 0) // controla si se ingreso "palabra" o "ID"
    {
        printf("\tOpcion no valida. Ingrese 'palabra' o 'ID': ");
        fgets(opc, sizeof(opc), stdin);
        opc[strcspn(opc, "\n")] = 0; // Eliminar el salto de línea
    }

    while (strcmp(opc, "palabra") != 0 && strcmp(opc, "ID") != 0) // controla si se ingreso "palabra" o "ID"
    {
        printf("\tOpcion no valida. Ingrese 'palabra' o 'ID': ");
        fgets(opc, sizeof(opc), stdin);
        opc[strcspn(opc, "\n")] = 0; // Eliminar el salto de línea
    }

    if (strcmp(opc, "palabra") == 0) // controla si se ingreso "palabra"
    {
        printf("\n\tIngrese la palabra a buscar: ");
        char palabraBuscada[30];
        scanf("%s", palabraBuscada);

        Nodo *NodoPalabra1 = buscarNodoPorPalabra(TPendientes, palabraBuscada);
        Nodo *NodoPalabra2 = buscarNodoPorPalabra(TRealizadas, palabraBuscada);

        if (NodoPalabra1 != NULL && NodoPalabra2 != NULL)
        {
            printf("\n\tPalabra encontrada en ambas listas\n");
            printf("\n******Lista Pendientes******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", NodoPalabra1->T.TareaID);
            printf("\n\tDescripcion: %s ", NodoPalabra1->T.Descripcion);
            printf("\n\tDuracion %ds", NodoPalabra1->T.Duracion);
            printf("\n******Lista Reslizadas******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", NodoPalabra2->T.TareaID);
            printf("\n\tDescripcion: %s ", NodoPalabra2->T.Descripcion);
            printf("\n\tDuracion %ds", NodoPalabra2->T.Duracion);
        }
        else if (NodoPalabra1 != NULL)
        {
            printf("\n\tPalabra encontrada en lista de tareas pendientes\n");
            printf("\n******Lista Pendientes******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", NodoPalabra1->T.TareaID);
            printf("\n\tDescripcion: %s ", NodoPalabra1->T.Descripcion);
            printf("\n\tDuracion %ds", NodoPalabra1->T.Duracion);
        }
        else if (NodoPalabra2 != NULL)
        {
            printf("\n\tPalabra encontrada en lista de tareas realizadas\n");
            printf("\n******Lista Pendientes******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", NodoPalabra2->T.TareaID);
            printf("\n\tDescripcion: %s ", NodoPalabra2->T.Descripcion);
            printf("\n\tDuracion %ds", NodoPalabra2->T.Duracion);
        }
        else
        {
            printf("\tPalabra no encontrado en las listas...\n");
        }
    }

    if (strcmp(opc, "ID") == 0) // controla si se ingreso "ID"
    {
        printf("\n\tIngrese el ID de la tarea a buscar: ");
        int ID;
        scanf("%d", &ID);

        Nodo* nodoId1 = buscarNodoPorId(TPendientes, ID);
        Nodo* nodoId2 = buscarNodoPorId(TRealizadas, ID);

        if (nodoId1 != NULL)
        {
            printf("\n\tID encontrado en lista de tareas pendientes\n");
            printf("\n******Lista Pendientes******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", nodoId1->T.TareaID);
            printf("\n\tDescripcion: %s ", nodoId1->T.Descripcion);
            printf("\n\tDuracion %ds", nodoId1->T.Duracion);
        }
        else if (nodoId2 != NULL)
        {
            printf("\n\tID encontrado en lista de tareas realizadas\n");
            printf("\n******Lista Pendientes******\n");
            printf("\nTarea: ");
            printf("\n\tID: %d ", nodoId2->T.TareaID);
            printf("\n\tDescripcion: %s ", nodoId2->T.Descripcion);
            printf("\n\tDuracion %ds", nodoId2->T.Duracion);
        }
        else
        {
            printf("\tId no encontrado en las listas\n");
        }
    }

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

Nodo *buscarNodoPorId(Nodo *Start, int IdBuscado)
{
    Nodo *Aux = Start;
    while (Aux && Aux->T.TareaID != IdBuscado)
    {
        Aux = Aux->Siguiente;
    }
    return Aux;
}

Nodo *buscarNodoPorPalabra(Nodo *Start, char palabra[])
{
    Nodo *Aux = Start;
    while (Aux && strstr(Aux->T.Descripcion, palabra) == NULL)
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
