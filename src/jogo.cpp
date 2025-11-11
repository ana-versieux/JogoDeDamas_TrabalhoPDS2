#include "jogo.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * @brief construtor da classe Jogo
 * @details Instancia um objeto da classe Jogo
 */
Jogo::Jogo() : turnoAtual_(Cor::BRANCA), emJogo_(true) {}

/**
 * @brief método para iniciar o jogo
 * @details Método que inicializa o tabuleiro com as peças nas posições iniciais.
 */
void Jogo::iniciarJogo() {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro_.removerPeca(i, j);
        }
    }

    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            if ((x + y) % 2 != 0) {
                tabuleiro_.adicionarPeca(new Peca(x, y, Cor::BRANCA));
            }
        }
    }

    for (int y = 5; y < 6; y++) {
        for (int x = 0; x < 1; x++) {
            if ((x + y) % 2 != 0) {
                tabuleiro_.adicionarPeca(new Peca(x, y, Cor::PRETA));
            }
        }
    }

    cout << "\n--- Jogo de Damas Iniciado ---\n\n";
    tabuleiro_.desenharTabuleiro();
    cout << "\nTurno: BRANCAS (b)\n";
}