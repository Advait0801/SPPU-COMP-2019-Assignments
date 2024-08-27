import random

class QuickSort:
    def __init__(self) -> None:
        pass

    def partition(self, arr, low, high):
        pivot = arr[low]
        i = low + 1
        j = high

        while True:
            while i <= high and arr[i] <= pivot:
                i += 1

            while j > low and arr[j] > pivot:
                j -= 1

            if i >= j:
                break

            arr[i], arr[j] = arr[j], arr[i]

        arr[low], arr[j] = arr[j], arr[low]
        return j
    
    def deterministic_quick_sort(self, arr, low, high):
        if low < high:
            pivot = self.partition(arr, low, high)
            self.deterministic_quick_sort(arr, low, pivot)
            self.deterministic_quick_sort(arr, pivot + 1, high)

    def random_quick_sort(self, arr, low, high):
        if low < high:
            r = random.randint(0, high - low - 1) + low
            arr[r], arr[low] = arr[low], arr[r]
            pivot = self.partition(arr, low, high)
            self.random_quick_sort(arr, low, pivot)
            self.random_quick_sort(arr, pivot + 1, high)


qs = QuickSort()
x = [10, 12, 15, 20, 1, 4, 17, 16, 11]

qs.deterministic_quick_sort(x, 0, len(x) -1)
for i in x:
    print(i, end = " ")
print()

x = [3, 4, 1, 5, 2]
qs.random_quick_sort(x, 0, len(x) - 1)
for i in x:
    print(i, end = " ")
print()