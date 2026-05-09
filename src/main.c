#include "raylib.h"
#include "estruturas.h"

int main(void) {
    // Inicialização
    const int larguraTela = 800;
    const int alturaTela = 600;

    InitWindow(larguraTela, alturaTela, "Trabalho Final - Algoritmos e Programação");

    SetTargetFPS(60); // Define o jogo para rodar a 60 frames por segundo

    // Loop principal do jogo
    while (!WindowShouldClose()) { // Detecta se apertou ESC ou o botão de fechar
        
        // Atualização de variáveis vai aqui...

        // Desenho
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Raylib configurada com sucesso! :D", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    // Desinicialização
    CloseWindow(); // Fecha a janela e o contexto OpenGL

    return 0;
}
