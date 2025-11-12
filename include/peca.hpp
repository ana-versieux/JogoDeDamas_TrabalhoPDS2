/**
 * @file peca.hpp
 * @details Este arquivo contém a definição da classe Peca, que representa uma peça do jogo de damas.
 */

#ifndef PECA_H
#define PECA_H

/**
 * @brief Enumeração de Cores
 * @details Esta enumeração contém as cores possíveis das peças no tabuleiro.
 */
enum class Cor {
    BRANCA, PRETA
};

/**
 * @brief Estrutura de Posição
 * @details Esta estrutura contém as coordenadas de uma posição no tabuleiro.
 */
struct Posicao {
    int x;
    int y;
    Posicao(int param_x = 0, int param_y = 0) : x(param_x), y(param_y) {}
};

/**
 * @brief Peça
 * @details Esta classe contém os atributos e métodos necessários para gerenciar uma peça do jogo de damas.
 */
class Peca {
public:
    Peca(int x, int y, Cor cor, bool dama = false);

    void moverPara(int novoX, int novoY);
    bool ehDama() const;
    void setToDama();
    Cor getCor() const;
    Posicao getPosicao() const;
    bool podeMover(int dx, int dy) const;

private:
    Posicao posicao_;
    Cor cor_;
    bool dama_;
};

#endif // PECA_H
