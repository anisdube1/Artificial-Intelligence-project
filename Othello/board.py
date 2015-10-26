import copy

class Board:
    global_board=[]
    def __init__(self, n, board):
        self.n = n
        Board.global_board = board

    def initialise(self):
        for i in range(0,self.n):
            row = []
            for j in range(0,self.n):
                row.append('.')
            Board.global_board.append(row)
        place = int(self.n/2) -1
        Board.global_board[place][place] = 'w'
        Board.global_board[place + 1][place + 1] = 'w'
        Board.global_board[place][place + 1] = 'b'
        Board.global_board[place + 1][place] = 'b'
        return Board.global_board

def count(b1, color):
    cou=0;
    for i in range(0, len(b1)):
        for j in range(0, len(b1)):
            if b1[i][j] == color:
                cou = cou+1
    return cou;

def make_move(curr_board, color, x, y):
    if(color == 'w'):
        m_color = 'b'
    else:
        m_color = 'w'
    board = copy.deepcopy(curr_board)
    change =0
    for i in range(0, len(board)):
        for j in range(0, len(board)):
            #Handling Row case
            if(i==x and board[i][j] == color and abs(y-j) > 1):
                k=j
                c=j
                if(y>k):
                    k=k+1
                    while(k!=y and board[i][k] == m_color):
                        k=k+1
                else:
                    k=k-1
                    while(k!=y and board[i][k] == m_color):
                        k=k-1
                #flip all the colors
                if(k==y):
                    change = 1
                    if(y>c):
                        while(c!=y):
                            board[i][c] = color
                            c= c+1
                    else:
                        while(c!=y):
                            board[i][c] = color
                            c= c-1
                    board[x][y] = color

            # Handling Column Case
            if(j==y and board[i][j] == color and abs(x-i) > 1):
                k=i
                c=i
                if(x>k):
                    k=k+1
                    while(k!=x and board[k][j] == m_color):
                        k=k+1
                else:
                    k=k-1
                    while(k!=x and board[k][j] == m_color):
                        k=k-1
                #flip all the colors
                if(k==x):
                    change = 2
                    if(x>c):
                        #print("X>c")
                        while(c!=x):
                            board[c][j] = color
                            c= c+1
                    else:
                        while(c!=x):
                            board[c][j] = color
                            c= c-1
                    board[x][y] = color

            #Handling Diagonal Case
            if(abs(i-x)== abs(j-y) and i !=x and j!=y and board[i][j] == color and abs(i-x) > 1 and abs(j-y) > 1):
                kx=i
                ky=j
                cx=i
                cy=j
                flag=0
                if(y<ky and x<kx):
                    #print("case1")
                    kx=kx-1
                    ky=ky-1
                    flag=1
                    while(kx!=x and board[kx][ky] == m_color):
                        kx=kx-1
                        ky=ky-1
                elif(y>ky and x<kx):
                    #print("case2")
                    kx=kx-1
                    ky=ky+1
                    flag=2
                    while(kx!=x and board[kx][ky] == m_color):
                        kx=kx-1
                        ky=ky+1
                elif(y<ky and x>kx):
                    #print("case3")
                    kx=kx+1
                    ky=ky-1
                    flag=3
                    while(kx!=x and board[kx][ky] == m_color):
                        kx=kx+1
                        ky=ky-1
                else:
                    #print("case4")
                    kx=kx+1
                    ky=ky+1
                    flag=4
                    while(kx!=x and board[kx][ky] == m_color):
                        kx=kx+1
                        ky=ky+1
                #flip all the colors
                if(kx==x):
                    change = 3
                    if(flag==1):
                        #print("What case1")
                        while(cx!=x):
                            board[cx][cy] = color
                            cx= cx-1
                            cy= cy-1
                    elif(flag==2):
                        #print("What case 2")
                        while(cx!=x):
                            board[cx][cy] = color
                            cx= cx-1
                            cy= cy+1
                    elif(flag==3):
                        #print("What case 3")
                        while(cx!=x):
                            board[cx][cy] = color
                            cx= cx+1
                            cy= cy-1
                    else:
                        #print("What case 4")
                        while(cx!=x):
                            board[cx][cy] = color
                            cx= cx+1
                            cy= cy+1
                    board[x][y] = color
    return board, change






