#include "IntercalacaoFMaisUmSubs.h"
long int leiturafMaisUmSubs = 0;
long int escritafMaisUmSubs = 0;
long long int comparacoesfMaisUmSubs = 0;

int gerarFitasOrdenadasSubsMaisUm(char *nomeArquivo) {
	char nomeFita[30] = "Fita";
	if (!geraFitas(nomeFita, ffsubs1)) {
		cout << "Erro ao gerar as fitas!" << endl;
		return 0;
	}
	FILE *arqIn = fopen(nomeArquivo, "rb");
	if (arqIn == NULL) {
		cout << "Erro ao abrir o arquivo de entrada" << endl;
		excluirFitas(nomeFita, ffsubs1);
		return 0;
	}
	Tlista *fila = criarLista();
	TipoRegistro *regNulo = criarRegistro();
	char nulo[10] = "-1";
	setNota(regNulo, -1);
	setInscricao(regNulo, -1);
	setCidade(regNulo, nulo);
	setEstado(regNulo, nulo);
	setCurso(regNulo, nulo);
	TipoRegistro *reg = criarRegistro();
	TipoRegistro *remov = criarRegistro();
	int numFita = 1;
	char aux[50] = "", num[10] = "";
	FILE *fita;
	while (fread(reg, sizeof(TipoRegistro), 1, arqIn)){
		leiturafMaisUmSubs++;
		if(getCont(fila) < fsubs1 - 1){ 
		// coloca os primeiros itens na fila
			inserirOrdenado(fila,reg);
			comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
		}else{
			if(getNota(getRegistro(getpPrimeiro(fila))) <= 100){ 
			//se o primeiro nao estiver marcado
				removerPrimeiro(fila,remov);
				if(getNota(reg) < getNota(remov)){
					setNota(reg, getNota(reg) + 101);	
					//marcamos a nota como "maior de todas"
					inserirOrdenado(fila,reg);
					comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
				}else{
					inserirOrdenado(fila,reg);
					comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
				}

				//definindo o nome da fita
				strcat(aux, nomeFita);
				sprintf(num, "%d", numFita);
				strcat(aux, num);
				strcat(aux, ".bin");
				fita = fopen(aux, "ab");
				if (fita == NULL){
					cout << "Erro ao abrir o arquivo" << endl;
					fclose(arqIn);
					return 0;
				}
				fwrite(remov,sizeof(TipoRegistro),1, fita); 
				//escreve o item removido na fita
				escritafMaisUmSubs++;
				fclose(fita);
				strcpy(aux, "");
			}else{
 				strcat(aux, nomeFita);
				sprintf(num, "%d", numFita);
				strcat(aux, num);
				strcat(aux, ".bin");
				fita = fopen(aux, "ab");
				if (fita == NULL){
					cout << "Erro ao abrir o arquivo" << endl;
					fclose(arqIn);
					return 0;
				}
				fwrite(regNulo,sizeof(TipoRegistro),1, fita); 
				//escreve registro nulo na fita que está terminando
				escritafMaisUmSubs++;
				fclose(fita);
				strcpy(aux, "");

				if(numFita < fsubs1){
					numFita++;
				}else{
					numFita = 1;
				}
				//Desmarca todos os registros da fila
				Tcelula * auxCelula = criaCelula();
				auxCelula = getpPrimeiro(fila);
				setNota(getRegistro(auxCelula),getNota(
							getRegistro(auxCelula)) - 101);
				while(getpProx(auxCelula) != NULL){
					auxCelula = getpProx(auxCelula);
					setNota(getRegistro(auxCelula),getNota(
						getRegistro(auxCelula)) - 101);
				}
				removerPrimeiro(fila,remov);
				if(getNota(reg) < getNota(remov)){
					setNota(reg, getNota(reg) + 101);	
					//marcamos a nota como "maior de todas"
					inserirOrdenado(fila,reg);
					comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
				}else{
					inserirOrdenado(fila,reg);
					comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
				}
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
				fwrite(remov,sizeof(TipoRegistro),1, fita); 
				//escreve o item removido na fita
				escritafMaisUmSubs++;
				fclose(fita);
				strcpy(aux, "");
			}
		}
	}
	while(!listaVazia(fila)){
		if(getNota(getRegistro(getpPrimeiro(fila))) <= 100){  
			removerPrimeiro(fila,remov);
			//se o primeiro nao estiver marcado

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
			fwrite(remov,sizeof(TipoRegistro),1, fita); 
			//escreve o item removido na fita
			escritafMaisUmSubs++;
			fclose(fita);
			strcpy(aux, "");
		}else{
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

			fwrite(regNulo,sizeof(TipoRegistro),1, fita); 
			//escreve registro nulo na fita que está terminando
			escritafMaisUmSubs++;
			fclose(fita);
			strcpy(aux, "");
			if(numFita < fsubs1){
				numFita++;
			}else{
				numFita = 1;
			}
			//Desmarca todos os registros da fila
			Tcelula * auxCelula = criaCelula();
			auxCelula = getpPrimeiro(fila);
			setNota(getRegistro(auxCelula),getNota(
					getRegistro(auxCelula)) - 101);
			while(getpProx(auxCelula) != NULL){
				auxCelula = getpProx(auxCelula);
				setNota(getRegistro(auxCelula),getNota(
					getRegistro(auxCelula)) - 101);
			}
			removerPrimeiro(fila,remov);
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
			fwrite(remov,sizeof(TipoRegistro),1, fita); 
			//escreve o item removido na fita
			escritafMaisUmSubs++;
			fclose(fita);
			strcpy(aux, "");
		}
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
	fwrite(regNulo,sizeof(TipoRegistro),1, fita); 
	//escreve o item removido na fita
	escritafMaisUmSubs++;
	fclose(fita);
	strcpy(aux, "");
	fclose(arqIn);
	return 1;
}

int ordenaFMaisUmSubs(char **nomeFitas){
	TipoRegistro *regNulo = criarRegistro();
	char nulo[10] = "-1";
	setNota(regNulo, -1);
	setInscricao(regNulo, -1);
	setCidade(regNulo, nulo);
	setEstado(regNulo, nulo);
	setCurso(regNulo, nulo);
	Tlista *fila = criarLista();
	
	//vetor para indicar a fita de onde o registro foi lido
	TipoRegistro *vaux = (TipoRegistro*) calloc(
							ffsubs1, sizeof(TipoRegistro));
	for (int i=0; i<ffsubs1;i++){
		vaux[i] = *regNulo;
	}
	
	//vetores que vao receber o tamanho das fitas
	long int *tamFitasEntrada = (long int*) malloc(
									fsubs1 * sizeof(long int));
	long int *tamFitasEntradaAtual = (long int*) malloc(
									fsubs1 * sizeof(long int));
	char nomeFita[30] = "Fita";
	char aux[30] = "", num[30] = "";
	FILE **fitaEnt, *fitaSaida;
	fitaEnt = (FILE**) malloc(fsubs1 * sizeof(FILE*));
	int primeiraFita = 1;

	//preenche o vetor com o nome das fitas
	for (int i = 0; i < ffsubs1; i++) {
		strcat(aux, nomeFita);
		sprintf(num, "%d", primeiraFita++);
		strcat(aux, num);
		strcat(aux, ".bin");
		strcpy(nomeFitas[i], aux);
		strcpy(aux, "");
	}
	
	//abre as fitas de entrada
	for (int i = 0; i < fsubs1; i++) {
		fitaEnt[i] = fopen(nomeFitas[i], "rb");
		if (fitaEnt[i] == NULL) {
			cout << "Erro ao abrir o arquivo" << endl;
			free(fila);
			free(vaux);
			return 0;
		}
	}
	tamanhoFitas(fitaEnt, tamFitasEntrada, fsubs1, 
					sizeof(TipoRegistro));

	//abre a fita de saida
	fitaSaida = fopen(nomeFitas[ffsubs1 - 1], "a+b");
	if (fitaSaida == NULL) {
		cout << "Erro ao abrir o arquivo" << endl;
		for (int j = 0; j < fsubs1; j++) {
			fclose(fitaEnt[j]);
		}
		free(fitaEnt);
		free(fila);
		free(vaux);
		return 0;
	}

	//le um registro de cada fita de entrada
	for(int i = 0; i < fsubs1; i++){
		fread(&vaux[i], sizeof(TipoRegistro),1,fitaEnt[i]);
		leiturafMaisUmSubs++;
		if(getInscricao(&vaux[i])!= -1){
			inserirOrdenado(fila,&vaux[i]);
			comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
		}
	}

	TipoRegistro *remov = criarRegistro();
	int numeroFitaRemov, terminouBlocos;
	while(1){removerPrimeiro(fila,remov);
		//procurando a qual fita o registro pertencia
		for(int i = 0; i < ffsubs1; i++){
			if(getInscricao(remov) == getInscricao(&vaux[i])){
				numeroFitaRemov = i;
				break;
			}
		}
		fwrite(remov,sizeof(TipoRegistro),1,fitaSaida);
		escritafMaisUmSubs++;

		//le o proximo registro da mesma fita do registro removido
		fread(&vaux[numeroFitaRemov],sizeof(TipoRegistro),1,fitaEnt[numeroFitaRemov]);
		leiturafMaisUmSubs++;
		if(getInscricao(&vaux[numeroFitaRemov]) != -1){
			inserirOrdenado(fila,&vaux[numeroFitaRemov]);
			comparacoesfMaisUmSubs += getComparacoesOrdenacaoLista();
		}
		terminouBlocos = 1;
		
		//verifica se terminou os blocos de todas as fitas de entrada
		for(int i = 0; i < ffsubs1; i++){
			if(getInscricao(&vaux[i]) != -1)
				terminouBlocos = 0;
		}
		if(terminouBlocos == 1){
			//conferimos se a fila já removeu tudo
			while(!listaVazia(fila)){
				removerPrimeiro(fila,remov);
				fwrite(remov,sizeof(TipoRegistro),1,fitaSaida);
				escritafMaisUmSubs++;
			}
			tamanhoFitasAtual(fitaEnt,tamFitasEntradaAtual,fsubs1,sizeof(TipoRegistro));
			if(!leuTodasFitas(tamFitasEntradaAtual,tamFitasEntrada,fsubs1)){ 
			// testamos se as fitas de entrada já foram todas lidas
				fwrite(regNulo,sizeof(TipoRegistro),1,fitaSaida);
				escritafMaisUmSubs++;
				for(int i = 0; i < fsubs1; i++){
					fread(&vaux[i], sizeof(TipoRegistro),1,fitaEnt[i]);
					leiturafMaisUmSubs++;
					if(getInscricao(&vaux[i])!= -1)
						inserirOrdenado(fila,&vaux[i]);
				}
			}else{
				fwrite(regNulo,sizeof(TipoRegistro),1,fitaSaida);
				escritafMaisUmSubs++;
				if(soTemUmBloco(fitaSaida)){ 
				// se so tiver um bloco na fita de saida, terminou
					liberaGeralFinalSubs1(vaux,regNulo,fitaEnt,fitaSaida,
											tamFitasEntrada,tamFitasEntradaAtual,
											remov,&fila,nomeFitas);
					return 1;
				}else{
					liberaGeralSubs1(vaux,regNulo,fitaEnt,fitaSaida,tamFitasEntrada,
									tamFitasEntradaAtual,remov,&fila);
					reorganizaFitasSubsMaisUm(ffsubs1, nomeFitas);
					ordenaFMaisUmSubs(nomeFitas);
					return 1;
				}
			}
		}
	}
	return 0;
}

int reorganizaFitasSubsMaisUm(int numFitaSaida, char **nomeFitas) {
	//Funcao que pega uma fita de saída e redistribui ela nas fitas de entrada
	TipoRegistro *regNulo = criarRegistro();
	char nulo[10] = "-1";
	setNota(regNulo, -1);
	setInscricao(regNulo, -1);
	setCidade(regNulo, nulo);
	setEstado(regNulo, nulo);
	setCurso(regNulo, nulo);

	FILE **fitaEnt, *fitaSaida;
	fitaEnt = (FILE**) malloc(fsubs1 * sizeof(FILE*));

    for (int i = 0; i < fsubs1; i++) {
    	remove(nomeFitas[i]);
    }

    //abre as fitas de entrada
    for (int i = 0; i < fsubs1; i++) {
	  fitaEnt[i] = fopen(nomeFitas[i], "ab");
	  if (fitaEnt[i] == NULL) {
		  cout << "Erro ao abrir o arquivo" << endl;
		  return 0;
	  }
    }

    // abre a fita de saida
	  fitaSaida = fopen(nomeFitas[ffsubs1 - 1], "rb");
	  if (fitaSaida == NULL) {
		  cout << "Erro ao abrir o arquivo" << endl;
		  for (int j = 0; j < fsubs1; j++) {
			  fclose(fitaEnt[j]);
		  }
		  free(fitaEnt);
		  return 0;
	  }

    TipoRegistro *reg = criarRegistro();

    // Agora vamos ler os blocos da fita de saida e 
	//enviar para as fitas de entrada
    int numeroFitaEntrada = 0;		
	// variável que irá receber o numero da fita que será a fita de entrada
    while (fread(reg, sizeof(TipoRegistro), 1, fitaSaida)) {
    	leiturafMaisUmSubs++;
    	if(getInscricao(reg) == - 1){		
		//terminamos um bloco, temos que mudar a fita de entrada
        	fwrite(regNulo, sizeof(TipoRegistro),1,fitaEnt[numeroFitaEntrada]);
        	escritafMaisUmSubs++;
            if(numeroFitaEntrada < fsubs1 - 1)
            	numeroFitaEntrada++;
            else
            	numeroFitaEntrada = 0;
        }else{  	
		// podemos escrever o item na fita de entrada designada
        	fwrite(reg,sizeof(TipoRegistro),1, fitaEnt[numeroFitaEntrada]);
        	escritafMaisUmSubs++;
        }
    }

    //libera a memória utilizada na função
    fclose(fitaSaida);
	remove(nomeFitas[ffsubs1 - 1]); 
	// remove a fita de saida

    for (int j = 0; j < fsubs1; j++) {
		fclose(fitaEnt[j]);
	}
	free(fitaEnt);
	free(reg);
    return 1;

}

int soTemUmBloco(FILE *fitaSaida){
	//Funcao que retorna 1 se tiver apenas um bloco 
	//no arquivo de saida, e zero caso contrario
	rewind (fitaSaida);
    TipoRegistro *reg = criarRegistro();
    int contBlocos = 0;
    while(fread(reg, sizeof(TipoRegistro), 1, fitaSaida)){
    	leiturafMaisUmSubs++;
    	if (getInscricao(reg)==-1){
        	contBlocos++;
        }
    }
    free(reg);
    if(contBlocos == 1)
		return 1;
    else
    	return 0;
}

void liberaGeralSubs1 (TipoRegistro *vaux, TipoRegistro *regNulo, 
					FILE** fitaEnt, FILE* fitaSaida,long int* tamFitasEntrada, 
					long int* tamFitasEntradaAtual, TipoRegistro *remov, 
															Tlista **fila){
	//Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
	free(vaux);
    free(regNulo);
    for (int j = 0; j < fsubs1; j++) {
    	fclose(fitaEnt[j]);
	}
	free(fitaEnt);
   	fclose(fitaSaida);
	free(tamFitasEntrada);
    free(tamFitasEntradaAtual);
    free(remov);
    free(*fila);
}


void liberaGeralFinalSubs1 (TipoRegistro *vaux, TipoRegistro *regNulo, 
							FILE** fitaEnt, FILE* fitaSaida,
							long int* tamFitasEntrada, long int* tamFitasEntradaAtual, 
							TipoRegistro *remov, Tlista **fila, char** nomeFitas){
	//Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
    for (int j = 0; j < fsubs1; j++) {
    	fclose(fitaEnt[j]);
    }
    fclose(fitaSaida);
    deletaFitasSubs1(nomeFitas,ffsubs1);
    free(vaux);
	free(regNulo);
	free(fitaEnt);
	free(tamFitasEntrada);
    free(tamFitasEntradaAtual);
    free(remov);
    free(*fila);
}

void liberaNomeFitasSubs1(char **nomeFitas){
	for (int i = 0; i < ffsubs1; i++) {
			free(nomeFitas[i]);
		}
	free(nomeFitas);
}

void deletaFitasSubs1(char** nomeFitas, int fitaSaida){
	//Deleta as fitas e deixa a fita de saida
	for(int i = 0; i < ffsubs1; i++){
		if(i != fitaSaida - 1){
			if(remove(nomeFitas[i])){
				cout << "Erro ao tentar apagar arquivo" << endl;
				exit(1);
			}
		}
	}
}

long int getLeiturafMaisUmSubs(){
	return leiturafMaisUmSubs;
}

long int getEscritafMaisUmSubs(){
	return escritafMaisUmSubs;
}

long long int getComparacoesfMaisUmSubs(){
	return comparacoesfMaisUmSubs;
}
