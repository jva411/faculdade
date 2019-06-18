# João Victor Alves de Oliveira - 473977
# Jonatha Willame de Almeida Oliveira - 428717

CN = "\033[34mo\033[30m"
CD = "\033[34mO\033[30m"
BN = "\033[31m@\033[30m"
BD = "\033[31m&\033[30m"
Vazio = " "
Preto = "#"
Tabuleiro = [[Vazio]*10 for c in range(10)]
posicoes = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J']
jogadorC = []
jogadorB = []
posicoesDeC = []
posicoesDeB = []

# Essa função reseta o tabuleiro, deixando-o na configuração inicial
def zerarTabuleiro():
    global posicoesDeC
    global posicoesDeB
    posicoesDeC = []
    posicoesDeB = []
    pontos = 1
    for i in range(0, 10):
        if i<3:
            for j in range(0, 5):
                Tabuleiro[i][j*2+(i%2)] = CN
                posicoesDeC.append(str(i)+str(j*2+(i%2)))
                Tabuleiro[i][j*2+1-(i%2)] = Preto
        elif i>6:
            for j in range(0, 5):
                Tabuleiro[i][j*2+(i%2)] = BN
                posicoesDeB.append(str(i)+str(j*2+(i%2)))
                Tabuleiro[i][j*2+1-(i%2)] = Preto
        else:
            for j in range(0, 5):
                Tabuleiro[i][j*2+i%2] = Vazio
                Tabuleiro[i][j*2-i%2+1] = Preto
        pontos = pontos%3+1


# Essa função imprimi no terminal o atual estado do tabuleiro, e as mensagens ao lado dele
def imprimirTabuleiro(**kwargs):
    linhas = kwargs.get("linhas", [])
    msgs = kwargs.get("msgs", [])
    possiveisComidas = kwargs.get("possiveisComidas", [[[], []], [[], []]])
    print("    A   B   C   D   E   F   G   H   I   J")
    print("  \033[47m\033[30m\033[1m+"+("---+"*10)+"\033[0;0m")
    for i in range(0, 10):
        print(i, "\033[47m\033[30m\033[1m|", end='')
        for j in range(0, 10):
            c = 0
            printado = False # Flag para saber se essa posição já foi ou não printada, para posteriormente não printá-la novamente
            while c< len(possiveisComidas[0][0]) and not printado: # Vai printar com fundo amarelo as peças que podem comer e o primeiro destino em possível em relação a pedra que pode ser comida
                if i==possiveisComidas[0][0][c] and j==possiveisComidas[0][1][c]:
                    print("\033[42m "+Tabuleiro[i][j]+" \033[47m\033[30m\033[1m|", end='')
                    printado = True
                c += 1
            c = 0
            while c< len(possiveisComidas[1][0]) and not printado: # Vai printar com fundo verde as peças que podem ser comidas
                if i in possiveisComidas[1][0] and j==possiveisComidas[1][1][possiveisComidas[1][0].index(i)]:
                    print("\033[43m "+Tabuleiro[i][j]+" \033[47m\033[30m\033[1m|", end='')
                    printado = True
                c += 1
            if not printado: # Checa se a peça já não foi printada colorida para não printar novamente
                print(" "+Tabuleiro[i][j]+" |", end='')
        print(end="\033[0;0m ")
        if i==0: # Vai printar todas as peças perdidas do jogador C na linha 0
            print("Jogador C: \033[47m", end='')
            for C in jogadorC:
                print(C, end='')
            print(end="\033[0;0m")
        elif i==1: # Vai printar todas as peças perdidas do jogador B na linha 1
            print("Jogador B: \033[47m", end='')
            for B in jogadorB:
                print(B, end='')
            print(end="\033[0;0m")
        elif i in linhas: # Vai printar todas as mensagens passadas pelo parâmetro da função, nas linhas também passadas pelo parâmetro da função, a partir da linha 2
            print(msgs[linhas.index(i)], end='')
        print("")
        print("  \033[47m\033[30m\033[1m"+("+---"*10)+"+\033[0;0m")



