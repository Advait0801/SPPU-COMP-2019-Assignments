class Job:
    def __init__(self, id, profit, deadline):
        self.id = id
        self.profit = profit
        self.deadline = deadline

    def display(self):
        print("Job ---->   id = " + str(self.id) + ", deadline = " + str(self.deadline) + ", profit = " + str(self.profit))


def job_scheduling(jobs: list[Job]):
    for i in range(len(jobs)):
        j = i

        while jobs[j].profit > jobs[j-1].profit and j > 0:
            temp = jobs[j]
            jobs[j] = jobs[j-1]
            jobs[j-1] = temp
            j -= 1

    max_deadline = max([job.deadline for job in jobs])
    slot_status = [True for i in range(max_deadline)]
    max_profit_seq = []
    for job in jobs:
        for i in range(job.deadline - 1, -1, -1):
            if slot_status[i] == True:
                slot_status[i] = False
                max_profit_seq.append(job)
                break
    
    for job in max_profit_seq:
        job.display()
    max_profit = sum([job.profit for job in max_profit_seq])
    return max_profit    


jobs = [
    Job( 1 , 20 , 2 ) , 
    Job( 2 , 15 , 2 ) , 
    Job( 3 , 10 , 1 ) , 
    Job( 4 , 5 , 3 ) , 
    Job( 5 , 1 , 3 )
]
max_profit = job_scheduling( jobs )
print( f"Max profit is {max_profit}" )

