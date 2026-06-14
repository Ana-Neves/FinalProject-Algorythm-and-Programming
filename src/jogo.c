#include "jogo.h"
#include "raylib.h"

void atualizarMovimentacao(EstadoJogo *jogo) {
    // Movimentação da Plataforma
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) jogo->jogador.rec.x -= jogo->jogador.velocidade;
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) jogo->jogador.rec.x += jogo->jogador.velocidade;

    if (jogo->jogador.rec.x <= 0) jogo->jogador.rec.x = 0;
    if (jogo->jogador.rec.x + jogo->jogador.rec.width >= 800) jogo->jogador.rec.x = 800 - jogo->jogador.rec.width;

    // Movimentação das Bolas
    jogo->bolaPrincipal.posicao.x += jogo->bolaPrincipal.velocidade.x;
    jogo->bolaPrincipal.posicao.y += jogo->bolaPrincipal.velocidade.y;

    for (int i = 0; i < 2; i++) {
        if (jogo->bolasExtras[i].ativa) {
            jogo->bolasExtras[i].posicao.x += jogo->bolasExtras[i].velocidade.x;
            jogo->bolasExtras[i].posicao.y += jogo->bolasExtras[i].velocidade.y;
        }
    }

    // Queda dos Power-Ups
    for (int p = 0; p < 20; p++) {
        if (jogo->powerUpsCaindo[p].ativo) {
            jogo->powerUpsCaindo[p].rec.y += 3.0f; // Velocidade de queda
            if (jogo->powerUpsCaindo[p].rec.y > 600) jogo->powerUpsCaindo[p].ativo = false;
        }
    }

    // Temporizador de Power-Ups (Bola de Fogo e Expansão)
    if (jogo->tempoPowerUp > 0) {
        jogo->tempoPowerUp -= GetFrameTime(); // Subtrai o tempo real em segundos
        if (jogo->tempoPowerUp <= 0) {
            jogo->jogador.rec.width = 100; // Plataforma volta ao normal
            jogo->bolaFogoAtiva = false;   // Bolinha perde o fogo
        }
    }
}

// Função auxiliar para calcular o dano em tijolos
void verificarColisaoBolaTijolos(Bola *bola, EstadoJogo *jogo) {
    bool colisaoDetectada = false; 
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            if (jogo->mapa[i][j].ativo) {
                if (CheckCollisionCircleRec(bola->posicao, bola->raio, jogo->mapa[i][j].rec)) {
                    
                    // Se for bola de fogo, atravessa o bloco sem quicar (exceto os indestrutíveis)
                    if (!jogo->bolaFogoAtiva || jogo->mapa[i][j].resistencia == -1) {
                        bola->velocidade.y *= -1; 
                    }

                    if (jogo->mapa[i][j].resistencia > 0) {
                        // Bola de fogo destrói na hora, se não, tira 1 ponto
                        if (jogo->bolaFogoAtiva) jogo->mapa[i][j].resistencia = 0;
                        else jogo->mapa[i][j].resistencia--; 
                        
                        // Quebrou o tijolo!
                        if (jogo->mapa[i][j].resistencia == 0) {
                            jogo->mapa[i][j].ativo = false; 
                            jogo->pontuacao += 10;          

                            // Libera o item para cair
                            if (jogo->mapa[i][j].tipoPowerUp > 0) {
                                for (int p = 0; p < 20; p++) {
                                    if (!jogo->powerUpsCaindo[p].ativo) {
                                        jogo->powerUpsCaindo[p].ativo = true;
                                        jogo->powerUpsCaindo[p].tipo = jogo->mapa[i][j].tipoPowerUp;
                                        // Centraliza o item no tijolo destruído
                                        jogo->powerUpsCaindo[p].rec = (Rectangle){ jogo->mapa[i][j].rec.x + 8, jogo->mapa[i][j].rec.y, 16, 16 };
                                        break;
                                    }
                                }
                            }
                        }
                    } 
                    colisaoDetectada = true;
                    break; 
                }
            }
        }
        if (colisaoDetectada) break; 
    }
}

void processarColisoes(EstadoJogo *jogo) {
    // Colisão Bola Principal com Paredes
    if (jogo->bolaPrincipal.posicao.x >= 800 || jogo->bolaPrincipal.posicao.x <= 0) jogo->bolaPrincipal.velocidade.x *= -1;
    if (jogo->bolaPrincipal.posicao.y <= 0) jogo->bolaPrincipal.velocidade.y *= -1;

    // Colisão Bola Principal com Plataforma
    if (CheckCollisionCircleRec(jogo->bolaPrincipal.posicao, jogo->bolaPrincipal.raio, jogo->jogador.rec)) {
        jogo->bolaPrincipal.velocidade.y *= -1;
        jogo->bolaPrincipal.posicao.y = jogo->jogador.rec.y - jogo->bolaPrincipal.raio;
    }

    // Colisões das Bolas Extras
    for (int i = 0; i < 2; i++) {
        if (jogo->bolasExtras[i].ativa) {
            if (jogo->bolasExtras[i].posicao.x >= 800 || jogo->bolasExtras[i].posicao.x <= 0) jogo->bolasExtras[i].velocidade.x *= -1;
            if (jogo->bolasExtras[i].posicao.y <= 0) jogo->bolasExtras[i].velocidade.y *= -1;

            if (CheckCollisionCircleRec(jogo->bolasExtras[i].posicao, jogo->bolasExtras[i].raio, jogo->jogador.rec)) {
                jogo->bolasExtras[i].velocidade.y *= -1;
                jogo->bolasExtras[i].posicao.y = jogo->jogador.rec.y - jogo->bolasExtras[i].raio;
            }
        }
    }

    // Quebrar tijolos (chama para a principal e paras as extras)
    verificarColisaoBolaTijolos(&jogo->bolaPrincipal, jogo);
    for (int i = 0; i < 2; i++) {
        if (jogo->bolasExtras[i].ativa) verificarColisaoBolaTijolos(&jogo->bolasExtras[i], jogo);
    }

    // Colisão Jogador Pegando Power-Up
    for (int p = 0; p < 20; p++) {
        if (jogo->powerUpsCaindo[p].ativo) {
            if (CheckCollisionRecs(jogo->jogador.rec, jogo->powerUpsCaindo[p].rec)) {
                jogo->powerUpsCaindo[p].ativo = false; // "Comeu" o item
                jogo->pontuacao += 20; // Ponto extra pela coleta

                // APLICA OS SUPERPODERES
                int tipo = jogo->powerUpsCaindo[p].tipo;
                if (tipo == 1) { // Expansão
                    jogo->jogador.rec.width = 200;
                    jogo->jogador.rec.x -= 50; 
                    jogo->tempoPowerUp = 10.0f; // Dura 10 segundos
                } else if (tipo == 2) { // Bola de Fogo
                    jogo->bolaFogoAtiva = true;
                    jogo->tempoPowerUp = 10.0f; // Dura 10 segundos
                } else if (tipo == 3) { // Bolas Extras
                    for (int b = 0; b < 2; b++) {
                        jogo->bolasExtras[b].ativa = true;
                        jogo->bolasExtras[b].posicao = jogo->bolaPrincipal.posicao; // Nascem de onde a original está
                        jogo->bolasExtras[b].raio = 8.0f;
                        // Uma vai pra esquerda, a outra pra direita
                        jogo->bolasExtras[b].velocidade = (Vector2){ (b==0)? 4.0f : -4.0f, -5.0f }; 
                    }
                }
            }
        }
    }
}