# Essa função recebe a posição atual "i0 e j0" da peça "peca", e checa se ela pode comer alguma peça inimiga
def podeComer(i0, j0, peca):
    pecasComiveis = [[], []] # Vai guardar todas as coordenadas onde há uma peça que possa ser comida
    pecasComedoras = [[], []] # Vai guardar todas as coordenadas onde há uma peça que possa comer, e a casa imediatamente posterior à peça que pode ser comida
    if peca==BD or peca==CD:
        for c in range(0, 4):
            for c2 in range(1, 9):
                i00 = i0 + (c2 + 1) * ((-1) ** (c // 2))
                j00 = j0 + (c2 + 1) * ((-1) ** c) # 'i00' e 'j00' são as coordenadas de destino da peça (pulando 1 casa)
                i01 = i0 + c2 * ((-1) ** (c // 2))
                j01 = j0 + c2 * ((-1) ** c) # 'i01' e 'j01' são as coordenadas entre o ponto de partida e o de destino (onde pode haver a peça a ser comida)
                if i00<10 and j00<10 and i00>-1 and j00>-1:
                    if peca==BD:
                        if Tabuleiro[i01][j01]==CN or Tabuleiro[i01][j01]==CD:
                            if Tabuleiro[i00][j00]==Vazio:
                                pecasComiveis[0].append(i01)
                                pecasComiveis[1].append(j01)
                                pecasComedoras[0].append(i0)
                                pecasComedoras[1].append(j0)
                                pecasComedoras[0].append(i00)
                                pecasComedoras[1].append(j00)
                    else:
                        if Tabuleiro[i01][j01]==BN or Tabuleiro[i01][j01]==BD:
                            if Tabuleiro[i00][j00]==Vazio:
                                pecasComiveis[0].append(i01)
                                pecasComiveis[1].append(j01)
                                pecasComedoras[0].append(i0)
                                pecasComedoras[1].append(j0)
                                pecasComedoras[0].append(i00)
                                pecasComedoras[1].append(j00)
        print(pecasComiveis, pecasComedoras)
    else:
        for c in range(0, 4):
            i00 = i0 + 2*((-1)**(c//2))
            j00 = j0 + 2*((-1)**c) # 'i00' e 'j00' são as coordenadas de destino da peça (pulando 1 casa)
            i01 = i0 + ((-1)**(c//2))
            j01 = j0 + ((-1)**c) # 'i01' e 'j01' são as coordenadas entre o ponto de partida e o de destino (onde pode haver a peça a ser comida)
            if i00<10 and j00<10 and i00>-1 and j00>-1:
                if peca==BN:
                    if Tabuleiro[i01][j01]==CN or Tabuleiro[i01][j01]==CD:
                        if Tabuleiro[i00][j00]==Vazio:
                            pecasComiveis[0].append(i01)
                            pecasComiveis[1].append(j01)
                            pecasComedoras[0].append(i0)
                            pecasComedoras[1].append(j0)
                            pecasComedoras[0].append(i00)
                            pecasComedoras[1].append(j00)
                elif peca==CN:
                    if Tabuleiro[i01][j01]==BN or Tabuleiro[i01][j01]==BD:
                        if Tabuleiro[i00][j00]==Vazio:
                            pecasComiveis[0].append(i01)
                            pecasComiveis[1].append(j01)
                            pecasComedoras[0].append(i0)
                            pecasComedoras[1].append(j0)
                            pecasComedoras[0].append(i00)
                            pecasComedoras[1].append(j00)
    return [pecasComiveis, pecasComedoras]




# 'i0', 'j0' representam as coordenadas do peça que vai mover, e 'i1', 'j1' representam as coordenadas de destino da peça
def mover(i0, j0, i1, j1, jogador):
    deltaI = i1-i0
    deltaJ = j1-j0
    # Faz uma primeira validação da jogada, checando se é um movimento na diagonal, se as posições inicial e final estão no tabuleiro e não são iguais, se no destino não há nenhuma peça, e se há uma peça na posição inical 
    if abs(deltaI)==abs(deltaJ) and i0>-1 and j0>-1 and i1<10 and j1<10 and not deltaI==0 and Tabuleiro[i1][j1]==Vazio and not (Tabuleiro[i0][j0] == Vazio and Tabuleiro == Preto):
        deveComer = False # Condição se o jogador que está jogando deve comer alguma peça do adversário
        podeComer2 = False # Condição se a peça que o jogador está jogando pode comer alguma do adversário
        posicoes = posicoesDeC # Assume que quem está jogando é o jogador C e pega as posições de todas as peças do jogador C, e depois checa se na verdade é o jogador B
        peca = CN # Assume que a peça que está sendo movida é uma peça normal do jogador C, e depois checa se é outra
        if jogador=="C":
            if Tabuleiro[i0][j0] == CD:
                peca = CD
        else:
            if Tabuleiro[i0][j0] == BD:
                peca = BD
            else:
                peca = BN
            posicoes = posicoesDeB
        possiveisComidas = [[[], []], [[], []]] # Vai armazendar duas matrizes, sendo a primeira todas as posições que deverão ser printadas de amarelo, e a segunda, todas que deverão ser printadas de verde
        for pos in posicoes: # Vai percorrer todas as peças do jogador, e vai verificar quais que podem comer, adicionando as posições das que podem ser comidas em possiveisComidas2[0] e as das que podem comer + destino em possiveisComidas2[1] no seguinte formato [[[iComivel,iComivel],[jComivel,jComivel]],[[iComedor,iDestino],[jComedor,jDestino]]]
            possiveisComidas2 = podeComer(int(pos[0]), int(pos[1]), peca)
            if len(possiveisComidas2[0][0])>0:
                deveComer = True
                if (str(i0)+str(j0))==pos:
                    podeComer2 = True
                for c in range(0, len(possiveisComidas2[0][0])):
                    possiveisComidas[0][0].append(possiveisComidas2[0][0][c])
                    possiveisComidas[0][1].append(possiveisComidas2[0][1][c])
                for c in range(0, len(possiveisComidas2[1][0])):
                    possiveisComidas[1][0].append(possiveisComidas2[1][0][c])
                    possiveisComidas[1][1].append(possiveisComidas2[1][1][c])
        if peca==CN:
            possiveisComidas.append(moverCN(i0, j0, i1, j1, deveComer, podeComer2))
            return possiveisComidas
        elif peca == CD:
            possiveisComidas.append(moverCD(i0, j0, i1, j1, deveComer, podeComer2))
            return possiveisComidas
        elif peca == BN:
            possiveisComidas.append(moverBN(i0, j0, i1, j1, deveComer, podeComer2))
            return possiveisComidas
        elif peca == BD:
            possiveisComidas.append(moverBD(i0, j0, i1, j1, deveComer, podeComer2))
            return possiveisComidas
    return [-1, -1, 0]

# Essa função serve para tratar o movimento de uma peça normal do jogador C
def moverCN(i0, j0, i1, j1, deveComer, podeComer2):
    deltaI = i1-i0
    deltaJ = j1-j0
    if podeComer2 and abs(deltaI)==2: # Checa se a peça com a qual o jogador tiver jogando pode comer, e se o movimento é um pulo (possível comida)
        meio = Tabuleiro[i0 + deltaI//2][j0 + deltaJ//2] # Pega a peça que está no meio do pulo
        if meio==BN or meio==BD:
            Tabuleiro[i0][j0] = Vazio
            jogadorB.append(meio)
            Tabuleiro[i0 + deltaI//2][j0 + deltaJ//2] = Vazio
            posicoesDeB.remove(str(i0 + deltaI//2) + str(j0 + deltaJ//2))
            if i1==9:
                Tabuleiro[i1][j1] = CD
            else:
                Tabuleiro[i1][j1] = CN
            posicoesDeC.remove(str(i0) + str(j0))
            posicoesDeC.append(str(i1) + str(j1))
            return 2 
    if deveComer: # Isso ocorre caso o movimento não tenha sido de comer, mas poderia ter sido
        return 3
    if deltaI==1: # Isso ocorre se o movimento não foi de comida e nem poderia ter sido
        if i1==9: # Caso ele tenha chegado da última linha, transforma sua peça em dama
            Tabuleiro[i1][j1] = CD
        else:
            Tabuleiro[i1][j1] = CN
        Tabuleiro[i0][j0] = Vazio
        posicoesDeC.remove(str(i0) + str(j0))
        posicoesDeC.append(str(i1) + str(j1))
        return 1
    return 0

# Essa função serve para tratar o movimento da dama do jogador C
def moverCD(i0, j0, i1, j1, deveComer, podeComer2):
    deltaI = i1-i0
    deltaJ = j1-j0
    pecas = 0
    i = 0
    j = 0
    i1 = 1
    i2 = 1
    if deltaI<0:
        i1 = -1
    if deltaJ<0:
        i2 = -1
    for c in range(1, abs(deltaI)+1):
        if Tabuleiro[i0 + c*i1][j0 + c*i2] == CN or Tabuleiro[i0 + c*i1][j0 + c*i2] == CD:
            return 0
        elif Tabuleiro[i0 + c*i1][j0 + c*i2] == BN or Tabuleiro[i0 + c*i1][j0 + c*i2] == BD:
            if pecas==1:
                return 0
            pecas = 1
            i = i0+(c*i1)
            j = j0+(c*i2)
    if deveComer:
        if podeComer2 and pecas==1:
            jogadorB.append(Tabuleiro[i][j])
            posicoesDeB.remove(str(i)+str(j))
            Tabuleiro[i0][j0] = Vazio
            Tabuleiro[i][j] = Vazio
            Tabuleiro[i1][j1] = CD
            posicoesDeC.remove(str(i0) + str(j0))
            posicoesDeC.append(str(i1) + str(j1))
            return 2
        return 3
    Tabuleiro[i0][j0] = Vazio
    Tabuleiro[i1][j1] = CD
    posicoesDeC.remove(str(i0) + str(j0))
    posicoesDeC.append(str(i1) + str(j1))
    return 1

# Essa função serve para tratar o movimento de uma peça normal do jogador B
def moverBN(i0, j0, i1, j1, deveComer, podeComer2):
    deltaI = i1-i0
    deltaJ = j1-j0
    if podeComer2 and abs(deltaI)==2:
        meio = Tabuleiro[i0 + (deltaI//2)][j0 + (deltaJ//2)]
        if meio==CN or meio==CD:
            Tabuleiro[i0][j0] = Vazio
            jogadorC.append(meio)
            Tabuleiro[i0 + (deltaI//2)][j0 + (deltaJ//2)] = Vazio
            posicoesDeC.remove(str(i0 + deltaI//2) + str(j0 + deltaJ//2))
            if i1==0:
                Tabuleiro[i1][j1] = BD
            else:
                Tabuleiro[i1][j1] = BN
            posicoesDeB.remove(str(i0) + str(j0))
            posicoesDeB.append(str(i1) + str(j1))
            return 2
        return 3
    if deveComer:
        return 3
    if deltaI==-1:
        if i1==0:
            Tabuleiro[i1][j1] = BD
        else:
            Tabuleiro[i1][j1] = BN
        Tabuleiro[i0][j0] = Vazio
        posicoesDeB.remove(str(i0) + str(j0))
        posicoesDeB.append(str(i1) + str(j1))
        return 1
    else:
        return 0

# Essa função serve para tratar o movimento da dama do jogador B
def moverBD(i0, j0, i1, j1, deveComer, podeComer2):
    deltaX = i1 - i0
    deltaY = j1 - j0
    pecas = 0
    i = 0
    j = 0
    i1 = 1
    i2 = 1
    if deltaX<0:
        i1 = -1
    if deltaY<0:
        i2 = -1
    for c in range(1, abs(deltaX)+1):
        if Tabuleiro[i0 + c*i1][j0 + c*i2] == BN or Tabuleiro[i0 + c*i1][j0 + c*i2] == BD:
            return 0
        elif Tabuleiro[i0 + c*i1][j0 + c*i2] == CN or Tabuleiro[i0 + c*i1][j0 + c*i2] == CD:
            if pecas==1:
                return 0
            pecas += 1
            i = i0 + c * i1
            j = j0 + c * i2
    if deveComer:
        if podeComer2 and pecas==1:
            jogadorB.append(Tabuleiro[i][j])
            posicoesDeC.remove(str(i)+str(j))
            Tabuleiro[i0][j0] = Vazio
            Tabuleiro[i][j]
            Tabuleiro[i1][j1] = CD
            posicoesDeB.remove(str(i0) + str(j0))
            posicoesDeB.append(str(i1) + str(j1))
            return 2
        return 3
    Tabuleiro[i0][j0] = Vazio
    Tabuleiro[i1][j1] = CD
    posicoesDeB.remove(str(i0) + str(j0))
    posicoesDeB.append(str(i1) + str(j1))
    return 1






import re, sys

def Main():
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
            j0 = posicoes.index(entrada[0][0])
            i0 = int(entrada[0][1])
            j1 = posicoes.index(entrada[1][0])
            i1 = int(entrada[1][1])
            jogada = mover(i0, j0, i1, j1, jogador)
            if jogada[2]>0:
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
                    if jogada[2]<3:
                        if jogada[2]==1:
                            if jogador=="C":
                                jogador = "B"
                            else:
                                jogador = "C"
                        print("\n"*3)
                        imprimirTabuleiro(linhas = [3], msgs = ["Agora é a vez do jogador %s"%jogador])
                    else:
                        print("\n"*3)
                        imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Você deve comer a peça do oponente!"], possiveisComidas = jogada)
            else:
                print("\n"*3)
                imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])
        else:
            print("\n"*3)
            imprimirTabuleiro(linhas = [3, 5], msgs = ["Agora é a vez do jogador %s"%jogador, "Jogada Inválida!"])


Main()