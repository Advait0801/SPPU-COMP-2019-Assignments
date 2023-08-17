s = input("Enter the message to be sent: ")
ascii_list = [ord(c) for c in s]

def calc_redundantbits(m):
    for i in range(m):
        if 2**i >= m + i + 1:
            return i

def get_modified_code(ascii_letter):
    b = bin(ascii_letter)[2:]
    no_of_rbits = calc_redundantbits(len(b))
    l = [char for char in b]    
    for i in range(no_of_rbits):
        st = 'p' + str(i+1)
        l.insert(2**(i)-1,st)
    final = ' '.join(l)
    print(final)

get_modified_code(ascii_list[0])
print()
get_modified_code(ascii_list[1])

