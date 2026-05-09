#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "raylib.h"

// Estrutura para a Bola
typedef struct {
    Vector2 posicao;
    Vector2 velocidade;
    float raio;
    bool ativa;
} Bola;

// Estrutura para a Plataforma
typedef struct {
    Rectangle rec;
    float velocidade;
    bool larguraExpandida;
} Plataforma;

// Estrutura para os Tijolos
typedef struct {
    Rectangle rec;
    int resistencia; // 0 para vazio, 1-4 para destrutíveis, -1 para indestrutíveis ('X')
    bool ativo;
    int tipoPowerUp; // 0: nenhum, 1: expansão, 2: bola fogo, 3: extra
} Tijolo;

// Estrutura Principal do Estado do Jogo
typedef struct {
    Tijolo mapa[15][25];
    Bola bolaPrincipal;
    Bola bolasExtras[2]; // Para o power-up de bolas extras
    Plataforma jogador;
    int pontuacao;
    int vidas;
    int faseAtual;
    int estadoTela; // 0: Menu, 1: Jogando, 2: Pausado, 3: Vitória, 4: Derrota
    bool bolaFogoAtiva;
    float tempoPowerUp;
} EstadoJogo;

#endif
