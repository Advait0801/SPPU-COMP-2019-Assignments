'''
Roll No and Name : 21354_Advait Naik

Problem Definition :
Write a python program to compute following operations on String:
a) To display word with the longest length
b) To determines the frequency of occurence of particular character in the string
c) To check whether given string is palindrome or not 
d) To display index of first appearance of the substring 
e) To count the occurences of each word in a given string
'''

#Program
class String:

    def __init__(self,stri):
        self.stri=stri

    def length(self,str1):
        index=0
        for i in str1:
            index = index + 1

        return index

    def palindrome(self):
        stri_reverse = self.stri[::-1]
        if(stri_reverse==self.stri):
            print("Given string is palindrome")
        else:
            print("Given string is not a palindrome")

    def occurence_char(self):
        char = input("Enter the charcter u want the frequency: ")
        count=0
        for item in self.stri:
            if(item==char):
                count = count + 1

        print("The entered character has occured the following times: ",count)

    def index(self):
        first_index = -1
        str2 = input("Enter a substring: ")
        a = self.length(self.stri)
        b = self.length(str2)
        for i in range(a):
            sub_string = self.stri[i:i+b]
            if(sub_string==str2):
                first_index = i
                break

        return first_index

    def display(self):
        l1 = self.stri.split()
        max = 1
        word = ""
        for item in l1:
            length = self.length(item)
            if(length > max):
                max = length
                word = item

        print("Longest word is: ",word)

    def occurence_word(self):
        l1 = self.stri.split()
        for i in l1:
            count = 0
            for char in self.stri:
                if(char==i):
                    count = count + 1

            print("The word ",i," has occured ",count," times in given string")



choice = 1
while(choice==1):
    s = String(input(("Enter a main string: ")))
    n = int(input("Enter your choice of operation i.e. 1 for longest word,2 for frequency of a particular character,"
                  "3 for palindrome check,4 for 1st index of a substring and 5 for frequency of each word in the string: "))
    if(n==1):
        s.display()
    elif(n==2):
        s.occurence_char()
    elif(n==3):
        s.palindrome()
    elif(n==4):
        s.index()
    elif(n==5):
        s.occurence_word()
    else:
        print("Invalid no.")

    choice = int(input("If you want to try again press 1 else press 0: "))
    if(choice==0):
        print("Thank You")