#include "arquivos.h"
#include <stdio.h> 
#include <stdbool.h> 

void carregarMapa(int fase, EstadoJogo *jogo) {
    char caminhoArquivo[50];
    sprintf(caminhoArquivo, "assets/fase_%d.txt", fase); 
    
    FILE *arquivo = fopen(caminhoArquivo, "r");
    
    if (arquivo == NULL) {
        printf("ERRO: Nao foi possivel encontrar o arquivo %s\n", caminhoArquivo);
        return;
    }

    float larguraTijolo = 32.0f; 
    float alturaTijolo = 20.0f;
    float margemTopo = 50.0f; 

    for (int p = 0; p < 20; p++) jogo->powerUpsCaindo[p].ativo = false;

    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            char c = fgetc(arquivo);
            while (c == '\n' || c == '\r' || c == ' ') c = fgetc(arquivo);
            if (c == EOF) break; 

            jogo->mapa[i][j].rec = (Rectangle){ j * larguraTijolo, margemTopo + (i * alturaTijolo), larguraTijolo, alturaTijolo };
            
            int sorteio = GetRandomValue(1, 100);
            if (sorteio <= 10) jogo->mapa[i][j].tipoPowerUp = 1;      
            else if (sorteio <= 20) jogo->mapa[i][j].tipoPowerUp = 2; 
            else if (sorteio <= 30) jogo->mapa[i][j].tipoPowerUp = 3; 
            else jogo->mapa[i][j].tipoPowerUp = 0;                    
            
            if (c == 'X') {
                jogo->mapa[i][j].resistencia = -1; 
                jogo->mapa[i][j].ativo = true;
                jogo->mapa[i][j].tipoPowerUp = 0; 
            } else if (c >= '1' && c <= '4') {
                jogo->mapa[i][j].resistencia = c - '0'; 
                jogo->mapa[i][j].ativo = true;
            } else {
                jogo->mapa[i][j].resistencia = 0; 
                jogo->mapa[i][j].ativo = false;
                jogo->mapa[i][j].tipoPowerUp = 0;
            }
        }
    }
    fclose(arquivo);
} 

void salvarJogoBinario(EstadoJogo jogo) {
    FILE *arquivo = fopen("save_quebra_blocos.bin", "wb"); 
    if (arquivo != NULL) {
        fwrite(&jogo, sizeof(EstadoJogo), 1, arquivo);
        fclose(arquivo);
    }
}

bool carregarJogoBinario(EstadoJogo *jogo) {
    FILE *arquivo = fopen("save_quebra_blocos.bin", "rb"); 
    if (arquivo != NULL) {
        fread(jogo, sizeof(EstadoJogo), 1, arquivo);
        fclose(arquivo);
        return true; 
    }
    return false; 
}

// --- ATUALIZAÇÕES DO RANKING AQUI ---
void carregarRanking(RegistroRanking ranking[5]) {
    FILE *arquivo = fopen("ranking.txt", "r");
    if (arquivo != NULL) {
        for (int i = 0; i < 5; i++) {
            fscanf(arquivo, "%s %d", ranking[i].nome, &ranking[i].pontuacao);
        }
        fclose(arquivo);
    } else {
        // Se não tiver arquivo, preenche com traços e zeros
        for (int i = 0; i < 5; i++) {
            ranking[i].pontuacao = 0;
            ranking[i].nome[0] = '-'; ranking[i].nome[1] = '-'; ranking[i].nome[2] = '-'; ranking[i].nome[3] = '\0';
        }
    }
}

void salvarRanking(int pontuacao, const char* nome, RegistroRanking ranking[5]) {
    for (int i = 0; i < 5; i++) {
        if (pontuacao > ranking[i].pontuacao) {
            for (int j = 4; j > i; j--) {
                ranking[j] = ranking[j-1];
            }
            ranking[i].pontuacao = pontuacao; 
            // Salva o nome letra por letra
            ranking[i].nome[0] = nome[0];
            ranking[i].nome[1] = nome[1];
            ranking[i].nome[2] = nome[2];
            ranking[i].nome[3] = '\0';
            break; 
        }
    }

    FILE *arquivo = fopen("ranking.txt", "w");
    if (arquivo != NULL) {
        for (int i = 0; i < 5; i++) {
            fprintf(arquivo, "%s %d\n", ranking[i].nome, ranking[i].pontuacao);
        }
        fclose(arquivo);
    }
}