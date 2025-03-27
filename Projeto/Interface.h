// Declaração das funções
void interfaceDoSistema();
void estruturaLadoEsquerdo();
void estruturaLadoDireito();
void preencherLadoDireito();
void preencherLadoEsquerdo();
void estruturaErroInferior();
void interfaceDoSistema(){
    retangulo(20, 100, 9, 21, MAGENTA);
    exibeTexto(52, 6, (char*)"GERENCIADOR DE TAREFAS", YELLOW);
    exibeTexto(25, 4, (char*)"AUTORES ", RED);
    exibeTexto(23, 6, (char*)"PEDRO ROTTA", GREEN);
    exibeTexto(23, 7, (char*)"BRUNO GOMES", YELLOW);
    exibeTexto(23, 8, (char*)"LEANDRO", BLUE);
    exibeTexto(90, 4, (char*)"AUTORES ", RED);
    exibeTexto(88, 6, (char*)"PEDRO ROTTA", BLUE);
    exibeTexto(88, 7, (char*)"BRUNO GOMES", YELLOW);
    exibeTexto(88, 8, (char*)"LEANDRO", GREEN);
    
    //ERRO INFERIOR
    estruturaErroInferior();

    //PARTE DE CIMA
    for(int y = 6, xi = 17, xf = 18;y > 2;y--){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    }
    
    
    for(int y = 6, xi = 102, xf = 103;y > 2;y--){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    } 
    linhaHorizontalComLaterais(17, 103, 3, CYAN);   

    //LADO DIREITO
    estruturaLadoDireito();
    preencherLadoDireito();

    //LADO ESQUERDO
    estruturaLadoEsquerdo();
    preencherLadoEsquerdo();
    linhaVerticalComExtremidades(48, 24, 30, GREEN);

    linhaVerticalComExtremidades(36, 22, 24, GREEN);
}

void estruturaLadoEsquerdo(){
    //PARTE SUPERIOR
    linhaHorizontalComLaterais(18, 19, 9, CYAN);
    linhaHorizontalComLaterais(17, 18, 8, CYAN);
    linhaHorizontalComLaterais(14, 17, 7, CYAN);

    //METADE DE CIMA DA PARTE CENTRAL
    for(int y = 8, xi = 13, xf = 14;y < 15; y++, xi--, xf--){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    }

    //METADE DE BAIXO DA PARTE CENTRAL
    for(int y = 15, xi = 6, xf = 7;y < 23; y++, xi++, xf++){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    }

    //PARTE INFERIOR
    linhaHorizontalComLaterais(14, 17, 23, CYAN);
    linhaHorizontalComLaterais(17, 18, 22, CYAN);
    linhaHorizontalComLaterais(18, 19, 21, CYAN);

    //COMPLETA A LATERAL DO LADO ESQUERDO COM OS CARACTERES 204 E 185
    repetirCaracterVertical(18, 10, 20, 204, CYAN);   
    repetirCaracterVertical(19, 10, 20, 185, CYAN);
}

void estruturaLadoDireito(){
    //PARTE SUPERIOR
    linhaHorizontalComLaterais(101, 102, 9, CYAN);
    linhaHorizontalComLaterais(102, 103, 8, CYAN);
    linhaHorizontalComLaterais(103, 106, 7, CYAN);

    //METADE DE CIMA DA PARTE CENTRAL
    for(int y = 8, xi = 106, xf = 107;y < 16;y++, xi++, xf++){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    }

    //METADE DE BAIXO DA PARTE CENTRAL
    for(int y = 16, xi = 112, xf = 113;y < 22;y++, xi--, xf--){
        linhaHorizontalComLaterais(xi, xf, y, CYAN);
    }

    //PARTE INFERIOR
    linhaHorizontalComLaterais(103, 106, 23, CYAN);
    linhaHorizontalComLaterais(101, 102, 21, CYAN);
    linhaHorizontalComLaterais(106, 107, 22, CYAN);
    linhaHorizontalComLaterais(102, 103, 22, CYAN);

    //COMPLETA A LATERAL DO LADO DIREITO COM OS CARACTERES 204 E 185
    repetirCaracterVertical(101, 10, 20, 204, CYAN);  
    repetirCaracterVertical(102, 10, 20, 185, CYAN);
}

void preencherLadoDireito(){ //PREENCHE A ASA DIREITA COM "#" EM VERMELHO
    repetirCaracterHorizontal(104, 105, 8, '#', RED);
    for(int y=9, xi = 103, xf = 106; y < 16; y++, xf++){
        repetirCaracterHorizontal(xi, xf, y, '#', RED);
    }
    for(int y=16, xi = 103, xf = 111; y < 22; y++, xf--){
        repetirCaracterHorizontal(xi, xf, y, '#', RED);
    }
    repetirCaracterHorizontal(104, 105, 22, '#', RED);
}

void preencherLadoEsquerdo(){ //PREENCHE A ASA ESQUERDA COM "#" EM VERMELHO
    repetirCaracterHorizontal(15, 16, 8, '#', RED);
    for(int y=9, xi = 14, xf = 17; y < 16; y++, xi--){
        repetirCaracterHorizontal(xi, xf, y, '#', RED);
    }
    for(int y=16, xi = 9, xf = 17; y < 22; y++, xi++){
        repetirCaracterHorizontal(xi, xf, y, '#', RED);
    }
    repetirCaracterHorizontal(15, 16, 22, '#', RED);
}

void estruturaErroInferior(){
    retangulo(19, 101, 22, 30, GREEN);

    gotoxy(21,21);
    textcolor(MAGENTA);
    printf("%c", 203);
    gotoxy(21,22);
    textcolor(GREEN);
    printf("%c", 202);

    gotoxy(99,21);
    textcolor(MAGENTA);
    printf("%c", 203);
    gotoxy(99,22);
    textcolor(GREEN);
    printf("%c", 202);

    gotoxy(50,21);
    textcolor(MAGENTA);
    printf("%c", 203);
    gotoxy(50,22);
    textcolor(GREEN);
    printf("%c", 202);

    gotoxy(70,21);
    textcolor(MAGENTA);
    printf("%c", 203);
    gotoxy(70,22);
    textcolor(GREEN);
    printf("%c", 202);

    //exibeTexto(53, 23, "RETORNO SISTEMA", RED);

    linhaHorizontalComLaterais(19, 101, 24, GREEN);
    linhaHorizontal(20, 100, 24, GREEN);

    
    gotoxy(51,22);
    textcolor(GREEN);
    printf("%c", 203);
    gotoxy(51,24);
    printf("%c", 202);

    gotoxy(51, 23);
    printf("%c", 186);

    gotoxy(69,22);

    printf("%c", 203);
    gotoxy(69,24);
    printf("%c", 202);

    gotoxy(69, 23);
    printf("%c", 186);
}

void limparDisplayPrincipal(){
    clearArea(42, 99, 10, 20);
}

void limparDisplayErroVerde(){
    clearArea(21,47,25,29);
}
void limparDisplayErroVermelho(){
    clearArea(49,100,25,29);
}

void exibirNoDisplayErroVerde(int &y, char txt[]){
    if(y == 30){
        limparDisplayErroVerde();
        y = 25;
    }
    exibeTexto(21, y, txt, GREEN);
    y++;
}

void exibirNoDisplayErroVermelho(int &y, char txt[]){
    if(y == 30){
        limparDisplayErroVermelho();
        y = 25;
    }
    exibeTexto(50, y, txt, RED);
    y++;
}