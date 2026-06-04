#include "../include/evento.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_evento {
    /************ Parte 4.1 ************/
    /*Escriba el código a continuación */
    int identificador;
    char descripcion[MAX_DESCRIPCION];
    TFecha fecha;
    /****** Fin de parte Parte 4.1 *****/
};

TEvento crearTEvento(int id, const char descripcion[MAX_DESCRIPCION], TFecha fecha) {
    TEvento nuevoEvento = NULL;
    /************ Parte 4.2 ************/
    /*Escriba el código a continuación */
    nuevoEvento = new rep_evento;
    nuevoEvento->fecha = fecha;
    strcpy(nuevoEvento->descripcion, descripcion);
    nuevoEvento->identificador = id;
    /****** Fin de parte Parte 4.2 *****/
    return nuevoEvento;
}

void imprimirTEvento(TEvento evento) {
    /************ Parte 4.3 ************/
    /*Escriba el código a continuación */
    printf("Evento %d: %s\nFecha: ",evento->identificador , evento->descripcion);
    imprimirTFecha(evento->fecha);
    /****** Fin de parte Parte 4.3 *****/
}

void liberarTEvento(TEvento &evento) {
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    if (evento != NULL) {
        if (evento->fecha != NULL) {
            liberarTFecha(evento->fecha);
        }
        delete evento;
        evento = NULL;
    }

    /****** Fin de parte Parte 4.4 *****/
}

int idTEvento(TEvento evento) {
    //int res = 0;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    int res = evento->identificador ;
    /****** Fin de parte Parte 4.4 *****/
    return res;
}

TFecha fechaTEvento(TEvento evento) {
    TFecha fecha = NULL;
    /************ Parte 4.4 ************/
    /*Escriba el código a continuación */
    fecha = evento->fecha ;
    /****** Fin de parte Parte 4.4 *****/
    return fecha;
}

void posponerTEvento(TEvento &evento, int dias) {
    /************ Parte 4.5 ************/
    /*Escriba el código a continuación */
    aumentarTFecha(evento->fecha,dias);
    /****** Fin de parte Parte 4.5 *****/
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia del evento
TEvento copiarTEvento(TEvento evento) {
    TEvento copia = crearTEvento(evento->identificador, evento->descripcion, copiarTFecha(evento->fecha));
    return copia;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
