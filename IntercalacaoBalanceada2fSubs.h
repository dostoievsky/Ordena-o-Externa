
#ifndef INTERCALACAOBALANCEADA2FSUBS_H_
#define INTERCALACAOBALANCEADA2FSUBS_H_

#include "Auxiliar.h"
#include "ListaDupla.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define fsubs 20
#define ffsubs 2 * f
#define m 20
//quantidade de itens que ser�o inseridos na fila de prioridades

int gerarFitasOrdenadasSubs(char *nomeArquivo);
int misturarFitasSubs(int fitaEntrada);
void liberaGeralSubs(long int* tamFitasEntrada, long int* tamFitasSaida,
		FILE** fitaEnt, FILE** fitaSaida,
		TipoRegistro* vaux, long int* tamFitasEntradaAtual, Tlista **fila);
void liberaGeralFinalSubs(long int* tamFitasEntrada, long int* tamFitasSaida,
		char** nomeFitas, FILE** fitaEnt, FILE** fitaSaida,	TipoRegistro* vaux,
        long int* tamFitasEntradaAtual, int fitaEntrada, Tlista **fila);
long int getLeitura2fSubs();
long int getEscrita2fSubs();
long int getComparacoes2fSubs();

#endif 
