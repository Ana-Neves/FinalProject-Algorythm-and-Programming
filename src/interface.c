#include "interface.h"

void desenharJogo(EstadoJogo jogo)
{
    // Definindo as cores exatas do wireframe
    Color corFundo = {10, 10, 26, 255};       // Azul muito escuro (#0A0A1A)
    Color corPlataforma = {255, 184, 0, 255}; // Laranja/Mostarda (#FFB800)
    Color corBola = {0, 255, 255, 255};       // Ciano (#00FFFF)

    // Limpar a tela com a cor do fundo do espaço
    ClearBackground(corFundo);

    // Desenhar a plataforma
    DrawRectangleRec(jogo.jogador.rec, corPlataforma);

    // Desenhar a bolinha
    // A função DrawCircleV recebe um Vector2 (posição X e Y) e o raio (float)
    DrawCircleV(jogo.bolaPrincipal.posicao, jogo.bolaPrincipal.raio, corBola);
}

void desenharMapa(EstadoJogo jogo) {
    // Percorre toda a matriz
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            
            // Só desenha se o tijolo estiver ativo
            if (jogo.mapa[i][j].ativo) {
                Color corTijolo;
                
                // Define a cor baseada na resistência
                switch (jogo.mapa[i][j].resistencia) {
                    case -1: corTijolo = GRAY; break;      // 'X' - Indestrutível
                    case 1:  corTijolo = GREEN; break;     // '1' - 1 batida
                    case 2:  corTijolo = YELLOW; break;    // '2' - 2 batidas
                    case 3:  corTijolo = ORANGE; break;    // '3' - 3 batidas
                    case 4:  corTijolo = RED; break;       // '4' - 4 batidas
                    default: corTijolo = BLANK; break;     // Caso de erro
                }
                
                // Desenha o retângulo do tijolo
                DrawRectangleRec(jogo.mapa[i][j].rec, corTijolo);
                
                // Desenha uma linha preta de 1 pixel em volta 
                // de cada tijolo para eles não virarem um borrão de cor só!
                DrawRectangleLinesEx(jogo.mapa[i][j].rec, 1.0f, BLACK);
            }
        }
    }
}