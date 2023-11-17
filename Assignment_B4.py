class PageReplacementAlgorithms:
    def __init__(self, page_numbers, max_num_frames) -> None:
        self.page_numbers = page_numbers
        self.max_num_frames = max_num_frames

    def first_in_first_out(self):
        frames = []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(frames, end=' '.ljust(10))

            if self.page_numbers[i] not in frames:
                print(str(self.page_numbers[i]).ljust(10)," Miss ".ljust(10))
                page_fault_count += 1
                if len(frames) == self.max_num_frames:
                    frames.pop(0)
                frames.append(self.page_numbers[i])
            else:
                print(str(self.page_numbers[i]).ljust(10)," Hit ".ljust(10))
            
        return page_fault_count / len(self.page_numbers)
    
    def least_recently_used(self):
        frames , frame_ages = [], []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(frames, end=' '.ljust(10))  

            for j in range(len(frame_ages)):
                frame_ages[j] += 1

            if self.page_numbers[i] not in frames:
                print(str(self.page_numbers[i]).ljust(10)," Miss ".ljust(10))
                page_fault_count += 1
                if len(frames) == self.max_num_frames:
                    max_index = frame_ages.index(max(frame_ages))
                    frame_ages.pop(max_index)
                    frames.pop(max_index)
                    frames.insert(max_index, self.page_numbers[i])
                    frame_ages.insert(max_index, 0)
                else:
                    frames.insert(0, self.page_numbers[i])
                    frame_ages.insert(0, 0)
            else:
                print(str(self.page_numbers[i]).ljust(10)," Hit ".ljust(10))
                index = frames.index(self.page_numbers[i])
                frame_ages[index] = 0

        return page_fault_count / len(self.page_numbers)
    
    def optimal_approach(self):
        frames = []
        page_fault_count = 0

        for i in range(len(self.page_numbers)):
            print(frames, end=' '.ljust(10))

            if self.page_numbers[i] not in frames:
                print(str(self.page_numbers[i]).ljust(10)," Miss ".ljust(10))
                page_fault_count += 1

                if len(frames) == self.max_num_frames:
                    max_usage_gap = -1
                    max_usage_gap_index = 0

                    for p in range(self.max_num_frames):
                        is_found = False

                        for j in range(i-1, len(self.page_numbers)):
                            if self.page_numbers[j] == frames[p]:
                                is_found = True
                                if (j-i) > max_usage_gap:
                                    max_usage_gap = j-i
                                    max_usage_gap_index = p
                        
                        if is_found == False:
                            max_usage_gap_index = p
                            break

                    frames[max_usage_gap_index] = self.page_numbers[i]
                else:
                    frames.append(self.page_numbers[i])
            else:
                print(str(self.page_numbers[i]).ljust(10)," Hit ".ljust(10))
                
        return page_fault_count / len(self.page_numbers)
    


frames = [7,0,1,2,0,3,0,4,2,3,0,3,2,3]
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
