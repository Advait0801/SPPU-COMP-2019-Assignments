class PageReplacementAlgorithms:
    def __init__(self, page_numbers, max_num_frames) -> None:
        self.page_numbers = page_numbers
        self.max_num_frames = max_num_frames

    def first_in_first_out(self):
        dq = []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(dq)

            if self.page_numbers[i] not in dq:
                page_fault_count += 1
                if len(dq) == self.max_num_frames:
                    dq.pop(0)
                dq.append(self.page_numbers[i])
            
        return page_fault_count / len(self.page_numbers)
    
    def least_recently_used(self):
        v , ages = [], []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(v)  

            for j in range(len(ages)):
                ages[j] += 1

            if self.page_numbers[i] not in v:
                page_fault_count += 1
                if len(v) == self.max_num_frames:
                    max_index = ages.index(max(ages))
                    ages.pop(max_index)
                    v.pop(max_index)
                    v.insert(max_index, self.page_numbers[i])
                    ages.insert(max_index, 0)
                else:
                    v.insert(0, self.page_numbers[i])
                    ages.insert(0, 0)
            else:
                index = v.index(self.page_numbers[i])
                ages[index] = 0

        return page_fault_count / len(self.page_numbers)
    
    def optimal_approach(self):
        v = []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(v)

            if self.page_numbers[i] not in v:
                page_fault_count += 1

                if len(v) == self.max_num_frames:
                    max_usage_gap = -1
                    max_usage_gap_index = 0

                    for p in range(self.max_num_frames):
                        is_found = False

                        for j in range(i-1, len(self.page_numbers)):
                            if self.page_numbers[j] == v[p]:
                                is_found = True
                                if (j-i) > max_usage_gap:
                                    max_usage_gap = j-i
                                    max_usage_gap_index = p
                        
                        if is_found == False:
                            max_usage_gap_index = p
                            break

                    v[max_usage_gap_index] = self.page_numbers[i]
                else:
                    v.append(self.page_numbers[i])
                
        return page_fault_count / len(self.page_numbers)
    


frames = [7,0,1,2,0,3,0,4,2,3]
algo = PageReplacementAlgorithms(frames, 4)
miss_ratio = 0

print("FIFO.....")
miss_ratio = algo.first_in_first_out()
print("Miss ratio: ",  miss_ratio)
print()

print("LRU.......")
miss_ratio = algo.least_recently_used()
print("Miss ratio: ",  miss_ratio)
print()

print("Optimal......")
miss_ratio = algo.optimal_approach()
print("Miss ratio: ",  miss_ratio)
print()
