Geometria Computacional
=======================

Ferramentas criadas para a disciplina de Geometria Computacional.

geraRetas.py
------------

Dependências: python 2 e pyglet.

Script em Python 2 para gerar retas aleatórias. Cada vez que um
caso de teste é criado (gerado um conjunto de retas), uma janela 
mostra como as retas estão no plano bidimensional.
Para cada caso, as coordenadas de cada reta são impressas na
saída padrão no seguinte formato:

```
N
X1a Y1a X1b Y1b
X2a Y2a X2b Y2b
```

N é a quantidade de retas, e as N linhas seguintes possuem as coordenadas
de uma reta, onde se as retas formassem um polígono, o lado à esquerda da
reta representa a parte interior do polígono.
Ao fechar a janela de visualização, é impresso uma linha com o número 0
que representa o caso de teste N = 0, marcando o fim da entrada.

Utilização:

```
python2 gerarRetas.py | tee casosteste.in
```

(Dependendo do sistema pode ser /usr/bin/python ou /usr/bin/python2)

Exemplo de saída:

![gerarRetas.py](http://i.imgur.com/EjmoY.png)

