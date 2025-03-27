//FILA CIRCULAR COM PRIORIDADE 
#ifndef TADATIVIDADE_H
#define TADATIVIDADE_H

#include "TADDEV.h"
#include "TADATIVIDADE.h" 


#define MAXFILAATIVIDADE 3

struct _Atividade{
    //Ler arquivo, e transformar o texto para 1,2 ou 3
    int prioridade; //1 = prioridade baixa || 2 = prioridade Media || 3 = prioridade alta
    int tempoConclusao; //Tempo ate concluir a tarefa, considerar em segundos
    char nomeTarefa[100]; // nome Tarefa a realizar
    char responsavel[30]; // Nome do cliente 
    char dataInicio[11]; // AAAA-MM-DD
    int tempoEspera;
};

struct _FilaAtividade{
    int inicio, fim, qtd;
    _Atividade fila[MAXFILAATIVIDADE];
};

void inicializarAtividade(_FilaAtividade &gerenciarAtividades);
void inserirAtividade(_FilaAtividade &gerenciarAtividades, char elem);
_Atividade retirarElementoAtividade(_FilaAtividade &gerenciarAtividades);
_Atividade RetornarElementoDoInicioAtividade(_FilaAtividade &gerenciarAtividades);
_Atividade RetornarElementoDoFimAtividade(_FilaAtividade &gerenciarAtividades);
bool VaziaAtividade(_FilaAtividade &gerenciarAtividades);
bool CheiaAtvividade(_FilaAtividade &gerenciarAtividades);


void inicializarAtividade(_FilaAtividade &gerenciarAtividades){
    gerenciarAtividades.inicio = 0;
    gerenciarAtividades.fim = -1;
    gerenciarAtividades.qtd = 0;
}
void inserirAtividade(_FilaAtividade &gerenciarAtividades, _Atividade elem){
    if(gerenciarAtividades.fim == MAXFILAATIVIDADE - 1){
        gerenciarAtividades.fim = -1;
    }
    gerenciarAtividades.fila[++gerenciarAtividades.fim] = elem;
    ++gerenciarAtividades.qtd;
    //INSERCAO COM PRIORIDADE
    for (int i = gerenciarAtividades.fim; i > 0 && gerenciarAtividades.fila[i].prioridade != gerenciarAtividades.fila[i - 1].prioridade; i--) {
        if (gerenciarAtividades.fila[i].prioridade > gerenciarAtividades.fila[i - 1].prioridade) {
            _Atividade temp = gerenciarAtividades.fila[i - 1];
            gerenciarAtividades.fila[i - 1] = gerenciarAtividades.fila[i];
            gerenciarAtividades.fila[i] = temp;
        }
    }
}
_Atividade retirarAtividade(_FilaAtividade &gerenciarAtividades){
    _Atividade aux;
    aux = gerenciarAtividades.fila[gerenciarAtividades.inicio];
    if(gerenciarAtividades.inicio == MAXFILAATIVIDADE - 1){
        gerenciarAtividades.inicio = -1;
    }
    gerenciarAtividades.inicio++;
    gerenciarAtividades.qtd--;
    return aux;
}
_Atividade RetornarPrimeiroElementoAtividade(_FilaAtividade &gerenciarAtividades){
    return gerenciarAtividades.fila[gerenciarAtividades.inicio];
}
_Atividade RetornarUltimoElementoAtividade(_FilaAtividade &gerenciarAtividades){
    return gerenciarAtividades.fila[gerenciarAtividades.fim];
}
bool VaziaAtividade(_FilaAtividade &gerenciarAtividades){
    return gerenciarAtividades.qtd == 0;
}
bool CheiaAtividade(_FilaAtividade &gerenciarAtividades){
    return gerenciarAtividades.qtd == MAXFILAATIVIDADE;
}

#endif