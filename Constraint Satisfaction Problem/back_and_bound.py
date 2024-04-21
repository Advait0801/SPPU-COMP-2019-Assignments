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
config = [ [ 0 for _ in range(N) ] for _ in range(N) ]

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

def print_board(board):
    for row in board:
        print( row )
    print( "===" * 6 )