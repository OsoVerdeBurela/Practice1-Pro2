/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "static_list.h"

/* Implementación estática del TAD Lista para gestionar consolas de videojuegos retro */

void createEmptyList(tList *L) {
    L->lastPos = LNULL;
}

bool isEmptyList(tList L) {
    return L.lastPos == LNULL;
}

tPosL first(tList L) {
    return 0;
}

tPosL last(tList L) {
    return L.lastPos;
}

tPosL next(tPosL p, tList L) {
    return p < L.lastPos ? ++p : LNULL;
}

tPosL previous(tPosL p, tList L) {
    return p > first(L) ? --p : LNULL;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    L->data[p] = d;
}

bool insertItem(tItemL d, tPosL p, tList *L) {
    bool aux = true;
    if (L->lastPos != MAX - 1) { // Verifica si hay espacio (máximo 25 elementos)
        L->lastPos++;
        if (p != LNULL) { // Inserción en una posición específica
            for (int i = L->lastPos; i > p; i--) {
                updateItem(L->data[i - 1], i, L); // Desplaza elementos a la derecha
            }
            updateItem(d, p, L); // Inserta el nuevo elemento
        } else { // Inserción al final
            updateItem(d, L->lastPos, L);
        }
        aux = false;
    }
    return aux;
}

void deleteAtPosition(tPosL p, tList *L) {
    for (tPosL i = p; i < L->lastPos; i++) {
        L->data[i] = L->data[i + 1]; // Desplaza elementos a la izquierda
    }
    L->lastPos--;
}

tItemL getItem(tPosL p, tList L) {
    return L.data[p];
}

tPosL findItem(tConsoleId c, tList L) {
    tPosL aux;
    if (isEmptyList(L)) {
        aux = LNULL;
    } else {
        tPosL i;
        for (i = 0; i <= L.lastPos && strcmp(c, L.data[i].consoleId) != 0; i++) { //  Busca el elemento mientas que no sea el ultimo
        }
        if (i <= L.lastPos && strcmp(c, L.data[i].consoleId) == 0) aux = i; // En caso de llegar al ultimo comprueba si encontro el elemento
        else aux = LNULL;
    }
    return aux;
}