class RingElection:
    def __init__(self, total_process):
        self.total = total_process
        self.state = [True for x in range(self.total)]

    def up(self, pos):
        self.state[pos - 1] = True

    def down(self, pos):
        self.state[pos - 1] = False

    def Election(self, pos):
        if (self.state[pos-1] == False):
            print(f"p{pos} cannot start election as it is down")
            return

        print(f"Election started by p{pos}")

        start = pos - 1
        ptr = (start+1) % self.total
        last_true = start

        while (ptr != start):
            if self.state[ptr] == True:
                print(f"p{last_true+1} sends election message to p{ptr+1}")
                last_true = ptr

            ptr = (ptr+1) % self.total

        print(f"p{last_true+1} sends election message to p{ptr+1}")

        max_process = max(x for x, val in enumerate(self.state) if val == True)
        print(f"Election is won by : p{max_process+1}")
        print(f"p{max_process+1} informs everyone that it is the new coordinator")


algo = RingElection(5)
algo.down(5)
algo.down(2)
# algo.down(4)
# algo.down(3)
algo.Election(1)
