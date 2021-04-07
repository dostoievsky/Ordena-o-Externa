
#ifndef INTERCALACAOBALANCEADA2F_H
#define INTERCALACAOBALANCEADA2F_

#include "Merge2F.h"
#include "Auxiliar.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define f 20 //quantidade de fitas
#define ff 2 * f
#define tamBloco 20 

using namespace std;

int gerarFitasOrdenadas(char *nomeArquivo);
int misturarFitas(int fitaEntrada) ;
void liberaGeral(long int* tamFitasEntrada, long int* tamFitasSaida,
		FILE** fitaEnt, FILE** fitaSaida, TipoRegistro* v,
		TipoRegistro* vaux, long int* tamFitasEntradaAtual);
void liberaGeralFinal(long int* tamFitasEntrada, long int* tamFitasSaida,
		char** nomeFitas, FILE** fitaEnt, FILE** fitaSaida, TipoRegistro* v,
		TipoRegistro* vaux, long int* tamFitasEntradaAtual, int fitaEntrada);
int binParaTxtPlus(FILE *arq, char *nomeArquivotxt);
long int getLeitura2f();
long int getEscrita2f();
long int getComparacoes2f();

#endif

