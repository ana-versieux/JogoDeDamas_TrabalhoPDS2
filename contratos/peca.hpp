#ifndef PECA_H
#define PECA_H

enum class Cor {
    BRANCA, PRETA
};

class Peca {
public:
    Peca(int x, int y, Cor cor, bool dama = false);

    void moverPara(int novoX, int novoY);
    bool ehDama() const;
    Cor getCor() const;
    // ... outros getters e setters (se necessário)

    // Métodos para verificar legalidade do movimento
    bool podeMover(int destX, int destY) const;
    bool podeCapturar(int destX, int destY) const;

private:
    int x_;
    int y_;
    Cor cor_;
    bool dama_;
};

#endif // PECA_H