"""
N-queens as a CSP (Constraint Satisfaction Problem)
and solving it with branch-and-bound

Branch and bound technique
* Limits the search space
* Through an estimate of the
* Upper bound or Lower bound
"""

N = 4

# Initial configuration
config = [[ 0 for _ in range(N)] for _ in range(N)]

def validate_configuration(configuration, row, col):
    # Check along horizontal axis
    for x in range(col):
        if configuration[row][x] == 1:
            return False
        
    for (x, y) in zip(range(row, -1, -1), range(col, -1, -1)):
        if configuration[x][y] == 1:
            return False
        
    for (x, y) in zip(range(row, N), range(col, -1, -1)):
        if configuration[x][y] == 1:
            return False
        
    return True

def display_board(board):
    for row in board:
        print( row )
    print( "===" * 6 )

def n_queens_algorithm(configuration, col):
    if col == N:
        display_board(config)
        return True
    
    for i in range(N):
        if validate_configuration(configuration, i, col):
            config[i][col] = 1
            if n_queens_algorithm(configuration, col + 1):
                return True
            config[i][col] = 0
            
    return False


res = n_queens_algorithm(config, 0)
print(res)