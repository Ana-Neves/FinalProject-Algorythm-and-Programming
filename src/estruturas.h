#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include "raylib.h"

typedef struct {
    Vector2 posicao;
    Vector2 velocidade;
    float raio;
    bool ativa;
} Bola;

typedef struct {
    Rectangle rec;
    float velocidade;
    bool larguraExpandida;
} Plataforma;

typedef struct {
    Rectangle rec;
    int resistencia; 
    bool ativo;
    int tipoPowerUp; 
} Tijolo;

typedef struct {
    Rectangle rec;
    int tipo; 
    bool ativo;
} PowerUp;

typedef struct {
    Tijolo mapa[15][25];
    Bola bolaPrincipal;
    Bola bolasExtras[2]; 
    Plataforma jogador;
    PowerUp powerUpsCaindo[20]; 
    int pontuacao;
    int vidas;
    int faseAtual;
    int estadoTela; 
    bool bolaFogoAtiva;
    float tempoPowerUp; 
} EstadoJogo;


typedef struct {
    char nome[4]; // 3 letras + terminador de string
    int pontuacao;
} RegistroRanking;

#endif