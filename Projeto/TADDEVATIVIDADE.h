//FILA CIRCULAR COM PRIORIDADE DE TEMPO

#ifndef TADDEVATIVIDADE_H
#define TADDEVATIVIDADE_H

#include "TADDEV.h" 
#include "TADATIVIDADE.h" 

#define MAXFILAATIVIDADEDEV 10

struct _AtividadeDev{
    _Dev dev;
    _Atividade atividade;
};

struct _FilaAtividadeDev{
    int inicio, fim, qtd;
    _AtividadeDev fila[MAXFILAATIVIDADEDEV];
};


void inicializarAtividadeDev(_FilaAtividadeDev &Fila){
    Fila.fim = -1;
    Fila.inicio = 0;
    Fila.qtd = 0;
}

void inserirAtividadeDev(_FilaAtividadeDev &Fila, _Dev elemDev, _Atividade elemAtividade, int contadorGeral){
    if(Fila.fim == MAXFILAATIVIDADEDEV - 1){
        Fila.fim = -1;
    }

    ++Fila.fim;
    Fila.qtd++;
    Fila.fila[Fila.fim].dev = elemDev;
    Fila.fila[Fila.fim].atividade = elemAtividade;

    Fila.fila[Fila.fim].dev.tempoFinalizacaoAtividade = Fila.fila[Fila.fim].atividade.tempoConclusao + contadorGeral;
    for(int i = Fila.fim; i > 0 && Fila.fila[i].dev.tempoFinalizacaoAtividade != Fila.fila[i-1].dev.tempoFinalizacaoAtividade; i--){
        if(Fila.fila[i].dev.tempoFinalizacaoAtividade < Fila.fila[i-1].dev.tempoFinalizacaoAtividade){
            _AtividadeDev aux = Fila.fila[i-1];
            Fila.fila[i-1] = Fila.fila[i];
            Fila.fila[i] = aux;
        }
    }
}

_AtividadeDev retirarAtividadeDev(_FilaAtividadeDev &Fila){
    if(Fila.inicio == MAXFILAATIVIDADEDEV - 1){
        Fila.inicio = -1;
    }

    _AtividadeDev aux;
    aux = Fila.fila[Fila.inicio];
    ++Fila.inicio;
    Fila.qtd--;
    return aux;
}

int visualizarTempoFinalizacaoAtividade(_FilaAtividadeDev Fila){
    return Fila.fila[Fila.inicio].dev.tempoFinalizacaoAtividade;
}

bool cheiaAtividadeDev(_FilaAtividadeDev &Fila){
    return Fila.qtd == MAXFILAATIVIDADEDEV;
}

bool vaziaAtividadeDev(_FilaAtividadeDev &Fila){
    return Fila.qtd == 0;
}

#endif
