#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int jogada_usuario(int linha, int coluna, char jogada);

void jogada_computador(char jogada, int nivel);

int menu();

void escolha_simb(char *jogador1, char *jogador2);

void inicializa_velha();

int verifica_ganhador(char jogada);

void tabuleiro();

//corpo do jogo
char corpo[3][3];

void main() {
    char jogador1, jogador2;
    int vez, anterior = 1, linha, coluna, i;

        inicializa_velha();
        menu();
        escolha_simb(&jogador1, &jogador2);
        
        for (i = 0; i < 9; i++){
            tabuleiro();
            vez = anterior;
            printf("\nJogador %d: Digite a linha e a coluna para jogar (L C):\n", vez);
            if (vez == 1) jogada_usuario(linha, coluna, jogador1);
            else jogada_usuario(linha, coluna, jogador2);
            if (anterior == 1) anterior = 2;
            else anterior = 1;
            system("clear");
        }
}

/*1. int jogada_usuario(int lin, int col, char jog): esta função preenche a posição informada pelos
parâmetros lin (linha) e col (coluna) com ‘X’ ou ‘O’ que são passados para a função através de
parâmetro jog. A função retorna um dos seguintes valores:
0 – se a jogada é válida
1 – se a posição informada é inválida
2 – se a posição informada já está preenchida*/
int jogada_usuario(int linha, int coluna, char jogada) {
    scanf("%d %d", &linha, &coluna);
    if ((jogada == 'X') || (jogada == 'O')) 
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
void jogada_computador(char jogada, int nivel);

/*3. int menu( ): esta função retorna 1 se o usuário quer jogar contra o computador ou 2 caso o
usuário queira jogar contra outro usuário. Caso o usuário queira jogar contra o computador ele
também deve escolher o nível da jogada do computador: básico, intermediário ou avançado.*/
int menu() {
    int escolha = 0;
    while ((escolha > 2)||(escolha < 1)) {
        printf("Bem vindo(a)! Escolha o modo de jogo.\n");
        printf("1. Jogar contra o computador.\n");
        printf("2. Jogar contra outro jogador.\n");
        scanf("%d", &escolha);
        system("clear");
    }    
    return escolha;
}

/*4. void escolha_simb(char *jog1, char *jog2 ): esta função define via entrada do usuário quem
é o jogador ‘X’ e quem é o jogador ‘O’.*/
//CHAMAR NA MAIN
void escolha_simb(char *jogador1, char *jogador2) {
    int escolha;
    char simbolo[3] = "XO";
    printf("Jogador 1: Escolha seu simbolo:\n");
    printf("1. X.    2. O\n");
    scanf("%d", &escolha);
    escolha -= 1;
    *jogador1 = simbolo[escolha];
    if (*jogador1 == simbolo[0])
        *jogador2 = simbolo[1];
    else *jogador2 = simbolo[0]; 
    system("clear");
}  

//PRONTO  5. void inicializa_velha( ): esta função inicializa a matriz do jogo da velha com vazio.
void inicializa_velha(){
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            corpo[i][j] = ' ';
}

/*6. int verifica_ganhador(char jog): esta função retorna 1 se o jogador ganhou e zero caso
contrário. O parâmetro jog conterá ‘X’ ou ‘O’.*/
int verifica_ganhador(char jogada) {

}

//PRONTO Formata a matriz 
void tabuleiro() {
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            if (j == 2)                   
                if (i != 2) printf("  %c\n-----------------\n", corpo[i][j]);
                else printf("  %c\n", corpo[i][j]);
            else printf("  %c  |", corpo[i][j]);    
}
