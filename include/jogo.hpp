#ifndef JOGO_H
#define JOGO_H

#include "tabuleiro.hpp"
#include "peca.hpp"
#include <string>

class Jogo {
public:
    Jogo();

    void iniciarJogo();
    bool processarJogada(const std::string& entrada);
    bool jogadaValida(int origX, int origY, int destX, int destY) const;
    void aplicarJogada(int origX, int origY, int destX, int destY);
    bool jogoAcabou() const;
    Cor getVencedor() const;

private:
    Tabuleiro tabuleiro_;
    Cor turnoAtual_;
    bool emJogo_;

    void alternarTurno();
    void transformarEmDama(Peca* peca, int y);
    void validarEntrada(const std::string& entrada, int& origX, int& origY, int& destX, int& destY) const;
};

#endif // JOGO_H
