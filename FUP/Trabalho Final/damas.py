Tabuleiro = []
CN = "o"
CD = "O"
BN = "@"
BD = "&"
Vazio = " "
posicoes = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']

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



def imprimirTabuleiro():
    global Tabuleiro
    print("  +-A-+-B-+-C-+-D-+-E-+-F-+-G-+-H-+-I-+-J-+")
    for x in range(0, 10):
        print(x, "| ", end='')
        for y in range(0, 10):
            print(Tabuleiro[x][y]+" | ", end='')
        print("")
        print("  "+("+---"*10)+"+")


def move(x0, y0, x1, y1, player):
    global Tabuleiro
    deltaX = y1-y0
    deltaY = x1-x0
    if abs(deltaX)==abs(deltaY) and x0>-1 and y0>-1 and x1<10 and y1<10 and not deltaX==0:
        if player=="C":
            if Tabuleiro[x0][y0] == CN:
                if deltaY==1 and Tabuleiro[x1][y1]==Vazio:
                    Tabuleiro[x1][y1] = CN
                    Tabuleiro[x0][y0] = Vazio
                    return True
                elif abs(deltaY)==2:
                    meio = Tabuleiro[x0+(deltaY)//2][y0+(deltaX)//2]
                    if meio==BN or meio==BD:
                        Tabuleiro[x0][y0] = Vazio
                        Tabuleiro[x0+(deltaY)//2][y0+(deltaX)//2] = Vazio
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
                if deltaY>0:
                    i2 = -1
                for i in range(1, abs(deltaX)+1):
                    if Tabuleiro[x0+i*i1][y0+i*i2] == CN or Tabuleiro[x0+i*i1][y0+i*i2] == CD:
                        return False
                    elif Tabuleiro[x0+i*i1][y0+i*i2] == BN or Tabuleiro[x0+i*i1][y0+i*i2] == BD:
                        if pecas==1:
                            return False
                        pecas += 1
                        x = x0+i*i1
                        y = y0+i*i2
                if pecas==1:
                    Tabuleiro[x0][y0] = Vazio
                    Tabuleiro[x][y] = Vazio
                    Tabuleiro[x1][y1] = CD
                    return True
        elif player=="B":
            if Tabuleiro[x0][y0] == BN:
                if deltaY==-1 and Tabuleiro[x1][y1]==Vazio:
                    Tabuleiro[x1][y1] = BN
                    Tabuleiro[x0][y0] = Vazio
                    return True
                elif abs(deltaY)==2:
                    meio = Tabuleiro[x0+(deltaY//2)][y0+(deltaX//2)]
                    if meio==CN or meio==CD:
                        Tabuleiro[x0][y0] = Vazio
                        Tabuleiro[x0+(deltaY//2)][y0+(deltaX//2)] = Vazio
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
                if deltaY>0:
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
                    Tabuleiro[x0][y0] = Vazio
                    Tabuleiro[x][y] = Vazio
                    Tabuleiro[x1][y1] = CD
                    return True
    return False












Jogando = True
imprimirTabuleiro()
print("O jogador de cima começa!")
jogador = "C"
while Jogando:
    print("Digite as coordenadas de saida e as de destino separadas por um espaço (Ex: 2A 3B):")
    entrada = input().split()
    y0 = posicoes.index(entrada[0][1])
    x0 = int(entrada[0][0])
    y1 = posicoes.index(entrada[1][1])
    x1 = int(entrada[1][0])
    if move(x0, y0, x1, y1, jogador):
        if jogador=="C":
            jogador = "B"
        else:
            jogador = "C"
        print("\n"*8)
        print("Agora é a vez do jogador " + jogador)
        imprimirTabuleiro()
    else:
        print("Esse movimento é inválido!")