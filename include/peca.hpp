#ifndef PECA_H
#define PECA_H

enum class Cor {
    BRANCA, PRETA
};

struct Posicao {
    int x;
    int y;
    Posicao(int param_x = 0, int param_y = 0) : x(param_x), y(param_y) {}
};

class Peca {
public:
    Peca(int x, int y, Cor cor, bool dama = false);

    void moverPara(int novoX, int novoY);
    bool ehDama() const;
    Cor getCor() const;
    bool podeMover(int destX, int destY) const;
    bool podeCapturar(int destX, int destY) const;

private:
    Posicao posicao_;
    Cor cor_;
    bool dama_;
};

#endif // PECA_H
