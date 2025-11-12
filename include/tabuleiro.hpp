/**
 * @file tabuleiro.hpp
 * @details Este arquivo contém a definição da classe Tabuleiro, que representa o tabuleiro do jogo de damas.
 */

#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "peca.hpp"

const int TAMANHO_TABULEIRO = 8;

/**
 * @brief Classe Tabuleiro
 * @details Contém os atributos e métodos necessários para gerenciar o tabuleiro do jogo de damas.
 */
class Tabuleiro {
public:
    Tabuleiro();

    void desenharTabuleiro() const;

    void adicionarPeca(Peca* peca);
    void removerPeca(int x, int y);
    Peca* getPeca(int x, int y) const;
    bool estaVazio(int x, int y) const;
    void moverPeca(int origemX, int origemY, int destinoX, int destinoY);
    static bool posicaoValida(int x, int y);

private:
    Peca* casas[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    void inicializarCasas();
};

#endif // TABULEIRO_H
