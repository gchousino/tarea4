#include "../include/tablaPersonas.h"

struct rep_tablaPersonas {
    TPersonasLDE *tabla;
    int tamanio;
};

nat funcionDeDispersion(const char nombre[100]){
    nat res = 0;
    int i = 0;
    while(i< 100 && nombre[i] != '\0'){
        res += int(nombre[i]);
        i++;
    }
    return res;
}

TTablaPersonas crearTTablaPersonas(int max){
    TTablaPersonas nuevaTabla = new rep_tablaPersonas;
    nuevaTabla->tamanio = max;
    nuevaTabla->tabla = new TPersonasLDE[max];
    for (int i = 0; i < max; i++) {
        nuevaTabla->tabla[i] = crearTPersonasLDE();
    }
    return nuevaTabla;
}

void insertarPersonaEnTTablaPersonas(TTablaPersonas &tabla, TPersona persona){
    int p = funcionDeDispersion(nombreTPersona(persona)) % tabla->tamanio;
    insertarInicioDeTPersonasLDE(tabla->tabla[p], persona);
}


void eliminarPersonaDeTTablaPersonas(TTablaPersonas &tabla, const char nombre[100]){
    int p = funcionDeDispersion(nombre) % tabla->tamanio;
    eliminarPersonaConNombreTPersonasLDE(tabla->tabla[p], nombre);
}

bool perteneceATTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    for (int i = 0; i < tabla->tamanio; i++) {
        if (estaPersonaConNombreEnTPersonasLDE(tabla->tabla[i], nombre)) {
            return true;
        }
    }
    return false;
}

TPersona obtenerPersonaDeTTablaPersonas(TTablaPersonas tabla, const char nombre[100]){
    for (int i = 0; i < tabla->tamanio; i++) {
        TPersona persona = obtenerPersonaConNombreTPersonasLDE(tabla->tabla[i], nombre);
        if (persona != NULL) {
            return persona;
        }
    }
    return NULL;
}


void liberarTTablaPersonas(TTablaPersonas &tabla){
    if (tabla != NULL) {
        for (int i = 0; i < tabla->tamanio; i++) {
            liberarTPersonasLDE(tabla->tabla[i]);
        }
        delete[] tabla->tabla;
        delete tabla;
        tabla = NULL;
    }
}


void imprimirTTablaPersonas(TTablaPersonas tabla){
    if (tabla != NULL) {
        for (int i = 0; i < tabla->tamanio; i++) {
            imprimirTPersonasLDE(tabla->tabla[i]);
        }
    }
}