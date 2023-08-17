'''
Name and RollNo : 21354_Advait Naik

Problem Statement:
Write a python program to store first year percentage of students in array. Write function for sorting array of
floating point numbers in ascending order using quick sort and display top 5 scores.
'''

class Percentage:
    def __init__(self):
        self.n = int(input("Enter no of students in a class: "))
        self.percentage = []
        for i in range(self.n):
            marks = float(input("Enter percentage of the student: "))
            self.percentage.append(marks)
        print("The entered percentage list is: ",self.percentage)

    def partition(self,array,low,high):
        pivot = array[high]
        i = low - 1
        for j in range(low,high):
            if(array[j]<=pivot):
                i = i + 1
                array[i] , array[j] = array[j] , array[i]

        array[i + 1] , array[high] = array[high] , array[i + 1]

        return i + 1

    def top5(self, list):
        l = []
        for i in range(5):
            highest_marks = max(list)
            l.append(highest_marks)
            list.remove(highest_marks)
        print("The top 5 percentage of students are: ", l)


    def quick_sort(self, arr , low, high):
        if(low<high):

            pivot_ = self.partition( arr ,low,high)
            self.quick_sort( arr , pivot_ + 1, high )
            self.quick_sort( arr , low, pivot_ - 1)


choice = 1
while(choice==1):
    p = Percentage()
    print()
    print("Here we are using quick sort method to sort the entered list of percentages.")
    p.quick_sort( p.percentage , 0 , p.n - 1)
    print()

    print("So by using quick sort method,the sorted list is......... ")
    print(p.percentage)
    print()
    p.top5(p.percentage)

    choice = int(input("If u want to try again press 1 else press 0: "))


