O arquivo “tabuleiro.hpp” define a classe “Tabuleiro”, que representa o tabuleiro fixo de 8x8 casas do jogo. Ele armazena as peças em uma matriz e oferece métodos para adicionar, remover, mover e acessar peças, além de verificar se uma posição está vazia ou inválida. O método “desenharTabuleiro()” exibe o estado atual do jogo e o método “inicializarCasas()” prepara o tabuleiro para iniciar outra jogada. 

O arquivo “peca.hpp” contém a classe “Peca”, que representa cada peça individualmente. Nela está armazenado a posição, cor (branca ou preta) e se é uma dama. Possui métodos para mover, promover a dama, consultar posição e cor, e verificar se o movimento é permitido. A estrutura “Posicao” ajuda no controle das coordenadas. As cores das peças também são usadas para determinar os dois lados do jogo.

O arquivo “jogo.hpp” define a classe “Jogo”, que controla a lógica da partida. É responsável por iniciar o jogo, processar e validar jogadas, alternar turnos, promover peças e verificar o fim da partida. Um objeto “Tabuleiro” é usado internamente e controla o turno atual e o estado do jogo, se está ativo ou encerrado. 

O Makefile foi criado para compilar os arquivos “peca.cpp”, “tabuleiro.cpp”, “jogo.cpp” e “main.cpp” para gerar o executável damas. O alvo “all” compila o programa e remove os arquivos temporários, enquanto o alvo “run” recompila, limpa a tela e executa o jogo. 

O Doxygen foi usado para gerar a documentação automática do código. 
