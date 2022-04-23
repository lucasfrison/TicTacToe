#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

typedef struct Velha
{
    int Partida; /*número da partida (Ex: primeira(1), segunda(2), terceira(3), ….,
    partida)*/
    char JogVelha[3][3]; // Tabuleiro do jogo. Armazenará as jogadas
    char resultado; // Resultado da Partida: X, 0 ou V(equivale a Velha - empate)
} partida;

//FUNCOES TRABALHO 1
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
void inicio_jogada(char mensagem[2], char mensagem2[2], int vit, int vit2);
void valida_jogada(int valida, int *vez, int *atual, int *fim);
int resultado(char jogada, int *vit1, int *vit2, int atual, int modo, int fim); 

//FUNCOES NOVAS, TRABALHO 2
void gerar_txt(char *nome1, char *nome2, char simbolo1, char simbolo2);
int gerar_bin(char *nome_arquivo, partida *Partida); //PENDENTE
partida ler_bin(char *nome_arquivo, int num_partida); //PENDENTE
void imprime_campeonato(); //PENDENTE
void limpa_buffer();
void ler_nome(char *nome, char mensagem);

//corpo do jogo
char corpo[3][3];

void main() {
    char jogador1, jogador2, jogada, nome1[100], nome2[100];
    int vez = 1,  atual = 0, linha, coluna, valida, fim, vit1 = 0, 
        vit2 = 0, vitcpu = 0, vit11 = 0, op, nivel, result, i, j;
    partida jogo, *jogoptr = &jogo;  
    FILE *bin = fopen("campeonato.bin", "wb");

    jogo.Partida = 0;

    do {
        valida = 0;
        fim = 0;
        vez = atual == 1 ? 2 : 1;
        inicializa_velha();
        system("clear");
        op = menu();
        
        switch (op) {
            case 1:
                do {
                    if ((vit11 == 0) && (vitcpu == 0))
                       escolha_simb(&jogador1, &jogador2);  
                    system("clear");
                    printf("Escolha o nivel de dificuldade do PC:\n\n");
                    printf("1. Basico.\n");
                    printf("2. Intermediario.\n");
                    printf("3. Avancado.\n");
                    nivel = scanint();
                } while ((nivel > 3) || (nivel < 1));
                
                for (;;) {  
                    inicio_jogada("J", "PC", vit11, vitcpu);  
                    if (vez == 1) { 
                        printf("\nJogador %d: Digite a linha e a coluna para jogar (L C):\n", vez);
                        jogada = jogador1;
                        valida = jogada_usuario(linha, coluna, jogada);
                    }    
                    else {
                        jogada = jogador2;
                        printf("\nComputador jogando...\n");
                        sleep(1);
                        jogada_computador(jogada, nivel);
                        valida = 0;
                    }    
                    inicio_jogada("J", "PC", vit11, vitcpu); 
                    valida_jogada(valida, &vez, &atual, &fim);       
                    result = resultado(jogada, &vit11, &vitcpu, atual, 1, fim);
                    if ((result == 1) || (result == 2)) {
                        sleep(2);
                        break;  
                    }         
                }
                inicio_jogada("J", "PC", vit11, vitcpu);     
                break;
            
            case 2:
                
                if ((vit1 == 0) && (vit2 == 0)) {
                    escolha_simb(&jogador1, &jogador2);
                    gerar_txt(nome1, nome2, jogador1, jogador2);
                }    

                for (;;) {   
                    inicio_jogada("J1", "J2", vit1, vit2);  
                    printf("\nJogador %d: Digite a linha e a coluna para jogar (L C):\n", vez);
                    if (vez == 1) jogada = jogador1;
                    else jogada = jogador2;
                    valida = jogada_usuario(linha, coluna, jogada);
                    inicio_jogada("J1", "J2", vit1, vit2); 
                    valida_jogada(valida, &vez, &atual, &fim);
                    result = resultado(jogada, &vit1, &vit2, atual, 2, fim);
                    if ((result == 1) || (result == 2)) {
                        sleep(2);
                        break;
                    }    
                }    
                inicio_jogada("J1", "J2", vit1, vit2);
                jogo.Partida++; 
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++)
                        jogo.JogVelha[i][j] = corpo[i][j];
                }
                jogo.resultado = result == 2 ? 'V' : jogada;
                gerar_bin("campeonato.txt", jogoptr);            
        } 
    } while (confirmar() != 'N');
    system("clear");
    printf("RESULTADO\n");
    printf("---------\n");
    if ((vit11 != 0) || (vitcpu != 0)) printf("J  %d x %d  PC\n\n", vit11, vitcpu);
    if ((vit1 != 0) || (vit2 != 0)) printf("J1  %d x %d  J2\n\n", vit1, vit2);
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
    
        case 2:
            intermediario(jogada);
            break;
        case 3:
            avancado(jogada);    
    } 
}

