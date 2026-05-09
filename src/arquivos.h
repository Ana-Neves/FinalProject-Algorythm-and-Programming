#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "estruturas.h"

// Lê o arquivo fase_X.txt e preenche a matriz do jogo
void carregarMapa(int fase, EstadoJogo *jogo);

// Salva o estado atual em um arquivo binário
void salvarProgresso(EstadoJogo jogo);

// Carrega o jogo salvo do arquivo binário
void carregarProgresso(EstadoJogo *jogo);

// Gerencia o ranking das TOP 5 pontuações em arquivo texto
void atualizarRanking(int pontuacao, char nome[]);

#endif
