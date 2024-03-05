def selection_sort(nums):
    n = len(nums)
    
    for i in range(n):
        mini = nums[i]
        index = i

        for j in range(i+1, n):
            if nums[j] < mini:
                mini = nums[j]
                index = j

        temp = nums[i]
        nums[i] = nums[index]
        nums[index] = temp


arr = [1, 0, 99, 5, 2, -99]
selection_sort(arr)
print(arr)