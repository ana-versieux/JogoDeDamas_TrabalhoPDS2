/**
 * @file jogo.hpp
 * @details Este arquivo contém a definição da classe Jogo, que gerencia a lógica do jogo de damas.
 */

#ifndef JOGO_H
#define JOGO_H

#include "tabuleiro.hpp"
#include "peca.hpp"
#include <string>

/**
 * @brief Classe Jogo
 * @details Contém os atributos e métodos necessários para gerenciar o jogo de damas.
 */
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
