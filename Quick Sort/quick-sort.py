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
            p = self.partition(arr, low, high)
            self.deterministic_quick_sort(arr, low, p)
            self.deterministic_quick_sort(arr, p + 1, high)

    def random_quick_sort(self, arr, low, high):
        if low < high:
            r = random.randint(low, high)
            arr[low], arr[r] = arr[r], arr[low]
            p = self.partition(arr, low, high)
            self.random_quick_sort(arr, low, p)
            self.random_quick_sort(arr, p + 1, high)


l1 = [29, 4, 11, 33, -1, 0, 55, 24]
l2 = [29, 4, 11, 33, -1, 0, 55, 24]
qs = QuickSort()
qs.deterministic_quick_sort(l1, 0, len(l1) - 1)
print(l1)           
qs.random_quick_sort(l2, 0, len(l2) - 1)
print(l2)                    