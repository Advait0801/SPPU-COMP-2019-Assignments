def is_safe(board, row, col):
    # Check if there is any queen in the same column
    for i in range(row):
        if board[i] == col:
            return False

    # Check upper diagonal on left side
    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i] == j:
            return False

    # Check upper diagonal on right side
    for i, j in zip(range(row, -1, -1), range(col, len(board))):
        if board[i] == j:
            return False

    return True

def solve_n_queens(board, row, n, solutions):
    if row == n:
        solutions.append(list(board))
        return

    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col
            solve_n_queens(board, row + 1, n, solutions)
            board[row] = -1

def n_queens_branch_and_bound(n):
    board = [-1] * n
    solutions = []
    solve_n_queens(board, 0, n, solutions)
    
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
solutions = n_queens_branch_and_bound(n)
print("Number of solutions for", n, "-queens:", len(solutions))
for solution in solutions:
    print_board(solution)