#ifndef INTERFACE_H
#define INTERFACE_H

#include "raylib.h"
#include "estruturas.h"

// Desenha a barra superior com pontos, fase e vidas
void desenharInterfaceUsuario(EstadoJogo jogo);

// Itera pela matriz e desenha os tijolos conforme a cor/resistência
void desenharMapa(EstadoJogo jogo);

// Desenha o menu principal e as telas de vitória/derrota
void desenharTelasSistema(EstadoJogo jogo);

#endif
