#include "jogo.h"


void atualizarMovimentacao(EstadoJogo *jogo) {
    // MOVIMENTO DA PLATAFORMA
    // Lê as setas do teclado (ou A e D) e move a plataforma
    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        jogo->jogador.rec.x += jogo->jogador.velocidade;
    }
    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        jogo->jogador.rec.x -= jogo->jogador.velocidade;
    }

    // Trava de Segurança: Impede a plataforma de fugir da tela (800 de largura)
    if (jogo->jogador.rec.x < 0) {
        jogo->jogador.rec.x = 0; // Bateu na parede esquerda
    }
    if (jogo->jogador.rec.x + jogo->jogador.rec.width > 800) {
        jogo->jogador.rec.x = 800 - jogo->jogador.rec.width; // Bateu na direita
    }

    // MOVIMENTO DA BOLA
    // A cada frame, a bola anda um pouquinho na direção da sua velocidade
    jogo->bolaPrincipal.posicao.x += jogo->bolaPrincipal.velocidade.x;
    jogo->bolaPrincipal.posicao.y += jogo->bolaPrincipal.velocidade.y;
}



void processarColisoes(EstadoJogo *jogo) {
    // COLISÃO COM AS PAREDES LATERAIS 
    // Se a bola bater no X 0 (esquerda) ou X 800 (direita), inverte a velocidade X
    if (jogo->bolaPrincipal.posicao.x - jogo->bolaPrincipal.raio <= 0 || 
        jogo->bolaPrincipal.posicao.x + jogo->bolaPrincipal.raio >= 800) {
        jogo->bolaPrincipal.velocidade.x *= -1; 
    }

    // COLISÃO COM O TETO
    // Se a bola bater no Y 0 (teto), inverte a velocidade Y para descer
    if (jogo->bolaPrincipal.posicao.y - jogo->bolaPrincipal.raio <= 0) {
        jogo->bolaPrincipal.velocidade.y *= -1; 
    }

    // COLISÃO COM O CHÃO  
    // No jogo final, cair no chão (Y 600) perde vida. 
    // Por enquanto, vamos fazer ela quicar para podermos testar o motor à vontade!
   // Como deve ficar:
if (jogo->bolaPrincipal.posicao.y <= 0) { // Bate apenas no teto!
    jogo->bolaPrincipal.velocidade.y *= -1;
}

    // COLISÃO COM A PLATAFORMA
    // CheckCollisionCircleRec checa automaticamente se o círculo entrou no retângulo
    if (CheckCollisionCircleRec(jogo->bolaPrincipal.posicao, jogo->bolaPrincipal.raio, jogo->jogador.rec)) {
        // Inverte a velocidade para a bola subir
        jogo->bolaPrincipal.velocidade.y *= -1; 
        
        // Coloca a bola milimetricamente acima da plataforma
        jogo->bolaPrincipal.posicao.y = jogo->jogador.rec.y - jogo->bolaPrincipal.raio;
    }

    // COLISÃO COM OS TIJOLOS
    bool colisaoDetectada = false; // Flag para não bater em dois blocos de uma vez
    
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 25; j++) {
            
            // Só checa colisão se o bloco ainda existir na tela
            if (jogo->mapa[i][j].ativo) {
                
                // A mágica da Raylib verificando o impacto
                if (CheckCollisionCircleRec(jogo->bolaPrincipal.posicao, jogo->bolaPrincipal.raio, jogo->mapa[i][j].rec)) {
                    
                    // 1. Faz a bolinha quicar (inverte o Y)
                    jogo->bolaPrincipal.velocidade.y *= -1;
                    
                    // 2. Lógica de dano (se não for bloco indestrutível '-1')
                    if (jogo->mapa[i][j].resistencia > 0) {
                        jogo->mapa[i][j].resistencia--; // Perde 1 de "vida"
                        
                        // Se a vida zerar, o bloco some da tela
                        if (jogo->mapa[i][j].resistencia == 0) {
                            jogo->mapa[i][j].ativo = false;
                            jogo->pontuacao += 10; // Soma 10 pontos!
                        }
                    }
                    
                    colisaoDetectada = true;
                    break; // Sai do loop da coluna
                }
            }
        }
        if (colisaoDetectada) break; // Sai do loop da linha
    }
}
