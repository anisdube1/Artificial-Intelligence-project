from board import *
from Othello import print_board
class move:
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.v = -1

def min_value(color, board, limit):
    if(color == 'w'):
        m_color = 'b'
    else:
        m_color = 'w'
    if(limit == 0):
        ans = count(board, 'b') - count(board, 'w')
        return ans
    v = 100
    many_boards, many_pos = legal_moves(color, board)
    for board in many_boards:
        v = min(max_value(m_color, board, limit-1), v)
    return v


def max_value(color, board, limit):
    if(color == 'w'):
        m_color = 'b'
    else:
        m_color = 'w'
    if(limit == 0):
        ans = count(board, 'b') - count(board, 'w')
        return ans
    v=-100
    many_boards, many_pos = legal_moves(color, board)
    for board, pos in zip(many_boards, many_pos):
        v = max(min_value(m_color, board, limit-1), v)
    return v

def minmax(color, board, flag, limit):
    gmin = 100
    gmax = -100
    gx =-1
    gy=-1
    if(color == 'w'):
        m_color = 'b'
    else:
        m_color = 'w'
    many_boards, many_pos = legal_moves(color, board)
    print("Making Move for" ,color)
    for board, pos in zip(many_boards, many_pos):
        print("Considering", "(", pos.x, ",", pos.y ,")")
        # For white color move
        if flag == 1:
            #print("In Flag =1")
            v = min_value(m_color, board, limit-1)
            #print("Min Value", v)
            if(v > gmax):
                gx = pos.x
                gy = pos.y
                gmax =v
        else:
            v = max_value(m_color, board, limit-1)
            if(v < gmin):
                gx = pos.x
                gy = pos.y
                gmin =v
        print(" Minmax Value", v)
    return gx, gy

def legal_moves(color, current_board):
    list_boards = []
    mov=[]
    if(color == 'w'):
        m_color = 'b'
    else:
        m_color = 'w'
    board = copy.deepcopy(current_board)
    for i in range(0, len(board)):
        for j in range(0, len(board)):
           if board[i][j] == '.':
               initial_count = count(board, m_color)
               boa, chan = make_move(board,color, i, j)
               final_count = count(boa, m_color)
               if(initial_count - final_count >=1):
                    mov.append(move(i, j))
                    list_boards.append(boa)
    return list_boards, mov