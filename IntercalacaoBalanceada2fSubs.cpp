long int leitura2fSubs = 0;
long int escrita2fSubs = 0;
long int comparacoes2fSubs = 0;

#include "IntercalacaoBalanceada2fSubs.h"

int gerarFitasOrdenadasSubs(char *nomeArquivo) {
    char nomeFita[30] = "Fita";
    if (!geraFitas(nomeFita, ffsubs)) {
        cout << "Erro ao gerar as fitas!" << endl;
        return 0;
    }
    FILE *arqIn = fopen(nomeArquivo, "rb");
    if (arqIn == NULL) {
        cout << "Erro ao abrir o arquivo de entrada" << endl;
        excluirFitas(nomeFita, ffsubs);
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
    while (fread(reg, sizeof(TipoRegistro), 1, arqIn)) {

        leitura2fSubs++;

        if (getCont(fila) < fsubs - 1) { 
		// coloca os primeiros itens na fila
            escrita2fSubs++;
            inserirOrdenado(fila, reg);
            comparacoes2fSubs += getComparacoesOrdenacaoLista();
        } else {
            if (getNota(getRegistro(getpPrimeiro(fila))) <= 100) {  
			//se o primeiro nao estiver marcado
                removerPrimeiro(fila, remov);
                if (getNota(reg) < getNota(remov)) {
                    setNota(reg, getNota(reg) + 101);    
					//marcamos a nota como "maior de todas"
                    inserirOrdenado(fila, reg);
                    comparacoes2fSubs += getComparacoesOrdenacaoLista();
                } else {
                    inserirOrdenado(fila, reg);
                    comparacoes2fSubs += getComparacoesOrdenacaoLista();
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
                fwrite(remov, sizeof(TipoRegistro), 1, fita); 
				//escreve o item removido na fita
                escrita2fSubs++;
                fclose(fita);
                strcpy(aux, "");
            } else {
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
                fwrite(regNulo, sizeof(TipoRegistro), 1, fita); 
				//escreve registro nulo na fita que esta terminando
                escrita2fSubs++;
                fclose(fita);
                strcpy(aux, "");
                if (numFita < fsubs) {
                    numFita++;
                } else {
                    numFita = 1;
                }
                //Desmarca todos os registros da fila
                Tcelula *auxCelula = criaCelula();
                auxCelula = getpPrimeiro(fila);
                setNota(getRegistro(auxCelula), getNota(getRegistro(auxCelula)) - 101);
                while (getpProx(auxCelula) != NULL) {
                    auxCelula = getpProx(auxCelula);
                    setNota(getRegistro(auxCelula), getNota(getRegistro(auxCelula)) - 101);
                }
                removerPrimeiro(fila, remov);
                if (getNota(reg) < getNota(remov)) {
                    setNota(reg, getNota(reg) + 101);    //marcamos a nota como "maior de todas"
                    inserirOrdenado(fila, reg);
                    comparacoes2fSubs += getComparacoesOrdenacaoLista();
                } else {
                    inserirOrdenado(fila, reg);
                    comparacoes2fSubs += getComparacoesOrdenacaoLista();
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
                fwrite(remov, sizeof(TipoRegistro), 1, fita); 
				//escreve o item removido na fita
                escrita2fSubs++;
                fclose(fita);
                strcpy(aux, "");
            }
        }
    }
    while (!listaVazia(fila)) {
        if (getNota(getRegistro(getpPrimeiro(fila))) <= 100) {  
		//se o primeiro nao estiver marcado
            removerPrimeiro(fila, remov);
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
            fwrite(remov, sizeof(TipoRegistro), 1, fita); 
			//escreve o item removido na fita
            escrita2fSubs++;
            fclose(fita);
            strcpy(aux, "");
        } else {
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
            fwrite(regNulo, sizeof(TipoRegistro), 1, fita); 
			//escreve registro nulo na fita que est� terminando
            escrita2fSubs++;
            fclose(fita);
            strcpy(aux, "");
            if (numFita < fsubs) {
                numFita++;
            } else {
                numFita = 1;
            }
            //Desmarca todos os registros da fila
            Tcelula *auxCelula = criaCelula();
            auxCelula = getpPrimeiro(fila);
            setNota(getRegistro(auxCelula), getNota(getRegistro(auxCelula)) - 101);
            while (getpProx(auxCelula) != NULL) {
                auxCelula = getpProx(auxCelula);
                setNota(getRegistro(auxCelula), getNota(getRegistro(auxCelula)) - 101);
            }
            removerPrimeiro(fila, remov);
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
            fwrite(remov, sizeof(TipoRegistro), 1, fita); 
			//escreve o item removido na fita
            escrita2fSubs++;
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
    fwrite(regNulo, sizeof(TipoRegistro), 1, fita); 
	//escreve o item removido na fita
    escrita2fSubs++;
    fclose(fita);
    strcpy(aux, "");
    fclose(arqIn);
    return 1;
}

int misturarFitasSubs(int fitaEntrada) {
    //Funcao que junta as fitas iniciais at� que sobre apenas uma
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
    Tlista *fila = criarLista();
    //vetor para indicar a fita de onde o registro foi lido
    TipoRegistro *vaux = (TipoRegistro *) calloc(fsubs, sizeof(TipoRegistro));
    for (int i = 0; i < fsubs; i++) {
        vaux[i] = *regNulo;
    }
    //vetores que vao receber o tamanho das fitas
    long int *tamFitasEntrada = (long int *) malloc(fsubs * sizeof(long int));
    //aloca um vetor com o nome das fitas
    nomeFitas = (char **) malloc(ffsubs * sizeof(char *));
    
	for (int i = 0; i < ffsubs; i++)
        nomeFitas[i] = (char *) malloc(30 * sizeof(char));
    
	char nomeFita[30] = "Fita";
    char aux[30] = "", num[30] = "";
    FILE **fitaEnt, **fitaSaida;
    fitaEnt = (FILE **) malloc(fsubs * sizeof(FILE *));
    fitaSaida = (FILE **) malloc(fsubs * sizeof(FILE *));
    int posicaoSaida, primeiraMetade, posicaoEntrada;
    //preenche o vetor com o nome das fitas
    for (int i = 0; i < ffsubs; i++) {
        strcat(aux, nomeFita);
        sprintf(num, "%d", primeiraFita++);
        strcat(aux, num);
        strcat(aux, ".bin");
        strcpy(nomeFitas[i], aux);
        strcpy(aux, "");
    }
    //abre as fitas de entrada
    if (fitaEntrada == 1) {        
	//primeira fita de entrada = 0
        posicaoEntrada = 0;
        for (int i = 0; i < fsubs; i++) {
            fitaEnt[i] = fopen(nomeFitas[i], "rb");
            if (fitaEnt[i] == NULL) {
                cout << "Erro ao abrir o arquivo" << endl;
                free(fila);
                free(vaux);
                return 0;
            }
            fitaEntrada++;
        }
        tamanhoFitas(fitaEnt, tamFitasEntrada, fsubs, sizeof(TipoRegistro));
    } else {            
	//primeira fita de entrada = f+1
        posicaoEntrada = 0;
        for (int i = 0; i < fsubs; i++) {
            fitaEnt[i] = fopen(nomeFitas[fitaEntrada - 1], "rb");
            if (fitaEnt[i] == NULL) {
                cout << "Erro ao abrir o arquivo" << endl;
                free(fila);
                free(vaux);
                return 0;
            }
            fitaEntrada++;
        }
        tamanhoFitas(fitaEnt, tamFitasEntrada, fsubs, sizeof(TipoRegistro));
    }
    int numFitaSaida;
    //abre as fitas de saida
    posicaoSaida = 0;
    if (fitaEntrada == fsubs + 1) {
        numFitaSaida = fsubs;
        primeiraMetade = 0;        
		//1 = primeira metade, 0 = segunda metade
        for (int i = 0; i < fsubs; i++) {
            fitaSaida[i] = fopen(nomeFitas[numFitaSaida], "ab");
            if (fitaSaida[i] == NULL) {
                cout << "Erro ao abrir o arquivo" << endl;
                for (int j = 0; j < fsubs; j++) {
                    fclose(fitaEnt[j]);
                }
                free(fitaEnt);
                free(fila);
                free(vaux);
                return 0;
            }
            numFitaSaida++;
        }
    }else 
        numFitaSaida = posicaoSaida = 0;
        primeiraMetade = 1;
        for (int i = 0; i < fsubs; i++) {
            fitaSaida[i] = fopen(nomeFitas[i], "ab");
            if (fitaSaida[i] == NULL) {
                cout << "Erro ao abrir o arquivo" << endl;
                for (int j = 0; j < fsubs; j++) {
                    fclose(fitaEnt[j]);
                }
                free(fitaEnt);
                free(fila);
                free(vaux);
                return 0;
            }
            numFitaSaida++;
        }
    int fita, i = 0;
    TipoRegistro *remov = criarRegistro();
    long int *tamFitasEntradaAtual = (long int *) malloc(fsubs * sizeof(long int));
    long int *tamFitasSaida = (long int *) malloc(fsubs * sizeof(long int));
    if (primeiraMetade == 0) {
        while (posicaoEntrada < fsubs) {
            fread(&vaux[i], sizeof(TipoRegistro), 1,
                  fitaEnt[posicaoEntrada++]);    
				  //pega um registro de cada fita de entrada
            leitura2fSubs++;
            inserirOrdenado(fila, &vaux[i]);
            comparacoes2fSubs += getComparacoesOrdenacaoLista();
            i++;
        }
    } else {
        while (posicaoEntrada < fsubs) {
            fread(&vaux[i], sizeof(TipoRegistro), 1,
                  fitaEnt[posicaoEntrada++]);    
				  //pega um registro de cada fita de entrada
            leitura2fSubs++;
            inserirOrdenado(fila, &vaux[i]);
            comparacoes2fSubs += getComparacoesOrdenacaoLista();
            i++;
        }
    }
    while (1) {
        if (listaVazia(fila)) {
            fwrite(regNulo, sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
            escrita2fSubs++;
            posicaoSaida++;
            tamanhoFitasAtual(fitaEnt, tamFitasEntradaAtual, fsubs,
                              sizeof(TipoRegistro)); 
			// tamFitasEntradaAtual = pega o tamanho das fitas no momento atual
            tamanhoFitas(fitaSaida, tamFitasSaida, fsubs, sizeof(TipoRegistro)); 
			//pega o tamanho das fitas de saida

            if ((leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada, fsubs)) 
				&& apenasUmaFitaSaida(tamFitasSaida, fsubs)) { 
				//se tiver s� uma fita (de saida) cheia e todas 
				//as fitas de entrada tiverem sido lidas
                liberaGeralFinalSubs(tamFitasEntrada, tamFitasSaida, nomeFitas, fitaEnt, 
							fitaSaida, vaux, tamFitasEntradaAtual, fitaRecursao, &fila);
                return 1;
            }
            if (leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada, fsubs)) { 
			//se leu todas as fitas de entrada, mas existe mais de uma fita de saida preenchida
                liberaGeralSubs(tamFitasEntrada, tamFitasSaida, fitaEnt, fitaSaida, vaux, 
								tamFitasEntradaAtual, &fila);
                if (primeiraMetade == 0) {    
				//fita de entrada esta na primeira metade
                    for (int i = 0; i < fsubs; i++) {
                        remove(nomeFitas[i]);
                    }
                } else {
                    for (int i = f; i < ffsubs; i++) {
                        remove(nomeFitas[i]);
                    }
                }
                liberaNomeFitas(nomeFitas);
                if (fitaRecursao == 1) {
                    misturarFitasSubs(fsubs + 1);
                    break;
                } else {
                    misturarFitasSubs(1);
                    break;
                }
            }
            if (!leuTodasFitas(tamFitasEntradaAtual, tamFitasEntrada,
                               fsubs)) {    //se nao leu todas as fitas, continuar do come�o
                for (int i = 0; i < fsubs; i++) {
                    vaux[i] = *regNulo;
                }
                for (int i = 0; i < fsubs; i++) {
                    if (tamFitasEntradaAtual[i] != tamFitasEntrada[i]) {
                        fread(&vaux[i], sizeof(TipoRegistro), 1,
                              fitaEnt[i]);    //pega um registro de cada fita de entrada
                        leitura2fSubs++;
                        inserirOrdenado(fila, &vaux[i]);
                        comparacoes2fSubs += getComparacoesOrdenacaoLista();
                    }
                }
            }
        }
        removerPrimeiro(fila, remov);
        for (int j = 0; j < tamBloco; j++) {
            if (getInscricao(remov) == getInscricao(&vaux[j])) {
                fita = j;        
				//indica a fita que devera ter um elemento lido
            }
        }
        if (posicaoSaida < fsubs) {
            if (vaux[fita].inscricao != -1) {
                fwrite(remov, sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
                escrita2fSubs++;
            }
        } else {
            posicaoSaida = 0;
            fwrite(remov, sizeof(TipoRegistro), 1, fitaSaida[posicaoSaida]);
            escrita2fSubs++;
        }
        fread(&vaux[fita], sizeof(TipoRegistro), 1, fitaEnt[fita]);        
		//pega registro da primeira Fita de entrada
        leitura2fSubs++;
        if (getInscricao(&vaux[fita]) != -1) {
            inserirOrdenado(fila, &vaux[fita]);
            comparacoes2fSubs += getComparacoesOrdenacaoLista();
        }
    }
    return 0;
}

void liberaGeralSubs(long int *tamFitasEntrada, long int *tamFitasSaida,
                     FILE **fitaEnt, FILE **fitaSaida,
                     TipoRegistro *vaux, long int *tamFitasEntradaAtual, 
					 Tlista **fila) {
    //Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
    free(tamFitasEntrada);
    free(tamFitasSaida);
    for (int j = 0; j < fsubs; j++) {
        fclose(fitaEnt[j]);
    }
    free(fitaEnt);
    for (int j = 0; j < fsubs; j++) {
        fclose(fitaSaida[j]);
    }
    free(fitaSaida);
    free(*fila);
    free(vaux);
    free(tamFitasEntradaAtual);
}

void liberaGeralFinalSubs(long int *tamFitasEntrada, long int *tamFitasSaida,
                          char **nomeFitas, FILE **fitaEnt, FILE **fitaSaida, 
						  TipoRegistro *vaux,long int *tamFitasEntradaAtual, 
						  int fitaEntrada, Tlista **fila) {
    //Funcao para liberar as memorias alocadas e fechar os arquivos utilizados
    free(tamFitasEntrada);
    free(tamFitasSaida);
    for (int j = 0; j < fsubs; j++) {
        fclose(fitaEnt[j]);
    }
    free(fitaEnt);
    for (int j = 0; j < fsubs; j++) {
        fclose(fitaSaida[j]);
    }
    deletaFitas(nomeFitas, fitaEntrada);
    for (int i = 0; i < ffsubs; i++) {
        free(nomeFitas[i]);
    }
    free(nomeFitas);
    free(fitaSaida);
    free(*fila);
    free(vaux);
    free(tamFitasEntradaAtual);
}

long int getLeitura2fSubs() {
    return leitura2fSubs;
}

long int getEscrita2fSubs() {
    return escrita2fSubs;
}

long int getComparacoes2fSubs() {
    return comparacoes2fSubs;
}


