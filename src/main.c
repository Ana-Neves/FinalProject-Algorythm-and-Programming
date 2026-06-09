#include "raylib.h"
#include "estruturas.h"
#include "jogo.h"
#include "interface.h"
#include "arquivos.h"

int main(void) {
    // Inicialização da Janela
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Trabalho Final - Algoritmos e Programação");
    SetTargetFPS(60);

    // Declaração principal e setup inicial
    EstadoJogo jogo = {0}; 
    carregarMapa(1, &jogo); 

    jogo.jogador.rec = (Rectangle){ 350, 550, 100, 20 };
    jogo.jogador.velocidade = 7.0f;
    jogo.bolaPrincipal.posicao = (Vector2){ 400, 300 };
    jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
    jogo.bolaPrincipal.raio = 8.0f;

    // --- VARIÁVEIS DE FLUXO DO JOGO ---
    int telaAtual = 0; // 0 = Menu, 1 = Jogo, 2 = Game Over
    int contadorFrames = 0; // Usado para criar o efeito do texto piscando

    // Loop principal
    while (!WindowShouldClose()) { 
        contadorFrames++;

     
        switch (telaAtual) {
            case 0: // TELA DE MENU
                if (IsKeyPressed(KEY_ENTER)) {
                    telaAtual = 1; // Aperte Enter para jogar!
                }
                break;

            case 1: // TELA DE JOGO (Ação)
                atualizarMovimentacao(&jogo);
                processarColisoes(&jogo);

                // --- SISTEMA DE SAVE / LOAD ---
                if (IsKeyPressed(KEY_S)) {
                    salvarJogoBinario(jogo);
                }
                if (IsKeyPressed(KEY_C)) {
                    carregarJogoBinario(&jogo);
                }

                // Condição de Derrota: Se a bolinha cair da tela
                if (jogo.bolaPrincipal.posicao.y > alturaTela) {
                    telaAtual = 2; // Vai para o Game Over
                }
                break;

            case 2: // TELA DE GAME OVER
                if (IsKeyPressed(KEY_ENTER)) {
                    // Reseta os valores para a pessoa jogar de novo
                    jogo.bolaPrincipal.posicao = (Vector2){ 400, 300 };
                    jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
                    jogo.jogador.rec.x = 350;
                    jogo.pontuacao = 0;
                    carregarMapa(1, &jogo); // Recarrega os blocos intocados
                    telaAtual = 1; // Volta direto para a ação
                }
                break;
        }

        
        BeginDrawing();

        switch (telaAtual) {
            case 0: // DESENHANDO O MENU
                ClearBackground(DARKBLUE); 
                
                // MeasureText centraliza a palavra matematicamente
                DrawText("BREAKOUT", larguraTela/2 - MeasureText("BREAKOUT", 60)/2, 200, 60, WHITE);
                
                // O texto só é desenhado a cada 30 frames (cria o piscar)
                if ((contadorFrames / 30) % 2 == 0) {
                    DrawText("PRESSIONE ENTER PARA COMECAR", larguraTela/2 - MeasureText("PRESSIONE ENTER PARA COMECAR", 20)/2, 400, 20, LIGHTGRAY);
                }
                break;

            case 1: // DESENHANDO O JOGO
                // Suas funções de renderização normais
                desenharJogo(jogo); 
                desenharMapa(jogo); 
                
                // Mostra a pontuação ali no topo esquerdo!
                DrawText(TextFormat("PONTOS: %d", jogo.pontuacao), 20, 15, 20, WHITE);
                break;

            case 2: // DESENHANDO O GAME OVER
                ClearBackground(BLACK); 
                DrawText("GAME OVER", larguraTela/2 - MeasureText("GAME OVER", 60)/2, 150, 60, RED);
                
                // Exibe o placar final
                DrawText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), larguraTela/2 - MeasureText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), 30)/2, 300, 30, WHITE);
                
                if ((contadorFrames / 30) % 2 == 0) {
                    DrawText("PRESSIONE ENTER PARA TENTAR NOVAMENTE", larguraTela/2 - MeasureText("PRESSIONE ENTER PARA TENTAR NOVAMENTE", 20)/2, 450, 20, LIGHTGRAY);
                }
                break;
        }
            
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}