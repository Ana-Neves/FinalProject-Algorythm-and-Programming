#include "interface.h"

void desenharJogo(EstadoJogo jogo) {
    // Desenha Plataforma
    DrawRectangleRec(jogo.jogador.rec, ORANGE);

    // Desenha Bola Principal
    Color corBola = jogo.bolaFogoAtiva ? RED : SKYBLUE; // Fica vermelha se o fogo estiver ativo
    if (jogo.bolaFogoAtiva) {
        DrawCircleV(jogo.bolaPrincipal.posicao, jogo.bolaPrincipal.raio + 3, ORANGE); // Efeito de brilho do fogo
    }
    DrawCircleV(jogo.bolaPrincipal.posicao, jogo.bolaPrincipal.raio, corBola);

    // Desenha Bolas Extras
    for (int i = 0; i < 2; i++) {
        if (jogo.bolasExtras[i].ativa) {
            DrawCircleV(jogo.bolasExtras[i].posicao, jogo.bolasExtras[i].raio, SKYBLUE);
        }
    }

    // Desenha Power-ups Caindo
    for (int p = 0; p < 20; p++) {
        if (jogo.powerUpsCaindo[p].ativo) {
            Color corP;
            char letra[2] = " ";
            if (jogo.powerUpsCaindo[p].tipo == 1) { corP = BLUE; letra[0] = 'E'; } // E = Expansão
            else if (jogo.powerUpsCaindo[p].tipo == 2) { corP = RED; letra[0] = 'F'; } // F = Fogo
            else if (jogo.powerUpsCaindo[p].tipo == 3) { corP = GREEN; letra[0] = '+'; } // + = Bolas Extras

            DrawRectangleRec(jogo.powerUpsCaindo[p].rec, corP);
            DrawText(letra, jogo.powerUpsCaindo[p].rec.x + 4, jogo.powerUpsCaindo[p].rec.y + 2, 12, WHITE);
        }
    }
}

void desenharMapa(EstadoJogo jogo) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            if (jogo.mapa[i][j].ativo) {
                Color corTijolo;
                if (jogo.mapa[i][j].resistencia == -1) corTijolo = DARKGRAY;
                else if (jogo.mapa[i][j].resistencia == 1) corTijolo = GREEN;
                else if (jogo.mapa[i][j].resistencia == 2) corTijolo = YELLOW;
                else if (jogo.mapa[i][j].resistencia == 3) corTijolo = ORANGE;
                else if (jogo.mapa[i][j].resistencia == 4) corTijolo = RED;

                DrawRectangleRec(jogo.mapa[i][j].rec, corTijolo);
                DrawRectangleLinesEx(jogo.mapa[i][j].rec, 1, BLACK);
            }
        }
    }
}