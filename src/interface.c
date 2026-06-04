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
    // A função DrawRectangleRec recebe perfeitamente a sua variável do tipo Rectangle!
    DrawRectangleRec(jogo.jogador.rec, corPlataforma);

    // Desenhar a bolinha
    // A função DrawCircleV recebe um Vector2 (posição X e Y) e o raio (float)
    DrawCircleV(jogo.bolaPrincipal.posicao, jogo.bolaPrincipal.raio, corBola);
}