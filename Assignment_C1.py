import socket

print("1. Get ip from name, 2. Get name from ip")
option = int(input("Enter option: "))

if option == 1:
    name = input("Enter host name: ")
    print("Host Address: " , socket.gethostbyname(name))
elif option == 2:
    address = input("Enter host address: ")
    print("Host Name: " , socket.gethostbyaddr(address))


