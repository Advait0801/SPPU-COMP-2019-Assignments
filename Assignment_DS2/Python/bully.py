class BullyElection:
    def __init__(self, total_process):
        self.total = total_process
        self.state = [True for x in range(self.total)]

    def up(self, pos):
        self.state[pos - 1] = True

    def down(self, pos):
        self.state[pos - 1] = False

    def Election(self, pos):
        if (pos > self.total):
            return

        if (self.state[pos-1] == False):
            print(f"p{pos} cannot start election as it is down")
            return

        print(f"Election started by p{pos}")

        for i in range(pos, self.total):
            print(f"Election message sent p{pos} to p{i+1}")

        for i in range(pos, self.total):
            if self.state[i] == True:
                print(f"p{i+1} responds OK to p{pos}")

        for i in range(pos, self.total):
            if (self.state[i] == True):
                self.Election(i+1)
                return

        max_process = max(x for x, val in enumerate(self.state) if val == True)
        print(f"Election is won by : p{max_process+1}")
        print(f"p{max_process+1} informs everyone that it is the new coordinator")


algo = BullyElection(5)
algo.down(5)
algo.down(2)
# algo.down(4)
# algo.down(3)
algo.Election(1)