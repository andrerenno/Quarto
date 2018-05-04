# Quarto
Quarto é um jogo de tabuleiro criado pelo matemático Blaise Müller em 1991, o jogo consiste de um tabuleiro 4x4 e 16 peças únicas  com 4 características binárias (alta ou baixa, azul ou vermelha, etc.). Durante o jogo, os jogadores se alternam em colocar a peça que o outro jogador escolheu e em seguida escolher uma peça, e o ganhador é o que puser a peça que forma uma fileira com uma característica igual (todas altas, por exemplo).

# Projeto
Esse projeto é uma implementação na linguagem C do jogo Quarto, feita por André Rennó de Campos (Nº USP 10298864) para o curso SSC0600 - Introdução à Ciência da Computação I.
No projeto, as peças foram substituidas por números de 0 a 15 (que podem ser representados em hexadecimal, decimal e binário) e suas características são os bits de cada número. Para ganhar, o jogador deve completar uma fileira em que todos os bits de determinada posição são iguais, por exemplo 10**1**0, 11**1**0, 00**1**0, 01**1**1, em que todos os terceiros bits (em negrito) são iguais.

Para compilar e executar o programa, é necessária a livraria *ncurses* no linux ou *pdcurses* no windows
