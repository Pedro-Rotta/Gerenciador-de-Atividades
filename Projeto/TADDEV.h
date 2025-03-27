//FILA CIRCULAR SEM PRIORIDADE
#ifndef TADDEV_H
#define TADDEV_H

#define MAXFILADEV 10

struct _Dev{
    int tempoFinalizacaoAtividade;
};

struct _FilaDev{
    int inicio, fim, qtd;
    _Dev fila[MAXFILADEV];
};


void inicializarDev(_FilaDev &Fila){
    Fila.fim = -1;
    Fila.inicio = 0;
    Fila.qtd = 0;
}

void inserirDev(_FilaDev &Fila){
    if(Fila.fim == MAXFILADEV - 1){
        Fila.fim = -1;
    }
    Fila.fim++;
    Fila.qtd++;
}

_Dev retirarDev(_FilaDev &Fila){
    _Dev aux;
    aux = Fila.fila[Fila.inicio];
    if(Fila.inicio == MAXFILADEV - 1){
        Fila.inicio = -1;
    }
    Fila.inicio++;
    Fila.qtd--;
    return aux;
}

bool cheiaDev(_FilaDev Fila){
    return Fila.qtd == MAXFILADEV;
}

bool vaziaDev(_FilaDev Fila){
    return Fila.qtd == 0;
}

int verificarDesenvolvedoresDisponiveis(_FilaDev Fila){
    return Fila.qtd;
}

#endif
