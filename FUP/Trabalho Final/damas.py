Tabuleiro = []
CN = "o"
CD = "O"
BN = "@"
BD = "&"
Vazio = " "
Preto = "#"
posicoes = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
jogadorC = []
jogadorB = []
posicoesDeC = []
posicoesDeB = []

for x in range(0, 10):
    Tabuleiro.append([])
    for y in range(0, 10):
        Tabuleiro[x].append(Vazio)

def zerarTabuleiro():
    for x in range(0, 10):
        if x<3:
            for y in range(0, 5):
                Tabuleiro[x][y*2+(x%2)] = CN
                posicoesDeC.append(str(x)+str(y*2+(x%2)))
                Tabuleiro[x][y*2+1-(x%2)] = Preto
        elif x>6:
            for y in range(0, 5):
                Tabuleiro[x][y*2+(x%2)] = BN
                posicoesDeB.append(str(x)+str(y*2+(x%2)))
                Tabuleiro[x][y*2+1-(x%2)] = Preto
        else:
            for y in range(0, 5):
                Tabuleiro[x][y*2+x%2] = Vazio
                Tabuleiro[x][y*2+x%2-1] = Preto



def imprimirTabuleiro(**kwargs):
    linhas = kwargs.get("linhas", [])
    msgs = kwargs.get("msgs", [])
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
        elif x in linhas:
            print(msgs[linhas.index(x)], end='')
        print("")
        print("  "+("+---"*10)+"+")