/*3. int menu( ): esta função retorna 1 se o usuário quer jogar contra o computador ou 2 caso o
usuário queira jogar contra outro usuário. Caso o usuário queira jogar contra o computador ele
também deve escolher o nível da jogada do computador: básico, intermediário ou avançado.*/
//PRONTO
int menu() {
    int escolha = 0;
    while ((escolha > 2)||(escolha < 1)) {
        printf("Bem vindo(a)! Escolha o modo de jogo.\n\n");
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
        printf("Escolha os simbolos: J1 ficara com o escolhido, J2 ou PC ficara com o outro:\n\n");
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
    int val;
    
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
    int i, j;

    do {
        srand(time(NULL));
        i = rand() % 3;
        srand(time(NULL));
        j = rand() % 3;
    } while (corpo[i][j] != ' ');
    corpo[i][j] = jogada;

}        
         
//Dificuldade intermediaria do cpu
void intermediario(char jogada) {
    int i, j, k = 2, l[3], c[3], d[2], maiorl, maiorc, maiord, escolha = -1, total = 0;

    if (corpo[1][1] == ' ') corpo[1][1] = jogada;
    else 
    {
        for (i = 0; i < 3; i++) {
            l[i] = 0;
            c[i] = 0;
        }

        for (i = 0; i < 2; i++) 
            d[i] = 0;

        for (i = 0; i < 3; i++) {
            if (corpo[i][i] != ' ') d[0]++;
    
            if (corpo[i][k] != ' ') d[1]++;

            for (j = 0; j < 3; j++) {
                if (corpo[i][j] != ' ') {
                    total++;
                    l[i]++; 
                }
                if (corpo[j][i] != ' ') c[i]++;  
            } 
            k--;
        }

        if (total == 8) {
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)  
                    if (corpo[i][j] == ' ') corpo[i][j] = jogada;
        }        
        else {
            maiorl = 0;
            maiorc = 0;
            maiord = 0;
            for (i = 0; i < 3; i++) {
                if (l[i] == 1) maiorl = i;
                if (c[i] == 1) maiorc = i;
            }
            for (i = 0; i < 3; i++) {
                if (l[i] == 2) maiorl = i;
                if (c[i] == 2) maiorc = i;
            }

            for (i = 0; i < 2; i++) {
                if (d[i] == 1) maiord = i;
            }

            for (i = 0; i < 2; i++) {
                if (d[i] == 2) maiord = i;
            }

            if ((l[maiorl] == 2)&&(c[maiorc] == 2)&&(d[maiord] == 2)) {
                srand(time(NULL));
                escolha = (rand() % 3) + 1;
            }    
            else if (l[maiorl] == 2) escolha = 1; 
            else if (c[maiorc] == 2) escolha = 2; 
            else if (d[maiord] == 2) escolha = 3; 
            else if ((l[maiorl] == 1)&&(c[maiorc] == 1)&&(d[maiord] == 1)) {
                srand(time(NULL));
                escolha = (rand() % 3) + 1;
            }   
            else if (l[maiorl] == 1) escolha = 1; 
            else if (c[maiorc] == 1) escolha = 2; 
            else if (d[maiord] == 1) escolha = 3;

            if (escolha == 1) {
                for (i = 0; i < 3; i++) {    
                    if (corpo[maiorl][i] == ' ') {
                        corpo[maiorl][i] = jogada;
                        break;
                    }    
                }
            }    
            else if (escolha == 2){ 
                for (i = 0; i < 3; i++) {    
                    if (corpo[i][maiorc] == ' ') {
                        corpo[i][maiorc] = jogada;
                        break;
                    }    
                } 
            }
            else if (escolha == 3) { 
                if (maiord == 0) {
                    for (i = 0; i < 3; i++) {    
                        if (corpo[i][i] == ' ') {
                            corpo[i][i] = jogada;
                            break;
                        }    
                    } 
                }    
                else {
                    for (i = 0; i < 3; i++) {    
                        if (corpo[i][k] == ' ') {
                            corpo[i][k] = jogada;
                            break;
                        }
                        k--;        
                     }
                } 
            } 
        }             
    }    
}

