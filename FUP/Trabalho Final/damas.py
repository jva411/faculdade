Tabuleiro = []
CN = "o"
CD = "O"
BN = "@"
BD = "&"
Vazio = " "
posicoes = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
jogadorC = []
jogadorB = []

for x in range(0, 10):
    Tabuleiro.append([])
    for y in range(0, 10):
        Tabuleiro[x].append(Vazio)

for x in range(0, 10):
    if x<3:
        for y in range(0, 5):
            Tabuleiro[x][y*2+(x%2)] = CN
    elif x>6:
        for y in range(0, 5):
            Tabuleiro[x][y*2+(x%2)] = BN



def imprimirTabuleiro(show, final, vencedor):
    global Tabuleiro
    print("  +-A-+-B-+-C-+-D-+-E-+-F-+-G-+-H-+-I-+-J-+")
    for x in range(0, 10):
        print(x, "| ", end='')
        for y in range(0, 10):
            print(Tabuleiro[x][y]+" | ", end='')
        if x==0:
            print("Jogador C: ", end='')
            for C in jogadorC:
                print(C, end='')
        elif x==1:
            print("Jogador B: ", end='')
            for B in jogadorB:
                print(B, end='')
        elif x==3:
            if show:
                print("Esse movimento é inválido!", end='')
            elif final:
                print("Parabéns jogador %s você venceu!"%(vencedor), end='')
        elif x==5 and final:
            print("O jogo acabou, quer começar novamente? (S/N)", end='')
        print("")
        print("  "+("+---"*10)+"+")


def move(x0, y0, x1, y1, player):
    global Tabuleiro
    global jogadorB
    global jogadorC
    deltaY = y1-y0
    deltaX = x1-x0
    if abs(deltaX)==abs(deltaY) and x0>-1 and y0>-1 and x1<10 and y1<10 and not deltaX==0 and Tabuleiro[x1][y1]==Vazio:
        if player=="C":
            if Tabuleiro[x0][y0] == CN:
                if deltaX==1:
                    Tabuleiro[x1][y1] = CN
                    Tabuleiro[x0][y0] = Vazio
                    return True
                elif abs(deltaX)==2:
                    meio = Tabuleiro[x0+(deltaX)//2][y0+(deltaY)//2]
                    if meio==BN or meio==BD:
                        Tabuleiro[x0][y0] = Vazio
                        jogadorB.append(meio)
                        Tabuleiro[x0+(deltaX)//2][y0+(deltaY)//2] = Vazio
                        Tabuleiro[x1][y1] = CN
                        return True 
            elif Tabuleiro[x0][y0] == CD:
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
                        return False
                    elif Tabuleiro[x0+i*i1][y0+i*i2] == BN or Tabuleiro[x0+i*i1][y0+i*i2] == BD:
                        if pecas==1:
                            return False
                        pecas = 1
                        x = x0+(i*i1)
                        y = y0+(i*i2)
                if pecas==1:
                    jogadorB.append(Tabuleiro[x][y])
                    Tabuleiro[x][y] = Vazio
                Tabuleiro[x0][y0] = Vazio
                Tabuleiro[x1][y1] = CD
                return True
        elif player=="B":
            if Tabuleiro[x0][y0] == BN:
                if deltaX==-1:
                    Tabuleiro[x1][y1] = BN
                    Tabuleiro[x0][y0] = Vazio
                    return True
                elif abs(deltaY)==2:
                    meio = Tabuleiro[x0+(deltaX//2)][y0+(deltaY//2)]
                    if meio==CN or meio==CD:
                        Tabuleiro[x0][y0] = Vazio
                        jogadorC.append(meio)
                        Tabuleiro[x0+(deltaX//2)][y0+(deltaY//2)] = Vazio
                        Tabuleiro[x1][y1] = BN
                        return True
            elif Tabuleiro[x0][y0] == BD:
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
                        return False
                    elif Tabuleiro[x0+i*i1][y0+i*i2] == CN or Tabuleiro[x0+i*i1][y0+i*i2] == CD:
                        if pecas==1:
                            return False
                        pecas += 1
                        x = x0+i*i1
                        y = y0+i*i2
                if pecas==1:
                    jogadorC.append(Tabuleiro[x][y])
                    Tabuleiro[x][y] = Vazio
                Tabuleiro[x0][y0] = Vazio
                Tabuleiro[x1][y1] = CD
                return True
    return False










import re


Jogando = True
jogador = "C"
print("\n"*8)
imprimirTabuleiro(False, False, jogador)
print("O jogador de cima começa!")
while Jogando:
    print("Digite as coordenadas de saida e as de destino separadas por um espaço (Ex: 2A 3B):")
    entrada = input()
    if bool(re.match("[0-9][A-J] [0-9][A-J]", entrada)):
        entrada = entrada.split()
        y0 = posicoes.index(entrada[0][1])
        x0 = int(entrada[0][0])
        y1 = posicoes.index(entrada[1][1])
        x1 = int(entrada[1][0])
        if move(x0, y0, x1, y1, jogador):
            if len(jogadorC)==15 or len(jogadorB)==15:
                imprimirTabuleiro(False, True, jogador)
                entrada = input().lower()
                while not (entrada=='s' or entrada=='n'):
                    print("Opção inválida! (S/N)")
                    entrada = input().lower()
                if entrada=='n':
                    Jogando = False
            else:
                if jogador=="C":
                    jogador = "B"
                else:
                    jogador = "C"
                print("\n"*8)
                print("Agora é a vez do jogador " + jogador)
                imprimirTabuleiro(False, False, jogador)
        else:
            print("\n"*8)
            imprimirTabuleiro(True, False, jogador)
    else:
        print("\n"*8)
        imprimirTabuleiro(True, False, jogador)