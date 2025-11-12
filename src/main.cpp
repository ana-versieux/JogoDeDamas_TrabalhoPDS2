/**
 * @file main.cpp
 * @details Este arquivo contém a implementação da função principal que controla o jogo de damas.
 */

#include "jogo.hpp"
#include <iostream>
#include <string>

using namespace std;


/**
 * @brief Função principal do jogo de damas.
 * @return int
 */
int main() {

    string entrada;

    Jogo jogo;
    jogo.iniciarJogo();

    while (!jogo.jogoAcabou()) {
        cout << "\nInsira sua jogada (ex: A3-B4, ou 'sair' para encerrar): ";
        if (!getline(cin, entrada)) {
            break;
        }

        if (entrada == "sair") {
            cout << "Jogo encerrado pelo jogador." << endl;
            break;
        }

        jogo.processarJogada(entrada);
    }

    return 0;
}