//Dificuldade avancada do cpu
void avancado(char jogada) {
    int i, j, k = 2, l[3], c[3], d[2], ganhal[3], ganhac[3], 
    ganhad[2], maiorl, maiorc, maiord, escolha = -1, total = 0;

    if (corpo[1][1] == ' ') corpo[1][1] = jogada;
    else 
    {
        for (i = 0; i < 3; i++) {
            l[i] = 0;
            c[i] = 0;
            ganhal[i] = 0;
            ganhac[i] = 0;
        }

        for (i = 0; i < 2; i++) {
            ganhad[i] = 0;
            d[i] = 0;
        }    

        for (i = 0; i < 3; i++) {
            if (corpo[i][i] != ' ') 
                if (corpo[i][i] == jogada) ganhad[0]++;
                else d[0]++;
    
            if (corpo[i][k] != ' ')    
                if (corpo[i][k] == jogada) ganhad[1]++;
                else d[1]++;

            for (j = 0; j < 3; j++) {
                if (corpo[i][j] != ' ') { 
                    total++;
                    if (corpo[i][j] == jogada) ganhal[i]++;
                    else l[i]++;   
                }
                if (corpo[j][i] != ' ')   
                    if (corpo[j][i] == jogada) ganhac[i]++;
                    else c[i]++;                  
            } 
            k--; 
        }   

        if (total == 8) {
            for (i = 0; i < 3; i++)
                for (j = 0; j < 3; j++)  
                    if (corpo[i][j] == ' ') corpo[i][j] = jogada;
        }            
        else {
            maiorl = 0;
            maiorc = 0;

            for (i = 0; i < 3; i++) {
                if ((l[i] == 1) && (ganhal[i] < 2)) 
                    maiorl = i;
                if ((c[i] == 1) && (ganhac[i] < 2))
                    maiorc = i;    
            }       

            for (i = 0; i < 3; i++) {
                if ((l[i] == 2) && (ganhal[i] == 0)) 
                    maiorl = i;
                if ((c[i] == 2) && (ganhac[i] == 0)) 
                    maiorc = i;    
            }      

            for (i = 0; i < 3; i++) {
                if ((ganhal[i] == 2) && (l[i] == 0)) 
                    maiorl = i;
                if ((ganhac[i] == 2) && (c[i] == 0)) 
                    maiorc = i;    
            }    
    
            maiord = 0;

            for (i = 0; i < 2; i++)  
                if ((d[i] == 1) && (ganhad[i] < 2)) 
                    maiord = i;
            for (i = 0; i < 2; i++)       
                if ((d[i] == 2) && (ganhad[i] == 0))
                    maiord = i;
            for (i = 0; i < 2; i++) 
                if ((ganhad[i] == 2) && (d[i] == 0))
                    maiord = i;         

            if (ganhal[maiorl] == 2) escolha = 1;
            else if (ganhac[maiorc] == 2) escolha = 2;
            else if (ganhad[maiord] == 2) escolha = 3;
            else if (((ganhal[maiorl] == 0)&&(l[maiorl] == 2))&&
                    ((ganhac[maiorc] == 0)&&(c[maiorc] == 2))) {
                    srand(time(NULL));
                    escolha = (rand() % 2) + 1;
            }   
            else if ((ganhal[maiorl] == 0)&&(l[maiorl] == 2)) escolha = 1; 
            else if ((ganhac[maiorc] == 0)&&(c[maiorc] == 2)) escolha = 2; 
            else if ((ganhad[maiord] == 0)&&(d[maiord] == 2)) escolha = 3; 
            else if (((ganhal[maiorl] < 2)&&(l[maiorl] == 1))&&
                    ((ganhac[maiorc] < 2)&&(c[maiorc] == 1))&&
                    ((ganhad[maiord] < 2)&&(d[maiord] == 1))) {
                    srand(time(NULL));
                    escolha = (rand() % 3) + 1;
            }   
            else if ((ganhal[maiorl] < 2)&&(l[maiorl] == 1)) escolha = 1; 
            else if ((ganhac[maiorc] < 2)&&(c[maiorc] == 1)) escolha = 2; 
            else if ((ganhad[maiord] < 2)&&(d[maiord] == 1)) escolha = 3; 

            k = 2;   

            if (escolha == 1) {
                for (i = 0; i < 3; i++) {    
                    if (corpo[maiorl][i] == ' ') {
                        corpo[maiorl][i] = jogada;
                        break;
                    }    
                }
            }    
            else if (escolha == 2){ 
                for (i = 0; i < 3; i++) {    
                    if (corpo[i][maiorc] == ' ') {
                        corpo[i][maiorc] = jogada;
                        break;
                    }    
                } 
            }
            else if (escolha == 3) { 
                if (maiord == 0) {
                    for (i = 0; i < 3; i++) {    
                        if (corpo[i][i] == ' ') {
                            corpo[i][i] = jogada;
                            break;
                        }    
                    } 
                }    
                else {
                    for (i = 0; i < 3; i++) {    
                        if (corpo[i][k] == ' ') {
                            corpo[i][k] = jogada;
                            break;
                        }
                        k--;        
                     }
                } 
            } 
        }                     
    }  
}

