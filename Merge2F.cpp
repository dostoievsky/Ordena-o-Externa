#include "Merge2F.h"
long int comparacoesOrdenacaoMerge = 0;

// Ordena o vetor v [0.. n -1]
// A cada iteracao , intercala dois " blocos " de b elementos :
// - o primeiro com o segundo , o terceiro com o quarto etc .
void mergeSort_iter (TipoRegistro *v , int n ) {
	comparacoesOrdenacaoMerge = 0;
	int esq , dir ;
	int b = 1;
	while (b < n) {
		esq = 0;
	while ( esq + b < n) {
		dir = esq + 2 * b ;
		if (dir > n) dir = n;
			mergeSort_intercala (v , esq , esq +b -1 , dir -1) ;
			esq = esq + 2 * b ;
		}
	b *= 2;
	}
}

// Intercala os vetores v[esq .. meio ] e v[ meio +1.. dir ]
void mergeSort_intercala(TipoRegistro *v, int esq, int meio, int dir){
	int i, j, k;
	int a_tam = meio-esq+1;
	int b_tam = dir-meio;
	TipoRegistro *a = (TipoRegistro*) calloc (a_tam,sizeof(TipoRegistro));
	TipoRegistro *b = (TipoRegistro*) calloc (b_tam,sizeof(TipoRegistro));

	for (i=0; i<a_tam;i++)
		a[i]=v[i+esq];
	for (i=0; i<b_tam;i++)
		b[i]=v[i+meio+1];

	for (i=0, j=0, k=esq; k<=dir;k++)
	{
		if (i==a_tam)
			v[k]=b[j++];
			else if (j==b_tam)
					v[k]=a[i++];
					else{
						comparacoesOrdenacaoMerge++;
						if (a[i].nota<b[j].nota)
							v[k]=a[i++];
						 else v[k]=b[j++];
						}
	}
	free(a);
	free(b);
}

long int getComparacoesOrdenacaoMerge(){
	return comparacoesOrdenacaoMerge;
}
