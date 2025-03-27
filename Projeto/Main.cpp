#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "Conio2_Facilitado.h"
#include "Interface.h"
#include "TADDEV.h"
#include "TADATIVIDADE.h"
#include "TADDEVATIVIDADE.h"

int main(void);
void executar(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int contTarefasConcluidas[3], int contEsperaTotal[3]);
void interfaceDoSistema();
_Atividade lerLinhaArquivo(FILE *f, int &yR);
void inicializarContador(int contador[3]);
void inserirAtividadeRandomicamente(int &numeroSorteado, int tempoExecucaoPrograma, FILE *f, _FilaAtividade &gerenciarAtividades, int &yG, int &yR, int contadorGeral);
void relatorios(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int contTarefasConcluidas[3], int contEsperaTotal[3]);
int sorteioNumero(int tempo);
void exibirInformacoesTela(_FilaAtividade gerenciarAtividades, _FilaDev desenvolvedores, _FilaAtividadeDev atividadeDev, int tempo);
void ocupaDevComAtividade(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int tempo, int &yR);
void mensagemInformacoesOcupacaoDev(_AtividadeDev aux, int &yR, int tempo);
void incrementoTarefasConcluidas(_AtividadeDev aux, int contTarefasConcluidas[3]);
void somarEsperaTotal(int contadorGeral, _AtividadeDev aux, int contEsperaTotal[3]);

int main(void){
        //CRIANDO ELEMENTOS QUE SERAO UTILIZADOS ATE O FIM DO PROGRAMA
    _FilaAtividade gerenciarAtividades;
    _FilaDev desenvolvedores;
    _FilaAtividadeDev atividadeDev;
    
    inicializarAtividade(gerenciarAtividades);
    inicializarDev(desenvolvedores);
    inicializarAtividadeDev(atividadeDev);

    int tarefasConcluidas[3]; // 1 = Melhoria || 2 = Importante || 3 = critico
    int tempoDeEspera[3]; // 1 = Melhoria || 2 = Importante || 3 = critico
    inicializarContador(tarefasConcluidas);
    inicializarContador(tempoDeEspera);
    
    executar(gerenciarAtividades, desenvolvedores, atividadeDev, tarefasConcluidas, tempoDeEspera);

    relatorios(gerenciarAtividades, desenvolvedores, atividadeDev, tarefasConcluidas, tempoDeEspera);
    return 0;
}

