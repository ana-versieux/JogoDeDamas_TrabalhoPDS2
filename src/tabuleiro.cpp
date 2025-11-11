#include "tabuleiro.hpp"
#include <iostream>

using namespace std;

/**
 * @brief construtor da classe Tabuleiro
 * @details Instancia um objeto da classe Tabuleiro
 */
Tabuleiro::Tabuleiro() {
    inicializarCasas();
}

/**
 * @brief método para inicializar as casas do tabuleiro
 * @details Inicializa as casas do tabuleiro.
 */
void Tabuleiro::inicializarCasas() {
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        for (int j = 0; j < TAMANHO_TABULEIRO; ++j) {
            casas[i][j] = nullptr;
        }
    }
}

/**
 * @brief método para desenhar o tabuleiro
 * @details Desenha o tabuleiro no console.
 */
void Tabuleiro::desenharTabuleiro() const {
    cout << "  ";
    for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
        cout << " " << (char)('A' + x);
    }
    cout << endl;

    for (int y = TAMANHO_TABULEIRO - 1; y >= 0; y--) {
        cout << y + 1 << " ";
        for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
            cout << "|";
            if (casas[x][y] == nullptr) {
                cout << " ";
            } else {
                if (casas[x][y]->getCor() == Cor::BRANCA) {
                    cout << (casas[x][y]->ehDama() ? 'B' : 'b');
                } else {
                    cout << (casas[x][y]->ehDama() ? 'P' : 'p');
                }
            }
        }
        cout << "| " << y + 1 << endl;
    }

    cout << "  ";
    for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
        cout << " " << (char)('A' + x);
    }
    cout << endl;
}

/**
 * @brief método para adicionar uma peça ao tabuleiro
 * @details Verifica se a posição é válida e se a casa está vazia antes de adicionar a peça.
 */
void Tabuleiro::adicionarPeca(Peca* peca) {
    if (peca && posicaoValida(peca->getPosicao().x, peca->getPosicao().y) && casas[peca->getPosicao().x][peca->getPosicao().y] == nullptr) {
        casas[peca->getPosicao().x][peca->getPosicao().y] = peca;
    }
}

/**
 * @brief método para remover uma peça do tabuleiro
 * @param x Coordenada X da posição da peça
 * @param y Coordenada Y da posição da peça
 * @details Remove a peça da casa especificada.
 */
void Tabuleiro::removerPeca(int x, int y) {
    if (posicaoValida(x, y)) {
        delete casas[x][y];
        casas[x][y] = nullptr;
    }
}

/**
 * @brief método para obter uma peça do tabuleiro
 * @param x Coordenada X da posição da peça
 * @param y Coordenada Y da posição da peça
 * @details Retorna a peça na posição especificada.
 */
Peca* Tabuleiro::getPeca(int x, int y) const {
    if (posicaoValida(x, y)) {
        return casas[x][y];
    }
    return nullptr;
}

/**
 * @brief método para verificar se a casa está vazia
 * @param x Coordenada X da posição da casa
 * @param y Coordenada Y da posição da casa
 * @details Verifica se a casa especificada está vazia.
 */
bool Tabuleiro::estaVazio(int x, int y) const {
    return posicaoValida(x, y) && casas[x][y] == nullptr;
}

/**
 * @brief método para mover uma peça
 * @param origemX Coordenada X da posição de origem
 * @param origemY Coordenada Y da posição de origem
 * @param destinoX Coordenada X da posição de destino
 * @param destinoY Coordenada Y da posição de destino
 * @details Move a peça da posição de origem para a posição de destino.
 */
void Tabuleiro::moverPeca(int origemX, int origemY, int destinoX, int destinoY) {
    if (posicaoValida(origemX, origemY) && casas[origemX][origemY] != nullptr &&
        posicaoValida(destinoX, destinoY) && casas[destinoX][destinoY] == nullptr) {

        Peca* peca = casas[origemX][origemY];
        peca->moverPara(destinoX, destinoY);

        casas[destinoX][destinoY] = peca;
        casas[origemX][origemY] = nullptr;
    }
}

/**
 * @brief método para verificar se a posição é válida
 * @param x Coordenada X da posição
 * @param y Coordenada Y da posição
 * @details Método que verifica se a posição especificada é válida.
 */
bool Tabuleiro::posicaoValida(int x, int y) {
    return x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO;
}
