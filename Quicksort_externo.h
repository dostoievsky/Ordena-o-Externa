#ifndef QUICKSORT_EXTERNO_H
#define QUICKSORT_EXTERNO_H

#include "ListaDupla.h"
#include "Registro.h"
#include <stdio.h>
#include <array>

using namespace std;

void QuicksortExterno (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, int Esq, int Dir);
void LeSup (FILE **ArqLEs, TipoRegistro *UltLido, int *Ls, short *OndeLer);
void LeInf (FILE **ArqLi, TipoRegistro *UltLido, int *Li, short *OndeLer);
void InserirArea (Tlista *Area, TipoRegistro *UltLido, int *NRArea);
void EscreveMax (FILE **ArqLEs, TipoRegistro R, int *Es);
void EscreveMin (FILE **ArqEi, TipoRegistro R, int *Ei);
void RetiraMax (Tlista *Area, TipoRegistro *R, int *NRArea);
void RetiraMin (Tlista *Area, TipoRegistro *R, int *NRArea);
void Particao (FILE **ArqLi, FILE **ArqEi, FILE **ArqLEs, Tlista Area, 
							int Esq, int Dir, int *i, int *j);
long int getEscritaQuick();
long int getLeituraQuick();
long int getComparacoesQuick();

#endif