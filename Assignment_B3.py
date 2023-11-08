class MemoryPlacementStrategies:
    def __init__(self, processes, memory_blocks) -> None:
        self.processes = processes
        self.memory_blocks = memory_blocks

    def first_fit(self):
        allocation = [-1] * len(self.processes)
        memory = self.memory_blocks

        for i in range(len(self.processes)):
            for j in range(len(memory)):
                if self.processes[i] <= memory[j]:
                    allocation[i] = j
                    memory[j] -= self.processes[i]
                    break
        
        print(allocation)

    def next_fit(self):
        allocation = [-1] * len(self.processes)
        memory = self.memory_blocks
        current_index = 0

        for i in range(len(self.processes)):
            for j in range(current_index , len(memory)):
                if self.processes[i] <= memory[j]:
                    allocation[i] = j
                    memory[j] -= self.processes[i]
                    current_index = (j + 1) % len(memory)
                    break

            for j in range(current_index):
                if self.processes[i] <= memory[j] and allocation[i] == -1:
                    allocation[i] = j
                    memory[j] -= self.processes[i]
                    current_index = (j + 1) % len(memory)
                    break
                    
        print(allocation)

    def best_fit(self):
        allocation = [-1] * len(self.processes)
        memory = self.memory_blocks

        for i in range(len(self.processes)):
            best_fit_index = -1
            for j in range(len(memory)):
                if self.processes[i] <= memory[j]:
                    if best_fit_index == -1 or memory[j] < memory[best_fit_index]:
                        best_fit_index = j
            
            if best_fit_index != -1:
                allocation[i] = best_fit_index
                memory[best_fit_index] -= self.processes[i]
            
        print(allocation)

    def worst_fit(self):
        allocation = [-1] * len(self.processes)
        memory = self.memory_blocks

        for i in range(len(self.processes)):
            worst_fit_index = -1
            for j in range(len(memory)):
                if self.processes[i] <= memory[j]:
                    if worst_fit_index == -1 or memory[j] > memory[worst_fit_index]:
                        worst_fit_index = j

            if worst_fit_index != -1:
                allocation[i] = worst_fit_index
                memory[worst_fit_index] -= self.processes[i]

        print(allocation)       

                    

processes = [212, 417, 112, 426]
memory_blocks = [100, 500, 200, 300, 600]

obj = MemoryPlacementStrategies(processes, memory_blocks)
print("First Fit......")
obj.first_fit()
print()

print("Next Fit.......")
obj.next_fit()
print()

print("Best Fit......")
obj.best_fit()
print()

print("Worst Fit.......")
obj.worst_fit()
print()
