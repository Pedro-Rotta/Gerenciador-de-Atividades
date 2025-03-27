//DECLARACOES DOS METODOS
void auxilioPosicoes();
void retangulo(int xI, int xF, int yI, int yF, int cor);
void exibeTexto(int x, int y, char txt[], int cor);
void linhaHorizontal(int xI, int xF, int y, int cor);
void linhaHorizontalComLaterais(int xI, int xF, int y, int cor);
void linhaVertical(int x, int yI, int yF, int cor);
void linhaVerticalComExtremidades(int x, int yI, int yF, int cor);
void cantoSuperiorEsquerdo(int x, int y, int cor);
void cantoSuperiorDireito(int x, int y, int cor);
void cantoInferiorEsquerdo(int x, int y, int cor);
void cantoInferiorDireito(int x, int y, int cor);
void repetirCaracterHorizontal(int xI, int xF, int y, char caracter, int cor);
void repetirCaracterVertical(int x, int yI, int yF, char caracter, int cor);
void opcoesMenu(int qntOpcoes, int x, int y, char tit[][26], int cor);
void opcoesMenuEspacado(int qntOpcoes, int x, int y, char tit[][26], int cor);
void clearArea(int xI, int xF, int yI, int yF);
void ligacao4Pontos(int x, int y, int cor);
void pintarArea(int xI, int xF, int yI, int yF, int cor);
void prateleiraVertical(int xI, int xF, int yI, int yF, int espacamento, int cor);
void preencherprateleiraVertical(int x, int yI, int yF, int espacamento, char preenchimento[][100], int cor);
void preencherprateleiraHorizontal(int xI, int xF, int y, int espacamento, char preenchimento[][100], int cor);


void auxilioPosicoes(){
    for (int x = 1; x <= 100;x++) {
        if (x < 10) {
            char aux[] = {x + '0', '\0'};
            exibeTexto(x, 1, aux, (x % 10 == 0) ? RED : WHITE);
        } else {
            char aux[] = {(x % 10) + '0', '\0'};
            exibeTexto(x, 2, aux, (x % 10 == 0) ? RED : WHITE);

            aux[0] = ((x / 10) % 10) + '0';
            exibeTexto(x, 1, aux, (x % 10 == 0) ? RED : WHITE);
        }
    }
    for (int y = 2; y <= 30; y++) {
        char aux[] = {((y / 10) % 10) + '0', (y % 10) + '0', '\0'};
        if (y < 10) {
            aux[0] = aux[1];
            aux[1] = '\0';
        }
        exibeTexto(1, y, aux, (y % 10 == 0) ? RED : WHITE);
    }
    for (int y = 10; y <= 30; y = y + 10) {
        for (int x = 10; x <= 100; x = x + 10) {
            exibeTexto(x, y, (char*)"+", RED);
        }
    }
    gotoxy(1,1);
}