def podeComer(x0, y0, peca):
    if peca==BD or peca==CD:
        for i in range(0, 4):
            for i2 in range(1, 9):
                if peca==BD:
                    if Tabuleiro[x0+i2*(-1**(i//2))][y0+(-1**i)]==CN or Tabuleiro[x0+i2*(-1**(i//2))][y0+(-1**i)]==CD:
                        if x0+(i2+1)*(-1**(i//2))<10 and y0+(i2+1)*(-1**i)<10 and Tabuleiro[x0+(i2+1)*(-1**(i//2))][y0+(i2+1)*(-1**i)]==Vazio:
                            return True
                elif peca==CD:
                    if Tabuleiro[x0+i2*(-1**(i//2))][y0+(-1**i)]==BN or Tabuleiro[x0+i2*(-1**(i//2))][y0+(-1**i)]==BD:
                        if x0+(i2+1)*(-1**(i//2))<10 and y0+(i2+1)*(-1**i)<10 and Tabuleiro[x0+(i2+1)*(-1**(i//2))][y0+(i2+1)*(-1**i)]==Vazio:
                            return True
        return False
    else:
        for i in range(0, 4):
            if peca==BN:
                if Tabuleiro[x0+(-1**(i//2))][y0+(-1**i)]==CN or Tabuleiro[x0+(-1**(i//2))][y0+(-1**i)]==CD:
                    if x0+2*(-1**(i//2))<10 and y0+2*(-1**i)<10 and Tabuleiro[x0+2*(-1**(i//2))][y0+2*(-1**i)]==Vazio:
                        return True
            elif peca==CN:
                print(x0, y0, i, (-1)**(i//2), (-1)**i)
                if Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==BN or Tabuleiro[x0+((-1)**(i//2))][y0+((-1)**i)]==BD:
                    if x0+2*((-1)**(i//2))<10 and y0+2*((-1)**i)<10 and Tabuleiro[x0+2*((-1)**(i//2))][y0+2*((-1)**i)]==Vazio:
                        return True
        return False



def mover(x0, y0, x1, y1, player):
    global Tabuleiro
    global jogadorB
    global jogadorC
    global podeComer
    deltaY = y1-y0
    deltaX = x1-x0
    if abs(deltaX)==abs(deltaY) and x0>-1 and y0>-1 and x1<10 and y1<10 and not deltaX==0 and Tabuleiro[x1][y1]==Vazio:
        if player=="C":
            precisaComer = False
            podeComer2 = False
            for pos in posicoesDeC:
                X = int(pos[0])
                Y = int(pos[1])
                peca = CN
                if Tabuleiro[X][Y] == CD:
                    peca = CD
                if podeComer(X, Y, peca):
                    precisaComer = True
                    print(X, Y, peca, x0, y0)
                    if X==x0 and Y==y0:
                        podeComer2 = True
                    exit()
            if Tabuleiro[x0][y0] == CN:
                if podeComer2 and abs(deltaX)==2:
                    meio = Tabuleiro[x0+deltaX//2][y0+deltaY//2]
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
                if precisaComer:
                    return 4
                if deltaX==1:
                    if x1==9:
                        Tabuleiro[x1][y1] = CD
                    else:
                        Tabuleiro[x1][y1] = CN
                    Tabuleiro[x0][y0] = Vazio
                    posicoesDeC.remove(str(x0)+str(y0))
                    posicoesDeC.append(str(x1)+str(y1))
                    return 1
                return 0
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
                        return 0
                    elif Tabuleiro[x0+i*i1][y0+i*i2] == BN or Tabuleiro[x0+i*i1][y0+i*i2] == BD:
                        if pecas==1:
                            return 0
                        pecas = 1
                        x = x0+(i*i1)
                        y = y0+(i*i2)
                if precisaComer:
                    if podeComer2 and pecas==1:
                        jogadorB.append(Tabuleiro[x][y])
                        posicoesDeB.remove(str(x)+str(y))
                        Tabuleiro[x0][y0] = Vazio
                        Tabuleiro[x1][y1] = CD
                        posicoesDeC.remove(str(x0)+str(y0))
                        posicoesDeC.append(str(x1)+str(y1))
                        return 2
                    return 4
                Tabuleiro[x0][y0] = Vazio
                Tabuleiro[x1][y1] = CD
                return 1
        elif player=="B":
            if Tabuleiro[x0][y0] == BN:
                precisaComer = False
                podeComer2 = False
                for pos in posicoesDeC:
                    peca = CN
                    if Tabuleiro[x0][y0] == CD:
                        peca = CD
                    if podeComer(int(pos[0]), int(pos[1]), peca):
                        precisaComer = True
                        if int(pos[0])==x0 and int(pos[1])==y0:
                            podeComer2 = True
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
                    return 4
                if precisaComer:
                    return 4
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
                        return 0
                    elif Tabuleiro[x0+i*i1][y0+i*i2] == CN or Tabuleiro[x0+i*i1][y0+i*i2] == CD:
                        if pecas==1:
                            return 0
                        pecas += 1
                        x = x0+i*i1
                        y = y0+i*i2
                if precisaComer:
                    if podeComer2 and pecas==1:
                        jogadorB.append(Tabuleiro[x][y])
                        posicoesDeC.remove(str(x)+str(y))
                        Tabuleiro[x0][y0] = Vazio
                        Tabuleiro[x1][y1] = CD
                        posicoesDeB.remove(str(x0)+str(y0))
                        posicoesDeB.append(str(x1)+str(y1))
                        return 2
                    return 4
                Tabuleiro[x0][y0] = Vazio
                Tabuleiro[x1][y1] = CD
                posicoesDeB.remove(str(x0)+str(y0))
                posicoesDeB.append(str(x1)+str(y1))
                return 1
    return 0








import re


zerarTabuleiro()
Jogando = True
jogador = "C"
print("\n"*8)
imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
while Jogando:
    print("Digite sua jogada (Ex: A2--B3):")
    entrada = input()
    if bool(re.match("[A-J][0-9]--[A-J][0-9]", entrada)):
        entrada = entrada.split("--")
        y0 = posicoes.index(entrada[0][0])
        x0 = int(entrada[0][1])
        y1 = posicoes.index(entrada[1][0])
        x1 = int(entrada[1][1])
        jogada = mover(x0, y0, x1, y1, jogador)
        if jogada>0:
            if len(jogadorC)==15 or len(jogadorB)==15:
                imprimirTabuleiro(linhas = [3, 5], msgs = ["Parabéns jogador %s você venceu!"%jogador, "O jogo acabou, quer começar novamente? (S/N)"])
                entrada = input().lower()
                while not (entrada=='s' or entrada=='n'):
                    print("Opção inválida! (S/N)")
                    entrada = input().lower()
                if entrada=='n':
                    Jogando = False
                zerarTabuleiro()
                jogador = "C"
                imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
            else:
                if jogada==1:
                    if jogador=="C":
                        jogador = "B"
                    else:
                        jogador = "C"
                elif jogada==4:
                    imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Você precisa comer a peça do oponente!"])
                print("\n"*8)
                imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
        else:
            print("\n"*8)
            imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])
    else:
        print("\n"*8)
        imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])
A2--B3
B7--A6
B3--A4
A6--B5
