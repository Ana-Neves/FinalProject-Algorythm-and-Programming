#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "estruturas.h"

// Vai ler o arquivo fase_X.txt e preencher a matriz do jogo
void carregarMapa(int fase, EstadoJogo *jogo);

void salvarJogoBinario(EstadoJogo jogo);
bool carregarJogoBinario(EstadoJogo *jogo);

// Salva o estado atual em um arquivo binário
void salvarProgresso(EstadoJogo jogo);

// Carrega o jogo salvo do arquivo binário
void carregarProgresso(EstadoJogo *jogo);

// Vai gerenciar o ranking das TOP 5 pontuações em arquivo texto
void atualizarRanking(int pontuacao, char nome[]);

#endif
