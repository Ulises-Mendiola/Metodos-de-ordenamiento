#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------------------------------------------------- Estructuras --------------------------------------------------*/

// Definición de la estructura Persona
struct Persona {
    char nombre[50];
    char apellidoPaterno[50];
    char apellidoMaterno[50];
    int edad;
    char correo[50];
};

// Nodo para listas y árboles
struct Nodo {
    struct Persona datos;
    struct Nodo* siguiente;
};

// Estructura para la pila
struct Pila {
    struct Nodo* tope;
};

// Estructura para el árbol binario de búsqueda
struct NodoArbol {
    struct Persona datos;
    struct NodoArbol* izquierda;
    struct NodoArbol* derecha;
};

// Estructura para el árbol
struct Arbol {
    struct NodoArbol* raiz;
};

// Estructura para la cola
struct Cola {
    struct Nodo* frente;
    struct Nodo* final;
};

// Estructura para la lista
struct Lista {
    struct Nodo* inicio;
};

/* -------------------------------------------------- Funciones auxiliares --------------------------------------------------*/

// Funciones para cada estructura
void menuPilas();
void menuColas();
void menuListas();
void menuArboles();
void menuOrdenamientoInsercion();

// Funciones auxiliares para las pilas
void inicializarPila(struct Pila* pila);
void push(struct Pila* pila, struct Persona datos);
void pop(struct Pila* pila);
void mostrarPila(struct Pila pila);
void modificarPila(struct Pila* pila);

// Funciones auxiliares para el árbol
struct NodoArbol* crearNodoArbol(struct Persona datos);
void insertarEnArbol(struct Arbol* arbol, struct Persona datos);
void mostrarArbolInOrden(struct NodoArbol* nodo);

// Funciones auxiliares para las colas
void inicializarCola(struct Cola* cola);
void encolar(struct Cola* cola, struct Persona datos);
void desencolar(struct Cola* cola);
void mostrarCola(struct Cola cola);

// Funciones auxiliares para las listas
void inicializarLista(struct Lista* lista);
void insertarAlInicio(struct Lista* lista, struct Persona datos);
void mostrarLista(struct Lista lista);
void eliminarLista(struct Lista* lista);

// Funciones auxiliares para el ordenamiento por inserción
void ordenamientoInsercion(struct Persona arreglo[], int n);
void mostrarArreglo(struct Persona arreglo[], int n);

/* -------------------------------------------------- MAIN --------------------------------------------------*/


