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

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
            if ((x + y) % 2 != 0) {
                tabuleiro_.adicionarPeca(new Peca(x, y, Cor::BRANCA));
            }
        }
    }

    for (int y = 5; y < TAMANHO_TABULEIRO; y++) {
        for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
            if ((x + y) % 2 != 0) {
                tabuleiro_.adicionarPeca(new Peca(x, y, Cor::PRETA));
            }
        }
    }

    cout << "\n--- Jogo de Damas Iniciado ---\n\n";
    tabuleiro_.desenharTabuleiro();
    cout << "\nTurno: BRANCAS (b)\n";
}

/**
 * @brief método para processar jogadas
 * @details Método que valida e aplica uma jogada no tabuleiro.
 */
bool Jogo::processarJogada(const std::string& entrada) {
    if (!emJogo_) {
        return false;
    }

    int origX, origY, destX, destY;

    try {
        validarEntrada(entrada, origX, origY, destX, destY);
    } catch (const invalid_argument& e) {
        cout << "Jogada invalida: " << e.what() << "" << endl;
        return false;
    }

    if (!jogadaValida(origX, origY, destX, destY)) {
        return false;
    }

    aplicarJogada(origX, origY, destX, destY);

    Peca* pecaMovida = tabuleiro_.getPeca(destX, destY);
    if (pecaMovida) {
        transformarEmDama(pecaMovida, destY);
    }

    if (jogoAcabou()) {
        emJogo_ = false;
        cout << "\n\n--- FIM DE JOGO ---\n\n";
        tabuleiro_.desenharTabuleiro();
        cout << "\nVencedor: " << (getVencedor() == Cor::BRANCA ? "BRANCAS" : "PRETAS") << "!" << endl;
        return true;
    }

    alternarTurno();
    tabuleiro_.desenharTabuleiro();
    cout << "\nTurno: " << (turnoAtual_ == Cor::BRANCA ? "BRANCAS (b)" : "PRETAS (p)\n");

    return true;
}

/**
 * @brief método para validar a entrada do usuário
 * @param entrada A string de entrada do usuário
 * @param origX Coordenada X da posição de origem
 * @param origY Coordenada Y da posição de origem
 * @param destX Coordenada X da posição de destino
 * @param destY Coordenada Y da posição de destino
 * @details Método que verifica se a entrada do usuário está no formato correto e se as posições são válidas.
 */
void Jogo::validarEntrada(const std::string& entrada, int& origX, int& origY, int& destX, int& destY) const {
    if (entrada.length() != 5 || entrada[2] != '-') {
        throw invalid_argument("Formato incorreto. Use o formato COLUNA_ORIGEM_LINHA_ORIGEM-COLUNA_DESTINO_LINHA_DESTINO (ex: A3-B4).");
    }

    // Coluna (A-H) para X (0-7)
    char colOrig = std::toupper(entrada[0]);
    char colDest = std::toupper(entrada[3]);
    origX = colOrig - 'A';
    destX = colDest - 'A';

    // Linha (1-8) para Y (0-7)
    origY = entrada[1] - '1';
    destY = entrada[4] - '1';

    if (!Tabuleiro::posicaoValida(origX, origY) || !Tabuleiro::posicaoValida(destX, destY)) {
        throw invalid_argument("Posições fora do tabuleiro (A1-H8).");
    }
}

/**
 * @brief método para validar jogadas
 * @param origX Coordenada X da posição de origem
 * @param origY Coordenada Y da posição de origem
 * @param destX Coordenada X da posição de destino
 * @param destY Coordenada Y da posição de destino
 * @details Método que verifica se uma jogada é válida de acordo com as regras do jogo.
 */
