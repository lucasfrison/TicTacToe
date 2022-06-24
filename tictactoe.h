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
        int partida; 
        char jogVelha[3][3]; 
        char resultado; 
    } Partida;
    
    //FUNCOES TRABALHO 1
    extern int jogada_usuario(int, int, char);
    extern void jogada_computador(char, int);
    extern int menu();
    extern void escolha_simb(char*, char*);
    extern void inicializa_velha();
    extern int verifica_ganhador(char);
    extern void tabuleiro();
    extern int scanint();
    extern char confirmar();
    extern void basico(char);
    extern void intermediario(char);
    extern void avancado(char);
    extern void inicio_jogada(char*, char*, int, int);
    extern void valida_jogada(int, int*, int*, int*);
    extern int resultado(char, int*, int*, int, int, int); 
    
    //FUNCOES NOVAS, TRABALHO 2
    extern void gerar_txt(char*, char*, char, char);
    extern int gerar_bin(char*, Partida*); 
    extern Partida ler_bin(char*, int);
    extern void imprime_campeonato(int, char*, char*); //PENDENTE
    extern void limpa_buffer();
    extern void ler_nome(char*, char, int);

#endif



