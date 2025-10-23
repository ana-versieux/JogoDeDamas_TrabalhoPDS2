#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "peca.hpp"

const int TAMANHO_TABULEIRO = 8;

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
