#include "tabuleiro.hpp"
#include <iostream>

using namespace std;

Tabuleiro::Tabuleiro() {
    inicializarCasas();
}

void Tabuleiro::inicializarCasas() {
    for (int i = 0; i < TAMANHO_TABULEIRO; ++i) {
        for (int j = 0; j < TAMANHO_TABULEIRO; ++j) {
            casas[i][j] = nullptr;
        }
    }
}

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

void Tabuleiro::adicionarPeca(Peca* peca) {
    if (peca && posicaoValida(peca->getPosicao().x, peca->getPosicao().y) && casas[peca->getPosicao().x][peca->getPosicao().y] == nullptr) {
        casas[peca->getPosicao().x][peca->getPosicao().y] = peca;
    }
}

void Tabuleiro::removerPeca(int x, int y) {
    if (posicaoValida(x, y)) {
        delete casas[x][y];
        casas[x][y] = nullptr;
    }
}

Peca* Tabuleiro::getPeca(int x, int y) const {
    if (posicaoValida(x, y)) {
        return casas[x][y];
    }
    return nullptr;
}

bool Tabuleiro::estaVazio(int x, int y) const {
    return posicaoValida(x, y) && casas[x][y] == nullptr;
}

void Tabuleiro::moverPeca(int origemX, int origemY, int destinoX, int destinoY) {
    if (posicaoValida(origemX, origemY) && casas[origemX][origemY] != nullptr &&
        posicaoValida(destinoX, destinoY) && casas[destinoX][destinoY] == nullptr) {

        Peca* peca = casas[origemX][origemY];
        peca->moverPara(destinoX, destinoY);

        casas[destinoX][destinoY] = peca;
        casas[origemX][origemY] = nullptr;
    }
}

bool Tabuleiro::posicaoValida(int x, int y) {
    return x >= 0 && x < TAMANHO_TABULEIRO && y >= 0 && y < TAMANHO_TABULEIRO;
}