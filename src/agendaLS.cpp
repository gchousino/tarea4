#include "../include/agendaLS.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////

struct rep_agendaLS {
    TEvento evento;
    TAgendaLS sig;
};

TAgendaLS crearAgendaLS() {
    return NULL;
}

void agregarEnAgendaLS(TAgendaLS &agenda, TEvento evento) {
    // Crear un nuevo nodo
    TAgendaLS nuevoNodo = new rep_agendaLS;    
    nuevoNodo->evento = evento;
    nuevoNodo->sig = NULL;
    
    // Si la agenda está vacía, el nuevo nodo es la agenda
    if (agenda == NULL) {
        agenda = nuevoNodo;
        return;
    }
    
    // Buscar la posición correcta para insertar el evento
    // fecha menor a mayor, si fecha igual el más reciente primero
    TAgendaLS actual = agenda;
    TAgendaLS anterior = NULL;
    
    while (actual != NULL) {
        int cmp = compararTFechas(fechaTEvento(evento), fechaTEvento(actual->evento));
        
        // Si la fecha del nuevo evento es menor, insertarlo
        if (cmp < 0) {
            nuevoNodo->sig = actual;
            if (anterior == NULL) {
                agenda = nuevoNodo;
            } else {
                anterior->sig = nuevoNodo;
            }
            return;
        }
        // Si la fecha es igual, el nuevo evento va primero
        else if (cmp == 0) {
            nuevoNodo->sig = actual;
            if (anterior == NULL) {
                agenda = nuevoNodo;
            } else {
                anterior->sig = nuevoNodo;
            }
            return;
        }
        
        anterior = actual;
        actual = actual->sig;
    }
    
    // Si llego el nuevo evento va al final
    anterior->sig = nuevoNodo;
}


void imprimirAgendaLS(TAgendaLS agenda) {
    TAgendaLS actual = agenda;
    while (actual != NULL) {
        imprimirTEvento(actual->evento);
        actual = actual->sig;
    }
}

void liberarAgendaLS(TAgendaLS &agenda) {
    while (agenda != NULL) {
        TAgendaLS temp = agenda;
        agenda = agenda->sig;
        liberarTEvento(temp->evento);
        delete temp;
    }
}

bool esVaciaAgendaLS(TAgendaLS agenda){
    return agenda == NULL;
}

TAgendaLS copiarAgendaLS(TAgendaLS agenda){
    if (agenda == NULL) {
        return NULL;
    }
    
    // Crear el primer nodo de la copia
    TAgendaLS copia = new rep_agendaLS;
    copia->evento = copiarTEvento(agenda->evento);
    copia->sig = NULL;

    // Copiar el resto de los nodos
    TAgendaLS actual = agenda->sig;
    TAgendaLS ultimoCopia = copia;

    while (actual != NULL) {
        TAgendaLS nuevoNodo = new rep_agendaLS;
        nuevoNodo->evento = copiarTEvento(actual->evento);
        nuevoNodo->sig = NULL;
        ultimoCopia->sig = nuevoNodo;
        ultimoCopia = nuevoNodo;
        actual = actual->sig;
    }
    
    return copia;
}


bool estaEnAgendaLS(TAgendaLS agenda, int id) {
    TAgendaLS actual = agenda;
    while (actual != NULL) {
        if (idTEvento(actual->evento) == id) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

TEvento obtenerDeAgendaLS(TAgendaLS agenda, int id) {
    TAgendaLS actual = agenda;
    while (actual != NULL) {
        if (idTEvento(actual->evento) == id) {
            return actual->evento;
        }
        actual = actual->sig;
    }
    return NULL;
}

void posponerEnAgendaLS(TAgendaLS &agenda, int id, nat n) {
    // Encontrar y remover el evento de la lista
    TAgendaLS actual = agenda;
    TAgendaLS anterior = NULL;
    TEvento eventoAPostponer = NULL;
    
    while (actual != NULL) {
        if (idTEvento(actual->evento) == id) {
            eventoAPostponer = actual->evento;
            // Remover de la lista
            if (anterior == NULL) {
                agenda = actual->sig;
            } else {
                anterior->sig = actual->sig;
            }
            delete actual;
            break;
        }
        anterior = actual;
        actual = actual->sig;
    }

    if (eventoAPostponer == NULL) {
        return;
    }

    // Posponer el evento
    posponerTEvento(eventoAPostponer, n);

    // Reinsertar el evento en la posición correcta
    TAgendaLS nuevoNodo = new rep_agendaLS;
    nuevoNodo->evento = eventoAPostponer;
    nuevoNodo->sig = NULL;
    
    // Si la agenda está vacía, el evento es la agenda
    if (agenda == NULL) {
        agenda = nuevoNodo;
        return;
    }
    
    // Buscar la posición correcta para reinsertar
    actual = agenda;
    anterior = NULL;
    
    while (actual != NULL) {
        int cmp = compararTFechas(fechaTEvento(eventoAPostponer), fechaTEvento(actual->evento));
        
        // Si la fecha del evento pospuesto es menor, insertarlo
        if (cmp < 0) {
            nuevoNodo->sig = actual;
            if (anterior == NULL) {
                agenda = nuevoNodo;
            } else {
                anterior->sig = nuevoNodo;
            }
            return;
        }
        // Si la fecha es igual, el evento pospuesto va primero
        else if (cmp == 0) {
            nuevoNodo->sig = actual;
            if (anterior == NULL) {
                agenda = nuevoNodo;
            } else {
                anterior->sig = nuevoNodo;
            }
            return;
        }
        
        anterior = actual;
        actual = actual->sig;
    }
    
    // Si llegó, el evento va al final
    anterior->sig = nuevoNodo;
}

void imprimirEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS actual = agenda;
    while (actual != NULL) {
        if (compararTFechas(fechaTEvento(actual->evento), fecha) == 0) {
            imprimirTEvento(actual->evento);
        }
        actual = actual->sig;
    }
}

bool hayEventosFechaLS(TAgendaLS agenda, TFecha fecha) {
    TAgendaLS actual = agenda;
    while (actual != NULL) {
        if (compararTFechas(fechaTEvento(actual->evento), fecha) == 0) {
            return true;
        }
        actual = actual->sig;
    }
    return false;
}

void removerDeAgendaLS(TAgendaLS &agenda, int id) {
    TAgendaLS actual = agenda;
    TAgendaLS anterior = NULL;
    
    while (actual != NULL) {
        if (idTEvento(actual->evento) == id) {
            // Encontrado el evento a remover
            if (anterior == NULL) {
                // Es el primer nodo
                agenda = actual->sig;
            } else {
                // No es el primer nodo
                anterior->sig = actual->sig;
            }
            // Liberar el evento y el nodo
            liberarTEvento(actual->evento);
            delete actual;
            return;
        }
        anterior = actual;
        actual = actual->sig;
    }
}


///////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
///////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/////////////  NUEVAS FUNCIONES  //////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

TEvento primerEventoAgendaLS(TAgendaLS agenda){
    return agenda->evento;
}

///////////////////////////////////////////////////////////////////////////
/////////////  FIN NUEVAS FUNCIONES  //////////////////////////////////////
///////////////////////////////////////////////////////////////////////////