void retangulo(int xI, int xF, int yI, int yF, int cor){
    textcolor(cor);    
    linhaHorizontal(xI, xF, yI, cor);
    linhaHorizontal(xI, xF, yF, cor);
    linhaVertical(xI, yI, yF, cor);
    linhaVertical(xF, yI, yF, cor);
    cantoSuperiorEsquerdo(xI, yI, cor);
    cantoSuperiorDireito(xF, yI, cor);
    cantoInferiorEsquerdo(xI, yF, cor);
    cantoInferiorDireito(xF, yF, cor);
}
void exibeTexto(int x, int y, char txt[], int cor){
    textcolor(cor);
    gotoxy(x, y);
    printf("%s", txt);
    textcolor(WHITE);
}
void linhaHorizontal(int xI, int xF, int y, int cor){
    textcolor(cor);
    while(xI <= xF){
        gotoxy(xI++,y);
        printf("%c", 205);
    }
}
void linhaHorizontalComLaterais(int xI, int xF, int y, int cor){
    textcolor(cor);
    gotoxy(xI++, y);
    printf("%c", 204);
    gotoxy(xF, y);
    printf("%c", 185);
    while(xI < xF){
        gotoxy(xI++,y);
        printf("%c", 205);
    }
}
void linhaVertical(int x, int yI, int yF, int cor){
    textcolor(cor);
    while(yI <= yF){
        gotoxy(x,yI);
        printf("%c", 186);
        yI++;
    }
}
void linhaVerticalComExtremidades(int x, int yI, int yF, int cor){
    textcolor(cor);
    gotoxy(x, yI++);
    printf("%c", 203);
    gotoxy(x, yF);
    printf("%c", 202);
    while(yI < yF){
        gotoxy(x,yI++);
        printf("%c", 186);
    }
}
void cantoSuperiorEsquerdo(int x, int y, int cor){
    textcolor(cor);
    gotoxy(x, y);
    printf("%c", 201);
}
void cantoSuperiorDireito(int x, int y, int cor){
    textcolor(cor);
    gotoxy(x, y);
    printf("%c", 187);
}
void cantoInferiorEsquerdo(int x, int y, int cor){
    textcolor(cor);
    gotoxy(x, y);
    printf("%c", 200);
}
void cantoInferiorDireito(int x, int y, int cor){
    textcolor(cor);
    gotoxy(x, y);
    printf("%c", 188);
}
void repetirCaracterHorizontal(int xI, int xF, int y, char caracter, int cor){
    textcolor(cor);
    while(xI <= xF){
        gotoxy(xI++, y);
        printf("%c", caracter);
    }
}
void repetirCaracterVertical(int x, int yI, int yF, char caracter, int cor){
    textcolor(cor);
    while(yI <= yF){
        gotoxy(x, yI++);
        printf("%c", caracter);
    }
}
void opcoesMenu(int qntOpcoes, int x, int y, char tit[][26], int cor){
    int i = 0;
    textcolor(cor);
    for(int i=0;i <= qntOpcoes;i++, y++){
        if(i == qntOpcoes){
            gotoxy(x, y);
            printf("[ESC] %s", tit[i]);
        }
        else{
            gotoxy(x, y);
            printf("[%c] %s", i+65, tit[i]);
        }
    }
}
void opcoesMenuEspacado(int qntOpcoes, int x, int y, char tit[][26], int cor){
    int i = 0;
    textcolor(cor);
    for(int i=0;i <= qntOpcoes;i++, y+=2){
        if(i == qntOpcoes){
            gotoxy(x, y);
            printf("[ESC] %s", tit[i]);
        }
        else{
            gotoxy(x, y);
            printf("[%c] %s", i+65, tit[i]);
        }
    }
}
void clearArea(int xI, int xF, int yI, int yF){
    while(yI <= yF){
        for(int i = xI; i <= xF;i++){
            gotoxy(i, yI);
            printf(" ");
        }
        yI++;
    }
}
void ligacao4Pontos(int x, int y, int cor){
    textcolor(cor);
    gotoxy(x,y);
    printf("%c", 206);
}
void pintarArea(int xI, int xF, int yI, int yF, int cor){
    textcolor(cor);
    while(yI <= yF){
        for(int i = xI; i <= xF;i++){
            gotoxy(i, yI);
            printf("%c", 177);
        }
        yI++;
    }
}
void prateleiraVertical(int xI, int xF, int yI, int yF, int espacamento, int cor){
    int auxEspacamento = yI;
    retangulo(xI, xF, yI, yF, cor);
    auxEspacamento+=espacamento+1;
    while(auxEspacamento < yF){
        linhaHorizontalComLaterais(xI, xF, auxEspacamento, cor);
        auxEspacamento+=espacamento+1;
    }
}
void prateleiraHorizontal(int xI, int xF, int yI, int yF, int espacamento, int cor){
    int auxEspacamento = xI;
    retangulo(xI, xF, yI, yF, cor);
    auxEspacamento+=espacamento+1;
    while(auxEspacamento < xF){
        linhaVerticalComExtremidades(auxEspacamento, yI, yF, cor);
        auxEspacamento+=espacamento+1;
    }
}
void preencherprateleiraVertical(int x, int yI, int yF, int espacamento, char preenchimento[][100], int cor){
    int i = 0, auxEspacamento = yI+1;
    textcolor(cor);
    while(auxEspacamento <= yF){
        gotoxy(x, auxEspacamento);
        printf("%s", preenchimento[i++]);
        auxEspacamento += espacamento+1;
    }
}
void preencherprateleiraHorizontal(int xI, int xF, int y, int espacamento, char preenchimento[][100], int cor){
    int i = 0, auxEspacamento = xI+1;
    textcolor(cor);
    while(auxEspacamento <= xF){
        gotoxy(auxEspacamento, y);
        printf("%s", preenchimento[i++]);
        auxEspacamento += espacamento+1;
    }
}