void executar(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int contTarefasConcluidas[3], int contEsperaTotal[3]){
    
        //INICIALIZACAO DE VARIAVEIS
    FILE *f = fopen("dados.txt", "r");
    srand(time(NULL));
    int yG = 25;
    int yR = 25;
    int tempoExecucaoPrograma;
    int numeroSorteado;
    int quantiaProgramadores;
    int auxQtd = 0;

        //Desenha interface
    interfaceDoSistema();

        //recebe e insere a quantidade de programadores
    exibeTexto(22, 10, "Quantidade de programadores: ", WHITE);
    scanf("%d", &quantiaProgramadores);
    for(int i = 0, erro = 0; i < quantiaProgramadores && erro == 0; i++){
        if(!cheiaDev(desenvolvedores)){
            inserirDev(desenvolvedores);
        }
        else{
            exibirNoDisplayErroVermelho(yR, "Erro, fila nao suporta todos os desenvolvedores");
            exibirNoDisplayErroVermelho(yR, "Fila preenchida ate o limite, 10 dev's");
            erro++;
        }
    }

        //Recebe tempo de execucao do programa
    exibeTexto(22, 12, "Tempo de execucao do programa: ", WHITE);
    scanf("%d", &tempoExecucaoPrograma);

        //Sorteia numero
    numeroSorteado = sorteioNumero(tempoExecucaoPrograma);

        //Pula a primeira linha do arquivo
    lerLinhaArquivo(f, yR);

        //INFORMACOES DA TELA
    exibirInformacoesTela(gerenciarAtividades, desenvolvedores, atividadeDev, tempoExecucaoPrograma);
    
        //limpa tela do display completa
    clearArea(21, 99, 10, 20);

        //Começa a repeticao em base do tempo do programa
    for (int contadorGeral = 1; contadorGeral <= tempoExecucaoPrograma; contadorGeral++)   // Repetir ate chegar no tempo pre-determinado
    {
            //Informacao em tempo real do contador
        exibeTexto(71, 23, "Contador Geral: ", YELLOW);  printf("%d", contadorGeral);

            //Estrutura para decidir se ira inserir nova atividade ou nao
        if((contadorGeral % numeroSorteado) == 0){   //Utiliza o numeroAleatorio para decidir quando inserir novos dados na fila
                //funcao que insere atividae e gera um novo numero aleatorio
            inserirAtividadeRandomicamente(numeroSorteado, tempoExecucaoPrograma, f, gerenciarAtividades, yG, yR, contadorGeral);
        }

            //Estrutura para verificar se tem Dev livre para a atividade
        while(!vaziaDev(desenvolvedores) && !VaziaAtividade(gerenciarAtividades) && !cheiaAtividadeDev(atividadeDev)){
                //Retira dev, atividade e insere na atividaDev
                //Retorna uma mensagem com detalhes a tela
            ocupaDevComAtividade(gerenciarAtividades, desenvolvedores, atividadeDev, contadorGeral, yR);
        }
            
            //Verifica se tem elementos na atividadeDev
        if(!vaziaAtividadeDev(atividadeDev)){
                //Verifica se o tempo da atividade ja foi concluida, se for, retira, senão ignora
            while(!vaziaAtividadeDev(atividadeDev) && visualizarTempoFinalizacaoAtividade(atividadeDev) <= contadorGeral){
                    //Manipula as estruturas
                _AtividadeDev aux = retirarAtividadeDev(atividadeDev);
                somarEsperaTotal(contadorGeral, aux, contEsperaTotal);
                inserirDev(desenvolvedores);
                    //Exibe mensagem na tela
                exibirNoDisplayErroVerde(yG, "Um Dev finalizou atividade");
                    //Incrementa os dados nos contadores
                incrementoTarefasConcluidas(aux, contTarefasConcluidas);
            }
        }

            //Atualiza informacoes na tela
        exibirInformacoesTela(gerenciarAtividades, desenvolvedores, atividadeDev, tempoExecucaoPrograma);

            //Verifica se atividade caiu na area de espera, se caiu, mensagem na tela
        if(auxQtd < gerenciarAtividades.qtd){
            exibirNoDisplayErroVermelho(yR, "Atividade enviada para area de espera");
        }
        auxQtd = gerenciarAtividades.qtd;

            //Tempo de 1 seg para melhor visualizacao do programa
        Sleep(1000);
    }

    fclose(f);
    limparDisplayPrincipal();
    exibeTexto(43, 15, "Pressione qualquer tecla para avancar", WHITE);
    getch();
}

//pega a linha no arquivo e insere atividade na Fila respeitando sua prioridade, atualiza o valor Aleatorio
void inserirAtividadeRandomicamente(int &numeroSorteado, int tempoExecucaoPrograma, FILE *f, _FilaAtividade &gerenciarAtividades, int &yG, int &yR, int contadorGeral){
        
        //SORTEIO DO NOVO VALOR
    numeroSorteado = sorteioNumero(tempoExecucaoPrograma);

    int posicaoPonteiro = ftell(f);
    _Atividade auxAtividade = lerLinhaArquivo(f, yR);
    auxAtividade.tempoEspera = contadorGeral;
    if(auxAtividade.prioridade != 0){    //verifica se deu certo a leitura
            //Mensagem no display para melhor visualizacao
        exibirNoDisplayErroVerde(yG, "Chegou uma atividade");
        if(!CheiaAtividade(gerenciarAtividades)){
            limparDisplayPrincipal();
            prateleiraVertical(21, 26, 10, 20, 1, BLUE);
            prateleiraVertical(28, 33, 10, 20, 1, GREEN);
            prateleiraVertical(35, 40, 10, 20, 1, RED);            
            exibeTexto(43, 10, "NOVA ATIVIDADE", RED);
            exibeTexto(44, 12, "Tipo: ", WHITE); printf("%d", auxAtividade.prioridade);
            exibeTexto(44, 14, "Tempo Conclusao: ", WHITE); printf("%d", auxAtividade.tempoConclusao);
            exibeTexto(44, 16, "Nome Tarefa: ", WHITE); printf("%s", auxAtividade.nomeTarefa);
            exibeTexto(44, 18, "Responsavel: ", WHITE); printf("%s", auxAtividade.responsavel);
            exibeTexto(44, 20, "Data: ", WHITE); printf("%s", auxAtividade.dataInicio);
            inserirAtividade(gerenciarAtividades, auxAtividade);
        }
        else{
            fseek(f, posicaoPonteiro, 0);
            exibirNoDisplayErroVermelho(yR, "atividade nao inserida, fila de atividades cheia");
        }
    }
}
    //Le linha do arquivo