//imprime cabecalho
void inicio_jogada(char mensagem[2], char mensagem2[2], int vit, int vit2) {
    system("clear");
    printf("Vitorias: %s  %d x %d  %s\n\n", mensagem, vit, vit2, mensagem2);
    tabuleiro();
}

//verifica a validade da jogada
void valida_jogada(int valida, int *vez, int *atual, int *fim) {
    if (valida > 0) {
        if (valida == 2) printf("\nPOSICAO JA PREENCHIDA!\n");
        else printf("\nJOGADA INVALIDA!\n");
        sleep(1);
    }    
    else {
        (*fim)++;
        if (*vez == 1) {
            *vez = 2;
            *atual = 1;
        }
        else {
            *vez = 1;
            *atual = 2;
        }    
    }     
}

//mostra o resultado
int resultado(char jogada, int *vit1, int *vit2, int atual, int modo, int fim) {
    int verifica;

    verifica = verifica_ganhador(jogada);
    if (verifica == 1) {
        *vit1 = atual == 1 ? ++(*vit1) : *vit1;
        *vit2 = atual == 2 ? ++(*vit2) : *vit2;
        if (modo == 1) inicio_jogada("J", "PC", *vit1, *vit2);
        else inicio_jogada("J1", "J2", *vit1, *vit2);
        if ((atual == 2) && (modo == 1))
            printf("\nO Computador ganhou! Mais sorte na proxima.\n");
        else printf("\nO Jogador %d ganhou! Parabens!\n", atual);
    } else if (fim == 9) {
        verifica = 2;
        (*vit1)++;
        (*vit2)++;
        printf("\nDeu Velha!\n");
    }    
    return verifica;
}

/*1) Função que grava em um arquivo txt as informações abaixo, no seguinte formato:
Nome do Jogador 1; símbolo; Nome do Jogador 2; símbolo.
Exemplo: Maria; X; José; 0*/
void gerar_txt(char *nome1, char *nome2, char simbolo1, char simbolo2){
    FILE *jogadores = fopen("jogadores.txt", "w");
    limpa_buffer();
    ler_nome(nome1, '1');
    ler_nome(nome2, '2');
    fprintf(jogadores, "Jogador 1:\n  Nome: %s  Simbolo: %c\n\n", nome1, simbolo1);
    fprintf(jogadores, "Jogador 2:\n  Nome: %s  Simbolo: %c", nome2, simbolo2);
    fclose(jogadores);
}

/*2) Função que grava em um arquivo binário uma partida do Jogo da Velha.
A função deve ter como entrada os seguintes parâmetros: (1) parâmetro string com o nome
do arquivo; (2) parâmetro Partida com os dados da partida. A função retorna 1 se a gravação
for um sucesso e zero caso contrário.*/
int gerar_bin(char *nome_arquivo, partida *Partida){
    FILE *bin = fopen(nome_arquivo, "ab");

    fwrite(Partida, 1, sizeof(partida), bin);
    fclose(bin);
    return 1;
    return 0;
}

/*3) Função que lê do arquivo binário os dados de uma determinada partida.
A função deve ter como entrada os seguintes parâmetros: (1) parâmetro string com o nome do
arquivo; (2) parâmetro inteiro com o número da partida a ser lida. A função retorna o registro com
os dados da partida que foi lida.*/
partida ler_bin(char *nome_arquivo, int num_partida){
    
}

/*4) Função que imprime na tela todas as partidas (tabuleiros com as respectivas jogadas e quem
ganhou) e o placar final (Ex: Maria 10 X José 5) A Maria foi a campeã do Campeonato de Jogo da
Velha!!!*/
void imprime_campeonato(){

}

void limpa_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void ler_nome(char *nome, char mensagem){
    printf("Jogador %c, seu nome: ", mensagem);
    fgets(nome,100,stdin);
}
