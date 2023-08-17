'''
Roll No and Name : 21354_Advait Naik

Problem Statement:
Write a python program to store second year percentage of students in array. Write function for sorting array
of floating-point numbers in ascending order using
a) Insertion sort
b) Shell sort
and display top 5 scores.
'''

class Percentage:
    def __init__(self):
        self.n = int(input("Enter no of students in a class: "))
        self.percentage = []
        for i in range(self.n):
            marks = float(input("Enter percentage of the student: "))
            self.percentage.append(marks)
        print("The entered percentage list is: ",self.percentage)

    def swap(list,i1,i2):
        list[i1] , list[i2] = list[i2] , list[i1]

    def top5(self, list):
        l = []
        for i in range(5):
            highest_marks = max(list)
            l.append(highest_marks)
            list.remove(highest_marks)
        print("The top 5 percentage of students are: ", l)

    def insertion_sort(self):
        l = self.percentage
        for i in range(self.n):
            for j in range(i,0,-1):
                if(l[j]<l[j-1]):
                    Percentage.swap(l,j,j-1)
        print(l)
        print()
        Percentage.top5(self,l)

    def shell_sort(self):
        l = self.percentage
        interval = self.n // 2

       
        while (interval > 0):
            for i in range(interval,self.n):
                for j in range(i, interval - 1, -interval):
                    if l[j] < l[j - interval]:
                        Percentage.swap(l, j, j - interval)

            interval = interval // 2


        print(l)
        print()
        Percentage.top5(self,l)


choice = 1
while(choice==1):
    p = Percentage()
    print()
    n = int(input(''' Enter the option by which you want to sort the entered list of students' percentage.
                      Press 1 for insertion sort and 2 for shell sort.........'''))
    print()
    if(n==1):
        print("By using insertion sort the sorted list is..........")
        p.insertion_sort()
    elif(n==2):
        print("By using shell sort the sorted list is..............")
        p.shell_sort()
    else:
        print("Invalid choice")

    choice = int(input("If u want ty again press 1 else press 0: "))
