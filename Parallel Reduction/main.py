from concurrent.futures import ThreadPoolExecutor
import math

class ParallelReduction:
    def __init__(self, arr):
        self.arr = arr

    def _chunkify(self, n_threads):
        """Split array into n_threads chunks."""
        chunk_size = math.ceil(len(self.arr) / n_threads)
        return [self.arr[i:i + chunk_size] for i in range(0, len(self.arr), chunk_size)]

    def sum(self):
        def partial_sum(chunk):
            return sum(chunk)

        n_threads = min(32, len(self.arr))
        chunks = self._chunkify(n_threads)
        
        with ThreadPoolExecutor(max_workers=n_threads) as executor:
            partial_sums = executor.map(partial_sum, chunks)

        return sum(partial_sums)

    def min(self):
        def partial_min(chunk):
            return min(chunk)

        n_threads = min(32, len(self.arr))
        chunks = self._chunkify(n_threads)

        with ThreadPoolExecutor(max_workers=n_threads) as executor:
            partial_mins = executor.map(partial_min, chunks)

        return min(partial_mins)

    def max(self):
        def partial_max(chunk):
            return max(chunk)

        n_threads = min(32, len(self.arr))
        chunks = self._chunkify(n_threads)

        with ThreadPoolExecutor(max_workers=n_threads) as executor:
            partial_maxs = executor.map(partial_max, chunks)

        return max(partial_maxs)

    def mean(self):
        total_sum = self.sum()
        return total_sum / len(self.arr)

# Example usage
if __name__ == "__main__":
    arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    pr = ParallelReduction(arr)

    print("Sum:", pr.sum())
    print("Max:", pr.max())
    print("Min:", pr.min())
    print("Mean:", pr.mean())