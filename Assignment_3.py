"""
RollNo and Name : 21354_Advait Naik

Problem Statement:
Write a python program to compute following computation on matrix:
a) Addition of 2 matrices
b) Subtraction of 2 matrices
c) Multiplication of 2 matrices
d) Transpose of a matrix
"""

#Program
class Matrix:
    def __init__(self,m=None,n=None):
        if(m==None and n==None):
            self.rows = int(input("Enter no of rows in the matrix: "))
            self.columns = int(input("Enter no of columns in the matrix: "))
        else:
            self.rows = m
            self.columns = n
        self.elements = []


    def build(self):
        print("Its a ",self.rows,"X",self.columns," matrix.")
        print("Enter values in the matrix")
        for i in range(self.rows):
            print("Enter values in row",i)
            l1=[]
            for j in range(self.columns):
                value = int(input())
                l1.append(value)
            self.elements.append(l1)

    def display(self):
        print("Entered matrix is as follows")
        for i in range(self.rows):
            for j in range(self.columns):
                print(self.elements[i][j],end = " ")
            print()


    def addition(self,m1):
        Sum = Matrix(self.rows,self.columns)
        if(self.rows==m1.rows and self.columns==m1.columns):
            for i in range(self.rows):
                l1=[]
                for j in range(self.columns):
                    element1 = self.elements[i][j]
                    element2 = m1.elements[i][j]
                    addition = element1 + element2
                    l1.append(addition)
                Sum.elements.append(l1)

            Sum.display()

        else:
            print("Passed matrix should be of dimension ",self.rows,"X",self.columns)



    def subtraction(self,m2):
        Diff = Matrix(self.rows,self.columns)
        if (self.rows == m2.rows and self.columns == m2.columns):
            for i in range(self.rows):
                l2=[]
                for j in range(self.columns):
                    element1 = self.elements[i][j]
                    element2 = m2.elements[i][j]
                    subtraction = element1 - element2
                    l2.append(subtraction)
                Diff.elements.append(l2)

            Diff.display()

        else:
            print("Passed matrix should be of dimension ", self.rows, "X", self.columns)


    def multiplication(self,m3):
        Product = Matrix(self.rows,m3.columns)
        if(self.columns==m3.rows):
            for i in range(self.rows):
                row = []
                for j in range(m3.columns):
                    row.append(0)
                Product.elements.append(row)   

            for i in range(self.rows):
                for j in range(m3.columns):
                    for k in range(m3.rows):
                        Product.elements[i][j] = Product.elements[i][j] + (self.elements[i][k] * m3.elements[k][j])

            Product.display()

        else:
            print("No of columns of 1st matrix doesnt match rows of second matrix.")

    def transpose(self):
        Transpose = Matrix(self.rows,self.columns)
        for i in range(self.rows):
            row = []
            for j in range(self.columns):
                element3 = self.elements[j][i]
                row.append(element3)
            Transpose.elements.append(row)

        Transpose.display()


choice = 1
while(choice==1):
    print("Enter details about 1st Matrix")
    M1 = Matrix()
    print()
    M1.build()
    print()
    print("Enter details about 2nd Matrix")
    M2 = Matrix()
    print()
    M2.build()
    print()
    print("The 2 entered matrix are as follows")
    M1.display()
    print()
    M2.display()
    print()
    n = int(input("Enter choice of operation.... Press 1 for addition,2 for subtraction,3 for multiplictaion "
                  "and 4 for transpose of a matrix: "))
    if(n==1):
        print("The required addition is")
        M1.addition(M2)
    elif(n==2):
        print("The required subtraction is")
        M1.subtraction(M2)
    elif(n==3):
        print("The required multiplication is")
        M1.multiplication(M2)
    elif(n==4):
        option = int(input("Enter the matrix u want to get transpose:"))
        if(option==1):
            M1.transpose()
        elif(option==2):
            M2.transpose()
        else:
            print("Invalid option")
    else:
        print("Invalid choice")

    choice = int(input("Press 1 to do again else press 0 to exit"))