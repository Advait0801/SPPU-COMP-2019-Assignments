import threading
import time

class ParallelSort:
    def __init__(self, arr):
        self.arr = arr

    def sequential_bubble_sort(self):
        start = time.time()

        n = len(self.arr)
        swapped = True

        while swapped:
            swapped = False
            for j in range(0, n - 1):
                if self.arr[j] > self.arr[j + 1]:
                    self.arr[j], self.arr[j + 1] = self.arr[j + 1], self.arr[j]
                    swapped = True

        end = time.time()
        print(f"Sequential Bubble Sort took {end - start:.4f} seconds")

    def parallel_bubble_sort(self):
        start = time.time()

        n = len(self.arr)
        swapped = True

        while swapped:
            swapped = False
            for j in range(0, n - 1, 2):
                if self.arr[j] > self.arr[j + 1]:
                    self.arr[j], self.arr[j + 1] = self.arr[j + 1], self.arr[j]
                    swapped = True
            for j in range(1, n - 1, 2):
                if self.arr[j] > self.arr[j + 1]:
                    self.arr[j], self.arr[j + 1] = self.arr[j + 1], self.arr[j]
                    swapped = True

        end = time.time()
        print(f"Parallel Bubble Sort took {end - start:.4f} seconds")

    def sequential_merge_sort(self):
        start = time.time()
        self.sequential_merge_sort_helper(0, len(self.arr) - 1)
        end = time.time()
        print(f"Sequential Merge Sort took {end - start:.4f} seconds")

    def sequential_merge_sort_helper(self, left, right):
        if left >= right:
            return

        mid = (left + right) // 2
        self.sequential_merge_sort_helper(left, mid)
        self.sequential_merge_sort_helper(mid + 1, right)
        self._merge(left, mid, right)

    def parallel_merge_sort(self):
        start = time.time()
        self.parallel_merge_sort_helper(0, len(self.arr) - 1, 0)
        end = time.time()
        print(f"Parallel Merge Sort took {end - start:.4f} seconds")

    def parallel_merge_sort_helper(self, left, right, depth):
        if left >= right:
            return

        mid = (left + right) // 2

        if depth <= 4:
            t1 = threading.Thread(target=self.parallel_merge_sort_helper, args=(left, mid, depth + 1))
            t2 = threading.Thread(target=self.parallel_merge_sort_helper, args=(mid + 1, right, depth + 1))
            t1.start()
            t2.start()
            t1.join()
            t2.join()
        else:
            self.parallel_merge_sort_helper(left, mid, depth + 1)
            self.parallel_merge_sort_helper(mid + 1, right, depth + 1)

        self._merge(left, mid, right)

    def _merge(self, left, mid, right):
        # common for sequential and parallel merge sort
        temp = []
        i, j = left, mid + 1

        while i <= mid and j <= right:
            if self.arr[i] <= self.arr[j]:
                temp.append(self.arr[i])
                i += 1
            else:
                temp.append(self.arr[j])
                j += 1

        while i <= mid:
            temp.append(self.arr[i])
            i += 1

        while j <= right:
            temp.append(self.arr[j])
            j += 1

        for idx, val in enumerate(temp):
            self.arr[left + idx] = val

    def print_array(self):
        print(self.arr)
        

if __name__ == "__main__":
    data = [5, 3, 10, 20, 0, -1]
    print("Original array:")
    print(data)

    sorter = ParallelSort(data.copy())
    sorter.sequential_bubble_sort()
    print("Sorted array with Sequential Bubble Sort:")
    sorter.print_array()

    sorter = ParallelSort(data.copy())
    sorter.parallel_bubble_sort()
    print("Sorted array with Parallel Bubble Sort:")
    sorter.print_array()

    sorter = ParallelSort(data.copy())
    sorter.sequential_merge_sort()
    print("Sorted array with Sequential Merge Sort:")
    sorter.print_array()

    sorter = ParallelSort(data.copy())
    sorter.parallel_merge_sort()
    print("Sorted array with Parallel Merge Sort:")
    sorter.print_array()