_Atividade lerLinhaArquivo(FILE *f, int &yR) {
    char auxPrioridade[15];
    char linha[256];
    _Atividade fila;

    if (fgets(linha, sizeof(linha), f) != NULL) {
        sscanf(linha, "%[^,],%d,%[^,],%[^,],%s",
        auxPrioridade,
        &fila.tempoConclusao,
        fila.nomeTarefa,
        fila.responsavel,
        fila.dataInicio);

        // Converter auxPrioridade
        if (strcmp(auxPrioridade, "Critico") == 0) {
            fila.prioridade = 3;
        } else if (strcmp(auxPrioridade, "Importante") == 0) {
            fila.prioridade = 2;
        } else {
            fila.prioridade = 1;
        }
    } else {
        fila.prioridade = 0; // Indica erro ou fim do arquivo
            //Exibe erro
        exibirNoDisplayErroVermelho(yR, "Erro ao ler linha do arquivo");
        exibirNoDisplayErroVermelho(yR, "Nao ha mais dados no arquivo");
    }
    return fila;
}
    
    //Inicializa os contadores para os niveis de prioridade
void inicializarContador(int contador[3]){
    for(int i = 0; i < 3; i++){
        contador[i] = 0;
    }
}
    
    //Relatorio final do programa, exibe todas as informacoes consideradas necessarias
void relatorios(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int contTarefasConcluidas[3], int contEsperaTotal[3]){
        //Limpa display principal
    clearArea(21, 99, 10, 20);
    interfaceDoSistema();
        //TAREFAS CONCLUIDAS
    exibeTexto(22, 10, "<-Tarefas Concluidas->", BLUE);
    exibeTexto(23, 11, "Critico: ", WHITE); printf("%d", contTarefasConcluidas[2]);
    exibeTexto(23, 12, "Importante: ", WHITE); printf("%d", contTarefasConcluidas[1]);
    exibeTexto(23, 13, "Melhoria: ", WHITE); printf("%d", contTarefasConcluidas[0]);

        //LINHA PARA SEPARAR
    linhaVerticalComExtremidades(45, 9, 21, MAGENTA);
    linhaVerticalComExtremidades(71, 9, 21, MAGENTA);

        //TEMPO MEDIO POR TAREFA
    exibeTexto(47, 10, "<-Tempo Medio Espera->", GREEN);
    exibeTexto(48, 11, "Critico: ", WHITE); 
    if(contTarefasConcluidas[2] > 0){
        printf("%d", contEsperaTotal[2]/contTarefasConcluidas[2]);
    }
    else{
        printf("Null");
    }
    exibeTexto(48, 12, "Importante: ", WHITE); 
    if(contTarefasConcluidas[1] > 0){
        printf("%.2f", (float)contEsperaTotal[1]/contTarefasConcluidas[1]);
    }
    else{
        printf("Null");
    }
    exibeTexto(48, 13, "Melhoria: ", WHITE); 
    if(contTarefasConcluidas[0] > 0){
        printf("%.2f", (float)contEsperaTotal[0]/contTarefasConcluidas[0]);
    }
    else{
        printf("Null");
    }

        //TAREFAS NAO CONCLUIDAS
    
    int tarefasNaoConcluidas[3];
    inicializarContador(tarefasNaoConcluidas);
    _Atividade auxAtividade;
    while(!VaziaAtividade(gerenciarAtividades)){
        auxAtividade = retirarAtividade(gerenciarAtividades);
        switch(auxAtividade.prioridade){
            case 1:{
                tarefasNaoConcluidas[0]++;
                break;
            }
            case 2:{
                tarefasNaoConcluidas[1]++;
                break;
            }
            case 3:{
                tarefasNaoConcluidas[2]++;
                break;
            }
        }
    }


    _AtividadeDev auxAtividadeDev;
    while(!vaziaAtividadeDev(atividadeDev)){
        auxAtividadeDev = retirarAtividadeDev(atividadeDev);
        switch(auxAtividadeDev.atividade.prioridade){
            case 1:{
                tarefasNaoConcluidas[0]++;
                break;
            }
            case 2:{
                tarefasNaoConcluidas[1]++;
                break;
            }
            case 3:{
                tarefasNaoConcluidas[2]++;
                break;
            }
        }
    }
    exibeTexto(73, 10, "<-Tarefas Nao Concluidas->", RED);
    exibeTexto(74, 11, "Critico: ", WHITE); printf("%d", tarefasNaoConcluidas[2]);
    exibeTexto(74, 12, "Importante: ", WHITE); printf("%d", tarefasNaoConcluidas[1]);
    exibeTexto(74, 13, "Melhoria: ", WHITE); printf("%d", tarefasNaoConcluidas[0]);
    getch();
}

