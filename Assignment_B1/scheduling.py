class Process:
    def __init__(self) -> None:
        self.id = 0
        self.priority = 0
        self.at = 0 #arrival time
        self.bt = 0 #burst time
        self.ct = 0 #completion time
        self.tat = 0 #turn_around time
        self.wt = 0 #wait time
        self.rt = 0 #response time

    def calculate_times(self):
        self.tat = self.ct - self.at
        self.wt = self.tat - self.bt

    def display(self):
        print("Process" + str(self.id).ljust(3) + " priority: " + str(self.priority).ljust(3) + " AT: " + str(self.at).ljust(3) + " BT: " + str(self.bt).ljust(3) + " CT: " + str(self.ct).ljust(3) + " TAT: " + str(self.tat).ljust(3) + " WT: " + str(self.wt).ljust(3) + " RT: " + str(self.rt))


class SchedulingAlgorithms:
    def __init__(self, processes: list[Process]) -> None:
        self.processes = processes    

    def fifo(self):
        ready_queue: list[Process] = []
        ans: list[Process] = []
        time = 0
        current_process: Process = None
        process_count = 0
        is_executing = False

        while process_count < len(self.processes):
            for p in self.processes:
                if p.at == time:
                    ready_queue.append(p)

            if is_executing == True and time == current_process.rt + current_process.bt:
                current_process.ct = time
                current_process.rt -= current_process.at
                current_process.calculate_times()
                ans.append(current_process)
                process_count += 1
                is_executing = False

            if not is_executing and len(ready_queue) > 0:
                current_process = ready_queue.pop(0)
                current_process.rt = time
                is_executing = True

            time += 1

        avg_tat = sum([proc.tat for proc in ans]) / len(self.processes)
        avg_wt = sum([proc.wt for proc in ans]) / len(self.processes)
        for p in ans:
            p.display()
        print("Average TAT: " + str(avg_tat))
        print("Average WT: " + str(avg_wt))
        print()

    def srtf(self):
        burst_times = {}
        for p in self.processes:
            burst_times[p.id] = p.bt

        ready_queue: list[Process] = []
        ans: list[Process] = []
        time = 0
        process_count = 0
        current_process: Process = None
        current_process_remaining_bt = 1e+4
        is_executing = False

        while process_count < len(self.processes):
            for p in self.processes:
                if p.at == time:
                    ready_queue.append(p)

            if is_executing == True and current_process_remaining_bt == 0:
                current_process.ct = time
                current_process.bt = burst_times[current_process.id]
                current_process.calculate_times()
                ans.append(current_process)
                process_count += 1
                is_executing = False

            if is_executing == True and len(ready_queue) > 0:
                min_bt_process = min(ready_queue, key=lambda p:p.bt)
                if min_bt_process.bt < current_process.bt:
                    current_process.bt = current_process_remaining_bt
                    ready_queue.append(current_process)
                    current_process = min_bt_process
                    current_process_remaining_bt = current_process.bt
                    ready_queue.remove(min_bt_process)

            if not is_executing and len(ready_queue) > 0:
                min_bt_process = min(ready_queue, key=lambda p:p.bt)
                ready_queue.remove(min_bt_process)
                current_process = min_bt_process
                current_process.rt = time
                current_process_remaining_bt = current_process.bt
                is_executing = True

            if is_executing == True:
                current_process_remaining_bt -= 1

            time += 1

        avg_tat = sum([proc.tat for proc in ans]) / len(self.processes)
        avg_wt = sum([proc.wt for proc in ans]) / len(self.processes)
        for p in ans:
            p.display()
        print("Average TAT: " + str(avg_tat))
        print("Average WT: " + str(avg_wt))
        print()

    def priority(self):
        ready_queue: list[Process] = []
        ans: list[Process] = []
        time = 0
        process_count = 0
        current_process: Process = None
        is_executing = False

        while process_count < len(self.processes):
            for p in self.processes:
                if p.at == time:
                    ready_queue.append(p)

            if is_executing == True and time == current_process.rt + current_process.bt:
                current_process.rt -= current_process.at
                current_process.ct = time
                current_process.calculate_times()
                process_count += 1
                is_executing = False
                ans.append(current_process)

            if not is_executing and len(ready_queue) > 0:
                current_process = min(ready_queue, key=lambda p:p.priority)
                ready_queue.remove(current_process)
                current_process.rt = time
                is_executing = True

            time += 1

        avg_tat = sum([proc.tat for proc in ans]) / len(self.processes)
        avg_wt = sum([proc.wt for proc in ans]) / len(self.processes)
        for p in ans:
            p.display()
        print("Average TAT: " + str(avg_tat))
        print("Average WT: " + str(avg_wt))
        print()

    def round_robin(self, quantum):
        burst_times = {}
        for p in self.processes:
            burst_times[p.id] = p.bt

        ready_queue: list[Process] = []
        ans: list[Process] = []
        time = 0
        process_count = 0
        current_process: Process = None
        is_executing = False
        current_process_remaining_bt = None
        step = None

        while process_count < len(self.processes):
            for p in self.processes:
                if p.at == time:
                    ready_queue.append(p)

            if is_executing == True and current_process_remaining_bt == 0:
                current_process.ct = time
                current_process_remaining_bt = burst_times[current_process.id]
                current_process.calculate_times()
                process_count += 1
                ans.append(current_process)
                is_executing = False

            if is_executing == True and time == step:
                current_process.bt = current_process_remaining_bt
                ready_queue.append(current_process)
                is_executing = False

            if not is_executing and len(ready_queue) > 0:
                current_process = ready_queue.pop(0)
                current_process.rt = time
                current_process_remaining_bt = current_process.bt
                step = time + quantum
                is_executing = True

            if is_executing == True:
                current_process_remaining_bt -= 1

            time += 1

        avg_tat = sum([proc.tat for proc in ans]) / len(self.processes)
        avg_wt = sum([proc.wt for proc in ans]) / len(self.processes)
        for p in ans:
            p.display()
        print("Average TAT: " + str(avg_tat))
        print("Average WT: " + str(avg_wt))
        print()


burst_times = [6,2,1,9,8]
arrival_times = [0,2,3,4,5]
priorities = [3,1,4,5,2]

processes: list[Process] = []
for i in range(5):
    p = Process()
    p.id = i+1
    p.bt = burst_times[i]
    p.at = arrival_times[i]
    p.priority = priorities[i]
    processes.append(p)

obj = SchedulingAlgorithms(processes=processes)
print("FCFS......")
obj.fifo()
print()

print("Priority....")
obj.priority()
print()

print("SJF......")
obj.srtf()
print()

print("Round Robin......")
obj.round_robin(2)
print()

        

                
