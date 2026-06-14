#ifndef ARQUIVOS_H
#define ARQUIVOS_H

#include "estruturas.h"
#include <stdbool.h>

void carregarMapa(int fase, EstadoJogo *jogo);
void salvarJogoBinario(EstadoJogo jogo);
bool carregarJogoBinario(EstadoJogo *jogo);

void carregarRanking(RegistroRanking ranking[5]);
void salvarRanking(int pontuacao, const char* nome, RegistroRanking ranking[5]);

#endif