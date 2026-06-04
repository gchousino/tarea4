#include "../include/fecha.h"

///////////////////////////////////
////// PEGAR CÓDIGO TAREA 3 //////
///////////////////////////////////


struct rep_fecha {
    /************ Parte 2.1 ************/
    /*Escriba el código a continuación */
    nat dia;
    nat mes;
    nat anio;
    /****** Fin de parte Parte 2.1 *****/
};

TFecha crearTFecha(nat dia, nat mes, nat anio) {
    TFecha nuevaFecha = NULL;
    /************ Parte 3.1 ************/
    /*Escriba el código a continuación */
    nuevaFecha = new rep_fecha;
    nuevaFecha->dia = dia;
    nuevaFecha->mes = mes;
    nuevaFecha->anio = anio;
    /****** Fin de parte Parte 3.1 *****/
    return nuevaFecha;
}

void liberarTFecha(TFecha &fecha) {
    /************ Parte 3.3 ************/
    /*Escriba el código a continuación */
    delete fecha;
    fecha = NULL;
    /****** Fin de parte Parte 3.3 *****/
}
void imprimirTFecha(TFecha fecha) {
    /************ Parte 3.5 ************/
    /*Escriba el código a continuación */
    printf("%d/%d/%d\n", fecha->dia, fecha->mes, fecha->anio);
    /****** Fin de parte Parte 3.5 *****/
}

bool anioBisiesto(nat anio){
        if (anio % 400 == 0){
            return true;
        }
        if (anio % 4 == 0 && anio % 100 != 0){
            return true;
        }
        return false;
    }
nat diasMes(nat mes, nat anio){
    if (anioBisiesto(anio)) {
        if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) { // 31 dias
            return  31;
        }
        if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
            return 30;
        }
        if (mes == 2){
            return 29;
        }
    }
    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) { // 31 dias
        return  31;
    }
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
        return 30;
    }
    if (mes == 2){
        return 28;
    }
    
    return 0 ;
}

void aumentarTFecha(TFecha &fecha, nat dias) {
    /************ Parte 3.9 ************/
    /*Escriba el código a continuación */
    /*Recuerde que las funciones auxiliares
      deben declararse antes de ser utilizadas*/
    fecha->dia += dias;
    while (fecha->dia > diasMes(fecha->mes, fecha->anio)) {
        fecha->dia -= diasMes(fecha->mes, fecha->anio);
        fecha->mes++;
        if (fecha->mes > 12) {
            fecha->mes = 1;
            fecha->anio++;
        }
    }
    /****** Fin de parte Parte 3.9 *****/
}



int compararTFechas(TFecha fecha1, TFecha fecha2) {
    /************ Parte 3.10 ************/
    /*Escriba el código a continuación */
    int res;
    if ((fecha1->anio > fecha2->anio) || (fecha1->anio == fecha2->anio && fecha1->mes > fecha2->mes) || (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia > fecha2->dia)) {
        res = 1;
    } else if (fecha1->anio == fecha2->anio && fecha1->mes == fecha2->mes && fecha1->dia == fecha2->dia) {
        res = 0;
    } else {
        res = -1;
    }
    /****** Fin de parte Parte 3.10 *****/
    return res;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 1 //////
/////////////////////////////////

/*-----------------------------*/

///////////////////////////
////// FUNCION NUEVA //////
///////////////////////////

// Retorna una copia de la fecha
TFecha copiarTFecha(TFecha fecha) {
    TFecha copia = crearTFecha(fecha->dia, fecha->mes, fecha->anio);
    return copia;
}

/////////////////////////////////
////// FIN CÓDIGO TAREA 3 //////
/////////////////////////////////
