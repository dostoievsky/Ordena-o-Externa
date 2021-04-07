
#ifndef GERADOR_H
#define GERADOR_H

#include <iostream>
#include "stdlib.h"
#include <cstdlib>
#include "stdio.h"
#include <string.h>

#include "Quicksort_externo.h"
#include "Registro.h"

int geraBinOrd(char *nomeArquivo); //retorna 1 se gerou com sucesso e 0 caso contrario
int binParaTxt(char *nomeArquivo, char *nomeArquivotxt);	//apenas para teste
int geraArquivoLimitado (char *nomeArquivoIn, char *nomeArquivoOut, int quant);

#endif 


