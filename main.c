#include "tictactoe.h"

void main() {
    char arq_bin[] = "campeonato.bin"; 
    char jogador1, jogador2, jogada, nome1[100], nome2[100], nome1_res[100], nome2_res[100];
    char confirma;
    int vez = 1, vez2 = 1,  atual = 0, atual2 = 0, linha, coluna, valida, fim, vit1 = 0, 
        vit2 = 0, vitcpu = 0, vit11 = 0, op, nivel, result, i, j;
    partida jogo, jogolido, *jogoptr = &jogo; 
    FILE *bin = fopen(arq_bin, "wb");

    fclose(bin);
    jogo.Partida = 0;

    do {
        valida = 0;
        fim = 0;
        vez = atual == 1 ? 2 : 1;
        vez2 = atual2 == 1 ? 2 : 1;
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

                strcpy(nome1_res, nome1);
                strcpy(nome2_res, nome2);
                for (i = 0; i < 100; i++) {
                    if (nome1_res[i] == '\n') nome1_res[i] = '\0';
                    if (nome2_res[i] == '\n') nome2_res[i] = '\0';
                }
                for (;;) {   
                    inicio_jogada(nome1_res, nome2_res, vit1, vit2);     
                    if (vez2 == 1) {
                        jogada = jogador1;
                        printf("\n%s: Digite a linha e a coluna para jogar (L C):\n", nome1_res);
                    }    
                    else {
                        jogada = jogador2;
                        printf("\n%s: Digite a linha e a coluna para jogar (L C):\n", nome2_res);
                    }    
                    valida = jogada_usuario(linha, coluna, jogada);
                    inicio_jogada(nome1_res, nome2_res, vit1, vit2); 
                    valida_jogada(valida, &vez2, &atual2, &fim);
                    result = resultado(jogada, &vit1, &vit2, atual2, 2, fim);
                    if ((result == 1) || (result == 2)) {
                        sleep(2);
                        break;
                    }    
                }    
                inicio_jogada(nome1_res, nome2_res, vit1, vit2);
                jogo.Partida++; 
                for (i = 0; i < 3; i++) {
                    for (j = 0; j < 3; j++)
                        jogo.JogVelha[i][j] = corpo[i][j];
                }
                jogo.resultado = result == 2 ? 'V' : jogada;
                if (gerar_bin(arq_bin, jogoptr) == 0) 
                    printf("\nERRO AO GRAVAR NO ARQUIVO\n");               
        } 
        if ((vit1 == vit2)&&(vit1 > 0)) confirma = 'S';
        else confirma = confirmar(); 
    } while (confirma != 'N');
    system("clear");
    if ((vit11 != 0) || (vitcpu != 0)) {
        printf("RESULTADO CONTRA O PC\n");
        printf("---------------------\n");
        printf("J  %d x %d  PC\n\n", vit11, vitcpu);
    }    
    if ((vit1 != 0) || (vit2 != 0)) 
        imprime_campeonato(jogo.Partida, arq_bin, "jogadores.txt");
}       