bool Jogo::jogadaValida(int origX, int origY, int destX, int destY) const {
    Peca* peca = tabuleiro_.getPeca(origX, origY);

    if (!peca) {
        cout << "Jogada invalida: Nao ha Peca na posicao de origem.\n";
        return false;
    }

    if (peca->getCor() != turnoAtual_) {
        cout << "Jogada invalida: Nao e o seu turno para mover esta Peca." << "" << endl;
        return false;
    }

    if (!tabuleiro_.estaVazio(destX, destY)) {
        cout << "Jogada invalida: Posicao de destino ja ocupada." << "" << endl;
        return false;
    }

    int dx = destX - origX;
    int dy = destY - origY;
    int absDx = std::abs(dx);
    int absDy = std::abs(dy);

    if (absDx != absDy) {
        cout << "Jogada invalida: Movimento deve ser diagonal." << "" << endl;
        return false;
    }

    // Jogada normal
    if (absDx == 1) {
        if (!peca->ehDama()) {
            if ((peca->getCor() == Cor::BRANCA && dy < 0) || (peca->getCor() == Cor::PRETA && dy > 0)) {
                cout << "Jogada invalida: Pecas normais so podem mover 'para frente'." << "" << endl;

            }
        }
        return peca->podeMover(dx, dy);
    }

    // Jogada de captura
    if (absDx == 2) {

        int meioX = origX + dx / 2;
        int meioY = origY + dy / 2;
        Peca* pecaCapturada = tabuleiro_.getPeca(meioX, meioY);

        if (pecaCapturada == nullptr) {
            cout << "Jogada invalida: nao ha Peca adversaria para capturar na diagonal." << "" << endl;
            return false;
        }
        if (pecaCapturada->getCor() == peca->getCor()) {
            cout << "Jogada invalida: a Peca e aliada." << "" << endl;
            return false;
        }
        return true;
    }

    if (peca->ehDama()) {

        int stepX = dx > 0 ? 1 : -1;
        int stepY = dy > 0 ? 1 : -1;

        Peca* pecaCapturada = nullptr;
        int numPecasNoCaminho = 0;

        for (int i = 1; i < absDx; i++) {
            int x = origX + i * stepX;
            int y = origY + i * stepY;

            if (tabuleiro_.getPeca(x, y) != nullptr) {
                numPecasNoCaminho++;
                pecaCapturada = tabuleiro_.getPeca(x, y);

                if (numPecasNoCaminho > 1) {
                    cout << "Jogada invalida: Dama nao pode saltar sobre mais de uma Peca." << endl;
                    return false;
                }
            }
        }

        if (numPecasNoCaminho == 1) {
            if (pecaCapturada->getCor() == peca->getCor()) {
                cout << "Jogada invalida: Dama nao pode capturar Peca aliada." << endl;
                return false;
            }
            return true;
        }

        // Número de peças no caminho = 0
        return true;
    }

    cout << "Jogada invalida: Movimento nao permitido." << endl;
    return false;
}

/**
 * @brief método para aplicar uma jogada
 * @param origX Coordenada X da posição de origem
 * @param origY Coordenada Y da posição de origem
 * @param destX Coordenada X da posição de destino
 * @param destY Coordenada Y da posição de destino
 * @details Método que aplica uma jogada no tabuleiro, movendo a peça da posição de origem para a posição de destino.
 */
void Jogo::aplicarJogada(int origX, int origY, int destX, int destY) {
    int dx = destX - origX;
    int dy = destY - origY;
    int absDx = std::abs(dx);

    int stepX = dx > 0 ? 1 : -1;
    int stepY = dy > 0 ? 1 : -1;

    for (int i = 1; i < absDx; i++) {
        int x = origX + i * stepX;
        int y = origY + i * stepY;
        if (tabuleiro_.getPeca(x, y) != nullptr) {
            tabuleiro_.removerPeca(x, y);
            break;
        }
    }

    tabuleiro_.moverPeca(origX, origY, destX, destY);
}

/**
 * @brief método para alternar o turno
 * @details Método que alterna o turno entre os jogadores.
 */
void Jogo::alternarTurno() {
    turnoAtual_ = (turnoAtual_ == Cor::BRANCA) ? Cor::PRETA : Cor::BRANCA;
}

/**
 * @brief método para transformar uma peça em dama
 * @param peca Ponteiro para a peça a ser transformada
 * @param y Coordenada Y da posição da peça
 * @details Método que transforma uma peça em dama se ela alcançar a última linha do tabuleiro.
 */
void Jogo::transformarEmDama(Peca* peca, int y) {
    if (peca && !peca->ehDama()) {
        if (peca->getCor() == Cor::BRANCA && y == TAMANHO_TABULEIRO - 1) {
            cout << "Peca BRANCA coroada: Tornou-se DAMA (B)!" << endl;
            peca->setToDama();
        }
        else if (peca->getCor() == Cor::PRETA && y == 0) {
            cout << "Peca PRETA coroada: Tornou-se DAMA (P)!" << endl;
            peca->setToDama();
        }

    }
}

/**
 * @brief método para verificar se o jogo acabou
 * @details Método que verifica se o jogo acabou, ou seja, se um dos jogadores não possui mais peças.
 */
bool Jogo::jogoAcabou() const {
    int brancas = 0;
    int pretas = 0;

    for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
        for (int y = 0; y < TAMANHO_TABULEIRO; ++y) {
            Peca* peca = tabuleiro_.getPeca(x, y);
            if (peca) {
                if (peca->getCor() == Cor::BRANCA) {
                    brancas++;
                } else {
                    pretas++;
                }
            }
        }
    }
    return (brancas == 0 || pretas == 0);
}

/**
 * @brief método para obter o vencedor
 * @details Método que verifica qual jogador venceu.
 */
Cor Jogo::getVencedor() const {
    int brancas = 0;
    int pretas = 0;

    for (int x = 0; x < TAMANHO_TABULEIRO; x++) {
        for (int y = 0; y < TAMANHO_TABULEIRO; ++y) {
            Peca* peca = tabuleiro_.getPeca(x, y);
            if (peca) {
                if (peca->getCor() == Cor::BRANCA) {
                    brancas++;
                } else {
                    pretas++;
                }
            }
        }
    }

    return (brancas > 0) ? Cor::BRANCA : Cor::PRETA;
}

