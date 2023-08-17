"""
RollNo and Name : 21354-Advait Naik

Problem Statement:
a) Write a python program to store roll nos of students in array who attended training program in random order.
   Write function for searching whether particular student attended training program or not, using Linear search
   and Sentinal search.

b) Write a python program to store roll nos of students in array who attended training program in random order.
   Write function for searching whether particular student attended training program or not, using Binary search
   and Fibonacci search.
"""

#Program
class List:
    def __init__(self):
        self.n = int(input("Enter no of students who attended the training programme: "))
        self.rollno = []
        i = 0
        while(i<self.n):
            rollno = int(input("Enter rollno: "))
            if(self.rollno.count(rollno)>0):
                print("Already entered rollno. Enter a new no.")
                i = i - 1
            else:
                self.rollno.append(rollno)
                i = i + 1
        print("The list of entered rollnos is: ",self.rollno)

    def linear(self,item):
        for element in self.rollno:
            if(element==item):
                print("The student with roll no ",item," attended the training programme.")
                break
        else:
            print("The student with roll no ",item," didn't attend the training programme.")


    def sentinal(self,item):
        l=self.rollno
        last_element = l[-1]
        if(last_element==item):
            print("The student with roll no ",item," attended the training programme.")
        else:
            l[-1] = item
            i=0
            while(i<self.n - 1):
                if(l[i]==item):
                    print("The student with roll no ",item," attended the training programme.")
                    break
                i = i + 1
            else:
                print("The student with roll no ",item," didn't attend the training programme.")


    def binary(self,item):
        l = self.rollno
        l1 = []
        for i in range(self.n):
            min_value = min(l)
            l1.append(min_value)
            l.remove(min_value)
        print("The sorted list is: ",l1)

        lower_bound = 0
        upper_bound = self.n-1
        while(lower_bound<=upper_bound):
            mid = (lower_bound + upper_bound)//2
            if(item<l1[mid]):
                upper_bound = mid - 1
            elif(item>l1[mid]):
                lower_bound = mid + 1
            else:
                print("The student with roll no ",item," attended the training programme.")
                break
        else:
            print("The student with roll no ",item," didn't attend the training programme.")

    def fibonacci(self,item):
        l = self.rollno
        l1 = []
        for i in range(self.n):
            min_value = min(l)
            l1.append(min_value)
            l.remove(min_value)
        print("The sorted list is: ",l1)

        f0 = 0
        f1 = 1
        f2 = 1
        offset = -1

        while(f2<self.n):
            f0 = f1
            f1 = f2
            f2 = f0 + f1

        while(f0>=0):
            index = min(f0 + offset,self.n - 1)
            if(l1[index]<item):
                f2 = f1
                f1 = f0
                f0 = f2 - f1
                offset = index
            elif(l1[index]>item):
                f2 = f0
                f1 = f1 - f2
                f0 = f2 - f1
            else:
                print("The student with roll no ", item, " attended the training programme.")
                break
        else:
            print("The student with roll no ", item, " didn't attend the training programme.")



choice = 1
while(choice==1):
    s = List()
    element = int(input("Enter the roll no u want to search: "))
    option = int(input("Enter the option by which u want to find the number............."
                       "i.e press 1 for linear search,2 for sentinal search,3 for binary search and 4 for fibonacci search: "))
    if(option==1):
        print("By linear search...........")
        s.linear(element)
    elif(option==2):
        print("By sentinal search..............")
        s.sentinal(element)
    elif(option==3):
        print("By binary search.............")
        s.binary(element)
    elif(option==4):
        print("By fibonacci search.............")
        s.fibonacci(element)
    else:
        print("Invalid option")

    choice = int(input("If u wish to search again press 1 else press 0: "))
