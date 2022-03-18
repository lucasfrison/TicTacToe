#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

int jogada_usuario(int linha, int coluna, char jogada);

void jogada_computador(char jogada, int nivel);

int menu();

void escolha_simb(char *jogador1, char *jogador2);

void inicializa_velha();

int verifica_ganhador(char jogada);

void tabuleiro();

int scanint();

char confirmar();

void basico(char jogada);

void intermediario(char jogada);

void avancado(char jogada);

//corpo do jogo
char corpo[3][3];

void main() {
    char jogador1, jogador2, jogada;
    int 
        vez = 1,  atual = 0, linha, coluna, valida, fim, vit1 = 0, 
        vit2 = 0, vitcpu = 0, vit11 = 0, op, nivel;

    do {
        valida = 0;
        fim = 0;
        vez = atual == 1 ? 2 : 1;
        inicializa_velha();
        system("clear");
        op = menu();
        escolha_simb(&jogador1, &jogador2);
        switch (op) {
            case 1:
                system("clear");
                printf("Escolha o nivel de dificuldade do PC:\n\n");
                printf("1. Basico.\n");
                printf("2. Intermediario.\n");
                printf("3. Avancado.\n");
                nivel = scanint();
                for (;;) {  
                    system("clear");
                    printf("Vitorias Jogador 1 : %d\n", vit11);
                    printf("Vitorias Computador: %d\n\n", vitcpu);
                    tabuleiro();  
                    printf("\nJogador %d: Digite a linha e a coluna para jogar (L C):\n", vez);
                    if (vez == 1) { 
                        jogada = jogador1;
                        valida = jogada_usuario(linha, coluna, jogada);
                    }    
                    else {
                        system("clear");
                        tabuleiro();
                        jogada = jogador2;
                        printf("\nComputador jogando...\n");
                        sleep(1);
                        jogada_computador(jogada, nivel);
                        valida = 0;
                    }    
                    system("clear"); 
                    tabuleiro();  
                    if (valida > 0) {
                        printf("\nJOGADA INVALIDA!\n");
                        sleep(1);
                    }    
                    else {
                        fim++;
                        if (vez == 1) {
                            vez = 2;
                            atual = 1;
                        }
                        else {
                            vez = 1;
                            atual = 2;
                        }    
                    }        
                    if (verifica_ganhador(jogada) == 1) {
                        system("clear");
                        tabuleiro();
                        printf("\nO Jogador %d ganhou! Parabens!\n", atual);
                        vit11 = atual == 1 ? ++vit11 : vit11;
                        vitcpu = atual == 2 ? ++vitcpu : vitcpu;
                        break;
                    } else if (fim == 9) {
                        printf("\nDeu Velha!\n");
                        break;
                    }    
                }     
                break;
            case 2:
                for (;;) {  
                    system("clear");
                    printf("Vitorias Jogador 1: %d\n", vit1);
                    printf("Vitorias Jogador 2: %d\n\n", vit2);
                    tabuleiro();  
                    printf("\nJogador %d: Digite a linha e a coluna para jogar (L C):\n", vez);
                    if (vez == 1) jogada = jogador1;
                    else jogada = jogador2;
                    valida = jogada_usuario(linha, coluna, jogada);
                    system("clear"); 
                    tabuleiro();  
                    if (valida > 0) 
                    {
                        printf("\nJOGADA INVALIDA!\n");
                        sleep(1);
                    }    
                    else {
                        fim++;
                        if (vez == 1) {
                            vez = 2;
                            atual = 1;
                        }
                        else {
                            vez = 1;
                            atual = 2;
                        }    
                    }        
                    if (verifica_ganhador(jogada) == 1) {
                        system("clear");
                        tabuleiro();
                        printf("\nO Jogador %d ganhou! Parabens!\n", atual);
                        vit1 = atual == 1 ? ++vit1 : vit1;
                        vit2 = atual == 2 ? ++vit2 : vit2;
                        break;
                    } else if (fim == 9) {
                        printf("\nDeu Velha!\n");
                        break;
                    }

                }             
        }    
    } while (confirmar() != 'N');
}       
           
/*1. int jogada_usuario(int lin, int col, char jog): esta função preenche a posição informada pelos
parâmetros lin (linha) e col (coluna) com ‘X’ ou ‘O’ que são passados para a função através de
parâmetro jog. A função retorna um dos seguintes valores:
0 – se a jogada é válida
1 – se a posição informada é inválida
2 – se a posição informada já está preenchida*/
//PRONTO

int jogada_usuario(int linha, int coluna, char jogada) {
    char str;
    
    linha  = scanint();
    coluna = scanint();
    if ((linha <= 3)&&(coluna <= 3))
        if (corpo[linha-1][coluna-1] == ' ') {
                corpo[linha-1][coluna-1] = jogada;
                return 0;
        } else return 2;
    else return 1;       
}

