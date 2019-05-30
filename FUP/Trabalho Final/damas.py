Tabuleiro = []
CN = "\033[34mo\033[30m"
CD = "\033[34mO\033[30m"
BN = "\033[31m@\033[30m"
BD = "\033[31m&\033[30m"
Vazio = " "
Preto = "#"
posicoes = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
jogadorC = []
jogadorB = []
posicoesDeC = []
posicoesDeB = []

import time

for x in range(0, 10):
    Tabuleiro.append([])
    for y in range(0, 10):
        Tabuleiro[x].append(Vazio)

def zerarTabuleiro():
    global posicoesDeC
    global posicoesDeB
    posicoesDeC = []
    posicoesDeB = []
    pontos = 1
    for x in range(0, 10):
        if x<3:
            for y in range(0, 5):
                Tabuleiro[x][y*2+(x%2)] = CN
                posicoesDeC.append(str(x)+str(y*2+(x%2)))
                Tabuleiro[x][y*2+1-(x%2)] = Preto
                imprimirTabuleiro(linhas = [3], msgs=["Caregando"+("."*pontos)])
                time.sleep(0.05)
        elif x>6:
            for y in range(0, 5):
                Tabuleiro[x][y*2+(x%2)] = BN
                posicoesDeB.append(str(x)+str(y*2+(x%2)))
                Tabuleiro[x][y*2+1-(x%2)] = Preto
                imprimirTabuleiro(linhas = [3], msgs=["Caregando"+("."*pontos)])
                time.sleep(0.05)
        else:
            for y in range(0, 5):
                Tabuleiro[x][y*2+x%2] = Vazio
                Tabuleiro[x][y*2+x%2-1] = Preto
                imprimirTabuleiro(linhas = [3], msgs=["Caregando"+("."*pontos)])
                time.sleep(0.05)
        pontos = pontos%3+1



def imprimirTabuleiro(**kwargs):
    linhas = kwargs.get("linhas", [])
    msgs = kwargs.get("msgs", [])
    print("    A   B   C   D   E   F   G   H   I   J")
    print("  \033[47m\033[30m\033[1m+"+("---+"*10)+"\033[0;0m")
    for x in range(0, 10):
        print(x, "\033[47m\033[30m\033[1m|", end='')
        for y in range(0, 10):
            print(" "+Tabuleiro[x][y]+" |", end='')
        print(end="\033[0;0m ")
        if x==0:
            print("Jogador C: \033[47m", end='')
            for C in jogadorC:
                print(C, end='')
            print(end="\033[0;0m")
        elif x==1:
            print("Jogador B: \033[47m", end='')
            for B in jogadorB:
                print(B, end='')
            print(end="\033[0;0m")
        elif x in linhas:
            print(msgs[linhas.index(x)], end='')
        print("")
        print("  \033[47m\033[30m\033[1m"+("+---"*10)+"+\033[0;0m")