int sorteioNumero(int tempo){
    if(tempo <= 50){
        return rand() % (tempo / 3) + 1;
    }
    else if(tempo <= 100){
        return rand() % (tempo / 5) + 1;
    }
    else if(tempo <= 200){
        return rand() % (tempo / 10) + 1;
    }
    else{
        return rand() % (tempo / 20) + 1;
    }
}

void exibirInformacoesTela(_FilaAtividade gerenciarAtividades, _FilaDev desenvolvedores, _FilaAtividadeDev atividadeDev, int tempo){
    gotoxy(21, 23);
    textcolor(YELLOW);
    printf("Dev's dispo: %d", verificarDesenvolvedoresDisponiveis(desenvolvedores));
    gotoxy(38, 23);
    printf("Resolvendo: %d", atividadeDev.qtd);
    gotoxy(54,23);
    printf("Aguardando: %d", gerenciarAtividades.qtd);
    exibeTexto(93, 23, "ate: ", YELLOW); printf("%d", tempo);
}

void ocupaDevComAtividade(_FilaAtividade &gerenciarAtividades, _FilaDev &desenvolvedores, _FilaAtividadeDev &atividadeDev, int tempo, int &yR){
    _AtividadeDev aux;
    aux.dev = retirarDev(desenvolvedores);
    aux.atividade = retirarAtividade(gerenciarAtividades);
    inserirAtividadeDev(atividadeDev, aux.dev, aux.atividade, tempo);
    mensagemInformacoesOcupacaoDev(aux, yR, tempo);
}

void mensagemInformacoesOcupacaoDev(_AtividadeDev aux, int &yR, int tempo){
    switch(aux.atividade.prioridade){
        case 1:{
            exibirNoDisplayErroVermelho(yR, "Dev ocupou com atividade Melhoria Conclusao em: "); 
            break;
        }
        case 2:{
            exibirNoDisplayErroVermelho(yR, "Dev ocupou com atividade Import. Conclusao em: "); 
            break;
        }
        case 3:{
            exibirNoDisplayErroVermelho(yR, "Dev ocupou com atividade Critica Conclusao em: "); 
            break;
        }
    }
    printf("%d", aux.atividade.tempoConclusao + tempo);
}

void incrementoTarefasConcluidas(_AtividadeDev aux, int contTarefasConcluidas[3]){
    switch(aux.atividade.prioridade){
        case 1:{
            contTarefasConcluidas[0]++;
            break;
        }
        case 2:{
            contTarefasConcluidas[1]++;
            break;
        }
        case 3:{
            contTarefasConcluidas[2]++;
            break;
        }
    }
}

void somarEsperaTotal(int contadorGeral, _AtividadeDev aux, int contEsperaTotal[3]){
    switch(aux.atividade.prioridade){
        case 1:{
            contEsperaTotal[0] += (contadorGeral - aux.atividade.tempoEspera);
        }
        case 2:{
            contEsperaTotal[1] += (contadorGeral - aux.atividade.tempoEspera);
        }
        case 3:{
            contEsperaTotal[2] += (contadorGeral - aux.atividade.tempoEspera);
        }
    }
}