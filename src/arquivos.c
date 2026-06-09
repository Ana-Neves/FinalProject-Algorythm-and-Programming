#include "arquivos.h"
#include <stdio.h> 
#include <stdbool.h> 
void carregarMapa(int fase, EstadoJogo *jogo) {
    // Abre o arquivo de texto em modo de leitura ("r")
    // O caminho considera que o jogo roda a partir da pasta raiz
    FILE *arquivo = fopen("assets/fase_1.txt", "r");
    
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel encontrar o arquivo assets/fase_1.txt\n");
        return;
    }

    // Calculando as dimensões de cada tijolo
    // Tela tem 800 de largura / 25 colunas = 32 pixels de largura por tijolo
    float larguraTijolo = 32.0f; 
    float alturaTijolo = 20.0f;
    float margemTopo = 50.0f; // Um espaço em cima para depois colocarmos a pontuação

    // Percorre a matriz de 15 linhas e 25 colunas
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            char c = fgetc(arquivo);
            
            // Ignora espaços e quebras de linha invisíveis
            while (c == '\n' || c == '\r' || c == ' ') {
                c = fgetc(arquivo);
            }

            // Fim de arquivo inesperado
            if (c == EOF) break; 

            // 1. Salva as medidas exatas do tijolo
            jogo->mapa[i][j].rec = (Rectangle){ j * larguraTijolo, margemTopo + (i * alturaTijolo), larguraTijolo, alturaTijolo };
            
            // 2. Define a resistência e ativa o tijolo
            if (c == 'X') {
                jogo->mapa[i][j].resistencia = -1; // Indestrutível
                jogo->mapa[i][j].ativo = true;
            } else if (c >= '1' && c <= '4') {
                jogo->mapa[i][j].resistencia = c - '0'; // Truque para converter o texto '1' no número 1
                jogo->mapa[i][j].ativo = true;
            } else {
                jogo->mapa[i][j].resistencia = 0; // Vazio
                jogo->mapa[i][j].ativo = false;
            }
            
            jogo->mapa[i][j].tipoPowerUp = 0; // Inicializa sem power-ups
        }
    }
    
    fclose(arquivo);
} 


// Salva a struct inteira em um arquivo binário
void salvarJogoBinario(EstadoJogo jogo) {
    FILE *arquivo = fopen("save_quebra_blocos.bin", "wb"); // "wb" = write binary
    if (arquivo != NULL) {
        fwrite(&jogo, sizeof(EstadoJogo), 1, arquivo);
        fclose(arquivo);
    }
}

// Carrega o arquivo binário de volta para a struct
bool carregarJogoBinario(EstadoJogo *jogo) {
    FILE *arquivo = fopen("save_quebra_blocos.bin", "rb"); // "rb" = read binary
    if (arquivo != NULL) {
        fread(jogo, sizeof(EstadoJogo), 1, arquivo);
        fclose(arquivo);
        return true; 
    }
    return false; 