def podeComer(x0, y0, peca):
    if peca==BD or peca==CD:
        for i in range(0, 4):
            for i2 in range(1, 9):
                if x0+(i2+1)*((-1)**(i//2))<10 and y0+(i2+1)*((-1)**i)<10 and x0+(i2+1)*((-1)**(i//2))>-1 and y0+(i2+1)*((-1)**i)>-1:   
                    if peca==BD:
                        if Tabuleiro[x0+i2*((-1)**(i//2))][y0+i2((-1)**i)]==CN or Tabuleiro[x0+i2*((-1)**(i//2))][y0+i2((-1)**i)]==CD:
                            if Tabuleiro[x0+(i2+1)*((-1)**(i//2))][y0+(i2+1)*((-1)**i)]==Vazio:
                                return True
                    elif peca==CD:
                        if Tabuleiro[x0+i2*((-1)**(i//2))][y0+i2*((-1)**i)]==BN or Tabuleiro[x0+i2*((-1)**(i//2))][y0+i2*((-1)**i)]==BD:
                            if Tabuleiro[x0+(i2+1)*((-1)**(i//2))][y0+(i2+1)*((-1)**i)]==Vazio:
                                return True
        return False
    else:
        for i in range(0, 4):
            if x0+2*((-1)**(i//2))<10 and y0+2*((-1)**i)<10 and x0+2*((-1)**(i//2))>-1 and y0+2*((-1)**i)>-1:
                if peca==BN:
                    if Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==CN or Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==CD:
                        if Tabuleiro[x0+2*((-1)**(i//2))][y0+2*((-1)**i)]==Vazio:
                            return True
                elif peca==CN:
                    if Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==BN or Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==BD:
                        if Tabuleiro[x0+2*((-1)**(i//2))][y0+2*((-1)**i)]==Vazio:
                            return True
        return False




# 'x0', 'y0' representam as coordenadas do peça que vai mover, e 'x1', 'y1' representam as coordenadas de destino da peça
def mover(x0, y0, x1, y1, jogador):
    deltaY = y1-y0
    deltaX = x1-x0
    if abs(deltaX)==abs(deltaY) and x0>-1 and y0>-1 and x1<10 and y1<10 and not deltaX==0 and Tabuleiro[x1][y1]==Vazio:
        deveComer = False
        podeComer2 = False
        posicoes = posicoesDeC
        if jogador=="B":
            posicoes = posicoesDeB
        for pos in posicoes:
            peca = CN
            if jogador=="C":
                if Tabuleiro[x0][y0] == CD:
                    peca = CD
            else:
                if Tabuleiro[x0][y0] == BD:
                    peca = BD
                else:
                    peca = BN
            if podeComer(int(pos[0]), int(pos[1]), peca):
                deveComer = True
                if int(pos[0])==x0 and int(pos[1])==y0:
                    podeComer2 = True
        if jogador=="C":
            if Tabuleiro[x0][y0] == CN:
                return moverCN(x0, y0, x1, y1, deveComer, podeComer2)
            elif Tabuleiro[x0][y0] == CD:
                return moverCD(x0, y0, x1, y1, deveComer, podeComer2)
        elif jogador=="B":
            if Tabuleiro[x0][y0] == BN:
                return moverBN(x0, y0, x1, y1, deveComer, podeComer2)
            elif Tabuleiro[x0][y0] == BD:
                return moverBD(x0, y0, x1, y1, deveComer, podeComer2)
    return 0

# Essa função serve para tratar o movimento de uma peça normal do jogador C
def moverCN(x0, y0, x1, y1, deveComer, podeComer2):
    deltaX = x1-x0
    deltaY = y1-y0
    if podeComer2 and abs(deltaX)==2: # Checa se a peça com a qual o jogador tiver jogando pode comer, e se o movimento é um pulo (possível comida)
        meio = Tabuleiro[x0+deltaX//2][y0+deltaY//2] # Pega a peça que está no meio do pulo
        if meio==BN or meio==BD:
            Tabuleiro[x0][y0] = Vazio
            jogadorB.append(meio)
            Tabuleiro[x0+deltaX//2][y0+deltaY//2] = Vazio
            posicoesDeB.remove(str(x0+deltaX//2)+str(y0+deltaY//2))
            if x1==9:
                Tabuleiro[x1][y1] = CD
            else:
                Tabuleiro[x1][y1] = CN
            posicoesDeC.remove(str(x0)+str(y0))
            posicoesDeC.append(str(x1)+str(y1))
            return 2 
    if deveComer: # Isso ocorre caso o movimento não tenha sido de comer, mas poderia ter sido
        return 3
    if deltaX==1: # Isso ocorre se o movimento não foi de comida e nem poderia ter sido
        if x1==9:
            Tabuleiro[x1][y1] = CD
        else:
            Tabuleiro[x1][y1] = CN
        Tabuleiro[x0][y0] = Vazio
        posicoesDeC.remove(str(x0)+str(y0))
        posicoesDeC.append(str(x1)+str(y1))
        return 1
    return 0

# Essa função serve para tratar o movimento da dama do jogador C
def moverCD(x0, y0, x1, y1, deveComer, podeComer2):
    deltaX = x1-x0
    deltaY = y1-y0
    pecas = 0
    x = 0
    y = 0
    i1 = 1
    i2 = 1
    if deltaX<0:
        i1 = -1
    if deltaY<0:
        i2 = -1
    for i in range(1, abs(deltaX)+1):
        if Tabuleiro[x0+i*i1][y0+i*i2] == CN or Tabuleiro[x0+i*i1][y0+i*i2] == CD:
            return 0
        elif Tabuleiro[x0+i*i1][y0+i*i2] == BN or Tabuleiro[x0+i*i1][y0+i*i2] == BD:
            if pecas==1:
                return 0
            pecas = 1
            x = x0+(i*i1)
            y = y0+(i*i2)
    if deveComer:
        if podeComer2 and pecas==1:
            jogadorB.append(Tabuleiro[x][y])
            posicoesDeB.remove(str(x)+str(y))
            Tabuleiro[x0][y0] = Vazio
            Tabuleiro[x][y] = Vazio
            Tabuleiro[x1][y1] = CD
            posicoesDeC.remove(str(x0)+str(y0))
            posicoesDeC.append(str(x1)+str(y1))
            return 2
        return 3
    Tabuleiro[x0][y0] = Vazio
    Tabuleiro[x1][y1] = CD
    posicoesDeC.remove(str(x0)+str(y0))
    posicoesDeC.append(str(x1)+str(y1))
    return 1

# Essa função serve para tratar o movimento de uma peça normal do jogador B
def moverBN(x0, y0, x1, y1, deveComer, podeComer2):
    deltaX = x1-x0
    deltaY = y1-y0
    if podeComer2 and abs(deltaX)==2:
        meio = Tabuleiro[x0+(deltaX//2)][y0+(deltaY//2)]
        if meio==CN or meio==CD:
            Tabuleiro[x0][y0] = Vazio
            jogadorC.append(meio)
            Tabuleiro[x0+(deltaX//2)][y0+(deltaY//2)] = Vazio
            posicoesDeC.remove(str(x0+deltaX//2)+str(y0+deltaY//2))
            if x1==0:
                Tabuleiro[x1][y1] = BD
            else:
                Tabuleiro[x1][y1] = BN
            posicoesDeB.remove(str(x0)+str(y0))
            posicoesDeB.append(str(x1)+str(y1))
            return 2
        return 3
    if deveComer:
        return 3
    if deltaX==-1:
        if x1==0:
            Tabuleiro[x1][y1] = BD
        else:
            Tabuleiro[x1][y1] = BN
        Tabuleiro[x0][y0] = Vazio
        posicoesDeB.remove(str(x0)+str(y0))
        posicoesDeB.append(str(x1)+str(y1))
        return 1
    else:
        return 0

# Essa função serve para tratar o movimento da dama do jogador B
def moverBD(x0, y0, x1, y1, deveComer, podeComer):
    deltaX = x1-x0
    deltaY = y1-y0
    pecas = 0
    x = 0
    y = 0
    i1 = 1
    i2 = 1
    if deltaX<0:
        i1 = -1
    if deltaY<0:
        i2 = -1
    for i in range(1, abs(deltaX)+1):
        if Tabuleiro[x0+i*i1][y0+i*i2] == BN or Tabuleiro[x0+i*i1][y0+i*i2] == BD:
            return 0
        elif Tabuleiro[x0+i*i1][y0+i*i2] == CN or Tabuleiro[x0+i*i1][y0+i*i2] == CD:
            if pecas==1:
                return 0
            pecas += 1
            x = x0+i*i1
            y = y0+i*i2
    if deveComer:
        if podeComer2 and pecas==1:
            jogadorB.append(Tabuleiro[x][y])
            posicoesDeC.remove(str(x)+str(y))
            Tabuleiro[x0][y0] = Vazio
            Tabuleiro[x][y]
            Tabuleiro[x1][y1] = CD
            posicoesDeB.remove(str(x0)+str(y0))
            posicoesDeB.append(str(x1)+str(y1))
            return 2
        return 3
    Tabuleiro[x0][y0] = Vazio
    Tabuleiro[x1][y1] = CD
    posicoesDeB.remove(str(x0)+str(y0))
    posicoesDeB.append(str(x1)+str(y1))
    return 1






import re
import sys

entradas = []
entradaI = 0
offline = False
if len(sys.argv)>1:
    offline = True
    with open(sys.argv[1], 'r') as f:
        entradas = f.read().split("\n")

zerarTabuleiro()
Jogando = True
jogador = "C"
print("\n"*3)
imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
while Jogando:
    print("Digite sua jogada (Ex: A2--B3):")
    entrada = ''
    if offline:
        entrada = entradas[entradaI].upper()
        entradaI += 1
    else:
        entrada = input().upper()
    if bool(re.match("[A-J][0-9]--[A-J][0-9]", entrada)):
        entrada = entrada.split("--")
        y0 = posicoes.index(entrada[0][0])
        x0 = int(entrada[0][1])
        y1 = posicoes.index(entrada[1][0])
        x1 = int(entrada[1][1])
        jogada = mover(x0, y0, x1, y1, jogador)
        if jogada>0:
            if len(posicoesDeC)==0 or len(posicoesDeB)==0:
                print("\n"*3)
                imprimirTabuleiro(linhas = [3, 5, 6], msgs = ["Parabéns jogador %s você venceu!"%jogador, "O jogo acabou, você quer começar", "novamente? (S/N)"])
                if offline:
                    entrada = entradas[entradaI].lower()
                    entradaI += 1
                else:
                    entrada = input().lower()
                while not (entrada=='s' or entrada=='n'):
                    print("\n"*3)
                    imprimirTabuleiro(linhas = [3, 5, 6, 8], msgs = ["Parabéns jogador %s você venceu!"%jogador, "O jogo acabou, você quer começar", "novamente? (S/N)", " "*8+"Opção Inválida!"])
                    if offline:
                        entrada = entradas[entradaI].lower()
                        entradaI += 1
                    else:
                        entrada = input().lower()
                if entrada=='n':
                    Jogando = False
                zerarTabuleiro()
                jogador = "C"
                imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
            else:
                if jogada<3:
                    if jogada==1:
                        if jogador=="C":
                            jogador = "B"
                        else:
                            jogador = "C"
                    print("\n"*3)
                    imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
                else:
                    print("\n"*3)
                    imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Você deve comer a peça do oponente!"])
        else:
            print("\n"*3)
            imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])
    else:
        print("\n"*3)
        imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])