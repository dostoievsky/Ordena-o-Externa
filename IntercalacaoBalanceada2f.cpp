#include "IntercalacaoBalanceada2f.h"
long int leitura2f = 0;
long int escrita2f = 0;
long int comparacoes2f = 0;

int gerarFitasOrdenadas(char *nomeArquivo){
	char nomeFita[30] = "Fita";
	if (!geraFitas(nomeFita, ff)) {
		cout << "Erro ao gerar as fitas!" << endl;
		return 0;
	}
	FILE *arqIn = fopen(nomeArquivo, "rb");
	if (arqIn == NULL) {
		cout << "Erro ao abrir o arquivo de entrada" << endl;
		excluirFitas(nomeFita, ff);
		return 0;
	}
	TipoRegistro *v = (TipoRegistro*) calloc(tamBloco, sizeof(TipoRegistro));
	TipoRegistro *regNulo = criarRegistro();
	char nulo[10] = "-1";
	setNota(regNulo, -1);
	setInscricao(regNulo, -1);
	setCidade(regNulo, nulo);
	setEstado(regNulo, nulo);
	setCurso(regNulo, nulo);
	for (int i = 0; i < tamBloco; i++)
		v[i] = *regNulo;

	int i = 0, numFita = 1;
	char aux[50] = "", num[10] = "";
	FILE *fita;
	while (fread(&v[i], sizeof(TipoRegistro), 1, arqIn)) {
		leitura2f++;
		if ((i + 1) % tamBloco == 0) {
			mergeSort_iter(v, tamBloco);
			comparacoes2f += getComparacoesOrdenacaoMerge();
			//definindo o nome da fita
			strcat(aux, nomeFita);
			sprintf(num, "%d", numFita);
			strcat(aux, num);
			strcat(aux, ".bin");
			fita = fopen(aux, "ab");
			if (fita == NULL) {
				cout << "Erro ao abrir o arquivo" << endl;
				fclose(arqIn);
				return 0;
			}
			for (int j = 0; j < tamBloco; j++) {
				if (getNota(&v[j]) != getNota(regNulo))
					fwrite(&v[j], sizeof(TipoRegistro), 1, fita);
			}
			fwrite(regNulo, sizeof(TipoRegistro), 1, fita);
			escrita2f++;
			if (numFita == f)
				numFita = 1;
			else
				numFita++;
			fclose(fita);
			strcpy(aux, "");
			i = 0;
			for (int j = 0; j < tamBloco; j++)
				v[j] = *regNulo;
		} else
			i++;
	}
	strcat(aux, nomeFita);
	sprintf(num, "%d", numFita);
	strcat(aux, num);
	strcat(aux, ".bin");
	fita = fopen(aux, "ab");
	if (fita == NULL) {
		cout << "Erro ao abrir o arquivo" << endl;
		fclose(arqIn);
		return 0;
	}
	for (int j = 0; j < tamBloco; j++) {
		if (getNota(&v[j]) != getNota(regNulo)){
			fwrite(&v[j], sizeof(TipoRegistro), 1, fita);
			escrita2f++;
		}
	}
	
	fwrite(regNulo, sizeof(TipoRegistro), 1, fita);
	escrita2f++;
	fclose(fita);
	fclose(arqIn);
	free(v);
	return 1;
}