int main() {
    int opcion;

    do {
        printf("\nMenú Principal:\n");
        printf("1. Pilas\n");
        printf("2. Colas\n");
        printf("3. Listas\n");
        printf("4. Árboles\n");
        printf("5. Método de Ordenamiento por Inserción\n");
        printf("0. Salir\n");
        printf("\n\nIngrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuPilas();
                break;
            case 2:
                menuColas();
                break;
            case 3:
                menuListas();
                break;
            case 4:
                menuArboles();
                break;
            case 5:
                menuOrdenamientoInsercion();
                break;
            case 0:
                printf("\n\nSaliendo del programa. ¡Hasta luego!\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 0);

    return 0;
}

// Funciones de cada estructura

/* --------------------------------------------------------------- PILAS ---------------------------------------------------------------*/

void menuPilas() {
    struct Pila pila;
    inicializarPila(&pila);

    int opcion;

    do {
        printf("\nMenú de Pilas:\n");
        printf("1. Agregar persona\n");
        printf("2. Modificar persona\n");
        printf("3. Eliminar persona\n");
        printf("4. Mostrar pilas\n");
        printf("0. Volver al menú principal\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                struct Persona nuevaPersona;
                printf("\nIngrese el nombre: ");
                scanf("%s", nuevaPersona.nombre);
                printf("Ingrese los apellidos (paterno materno): ");
				scanf("%s %s", nuevaPersona.apellidoPaterno, nuevaPersona.apellidoMaterno);
                printf("Ingrese la edad: ");
                scanf("%d", &nuevaPersona.edad);
                printf("Ingrese el correo electrónico: ");
                scanf("%s", nuevaPersona.correo);

                push(&pila, nuevaPersona);
                printf("Persona agregada a la pila.\n");
                break;
            }
            case 2:
                modificarPila(&pila);
                break;
            case 3:
                pop(&pila);
                break;
            case 4:
                mostrarPila(pila);
                break;
            case 0:
                printf("\n\nVolviendo al menú principal.\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 0);
}

void inicializarPila(struct Pila* pila) {
    pila->tope = NULL;
}

void push(struct Pila* pila, struct Persona datos) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("\nError: No se pudo asignar memoria para el nuevo nodo.\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->datos = datos;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

void pop(struct Pila* pila) {
    if (pila->tope == NULL) {
        printf("La pila está vacía. No se puede eliminar.\n");
        return;
    }

    struct Nodo* temp = pila->tope;
    pila->tope = temp->siguiente;
    free(temp);
}

void mostrarPila(struct Pila pila) {
    if (pila.tope == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    printf("Contenido de la pila:\n");
    struct Nodo* actual = pila.tope;
    while (actual != NULL) {
    	printf("+-------------------------------+");
    	printf("\n|	      PILAS   	        |");
    	printf("\n+-------------------------------+");
        printf("\n  Nombre: %s, \n  Apellido Paterno: %s, \n  Apellido Materno: %s, \n  Edad: %d, \n  Correo: %s\n",
       actual->datos.nombre, actual->datos.apellidoPaterno, actual->datos.apellidoMaterno,
       actual->datos.edad, actual->datos.correo);
        printf("+-------------------------------+\n");
        actual = actual->siguiente;
    }
}

void modificarPila(struct Pila* pila) {
    char nombreBuscar[50];
    printf("\n\nIngrese el nombre de la persona a modificar: ");
    scanf("%s", nombreBuscar);

    struct Nodo* actual = pila->tope;

    while (actual != NULL) {
        if (strcmp(actual->datos.nombre, nombreBuscar) == 0) {
            // Persona encontrada, permite modificar los datos
            printf("Nueva información para %s:\n", nombreBuscar);
    
            printf("Ingrese el nuevo nombre: ");
            scanf("%s", actual->datos.nombre);
    
            printf("Ingrese el nuevo apellido paterno: ");
            scanf("%s", actual->datos.apellidoPaterno);
    
            printf("Ingrese el nuevo apellido materno: ");
            scanf("%s", actual->datos.apellidoMaterno);
    
            printf("Ingrese la nueva edad: ");
            scanf("%d", &actual->datos.edad);
    
            printf("Ingrese el nuevo correo electrónico: ");
            scanf("%s", actual->datos.correo);

            printf("\nInformación modificada con éxito.\n");
            return;
        }
        actual = actual->siguiente;
    }

    // Si llega aquí, no se encontró la persona
    printf("\nNo se encontró la persona con nombre %s en la pila.\n", nombreBuscar);
}


/* --------------------------------------------------------------- COLAS ---------------------------------------------------------------*/
void menuColas() {
    struct Cola cola;
    inicializarCola(&cola);

    int opcion;

    do {
        printf("\nMenú de Colas:\n");
        printf("1. Agregar persona a la cola\n");
        printf("2. Eliminar persona de la cola\n");
        printf("3. Mostrar cola\n");
        printf("0. Volver al menú principal\n");
        printf("\n\nIngrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                struct Persona nuevaPersona;
                printf("\nIngrese el nombre: ");
                scanf("%s", nuevaPersona.nombre);
                printf("Ingrese los apellidos (paterno materno): ");
				scanf("%s %s", nuevaPersona.apellidoPaterno, nuevaPersona.apellidoMaterno);
                printf("Ingrese la edad: ");
                scanf("%d", &nuevaPersona.edad);
                printf("Ingrese el correo electrónico: ");
                scanf("%s", nuevaPersona.correo);

                encolar(&cola, nuevaPersona);
                printf("\nPersona agregada a la cola.\n");
                break;
            }
            case 2:
                desencolar(&cola);
                break;
            case 3:
                mostrarCola(cola);
                break;
            case 0:
                printf("\n\nVolviendo al menú principal.\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 0);
}

void inicializarCola(struct Cola* cola) {
    cola->frente = NULL;
    cola->final = NULL;
}

void encolar(struct Cola* cola, struct Persona datos) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("\nError: No se pudo asignar memoria para el nuevo nodo de la cola.\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->datos = datos;
    nuevoNodo->siguiente = NULL;

    if (cola->final == NULL) {
        cola->frente = nuevoNodo;
        cola->final = nuevoNodo;
    } else {
        cola->final->siguiente = nuevoNodo;
        cola->final = nuevoNodo;
    }
}

void desencolar(struct Cola* cola) {
    if (cola->frente == NULL) {
        printf("\nLa cola está vacía. No se puede desencolar.\n");
        return;
    }

    struct Nodo* temp = cola->frente;
    cola->frente = temp->siguiente;

    if (cola->frente == NULL) {
        // Si la cola está vacía, también actualiza el puntero al final
        cola->final = NULL;
    }

    free(temp);
}

void mostrarCola(struct Cola cola) {
    if (cola.frente == NULL) {
        printf("\nLa cola está vacía.\n");
        return;
    }

    printf("\nContenido de la cola:\n");
    struct Nodo* actual = cola.frente;
    while (actual != NULL) {
        printf("+-------------------------------+");
        printf("\n|	      COLAS   	        |");
        printf("\n+-------------------------------+");
        printf("\n  Nombre: %s, \n  Apellido Paterno: %s, \n  Apellido Materno: %s, \n  Edad: %d, \n  Correo: %s\n",
       actual->datos.nombre, actual->datos.apellidoPaterno, actual->datos.apellidoMaterno,
       actual->datos.edad, actual->datos.correo);
        printf("+-------------------------------+\n");
        actual = actual->siguiente;
    }
}


/* --------------------------------------------------------------- LISTAS ---------------------------------------------------------------*/
void menuListas() {
    struct Lista lista;
    inicializarLista(&lista);

    int opcion;

    do {
        printf("\nMenú de Listas:\n");
        printf("1. Agregar persona al inicio de la lista\n");
        printf("2. Mostrar lista\n");
        printf("3. Eliminar lista\n");
        printf("0. Volver al menú principal\n");
        printf("\n\nIngrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                struct Persona nuevaPersona;
                printf("\nIngrese el nombre: ");
                scanf("%s", nuevaPersona.nombre);
                printf("Ingrese los apellidos (paterno materno): ");
				scanf("%s %s", nuevaPersona.apellidoPaterno, nuevaPersona.apellidoMaterno);
                printf("Ingrese la edad: ");
                scanf("%d", &nuevaPersona.edad);
                printf("Ingrese el correo electrónico: ");
                scanf("%s", nuevaPersona.correo);

                insertarAlInicio(&lista, nuevaPersona);
                printf("\nPersona agregada al inicio de la lista.\n");
                break;
            }
            case 2:
                mostrarLista(lista);
                break;
            case 3:
                eliminarLista(&lista);
                printf("\nLista eliminada.\n");
                break;
            case 0:
                printf("\n\nVolviendo al menú principal.\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 0);
}

void inicializarLista(struct Lista* lista) {
    lista->inicio = NULL;
}

void insertarAlInicio(struct Lista* lista, struct Persona datos) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    if (nuevoNodo == NULL) {
        printf("\nError: No se pudo asignar memoria para el nuevo nodo de la lista.\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->datos = datos;
    nuevoNodo->siguiente = lista->inicio;
    lista->inicio = nuevoNodo;
}

void mostrarLista(struct Lista lista) {
    if (lista.inicio == NULL) {
    	printf("+-------------------------------+\n");
        printf("La lista está vacía.\n");
        printf("+-------------------------------+");
        return;
    }

    printf("\nContenido de la lista:\n");
    struct Nodo* actual = lista.inicio;
    while (actual != NULL) {
        printf("+-------------------------------+");
        printf("\n|	      LISTAS   	        |");
        printf("\n+-------------------------------+");
        printf("\n  Nombre: %s, \n  Apellido Paterno: %s, \n  Apellido Materno: %s, \n  Edad: %d, \n  Correo: %s\n",
       actual->datos.nombre, actual->datos.apellidoPaterno, actual->datos.apellidoMaterno,
       actual->datos.edad, actual->datos.correo);
        printf("+-------------------------------+\n");
        actual = actual->siguiente;
    }
}

void eliminarLista(struct Lista* lista) {
    while (lista->inicio != NULL) {
        struct Nodo* temp = lista->inicio;
        lista->inicio = temp->siguiente;
        free(temp);
    }
}


/* --------------------------------------------------------------- ARBOLES ---------------------------------------------------------------*/
void menuArboles() {
    struct Arbol arbol;
    arbol.raiz = NULL;

    int opcion;

    do {
        printf("\nMenú de Árboles:\n");
        printf("1. Agregar persona\n");
        printf("2. Mostrar personas en orden\n");
        printf("0. Volver al menú principal\n");
        printf("\nIngrese su opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                struct Persona nuevaPersona;
                printf("\nIngrese el nombre: ");
                scanf("%s", nuevaPersona.nombre);
                printf("Ingrese los apellidos (paterno materno): ");
				scanf("%s %s", nuevaPersona.apellidoPaterno, nuevaPersona.apellidoMaterno);
                printf("Ingrese la edad: ");
                scanf("%d", &nuevaPersona.edad);
                printf("Ingrese el correo electrónico: ");
                scanf("%s", nuevaPersona.correo);

                insertarEnArbol(&arbol, nuevaPersona);
                printf("\nPersona agregada al árbol.\n");
                break;
            }
            case 2:
            	printf("+-------------------------------+");
                printf("\nPersonas en orden:\n");
                mostrarArbolInOrden(arbol.raiz);
                printf("+-------------------------------+");
                break;
            case 0:
                printf("\n\nVolviendo al menú principal.\n");
                break;
            default:
                printf("\nOpción no válida. Por favor, ingrese una opción válida.\n");
        }
    } while (opcion != 0);
}

struct NodoArbol* crearNodoArbol(struct Persona datos) {
    struct NodoArbol* nuevoNodo = (struct NodoArbol*)malloc(sizeof(struct NodoArbol));
    if (nuevoNodo == NULL) {
        printf("\nError: No se pudo asignar memoria para el nuevo nodo del árbol.\n");
        exit(EXIT_FAILURE);
    }

    nuevoNodo->datos = datos;
    nuevoNodo->izquierda = NULL;
    nuevoNodo->derecha = NULL;
    return nuevoNodo;
}

void insertarEnArbol(struct Arbol* arbol, struct Persona datos) {
    if (arbol->raiz == NULL) {
        arbol->raiz = crearNodoArbol(datos);
    } else {
        struct NodoArbol* actual = arbol->raiz;
        while (1) {
            if (strcmp(datos.nombre, actual->datos.nombre) < 0) {
                if (actual->izquierda == NULL) {
                    actual->izquierda = crearNodoArbol(datos);
                    break;
                } else {
                    actual = actual->izquierda;
                }
            } else if (strcmp(datos.nombre, actual->datos.nombre) > 0) {
                if (actual->derecha == NULL) {
                    actual->derecha = crearNodoArbol(datos);
                    break;
                } else {
                    actual = actual->derecha;
                }
            } else {
                // Ignora duplicados (puedes decidir qué hacer en este caso)
                printf("\nLa persona con nombre %s ya existe en el árbol. Ignorando duplicado.\n", datos.nombre);
                break;
            }
        }
    }
}

void mostrarArbolInOrden(struct NodoArbol* nodo) {
    if (nodo != NULL) {
        mostrarArbolInOrden(nodo->izquierda);
        printf("\n  Nombre: %s, \n  Apellido Paterno: %s, \n  Apellido Materno: %s, \n  Edad: %d, \n  Correo: %s\n",
       nodo->datos.nombre, nodo->datos.apellidoPaterno, nodo->datos.apellidoMaterno,
       nodo->datos.edad, nodo->datos.correo);
        mostrarArbolInOrden(nodo->derecha);
    }
}

/* --------------------------------------------------------------- ORDENAMIENTO INSERCION ---------------------------------------------------------------*/
void menuOrdenamientoInsercion() {
    int n;

    printf("\nIngrese la cantidad de personas para el ordenamiento: ");
    scanf("%d", &n);

    struct Persona personas[n];

    for (int i = 0; i < n; ++i) {
        struct Persona nuevaPersona;  // Declarar nuevaPersona aquí
        printf("\nIngrese el nombre: ");
        scanf("%s", nuevaPersona.nombre);
        printf("Ingrese los apellidos (paterno materno): ");
        scanf("%s %s", nuevaPersona.apellidoPaterno, nuevaPersona.apellidoMaterno);
        printf("Ingrese la edad: ");
        scanf("%d", &nuevaPersona.edad);
        printf("Ingrese el correo electrónico: ");
        scanf("%s", nuevaPersona.correo);

        personas[i] = nuevaPersona;  // Asignar nuevaPersona al arreglo
    }

    printf("\n\nPersonas antes del ordenamiento:\n");
    mostrarArreglo(personas, n);

    ordenamientoInsercion(personas, n);

    printf("\n\nPersonas después del ordenamiento por inserción:\n");
    mostrarArreglo(personas, n);
}


void ordenamientoInsercion(struct Persona arreglo[], int n) {
    int i, j;
    struct Persona actual;

    for (i = 1; i < n; ++i) {
        actual = arreglo[i];
        j = i - 1;

        while (j >= 0 && strcmp(arreglo[j].nombre, actual.nombre) > 0) {
            arreglo[j + 1] = arreglo[j];
            --j;
        }

        arreglo[j + 1] = actual;
    }
}

void mostrarArreglo(struct Persona arreglo[], int n) {
    printf("Contenido del arreglo:\n");
    for (int i = 0; i < n; ++i) {
        printf("+-------------------------------+");
        printf("\n|	      ORDENAMIENTO   	    |");
        printf("\n+-------------------------------+");
        printf("\n  Nombre: %s, \n  Apellido Paterno: %s, \n  Apellido Materno: %s, \n  Edad: %d, \n  Correo: %s\n",
               arreglo[i].nombre, arreglo[i].apellidoPaterno, arreglo[i].apellidoMaterno,
               arreglo[i].edad, arreglo[i].correo);
        printf("+-------------------------------+\n");
    }
}
