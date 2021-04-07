#include <iostream>
#include <iomanip>
#include <sys/time.h>
#include "time.h"
#include "Merge2F.h"
#include "stdlib.h"
#include "Gerador.h"
#include "stdio.h"
#include "string.h"
#include "Celula.h"
#include "IntercalacaoBalanceada2f.h"
#include "IntercalacaoBalanceada2fSubs.h"
#include "IntercalacaoFMaisUmSubs.h"
#include "Quicksort_externo.h"

using namespace std;

int gerador(char *quantidade, char *situacao, char *nomeArquivoIn, char *nomeArquivoOut);
int geraBinOrdInv (char *nomeArquivoIn, char *nomeArquivoOut, int qtd);
int lerBin(char *nomeArquivo);
int copiaBin (char *nomeArquivoIn, char* nomeArquivoOut);
void visu();