int misturarFitas(int fitaEntrada) {
	//Funcao que junta as fitas iniciais ate que sobre apenas uma
	char **nomeFitas;
	int primeiraFita = 1;
	int fitaRecursao = fitaEntrada;
	TipoRegistro *regNulo = criarRegistro();
	char nulo[10] = "-1";
	setNota(regNulo, -1);
	setInscricao(regNulo, -1);
	setCidade(regNulo, nulo);
	setEstado(regNulo, nulo);
	setCurso(regNulo, nulo);
	TipoRegistro *v = (TipoRegistro*) calloc(f, sizeof(TipoRegistro));
	TipoRegistro *vaux = (TipoRegistro*) calloc(f, sizeof(TipoRegistro));

	for (int i=0; i<f;i++){
		vaux[i] = *regNulo;
	}
	//vetores que vao receber o tamanho das fitas
	long int *tamFitasEntrada = (long int*) malloc(f * sizeof(long int));
	//aloca um vetor com o nome das fitas
	nomeFitas = (char**) malloc(ff * sizeof(char*));
	for (int i = 0; i < ff; i++)
		nomeFitas[i] = (char*) malloc(30 * sizeof(char));

	char nomeFita[30] = "Fita";
	char aux[30] = "", num[30] = "";
	FILE **fitaEnt, **fitaSaida;
	fitaEnt = (FILE**) malloc(f * sizeof(FILE*));
	fitaSaida = (FILE**) malloc(f * sizeof(FILE*));
	int posicaoSaida, primeiraMetade, posicaoEntrada;
	//preenche o vetor com o nome das fitas
	for (int i = 0; i < ff; i++) {
		strcat(aux, nomeFita);
		sprintf(num, "%d", primeiraFita++);
		strcat(aux, num);
		strcat(aux, ".bin");
		strcpy(nomeFitas[i], aux);
		strcpy(aux, "");
	}
	//abre as fitas de entrada
	if (fitaEntrada == 1) {		//primeira fita de entrada = 0
		posicaoEntrada = 0;
		for (int i = 0; i < f; i++) {
			fitaEnt[i] = fopen(nomeFitas[i], "rb");
			if (fitaEnt[i] == NULL) {
				cout << "Erro ao abrir o arquivo" << endl;
				free(v);
				free(vaux);
				return 0;
			}
			fitaEntrada++;
		}
		tamanhoFitas(fitaEnt, tamFitasEntrada, f, sizeof(TipoRegistro));
	} else {			//primeira fita de entrada = f+1
		posicaoEntrada = 0;
		for (int i = 0; i < f; i++) {
			fitaEnt[i] = fopen(nomeFitas[fitaEntrada-1], "rb");
			if (fitaEnt[i] == NULL) {
				cout << "i = " << i << endl;
				cout << "Erro ao abrir o arquivo" << endl;
				free(v);
				free(vaux);
				return 0;
			}
			fitaEntrada++;
		}
		tamanhoFitas(fitaEnt, tamFitasEntrada, f, sizeof(TipoRegistro));
	}

	int numFitaSaida;
	//abre as fitas de saida
	posicaoSaida = 0;
	if (fitaEntrada == f+1) {
		numFitaSaida = f;
		primeiraMetade = 0;		//1 = primeira metade, 0 = segunda metade
		for (int i = 0; i < f; i++) {
			fitaSaida[i] = fopen(nomeFitas[numFitaSaida], "ab");
			if (fitaSaida[i] == NULL) {
				cout << "Erro ao abrir o arquivo" << endl;
				for (int j = 0; j < f; j++) {
					fclose(fitaEnt[j]);
				}
				free(fitaEnt);
				free(v);
				free(vaux);
				return 0;
			}
			numFitaSaida++;
		}
	} else {
		numFitaSaida = posicaoSaida = 0;
		primeiraMetade = 1;
		for (int i = 0; i < f; i++) {
			fitaSaida[i] = fopen(nomeFitas[i], "ab");
			if (fitaSaida[i] == NULL) {
				cout << "Erro ao abrir o arquivo" << endl;
				for (int j = 0; j < f; j++) {
					fclose(fitaEnt[j]);
				}
				free(fitaEnt);
				free(v);
				free(vaux);
				return 0;
			}
			numFitaSaida++;
		}
	}
	
	int fita,i=0;
	float menor;
	long int *tamFitasEntradaAtual = (long int*) malloc(f * sizeof(long int));
	long int *tamFitasSaida = (long int*) malloc(f * sizeof(long int));
	if (primeiraMetade == 0) {
		while (posicaoEntrada < f) {
			fread(&vaux[i], sizeof(TipoRegistro), 1, fitaEnt[posicaoEntrada++]);	
			//pega um registro de cada fita de entrada
			leitura2f++;
			i++;
		}
	} else {
		while (posicaoEntrada < f) {
			fread(&vaux[i], sizeof(TipoRegistro), 1, fitaEnt[posicaoEntrada++]);	
			//pega um registro de cada fita de entrada
			leitura2f++;
			i++;
		}
	}
	while (1) {
		for (int j = 0; j < f; j++) {//faz uma copia do vetor auxiliar
			v[j] = vaux[j];
		}

		mergeSort_iter(v, f);		//ordena o vetor v

		comparacoes2f += getComparacoesOrdenacaoMerge();

		menor = -1;
		for (int j = 0; j < f; j++) {//pega o menor valor dentro do vetor ordenado
			if (getNota(&v[j]) != -1) {
				menor = getNota(&v[j]);
				break;
			}
		}
		if (menor == -1) {
			fwrite(regNulo, sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
			escrita2f++;
			posicaoSaida++;
			tamanhoFitasAtual(fitaEnt, tamFitasEntradaAtual, f, sizeof(TipoRegistro)); 
			// tamFitasEntradaAtual = pega o tamanho das fitas no momento atual
			tamanhoFitas(fitaSaida, tamFitasSaida, f, sizeof(TipoRegistro)); 
			//pega o tamanho das fitas de saida
			if ((leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada, f)) && 
									apenasUmaFitaSaida(tamFitasSaida, f)) { 
				//se tiver só uma fita (de saida) cheia e todas as fitas de entrada tiverem sido lidas
				liberaGeralFinal(tamFitasEntrada, tamFitasSaida, nomeFitas, 
				fitaEnt, fitaSaida, v, vaux, tamFitasEntradaAtual,fitaRecursao);
				return 1;
			}
			if (leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada, f)) { 
			//se leu todas as fitas de entrada, mas existe mais de uma fita de saida preenchida
				liberaGeral(tamFitasEntrada, tamFitasSaida, fitaEnt, fitaSaida, 
													v, vaux, tamFitasEntradaAtual);
            	if (primeiraMetade==0){	
				//fita de entrada esta na primeira metade
            		for (int i=0;i<f;i++){
            			remove(nomeFitas[i]);
            		}
            	}
            	else {
            		for (int i=f;i<ff;i++){
            			remove(nomeFitas[i]);
            		}
            	}
            	liberaNomeFitas(nomeFitas);
				if (fitaRecursao == 1){
					misturarFitas(f + 1);
					break;
				}
				else{
					misturarFitas(1);
					break;
				}
			}
			if (!leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada, f)){ 	
			//se nao leu todas as fitas, continuar do começo
				for (int i=0;i<f;i++){
					vaux[i] = *regNulo;
				}
				for (int i=0;i<f;i++){
					if(tamFitasEntradaAtual[i] != tamFitasEntrada[i]){
						fread(&vaux[i], sizeof(TipoRegistro), 1, fitaEnt[i]);	
						//pega um registro de cada fita de entrada
						leitura2f++;
					}
				}
			}
		}
		for (int j = 0; j < tamBloco; j++) {
			if (menor == getNota(&vaux[j])){
				fita = j;		
				//posicao do vaux que precisa ser lida
			}
		}
		if (primeiraMetade == 0) {
			if (posicaoSaida < f){
				if (vaux[fita].inscricao!=-1){fwrite(&vaux[fita], 
											sizeof(TipoRegistro), 
									1, fitaSaida[posicaoSaida]);
					escrita2f++;
				}
			}
			else {
				posicaoSaida = 0;
				if (vaux[fita].inscricao!=-1){
					fwrite(&vaux[fita], sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
					escrita2f++;
				}
			}
		} else {
			if (posicaoSaida < f){
				if (vaux[fita].inscricao!=-1){
					fwrite(&vaux[fita], sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
					escrita2f++;
				}
			}
			else{
				posicaoSaida = 0;
				if (vaux[fita].inscricao!=-1){
					fwrite(&vaux[fita], sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
					escrita2f++;
				}
			}
		}
		fread(&vaux[fita], sizeof(TipoRegistro), 1, fitaEnt[fita]);	
		//pega registro da primeira Fita de entrada
		leitura2f++;
	}
	return 0;
}

int binParaTxtPlus(FILE *arq, char *nomeArquivotxt){
	//Recebe o nome de um arquivo binario e realiza sua gestao
	rewind(arq);
	FILE *arquivotxt = fopen(nomeArquivotxt, "w");
	if(arquivotxt == NULL){
		cout << "Erro ao abrir o arquivo texto" << endl;
		return 0;
	}
	TipoRegistro ch;
	while (fread(&ch, sizeof(ch), 1, arq) == 1){
		fprintf(arquivotxt, "%ld \n", ch.inscricao);
	}
	fseek(arq,0, SEEK_SET);
	fclose(arquivotxt);
	return 1;
}

void liberaGeral(long int* tamFitasEntrada, long int* tamFitasSaida,
		FILE** fitaEnt, FILE** fitaSaida, TipoRegistro* v,
		TipoRegistro* vaux, long int* tamFitasEntradaAtual) {
	//Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
	free(tamFitasEntrada);
	free(tamFitasSaida);
	for (int j = 0; j < f; j++) {
		fclose(fitaEnt[j]);
	}
	free(fitaEnt);
	for (int j = 0; j < f; j++) {
		fclose(fitaSaida[j]);
	}
	free(fitaSaida);
	free(v);
	free(vaux);
	free(tamFitasEntradaAtual);
}

void liberaGeralFinal(long int* tamFitasEntrada, long int* tamFitasSaida,
		char** nomeFitas, FILE** fitaEnt, FILE** fitaSaida, TipoRegistro* v,
		TipoRegistro* vaux, long int* tamFitasEntradaAtual, int fitaEntrada) {
	//Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
	free(tamFitasEntrada);
	free(tamFitasSaida);
	for (int j = 0; j < f; j++) {
		fclose(fitaEnt[j]);
	}
	free(fitaEnt);
	for (int j = 0; j < f; j++) {
		fclose(fitaSaida[j]);
	}
	deletaFitas(nomeFitas,fitaEntrada);
	for (int i = 0; i < ff; i++) {
		free(nomeFitas[i]);
	}
	free(nomeFitas);

	free(fitaSaida);
	free(v);
	free(vaux);
	free(tamFitasEntradaAtual);
}


long int getLeitura2f(){
	return leitura2f;
}

long int getEscrita2f(){
	return escrita2f;
}

long int getComparacoes2f(){
	return comparacoes2f;
}

