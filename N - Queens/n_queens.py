def is_safe(board, row, col):
    for i in range(row):
        if board[i] == col or abs(board[i] - col) == abs(i - row):
            return False
        
    return True

def solve_n_queens(solutions, board, row, n):
    if row == n:
        solutions.append(list(board))
        return

    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col
            solve_n_queens(solutions, board, row + 1, n)
            board[row] = -1  # backtrack

def n_queens_backtracking(n):
    solutions = []
    board = [-1] * n
    solve_n_queens(solutions, board, 0, n)
    
    return solutions

def print_board(board):
    n = len(board)
    for i in range(n):
        for j in range(n):
            if board[i] == j:
                print("Q ", end="")
            else:
                print(". ", end="")
        print()
    print()


n = 4
solutions = n_queens_backtracking(n)
print("Number of solutions for", n, "-queens:", len(solutions))
for solution in solutions:
    print_board(solution)