from heapq import heappush, heappop
import copy

def is_safe(board, row, col):
    for i in range(row):
        if board[i] == col or abs(board[i] - col) == abs(i - row):
            return False
    
    return True

def objective_func(board, n):
    cost = 0
    for i in range(n):
        for j in range(i + 1, n):
            if board[i] == board[j] or abs(board[j] - board[i]) == j - 1:
                cost += 1
    
    return cost

def solve(n):
    board = [-1] * n
    queue = []
    heappush(queue, (objective_func(board, n), board))
    flag = False

    while len(queue) != 0:
        curr_node = heappop(queue)
        curr_board = curr_node[1]

        row = 0
        while row < n and curr_board[row] != -1:
            row += 1

        if row == n:
            print("The final positions of queens are as follows...")
            for i in range(n):
                for j in range(n):
                    if curr_board[i] == j:
                        print('Q ', end = ' ')
                    else:
                        print('. ', end = ' ')
                print()
            print()
            flag = True
            return
        
        for col in range(n):
            if is_safe(curr_board, row, col):
                new_board = copy.deepcopy(curr_board)
                new_board[row] = col
                print(new_board)
                new_cost = objective_func(new_board, n)
                heappush(queue, (new_cost, new_board))

    if not flag:
        print("Solution doesnt exist for n = " + str(n))

n = int(input("Enter no of queens: "))
solve(n)    