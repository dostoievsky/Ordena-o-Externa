#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "IntercalacaoBalanceada2f.h"
#include "Merge2F.h"
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>

int geraFitas(char* nomeFita, int quantidade);
int excluirFitas(char* nomeFita, int quantidade);
void tamanhoFitas(FILE **fitas, long int *tamanhos, 
						int quantFitas, int size);
void tamanhoFitasAtual (FILE **fitas, long int *tamanhos, 
						int quantFitas, int size);
bool leuTodasFitas(long int *tamFitasAtual, long int *tamFitasOriginal, 
								int quantFitas);
bool apenasUmaFitaSaida(long int *tamFitasAtual, int quantFitas);
void deletaFitas(char** nomeFitas, int fitaEntrada);
void liberaNomeFitas(char **nomeFitas);

#endif