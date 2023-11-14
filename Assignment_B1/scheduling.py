class Process:
    def __init__(self, name) -> None:
        self.name = name
        self.priority = 0
        self.arrival_time = 0
        self.burst_time = 0
        self.completion_time = 0
        self.turn_around_time = 0
        self.wait_time = 0
        self.response_time = 0

    def display(self):
        print("Process " + str(self.name) + " priority: " + str(self.priority) + " AT: " + str(self.arrival_time) + " BT: " + str(self.burst_time) + " CT: " + str(self.completion_time) + " TAT: " + str(self.turn_around_time) + " WT: " + str(self.wait_time) + " RT: " + str(self.response_time))
    

class SchedulingAlgorithms:
    def __init__(self, processes: list[Process]) -> None:
        self.processes = processes
        self.tat = 0
        self.wt = 0

    def first_come_first_serve(self):
        self.wt = 0
        self.tat = 0
        ready_queue: list[Process] = []
        output: list[Process] = []

        time = 0
        is_executing = False
        current_process = self.processes[0]
        n = 0

        while n < len(self.processes):
            for process in self.processes:
                if process.arrival_time == time:
                    ready_queue.append(process)

            if is_executing == True and time == current_process.response_time + current_process.burst_time:
                is_executing = False
                current_process.completion_time = time
                current_process.turn_around_time = current_process.completion_time - current_process.arrival_time
                current_process.wait_time = current_process.turn_around_time - current_process.burst_time
                output.append(current_process)
                n += 1

            if len(ready_queue) != 0 and is_executing == False:
                current_process = ready_queue[0]
                ready_queue.pop(0)
                current_process.response_time = time
                is_executing = True
            
            time += 1
        

        for process in output:
            self.tat += process.turn_around_time
            self.wt += process.wait_time
            process.display()

        print("Average TAT: ", self.tat / len(output))
        print("Average WT: ", self.wt / len(output))

    def round_robin(self, quantum):
        self.wt = 0
        self.tat = 0
        burst_times = {}
        for process in self.processes:
            burst_times[process.name] = process.burst_time

        ready_queue: list[Process]  = []
        output: list[Process] = []
        current_process = self.processes[0]

        time = 0
        is_executing = False
        n = 0
        step = 0
        current_process_remaining_bt = 1000

        while n < len(self.processes):
            for process in self.processes:
                if process.arrival_time == time:
                    ready_queue.append(process)

            if current_process_remaining_bt == 0:
                current_process.response_time -= current_process.arrival_time
                current_process.burst_time = burst_times[process.name]
                current_process.completion_time = time
                current_process.turn_around_time = current_process.completion_time - current_process.arrival_time
                current_process.wait_time = current_process.turn_around_time - current_process.burst_time
                output.append(current_process)
                is_executing = False
                n += 1

                if len(ready_queue) != 0:
                    current_process = ready_queue[0]
                    if current_process.response_time == 0:
                        current_process.response_time = time
                    current_process_remaining_bt = current_process.burst_time
                    step = time + quantum
                    is_executing = True
                    ready_queue.pop(0)

            if is_executing == True:
                if time == step:
                    current_process.burst_time = current_process_remaining_bt
                    ready_queue.append(current_process)

                    if len(ready_queue) != 0:
                        current_process = ready_queue[0]
                        if current_process.response_time == 0:
                            current_process.response_time = time
                        current_process_remaining_bt = current_process.burst_time
                        step = time + quantum
                        is_executing = True
                        ready_queue.pop(0)
            else:
                if len(ready_queue) != 0:
                    current_process = ready_queue[0]
                    current_process_remaining_bt = current_process.burst_time
                    step = time + quantum
                    is_executing = True
                    ready_queue.pop(0)

            if is_executing == True:
                current_process_remaining_bt -= 1
            
            time += 1

        for process in output:
            self.tat += process.turn_around_time
            self.wt += process.wait_time
            process.display()

        print("Average TAT: ", self.tat / len(output))
        print("Average WT: ", self.wt / len(output))

    def priority(self):
        self.wt = 0
        self.tat = 0
        ready_queue: list[Process] = []
        output: list[Process] = []

        time = 0
        is_executing = False
        current_process = self.processes[0]
        n = 0

        while n < len(self.processes):
            for process in self.processes:
                if process.arrival_time == time:
                    ready_queue.append(process)

            if is_executing == True and time == current_process.response_time + current_process.burst_time:
                is_executing = False
                current_process.completion_time = time
                current_process.turn_around_time = current_process.completion_time - current_process.arrival_time
                current_process.wait_time = current_process.turn_around_time - current_process.burst_time
                output.append(current_process)
                n += 1

            if len(ready_queue) != 0 and is_executing == False:
                max_priority = 999
                process_index = 0
                for i in range(len(ready_queue)):
                    if ready_queue[i].priority < max_priority:
                        max_priority = ready_queue[i].priority
                        current_process = ready_queue[i]
                        process_index = i
                current_process.response_time = time
                ready_queue.pop(process_index)
                is_executing = True
            time += 1

        for process in output:
            self.tat += process.turn_around_time
            self.wt += process.wait_time
            process.display()

        print("Average TAT: ", self.tat / len(output))
        print("Average WT: ", self.wt / len(output))

    def smallest_job_first(self):
        self.wt = 0
        self.tat = 0
        burst_times = {}
        for process in self.processes:
            burst_times[process.name] = process.burst_time

        ready_queue: list[Process]  = []
        output: list[Process] = []
        current_process = self.processes[0]

        time = 0
        is_executing = False
        n = 0
        current_process_remaining_bt = 1000

        while n < len(self.processes):
            for process in self.processes:
                if process.arrival_time == time:
                    ready_queue.append(process)

            if current_process_remaining_bt == 0:
                current_process.response_time -= current_process.arrival_time
                current_process.burst_time = burst_times[current_process.name]
                current_process.completion_time = time
                current_process.turn_around_time = current_process.completion_time - current_process.arrival_time
                current_process.wait_time = current_process.turn_around_time - current_process.burst_time
                output.append(current_process)
                n += 1
                is_executing = False

                if len(ready_queue) != 0:
                    ready_queue = sorted(ready_queue, key=lambda p: p.burst_time)
                    if ready_queue[0].response_time == 0:
                        ready_queue[0].response_time = time
                    current_process_remaining_bt = ready_queue[0].burst_time
                    current_process = ready_queue[0]
                    ready_queue.pop(0)
                    is_executing = True
            else:
                if len(ready_queue) != 0:
                    ready_queue = sorted(ready_queue, key=lambda p: p.burst_time)
                    if is_executing == True:
                        if ready_queue[0].burst_time < current_process_remaining_bt:
                            current_process.burst_time = current_process_remaining_bt
                            ready_queue.append(current_process)
                            current_process = ready_queue[0]
                            ready_queue.pop(0)
                            current_process_remaining_bt = current_process.burst_time
                            is_executing = True
                    else:
                        current_process = ready_queue[0]
                        ready_queue.pop(0)
                        current_process_remaining_bt = current_process.burst_time
                        is_executing = True

            if is_executing == True:
                current_process_remaining_bt -= 1
            time += 1

        for process in output:
            self.tat += process.turn_around_time
            self.wt += process.wait_time
            process.display()

        print("Average TAT: ", self.tat / len(output))
        print("Average WT: ", self.wt / len(output))

        

burst_times = [6,2,1,9,8]
arrival_times = [0,2,3,4,5]
priorities = [3,1,4,5,2]

processes: list[Process] = []
for i in range(5):
    name = "P" + str(i+1)
    p = Process(name)
    p.burst_time = burst_times[i]
    p.arrival_time = arrival_times[i]
    p.priority = priorities[i]
    processes.append(p)

obj = SchedulingAlgorithms(processes=processes)
print("FCFS......")
obj.first_come_first_serve()
print()

# print("Priority....")
# obj.priority()
# print()

# print("SJF......")
# obj.smallest_job_first()
# print()

# print("Round Robin......")
# obj.round_robin(2)
# print()
