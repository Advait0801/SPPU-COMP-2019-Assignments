'''
Roll No and Name : 21354_Advait Naik

Problem Defination:
In second year computer engineering class, group A students play cricket, group B students play badminton
and group C students play football. Write a python program using functions to compute the following:-
a) List of students who play both cricket and badminton
b) List of students who play either cricket or badminton but not both
c) Number of stuents who play neither cricket nor badminton
d) Number of students who play cricket and football but not badminton.

'''

#Group a,b,c and d represent students playing cricket,football,badminton and nothing respectively.
group_a=[]
group_b=[]
group_c=[]
group_d=[]

#Roll no list represents list of all students in class
roll_no_list=[]


#Functions for sets part
def union(a,b):
    for i in b:
        a.append(i)
    for element in a:
        if(a.count(element)>1):
            a.remove(element)
    unionset=a
    return unionset

def intersection(x,y):
    intersection_set=[]
    for j in y:
        x.append(j)
    for item in x:
        if(x.count(item)>1):
            intersection_set.append(item)
    for element in intersection_set:
        if(intersection_set.count(element)>1):
            intersection_set.remove(element)

    return intersection_set

def difference(m,n):
    for k in n:
        m.remove(k)
    diff=m
    return diff



print("This data shows no of students in a division and their respective sport which are cricket,football or badminton")


#Taking info of the students
n=int(input("Enter no of students in the division: "))
for i in range(n):
    roll_no=int(input("Enter roll no of the student"))
    roll_no_list.append(roll_no)
    if(roll_no_list.count(roll_no)>1):
        print("Already entered data. Enter new roll no.")
    else:
        choice=1
        while(choice==1):
            sport=input("Enter the sport u play i.e. press c for cricket, f for football and b for badminton. If u dont play any press n: ")
            if(sport=="c"):
                group_a.append(roll_no)
            elif(sport=="f"):
                group_b.append(roll_no)
            elif(sport=="b"):
                group_c.append(roll_no)
            elif(sport=="n"):
                group_d.append(roll_no)
                break
            else:
                print("Enter correct sport")
            choice=int(input("If you play another sport as well press 1 else press 0: "))


#Calculation part
cric_or_badmi = union(group_a,group_c)
cric_and_badmi = intersection(group_a,group_c)
cric_and_badmi_but_no_both = difference(cric_or_badmi,cric_and_badmi)
cric_and_foot_but_no_badmi = difference(intersection(group_a,group_b),group_c)
niether_cric_nor_badmi = union(group_b,group_d)


#Display
print("Following is list of students playing cricket and badminton: ",cric_and_badmi)
print("Their total no is: ",len(cric_and_badmi))
print()
print("Following is list of students playing cricket or badminton but not both: ",cric_and_badmi_but_no_both)
print("Their total no is: ",len(cric_and_badmi_but_no_both))
print()
print("Following is the list of students playing neither cricket nor badminton: ",niether_cric_nor_badmi)
print("Their total no is: ",len(niether_cric_nor_badmi))
print()
print("Following is the list of students playing cricket and football but not badminton: ",cric_and_foot_but_no_badmi)
print("Their total no is: ",len(cric_and_foot_but_no_badmi))
