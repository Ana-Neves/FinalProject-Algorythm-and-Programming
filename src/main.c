#include "raylib.h"
#include "estruturas.h"
#include "jogo.h"
#include "interface.h"

int main(void)
{
    // Inicialização da Janela
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Trabalho Final - Algoritmos e Programação");
    SetTargetFPS(60);

    // Declarar a variável principal
    EstadoJogo jogo = {0};

    // Definir os valores iniciais
    // Plataforma no centro-inferior (X: 350, Y: 550, Largura: 100, Altura: 20)
    jogo.jogador.rec = (Rectangle){350, 550, 100, 20};
    jogo.jogador.velocidade = 7.0f; // Quantos pixels ela anda por frame

    // Bola começando bem no meio da tela
    jogo.bolaPrincipal.posicao = (Vector2){400, 300};
    jogo.bolaPrincipal.velocidade = (Vector2){5.0f, -5.0f}; // Vai para a direita e para cima
    jogo.bolaPrincipal.raio = 8.0f;

    // Loop principal do jogo (Roda 60 vezes por segundo)
    while (!WindowShouldClose())
    {

        // Atualizar a Física e Movimento
        // Usei '&' porque essas funções PRECISAM alterar os valores da variável original
        atualizarMovimentacao(&jogo);
        processarColisoes(&jogo);

        // Desenhar na tela
        BeginDrawing();

        
        desenharJogo(jogo);

        EndDrawing();
    }

    
    CloseWindow();
    return 0;
}