/*2. void jogada_computador(char jog, int nivel): esta função realiza a jogada do computador. O
parâmetro jog define se o computador é ‘X’ ou ‘O’ e o parâmetro nível define se a jogada do
computador é de nível básico, intermediário ou avançado. Você deve criar uma função para
jogada nível básico do computador; outra função para a jogada nível intermediário do
computador; e outra função para a jogada nível avançado do computador. Estas funções
deverão ser chamadas dentro desta função jogada_computador.*/
void jogada_computador(char jogada, int nivel) {
    switch (nivel)
    {
    case 1:
        basico(jogada);
        break;
    
    default:
        break;
    } 
}

/*3. int menu( ): esta função retorna 1 se o usuário quer jogar contra o computador ou 2 caso o
usuário queira jogar contra outro usuário. Caso o usuário queira jogar contra o computador ele
também deve escolher o nível da jogada do computador: básico, intermediário ou avançado.*/
//PRONTO
int menu() {
    int escolha = 0;
    while ((escolha > 2)||(escolha < 1)) {
        printf("Bem vindo(a)! Escolha o modo de jogo.\n");
        printf("1. Jogar contra o computador.\n");
        printf("2. Jogar contra outro jogador.\n");
        escolha = scanint();
        system("clear");
    }    
    return escolha;
}

/*4. void escolha_simb(char *jog1, char *jog2 ): esta função define via entrada do usuário quem
é o jogador ‘X’ e quem é o jogador ‘O’.*/
//PRONTO
void escolha_simb(char *jogador1, char *jogador2) {
    int escolha = -1;
    char simbolo[3] = "XO";
    while ((escolha != 0) && (escolha != 1)) {
        printf("Escolha os simbolos: J1 ficara com o escolhido, J2 ou PC ficara com o outro:\n");
        printf("1. X.    2. O\n");
        escolha = scanint();
        escolha--;
        *jogador1 = simbolo[escolha];
        if (*jogador1 == simbolo[0])
            *jogador2 = simbolo[1];
        else *jogador2 = simbolo[0]; 
        system("clear");
    }
}  

//5. void inicializa_velha( ): esta função inicializa a matriz do jogo da velha com vazio.
//PRONTO
void inicializa_velha(){
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            corpo[i][j] = ' ';
}

/*6. int verifica_ganhador(char jog): esta função retorna 1 se o jogador ganhou e zero caso
contrário. O parâmetro jog conterá ‘X’ ou ‘O’.*/
//PRONTO
int verifica_ganhador(char jogada) {
    int i, venceu;

    venceu = 0;

    if ((corpo[0][0] == jogada) && (corpo[0][0] == corpo[1][1]) && 
    (corpo[1][1] == corpo[2][2])) venceu = 1;

    else if ((corpo[0][2] == jogada) && (corpo[0][2] == corpo[1][1]) && 
    (corpo[1][1] == corpo[2][0])) venceu = 1;

    for (i = 0; i < 3; i++) {
        if ((corpo[i][0] == jogada) && (corpo[i][0] == corpo[i][1]) && 
        (corpo[i][1] == corpo[i][2])) venceu = 1;

        else if ((corpo[0][i] == jogada) && (corpo[0][i] == corpo[1][i]) && 
        (corpo[1][i] == corpo[2][i])) venceu = 1;                
    }

    return venceu;
}

//Formata a matriz
//PRONTO 
void tabuleiro() {
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (j == 2)                   
                if (i != 2) printf("  %c\n-----------------\n", corpo[i][j]);
                else printf("  %c\n", corpo[i][j]);
            else printf("  %c  |", corpo[i][j]);    
}

//Le um char e retorna o valor inteiro
int scanint() {
    char str;
    int val = 0;
    
    scanf(" %c", &str);
    val = atoi(&str);
    return val; 
}

//Menu de confirmacao
char confirmar() {
    const char mensagem[] = "Deseja jogar outra partida? (S/N)";
    char confirm;

    do {
        printf("\n%s\n", mensagem);
        scanf(" %c", &confirm);
        confirm = toupper(confirm);
        system("clear");
    } while ((confirm != 'S') && (confirm != 'N'));
}

//Dificuldade facil do cpu
void basico(char jogada) {
    int i, j, jogou = 0;

    while (jogou == 0)
        for (j = 0; j < 3; j++) { 
            if (j == 0) {
                if ((corpo[i][j] == ' ') && (corpo[i][j+1] != ' ')) {
                    corpo[i][j] = jogada;    
                    jogou++;
                    break;
                }    
            }   
            else if (j == 1) {
                if ((corpo[i][j] == ' ') && (corpo[i][j+1] != ' ')) {
                    corpo[i][j] = jogada;    
                    jogou++;
                    break;
                }
                else if ((corpo[i][j] == ' ') && (corpo[i][j-1] != ' ')) {
                    corpo[i][j] = jogada;    
                    jogou++;
                    break;
                }  
            }
            else {
                if ((corpo[i][j] == ' ') && (corpo[i][j-1] != ' ')) {
                    corpo[i][j] = jogada;    
                    jogou++;
                    break;
                }  
            }    
        }    
}

//Dificuldade media do cpu
void intermediario(char jogada) {
    int i;
}

//Dificuldade avancada do cpu
void avancado(char jogada) {
    int i;
}
