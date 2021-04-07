#ifndef INTERCALACAOFMAISUMSUBS_H
#define INTERCALACAOFMAISUMSUBS_H

#include "Auxiliar.h"
#include "ListaDupla.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define fsubs1 39
#define ffsubs1 fsubs1 + 1

int gerarFitasOrdenadasSubsMaisUm(char *nomeArquivo);
int reorganizaFitasSubsMaisUm(int numFitaSaida, char **nomeFitas) ;
int ordenaFMaisUmSubs(char **nomeFitas);
int soTemUmBloco(FILE *fitaSaida);
void liberaGeralSubs1 (TipoRegistro *vaux, TipoRegistro *regNulo, 
						FILE** fitaEnt, FILE* fitaSaida,
						long int* tamFitasEntrada, long int* tamFitasEntradaAtual, 
						TipoRegistro *remov, Tlista **fila);
						
void liberaGeralFinalSubs1 (TipoRegistro *vaux, TipoRegistro *regNulo, 
								FILE** fitaEnt, FILE* fitaSaida,
						long int* tamFitasEntrada, long int* tamFitasEntradaAtual, 
						TipoRegistro *remov, Tlista **fila, char** nomeFitas);
						
void liberaNomeFitasSubs1(char **nomeFitas);
void deletaFitasSubs1(char** nomeFitas, int fitaSaida);
long int getLeiturafMaisUmSubs();
long int getEscritafMaisUmSubs();
long long int getComparacoesfMaisUmSubs();

#endif