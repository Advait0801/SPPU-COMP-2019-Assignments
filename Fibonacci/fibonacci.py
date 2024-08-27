class Fibonacci:
    def __init__(self) -> None:
        pass

    def fib_solve(self, n):
        if n < 2:
            return n
        
        return  self.fib_solve(n-1) + self.fib_solve(n-2)
    
    def fibonacci_recursive(self, n):
        print("The fibonacci series by recursive algorithm is......")
        for i in range(0, n):
            print(self.fib_solve(i), end = " ")
        print()

    def fibonacci_iterative(self, n):
        print("The fibonacci series by iterative algorithm is......")

        f1 = 0
        f2 = 1
        print(f1, f2, end = " ")

        for _ in range(n-2):
            f3 = f1 + f2
            print(f3, end = " ")
            f1 = f2
            f2 = f3
        print()

f = Fibonacci()
f.fibonacci_recursive(10)
print()
f.fibonacci_iterative(10)