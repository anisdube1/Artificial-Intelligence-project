import sys
from board import *
from moves import *

def print_board(board):
    for row in board:
        print(row,"\n")

if __name__ == "__main__":
    board=[]

    while(1):
        a = input("Enter the command ")
        
        if (a == "init"):
            obj_board = Board(6, board)
            obj_board.initialise()
            print_board(Board.global_board)
            
        elif("put" in a):
            command = a.split()
            if (len(command)!= 4):
                print("Please try Again!!!")
                continue
            color = command[1]
            x = command[2]
            y = command[3]
            if (not color or not x or not y):
                print("Please try again!!!")
                continue
            try:
                curr_board, change = make_move(Board.global_board, color, int(x), int(y))
            except:
                print("Please Try Again!!!")
                continue
            if change == 0:
                print("FORFEIT")
            else:
                Board.global_board = copy.deepcopy(curr_board)
                print_board(Board.global_board)
                
        elif("move" in a):
            command = a.split()
            if (len(command)!= 2):
                print("Please try Again!!!")
                continue
            color = command[1]
            if (color == 'b'):
                x, y =  minmax(color, Board.global_board, 0, 6)
                curr_board, change = make_move(Board.global_board, color, int(x), int(y))
                if change == 0:
                    print("You Won")
                else:
                    Board.global_board = copy.deepcopy(curr_board)
                    print_board(Board.global_board)
            else:
                x, y = minmax(color, Board.global_board, 1, 6)
                curr_board, change = make_move(Board.global_board, color, int(x), int(y))
                if change == 0:
                    print("Computer Won")
                else:
                    Board.global_board = copy.deepcopy(curr_board)
                    print_board(Board.global_board)
                    
        else:
            print("Wrong Option")
