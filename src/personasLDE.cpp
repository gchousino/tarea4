#include "../include/personasLDE.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////


struct nodo_personasLDE {
    TPersona persona;
    struct nodo_personasLDE *siguiente;
    struct nodo_personasLDE *anterior;
};

struct rep_personasLDE {
    struct nodo_personasLDE *inicio;
    struct nodo_personasLDE *final;
    nat cantidad;
};

// Función auxiliar para liberar un nodo
static void liberarNodo(struct nodo_personasLDE *nodo) {
    if (nodo != NULL) {
        liberarTPersona(nodo->persona);
        delete nodo;
    }
}

TPersonasLDE crearTPersonasLDE(){
    TPersonasLDE lista = new rep_personasLDE;
    lista->inicio = NULL;
    lista->final = NULL;
    lista->cantidad = 0;
    return lista;
}

void insertarTPersonasLDE(TPersonasLDE &personas, TPersona persona, nat pos){
    // Crear un nuevo nodo
    struct nodo_personasLDE *nuevoNodo = new nodo_personasLDE;
    nuevoNodo->persona = persona;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    
    // Si la lista está vacía
    if (personas->cantidad == 0) {
        personas->inicio = nuevoNodo;
        personas->final = nuevoNodo;
        personas->cantidad = 1;
        return;
    }
    
    // Si pos es 1, insertar al inicio
    if (pos == 1) {
        nuevoNodo->siguiente = personas->inicio;
        personas->inicio->anterior = nuevoNodo;
        personas->inicio = nuevoNodo;
        personas->cantidad++;
        return;
    }
    
    // Si pos >= cantidad+1, insertar al final
    if (pos >= personas->cantidad + 1) {
        nuevoNodo->anterior = personas->final;
        personas->final->siguiente = nuevoNodo;
        personas->final = nuevoNodo;
        personas->cantidad++;
        return;
    }
    
    // Buscar la posición correcta
    struct nodo_personasLDE *actual = personas->inicio;
    for (nat i = 1; i < pos - 1; i++) {
        actual = actual->siguiente;
    }
    
    // Insertar el nodo entre actual y actual->siguiente
    nuevoNodo->siguiente = actual->siguiente;
    nuevoNodo->anterior = actual;
    actual->siguiente->anterior = nuevoNodo;
    actual->siguiente = nuevoNodo;
    personas->cantidad++;
}

void liberarTPersonasLDE(TPersonasLDE &personasLDE){
    if (personasLDE == NULL) {
        return;
    }
    
    struct nodo_personasLDE *actual = personasLDE->inicio;
    while (actual != NULL) {
        struct nodo_personasLDE *temp = actual;
        actual = actual->siguiente;
        liberarNodo(temp);
    }
    
    delete personasLDE;
    personasLDE = NULL;
}

void imprimirTPersonasLDE(TPersonasLDE personas){
    if (personas == NULL) {
        return;
    }
    
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        imprimirTPersona(actual->persona);
        actual = actual->siguiente;
    }
}

nat cantidadTPersonasLDE(TPersonasLDE personas){
    if (personas == NULL) {
        return 0;
    }
    return personas->cantidad;
}

void eliminarInicioTPersonasLDE(TPersonasLDE &personas){
    if (personas == NULL || personas->inicio == NULL) {
        return;
    }
    
    struct nodo_personasLDE *temp = personas->inicio;
    
    // Si solo hay un nodo
    if (personas->inicio == personas->final) {
        liberarNodo(temp);
        personas->inicio = NULL;
        personas->final = NULL;
        personas->cantidad = 0;
    } else {
        personas->inicio = personas->inicio->siguiente;
        personas->inicio->anterior = NULL;
        liberarNodo(temp);
        personas->cantidad--;
    }
}

void eliminarFinalTPersonasLDE(TPersonasLDE &personas){
    if (personas == NULL || personas->final == NULL) {
        return;
    }
    
    struct nodo_personasLDE *temp = personas->final;
    
    // Si solo hay un nodo
    if (personas->inicio == personas->final) {
        liberarNodo(temp);
        personas->inicio = NULL;
        personas->final = NULL;
        personas->cantidad = 0;
    } else {
        personas->final = personas->final->anterior;
        personas->final->siguiente = NULL;
        liberarNodo(temp);
        personas->cantidad--;
    }
}

bool estaEnTPersonasLDE(TPersonasLDE personas, nat id){
    if (personas == NULL) {
        return false;
    }
    
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        if (idTPersona(actual->persona) == id) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

TPersona obtenerDeTPersonasLDE(TPersonasLDE personas, nat id){
    if (personas == NULL) {
        return NULL;
    }
    
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        if (idTPersona(actual->persona) == id) {
            return actual->persona;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

TPersonasLDE concatenarTPersonasLDE(TPersonasLDE personas1, TPersonasLDE personas2){
    // Si la primera lista es vacía, retornar la segunda (alterada para que sea la nueva cabeza)
    if (personas1 == NULL || personas1->cantidad == 0) {
        delete personas1;
        return personas2;
    }

    // Si la segunda lista es vacía, retornar la primera
    if (personas2 == NULL || personas2->cantidad == 0) {
        delete personas2;
        return personas1;
    }
    
    // Conectar el final de la primera con el inicio de la segunda
    personas1->final->siguiente = personas2->inicio;
    personas2->inicio->anterior = personas1->final;
    
    // Actualizar el final de la nueva lista
    personas1->final = personas2->final;
    
    // Actualizar la cantidad
    personas1->cantidad += personas2->cantidad;
    
    // Liberar solo el cabezal de la segunda lista
    delete personas2;
    
    return personas1;
}

///////////////////////////////////
////// FIN CÓDIGO TAREA 2 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void insertarInicioDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){
    TPersonasLDE nuevaLista = crearTPersonasLDE();
    insertarTPersonasLDE(nuevaLista, persona, 1);
    personas = concatenarTPersonasLDE(nuevaLista, personas);
}

void insertarFinalDeTPersonasLDE(TPersonasLDE &personas, TPersona persona){    
    TPersonasLDE nuevaLista = crearTPersonasLDE();
    insertarTPersonasLDE(nuevaLista, persona, personas->cantidad + 1);
    personas = concatenarTPersonasLDE(personas, nuevaLista);
}

TPersona obtenerInicioDeTPersonasLDE(TPersonasLDE personas){
    return personas->inicio->persona;
}

TPersona obtenerFinalDeTPersonasLDE(TPersonasLDE personas){
    return personas->final->persona;
}
///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void eliminarPersonaConNombreTPersonasLDE(TPersonasLDE &personas, const char nombre[100]){
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        if (strcmp(nombreTPersona(actual->persona), nombre) == 0) {
            // Encontrado el nodo a eliminar
            if (actual->anterior != NULL) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                // Es el primer nodo
                personas->inicio = actual->siguiente;
            }
            if (actual->siguiente != NULL) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                // Es el último nodo
                personas->final = actual->anterior;
            }
            liberarNodo(actual);
            personas->cantidad--;
            return;
        }
        actual = actual->siguiente;
    }
    
}

bool estaPersonaConNombreEnTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        if (strcmp(nombreTPersona(actual->persona), nombre) == 0) {
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

TPersona obtenerPersonaConNombreTPersonasLDE(TPersonasLDE personas, const char nombre[100]){
    struct nodo_personasLDE *actual = personas->inicio;
    while (actual != NULL) {
        if (strcmp(nombreTPersona(actual->persona), nombre) == 0) {
            return actual->persona;
        }
        actual = actual->siguiente;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

