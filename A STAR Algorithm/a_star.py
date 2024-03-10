import copy

NFINITY = 1e + 10

class Puzzle:
    def __init__(self, elements):
        assert(len(elements) == len(elements[0]), "Puzzle must have equal rows and columns")
        self.board = elements
        self.n_dims = len(elements)
        
        for i in range(self.n_dims):
            for j in range(self.n_dims):
                if self.board[i][j] == 0:
                    self.pos = (i, j)
                    break
                
    def display(self):
        for i in range(self.n_dims):
            for j in range(self.n_dims):
                print(self.board[i][j], end = " ")
            print()
        
        

def move(puzzle: Puzzle):
    x, y = puzzle.pos[0], puzzle.pos[1]
    dim = puzzle.n_dims
    possible_pos = []
    
    if x+1 < dim and y < dim:
        possible_pos.append((x+1, y))
    if x < dim and y+1 < dim:
        possible_pos.append((x, y+1))
    if x >= 1 and y >= 0:
        possible_pos.append((x-1, y))
    if x >= 0 and y >= 1:
        possible_pos.append((x, y-1))
        
    new_states = []
    for pos in possible_pos:
        pos_x, pos_y = pos[0], pos[1]
        new_elements = copy.deepcopy(puzzle.board)
        new_elements[pos_x][pos_y], new_elements[x][y] = new_elements[x][y], new_elements[pos_x][pos_y]
        new_states.append(Puzzle(new_elements))
        
    return new_states


def heuristic(init_puzzle: Puzzle, goal_puzzle: Puzzle):
    assert(init_puzzle.n_dims == goal_puzzle.n_dims, "Puzzles must have equal dimensions")
    count_misplaced = 0
    
    for i in range(init_puzzle.n_dims):
        for j in range(init_puzzle.n_dims):
            if init_puzzle.board[i][j] != goal_puzzle.board[i][j]:
                count_misplaced += 1
                
    return count_misplaced


def is_goal(curr_puzzle: Puzzle, goal_puzzle: Puzzle):
    pass   
    