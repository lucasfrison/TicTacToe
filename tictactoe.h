#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#ifndef _TICTACTOE_H_
#define _TICTACTOE_H_

    //INTERFACE
    
    //corpo do jogo
    char corpo[3][3];
    
    
    typedef struct Velha
    {
        int Partida; /*número da partida (Ex: primeira(1), segunda(2), terceira(3), ….,
        partida)*/
        char JogVelha[3][3]; // Tabuleiro do jogo. Armazenará as jogadas
        char resultado; // Resultado da Partida: X, 0 ou V(equivale a Velha - empate)
    } partida;
    
    //FUNCOES TRABALHO 1
    extern int jogada_usuario(int linha, int coluna, char jogada);
    extern void jogada_computador(char jogada, int nivel);
    extern int menu();
    extern void escolha_simb(char *jogador1, char *jogador2);
    extern void inicializa_velha();
    extern int verifica_ganhador(char jogada);
    extern void tabuleiro();
    extern int scanint();
    extern char confirmar();
    extern void basico(char jogada);
    extern void intermediario(char jogada);
    extern void avancado(char jogada);
    extern void inicio_jogada(char *mensagem, char *mensagem2, int vit, int vit2);
    extern void valida_jogada(int valida, int *vez, int *atual, int *fim);
    extern int resultado(char jogada, int *vit1, int *vit2, int atual, int modo, int fim); 
    
    //FUNCOES NOVAS, TRABALHO 2
    extern void gerar_txt(char *nome1, char *nome2, char simbolo1, char simbolo2);
    extern int gerar_bin(char *nome_arquivo, partida *Partida); 
    extern partida ler_bin(char *nome_arquivo, int num_partida);
    extern void imprime_campeonato(int MAX, char *nome_bin, char *nome_txt); //PENDENTE
    extern void limpa_buffer();
    extern void ler_nome(char *nome, char mensagem, int MAX);

#endif



