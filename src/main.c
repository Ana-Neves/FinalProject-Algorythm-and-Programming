#include "raylib.h"
#include "estruturas.h"
#include "jogo.h"
#include "interface.h"
#include "arquivos.h"

bool faseConcluida(EstadoJogo *jogo) {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            if (jogo->mapa[i][j].ativo && jogo->mapa[i][j].resistencia > 0) return false; 
        }
    }
    return true; 
}

int main(void) {
    const int larguraTela = 800;
    const int alturaTela = 600;
    InitWindow(larguraTela, alturaTela, "Trabalho Final - Algoritmos e Programação");
    SetTargetFPS(60);

    EstadoJogo jogo = {0}; 
    jogo.faseAtual = 1; 
    carregarMapa(jogo.faseAtual, &jogo); 

    jogo.jogador.rec = (Rectangle){ 350, 550, 100, 20 };
    jogo.jogador.velocidade = 7.0f;
    jogo.bolaPrincipal.posicao = (Vector2){ 400, 530 }; 
    jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
    jogo.bolaPrincipal.raio = 8.0f;
    jogo.vidas = 3; 

    // VARIÁVEIS DE FLUXO DO JOGO
    RegistroRanking ranking[5]; 
    carregarRanking(ranking); 
    
    int telaAtual = 0; // 0=Menu, 1=Jogo, 2=Game Over, 3=Vitória, 4=Novo Recorde
    int contadorFrames = 0; 
    int opcaoMenu = 0; 
    bool sairDoJogo = false; 

    // Variáveis para digitação do nome
    char nomeJogador[4] = "\0\0\0\0";
    int contaLetras = 0;
    bool venceuJogo = false;

    while (!WindowShouldClose() && !sairDoJogo) { 
        contadorFrames++;

        switch (telaAtual) {
            case 0: // TELA DE MENU
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                    opcaoMenu++;
                    if (opcaoMenu > 2) opcaoMenu = 0; 
                }
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                    opcaoMenu--;
                    if (opcaoMenu < 0) opcaoMenu = 2; 
                }

                if (IsKeyPressed(KEY_ENTER)) {
                    if (opcaoMenu == 0) {
                        jogo.faseAtual = 1;
                        jogo.pontuacao = 0;
                        jogo.vidas = 3;
                        jogo.bolaPrincipal.posicao = (Vector2){ 400, 530 };
                        jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
                        jogo.jogador.rec.x = 350;
                        jogo.jogador.rec.width = 100;
                        jogo.bolaFogoAtiva = false;
                        jogo.bolasExtras[0].ativa = false;
                        jogo.bolasExtras[1].ativa = false;
                        carregarMapa(jogo.faseAtual, &jogo);
                        telaAtual = 1; 
                    } else if (opcaoMenu == 1) {
                        if (carregarJogoBinario(&jogo)) telaAtual = 1;
                    } else if (opcaoMenu == 2) {
                        sairDoJogo = true;
                    }
                }
                break;

            case 1: // TELA DE JOGO
                atualizarMovimentacao(&jogo);
                processarColisoes(&jogo);

                if (IsKeyPressed(KEY_S)) salvarJogoBinario(jogo);

                bool algumaBolaViva = false;
                if (jogo.bolaPrincipal.posicao.y <= alturaTela) algumaBolaViva = true;
                if (jogo.bolasExtras[0].ativa && jogo.bolasExtras[0].posicao.y <= alturaTela) algumaBolaViva = true;
                if (jogo.bolasExtras[1].ativa && jogo.bolasExtras[1].posicao.y <= alturaTela) algumaBolaViva = true;

                if (!algumaBolaViva) {
                    jogo.vidas--; 
                    if (jogo.vidas > 0) {
                        jogo.bolaPrincipal.posicao = (Vector2){ 400, 530 }; 
                        jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
                        jogo.jogador.rec.x = 350;
                        jogo.jogador.rec.width = 100; 
                        jogo.bolaFogoAtiva = false;   
                        jogo.bolasExtras[0].ativa = false; 
                        jogo.bolasExtras[1].ativa = false;
                    } else {
                        venceuJogo = false;
                        // Checa se entrou no Top 5
                        if (jogo.pontuacao > ranking[4].pontuacao) {
                            telaAtual = 4; // Vai digitar o nome
                            contaLetras = 0;
                            nomeJogador[0] = '\0';
                        } else {
                            telaAtual = 2; // Game Over normal
                        }
                    }
                }

                if (faseConcluida(&jogo)) {
                    if (jogo.faseAtual < 3) {
                        jogo.faseAtual++;
                        carregarMapa(jogo.faseAtual, &jogo);
                        jogo.bolaPrincipal.posicao = (Vector2){ 400, 530 }; 
                        jogo.bolaPrincipal.velocidade = (Vector2){ 5.0f, -5.0f };
                        jogo.jogador.rec.x = 350;
                        jogo.jogador.rec.width = 100;
                        jogo.bolaFogoAtiva = false;
                        jogo.bolasExtras[0].ativa = false;
                        jogo.bolasExtras[1].ativa = false;
                    } else {
                        venceuJogo = true;
                        // Checa se entrou no Top 5
                        if (jogo.pontuacao > ranking[4].pontuacao) {
                            telaAtual = 4; // Vai digitar o nome
                            contaLetras = 0;
                            nomeJogador[0] = '\0';
                        } else {
                            telaAtual = 3; // Vitória normal
                        }
                    }
                }
                break;

/* Função desenvolvida com auxílio do Gemini. 
   Ver apêndice A do relatório (Sistema de Transição e Entrada de Texto). */
            case 4: { // TELA DE DIGITAR O NOME
                int tecla = GetCharPressed();
                while (tecla > 0) {
                    // Aceita letras e garante o máximo de 3 caracteres
                    if ((tecla >= 32) && (tecla <= 125) && (contaLetras < 3)) {
                        nomeJogador[contaLetras] = (char)tecla;
                        nomeJogador[contaLetras+1] = '\0';
                        contaLetras++;
                    }
                    tecla = GetCharPressed();
                }
                
                // Apagar letra
                if (IsKeyPressed(KEY_BACKSPACE)) {
                    contaLetras--;
                    if (contaLetras < 0) contaLetras = 0;
                    nomeJogador[contaLetras] = '\0';
                }
                
                // Confirmar nome
                if (IsKeyPressed(KEY_ENTER) && contaLetras > 0) {
                    salvarRanking(jogo.pontuacao, nomeJogador, ranking);
                    if (venceuJogo) telaAtual = 3;
                    else telaAtual = 2;
                }
                break;
            } 

            case 2: // TELA DE GAME OVER
            case 3: // TELA DE VITÓRIA
                if (IsKeyPressed(KEY_ENTER)) {
                    carregarRanking(ranking); 
                    opcaoMenu = 0; 
                    telaAtual = 0;            
                }
                break;
        }

        BeginDrawing();

        switch (telaAtual) {
            case 0: // DESENHANDO O MENU
                ClearBackground(DARKBLUE); 
                DrawText("BREAKOUT", larguraTela/2 - MeasureText("BREAKOUT", 60)/2, 60, 60, WHITE);
                
                Color corNovo = (opcaoMenu == 0) ? YELLOW : LIGHTGRAY;
                Color corCarregar = (opcaoMenu == 1) ? YELLOW : LIGHTGRAY;
                Color corSair = (opcaoMenu == 2) ? YELLOW : LIGHTGRAY;

                const char* txtNovo = (opcaoMenu == 0) ? "> NOVO JOGO <" : "NOVO JOGO";
                const char* txtCarregar = (opcaoMenu == 1) ? "> CARREGAR JOGO <" : "CARREGAR JOGO";
                const char* txtSair = (opcaoMenu == 2) ? "> SAIR <" : "SAIR";

                DrawText(txtNovo, larguraTela/2 - MeasureText(txtNovo, 30)/2, 160, 30, corNovo);
                DrawText(txtCarregar, larguraTela/2 - MeasureText(txtCarregar, 30)/2, 210, 30, corCarregar);
                DrawText(txtSair, larguraTela/2 - MeasureText(txtSair, 30)/2, 260, 30, corSair);

                // DESENHA O NOVO RANKING COM NOME E PONTOS
                DrawText("TOP 5 RECORDES", larguraTela/2 - MeasureText("TOP 5 RECORDES", 20)/2, 340, 20, GOLD);
                for (int i = 0; i < 5; i++) {
                    DrawText(TextFormat("%d. %s - %d pts", i + 1, ranking[i].nome, ranking[i].pontuacao), larguraTela/2 - 80, 380 + (i * 30), 20, LIGHTGRAY);
                }
                break;

            case 1: // DESENHANDO O JOGO
                ClearBackground(BLACK); 
                desenharJogo(jogo); 
                desenharMapa(jogo); 
                DrawText(TextFormat("PONTOS: %d", jogo.pontuacao), 20, 15, 20, WHITE);
                DrawText(TextFormat("FASE: %d", jogo.faseAtual), larguraTela/2 - 40, 15, 20, GREEN);
                DrawText(TextFormat("VIDAS: %d", jogo.vidas), larguraTela - 120, 15, 20, RED);
                break;

            case 4: // DESENHANDO A TELA DE RECORDE
                ClearBackground(BLACK);
                DrawText("NOVO RECORDE!", larguraTela/2 - MeasureText("NOVO RECORDE!", 50)/2, 150, 50, GOLD);
                DrawText("DIGITE SUAS INICIAIS (3 LETRAS):", larguraTela/2 - MeasureText("DIGITE SUAS INICIAIS (3 LETRAS):", 20)/2, 250, 20, WHITE);

                DrawRectangleLines(larguraTela/2 - 50, 300, 100, 50, LIGHTGRAY);
                DrawText(nomeJogador, larguraTela/2 - MeasureText(nomeJogador, 40)/2, 305, 40, YELLOW);

                if (contaLetras > 0 && ((contadorFrames / 30) % 2 == 0)) {
                    DrawText("PRESSIONE ENTER PARA SALVAR", larguraTela/2 - MeasureText("PRESSIONE ENTER PARA SALVAR", 20)/2, 450, 20, LIGHTGRAY);
                }
                break;

            case 2: // DESENHANDO O GAME OVER
                ClearBackground(BLACK); 
                DrawText("GAME OVER", larguraTela/2 - MeasureText("GAME OVER", 60)/2, 150, 60, RED);
                DrawText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), larguraTela/2 - MeasureText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), 30)/2, 300, 30, WHITE);
                if ((contadorFrames / 30) % 2 == 0) DrawText("PRESSIONE ENTER PARA VOLTAR AO MENU", larguraTela/2 - MeasureText("PRESSIONE ENTER PARA VOLTAR AO MENU", 20)/2, 450, 20, LIGHTGRAY);
                break;

            case 3: // DESENHANDO A VITÓRIA
                ClearBackground(DARKGREEN); 
                DrawText("VITORIA!", larguraTela/2 - MeasureText("VITORIA!", 60)/2, 150, 60, YELLOW);
                DrawText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), larguraTela/2 - MeasureText(TextFormat("PONTUACAO FINAL: %d", jogo.pontuacao), 30)/2, 300, 30, WHITE);
                if ((contadorFrames / 30) % 2 == 0) DrawText("PRESSIONE ENTER PARA VOLTAR AO MENU", larguraTela/2 - MeasureText("PRESSIONE ENTER PARA VOLTAR AO MENU", 20)/2, 450, 20, LIGHTGRAY);
                break;
        }
            
        EndDrawing();
    }

    CloseWindow(); 
    return 0;
}