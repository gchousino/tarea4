#include "../include/colaDePrioridadPersona.h"
#include "../include/utils.h"
#include "../include/evento.h"

struct rep_colaDePrioridadPersona {
  TPersona* heap;
  nat cantidad;
  int* posicion;
  int N;
  bool esMinHeap;
};

TColaDePrioridadPersona crearCP(nat N) {
  TColaDePrioridadPersona cp = new rep_colaDePrioridadPersona;
  cp->heap = new TPersona[N+1];
  cp->posicion = new int[N+1];
  for (nat i = 0; i <= N; i++) {
    cp->posicion[i] = 0;
  }
  cp->cantidad = 0;
  cp->N = N;
  cp->esMinHeap = true;
  return cp;
}

static TFecha obtenerFechaPrioridad(TPersona persona) {
  return fechaTEvento(primerEventoAgendaLS(agendaTPersona(persona)));
}

static void filtrado_ascendente(nat pos, TColaDePrioridadPersona &cp) {
  nat i = pos;
  while (i > 1) {
    int cmp = compararTFechas(obtenerFechaPrioridad(cp->heap[i]), obtenerFechaPrioridad(cp->heap[i/2]));
    if (cp->esMinHeap ? cmp < 0 : cmp > 0) {
      TPersona temp = cp->heap[i];
      cp->heap[i] = cp->heap[i/2];
      cp->heap[i/2] = temp;
      cp->posicion[idTPersona(cp->heap[i])] = i;
      cp->posicion[idTPersona(cp->heap[i/2])] = i/2;
      i /= 2;
    } else {
      break;
    }
  }
}

static void filtrado_descendente(nat pos, TColaDePrioridadPersona &cp) {
  nat i = pos;
  while (2*i <= cp->cantidad) {
    nat j = 2*i;
    if (j < cp->cantidad) {
      int cmpHijos = compararTFechas(obtenerFechaPrioridad(cp->heap[j+1]), obtenerFechaPrioridad(cp->heap[j]));
      if (cp->esMinHeap ? cmpHijos < 0 : cmpHijos > 0) {
        j++;
      }
    }
    int cmp = compararTFechas(obtenerFechaPrioridad(cp->heap[j]), obtenerFechaPrioridad(cp->heap[i]));
    if (cp->esMinHeap ? cmp < 0 : cmp > 0) {
      TPersona temp = cp->heap[i];
      cp->heap[i] = cp->heap[j];
      cp->heap[j] = temp;
      cp->posicion[idTPersona(cp->heap[i])] = i;
      cp->posicion[idTPersona(cp->heap[j])] = j;
      i = j;
    } else {
      break;
    }
  }
}

void invertirPrioridad(TColaDePrioridadPersona &cp) {
  cp->esMinHeap = !cp->esMinHeap;
  for (int k = cp->cantidad / 2; k >= 1; k--) {
    filtrado_descendente(k, cp);
  }
}

void liberarCP(TColaDePrioridadPersona &cp) {
  for (nat i = 1; i <= cp->cantidad; i++) {
    liberarTPersona(cp->heap[i]);
  }
  delete[] cp->heap;
  delete[] cp->posicion;
  delete cp;
}

void insertarEnCP(TPersona persona, TColaDePrioridadPersona &cp) {
  nat pos = ++cp->cantidad;
  cp->heap[pos] = persona;
  cp->posicion[idTPersona(persona)] = pos;
  filtrado_ascendente(pos, cp);
}

bool estaVaciaCP(TColaDePrioridadPersona cp) {
  return cp->cantidad == 0;
}

TPersona prioritaria(TColaDePrioridadPersona cp) {
  return cp->heap[1];
}

void eliminarPrioritaria(TColaDePrioridadPersona &cp) {
  if (estaVaciaCP(cp)) return;
  TPersona eliminada = cp->heap[1];
  nat idEliminada = idTPersona(eliminada);
  cp->heap[1] = cp->heap[cp->cantidad];
  cp->posicion[idTPersona(cp->heap[1])] = 1;
  cp->cantidad--;
  cp->posicion[idEliminada] = 0;
  filtrado_descendente(1, cp);
  liberarTPersona(eliminada);
}

bool estaEnCP(nat id, TColaDePrioridadPersona cp) {
  return cp->posicion[id] != 0;
}

TFecha prioridad(nat id, TColaDePrioridadPersona cp) {
  return obtenerFechaPrioridad(cp->heap[cp->posicion[id]]);
}