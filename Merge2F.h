
#ifndef MERGE2F_H
#define MERGE2F_H

#include "Registro.h"
#include <stdlib.h>
#include <stdio.h>

void mergeSort_intercala(TipoRegistro *v, int esq, int meio, int dir);
void mergeSort_iter ( TipoRegistro *v , int n ) ;
long int getComparacoesOrdenacaoMerge();

#endif

