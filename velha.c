#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int jogada_usuario(int linha, int coluna, char jogada);

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
int menu();

/*4. void escolha_simb(char *jog1, char *jog2 ): esta função define via entrada do usuário quem
é o jogador ‘X’ e quem é o jogador ‘O’.*/
void escolha_simb(char *jogador1, char *jogador2);

//5. void inicializa_velha( ): esta função inicializa a matriz do jogo da velha com vazio.
void inicializa_velha();

/*6. int verifica_ganhador(char jog): esta função retorna 1 se o jogador ganhou e zero caso
contrário. O parâmetro jog conterá ‘X’ ou ‘O’.*/
int verifica_ganhador(char jogada);

//corpo do jogo
char corpo[3][3];

void main() {
    inicializa_velha();
}

/*1. int jogada_usuario(int lin, int col, char jog): esta função preenche a posição informada pelos
parâmetros lin (linha) e col (coluna) com ‘X’ ou ‘O’ que são passados para a função através de
parâmetro jog. A função retorna um dos seguintes valores:
0 – se a jogada é válida
1 – se a posição informada é inválida
2 – se a posição informada já está preenchida*/
int jogada_usuario(int linha, int coluna, char jogada) {
    if ((jogada == 'X') || (jogada == 'O')) 
        if ((linha <= 3)&&(coluna <= 3))
            if (corpo[linha][coluna] == ' ')
                corpo[linha][coluna] = jogada;
}

void jogada_computador(char jogada, int nivel);

int menu();

void escolha_simb(char *jogador1, char *jogador2);

void inicializa_velha(){
    int i, j;
    for (i = 0; i < 3; i++)
        for (j = 0; j <3; j++)
            corpo[i][j] = ' ';
}

int verifica_ganhador(char jogada);