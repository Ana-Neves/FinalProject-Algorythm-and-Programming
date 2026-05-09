#ifndef JOGO_H
#define JOGO_H

#include "estruturas.h"

// Inicializa as variáveis no centro da tela e reseta o jogo
void inicializarEstado(EstadoJogo *jogo);

// Processa o movimento da plataforma e da bola
void atualizarMovimentacao(EstadoJogo *jogo);

// Verifica colisões com paredes, tijolos e plataforma
void processarColisoes(EstadoJogo *jogo);

// Gerencia o tempo de duração e efeito dos power-ups
void gerenciarPowerUps(EstadoJogo *jogo);

#endif
