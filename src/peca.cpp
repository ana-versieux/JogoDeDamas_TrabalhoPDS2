#include "peca.hpp"
#include <cmath>
#include <cstdlib>

/**
 * @brief construtor da classe Peca
 * @details Instancia uma peça no tabuleiro.
 */
Peca::Peca(int x, int y, Cor cor, bool dama)
    : posicao_(x, y), cor_(cor), dama_(dama) {}

/**
 * @brief método para mover a peça
 * @param novoX Nova coordenada X da peça
 * @param novoY Nova coordenada Y da peça
 * @details Método que move a peça para uma nova posição no tabuleiro.
 */
void Peca::moverPara(int novoX, int novoY) {
    posicao_.x = novoX;
    posicao_.y = novoY;
}

/**
 * @brief método para verificar se a peça é uma dama
 * @details Método que verifica se a peça é uma dama.
 */
bool Peca::ehDama() const {
    return dama_;
}

/**
 * @brief método para promover a peça a dama
 * @details Método que promove a peça a dama.
 */
void Peca::setToDama() {
    dama_ = true;
}

/**
 * @brief método para obter a cor da peça
 * @details Método que retorna a cor da peça.
 */
Cor Peca::getCor() const {
    return cor_;
}

/**
 * @brief método para obter a posição da peça
 * @details Método que retorna a posição da peça.
 */
Posicao Peca::getPosicao() const {
    return posicao_;
}

/**
 * @brief método para verificar se a peça pode se mover
 * @details Método que verifica se a peça pode se mover para a posição desejada.
 */
bool Peca::podeMover(int dx, int dy) const {

    if (cor_ == Cor::BRANCA) {
        return dy == 1;
    }
    else {
        return dy == -1;
    }

}

