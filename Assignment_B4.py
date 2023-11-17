class PageReplacementAlgorithms:
    def __init__(self, page_numbers, max_num_frames) -> None:
        self.page_numbers = page_numbers
        self.max_num_frames = max_num_frames

    def first_in_first_out(self):
        frames = []
        miss_count = 0

        for i in range(len(self.page_numbers)):
            if self.page_numbers[i] not in frames:
                miss_count += 1
                if len(frames) == self.max_num_frames:
                    frames.pop(0)
                frames.append(self.page_numbers[i])
                print(str(self.page_numbers[i]).ljust(5) + " Miss ".ljust(5) + str(frames))
            else:
                print(str(self.page_numbers[i]).ljust(5) + " Hit ".ljust(5) + str(frames))
            
        return miss_count, len(self.page_numbers) - miss_count
    
    def least_recently_used(self):
        frames , frame_ages = [], []
        miss_count = 0

        for i in range(len(self.page_numbers)): 

            for j in range(len(frame_ages)):
                frame_ages[j] += 1

            if self.page_numbers[i] not in frames:
                miss_count += 1
                if len(frames) == self.max_num_frames:
                    max_index = frame_ages.index(max(frame_ages))
                    frame_ages.pop(max_index)
                    frames.pop(max_index)
                    frames.insert(max_index, self.page_numbers[i])
                    frame_ages.insert(max_index, 0)
                else:
                    frames.append( self.page_numbers[i])
                    frame_ages.append(0)
                print(str(self.page_numbers[i]).ljust(5) + " Miss ".ljust(5) + str(frames))
            else:
                index = frames.index(self.page_numbers[i])
                frame_ages[index] = 0
                print(str(self.page_numbers[i]).ljust(5) + " Hit ".ljust(5) + str(frames))

        return miss_count, len(self.page_numbers) - miss_count
    
    def optimal_approach(self):
        frames = []
        miss_count = 0

        for i in range(len(self.page_numbers)):

            if self.page_numbers[i] not in frames:
                miss_count += 1

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
                print(str(self.page_numbers[i]).ljust(5) + " Miss ".ljust(5) + str(frames))
            else:
                print(str(self.page_numbers[i]).ljust(5) + " Hit ".ljust(5) + str(frames))
                
        return miss_count, len(self.page_numbers) - miss_count
    


frames = [7,0,1,2,0,3,0,4,2,3,0,3,2,3]
algo = PageReplacementAlgorithms(frames, 4)
frame_miss_count = 0
frame_hit_count = 0

print("FIFO.....")
frame_miss_count, frame_hit_count = algo.first_in_first_out()
print("Hit count: " + str(frame_hit_count) + " Miss count: " + str(frame_miss_count))
print()

print("LRU.......")
frame_miss_count, frame_hit_count = algo.least_recently_used()
print("Hit count: " + str(frame_hit_count) + " Miss count: " + str(frame_miss_count))
print()

print("Optimal......")
frame_miss_count, frame_hit_count = algo.optimal_approach()
print("Hit count: " + str(frame_hit_count) + " Miss count: " + str(frame_miss_count))
print()
