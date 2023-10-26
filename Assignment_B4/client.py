import socket

def hello_client(client_socket):
    client_name = input("Enter your name: ")
    client_socket.send(client_name.encode())
    message = client_socket.recv(1024).decode()
    print(f"Server says: {message}")

def file_transfer_client(client_socket):
    file_name = "received_file.txt"
    with open(file_name, 'wb') as file:
        while True:
            data = client_socket.recv(1024)
            if not data:
                break
            file.write(data)
    print(f"File '{file_name}' received successfully.")

def calculator_client(client_socket):
    expression = input("Enter a mathematical expression: ")
    client_socket.send(expression.encode())
    result = client_socket.recv(1024).decode()
    print(f"Result: {result}")


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = '127.0.0.1'
port = 12345  
client_socket.connect((host, port))
print("Select an option:")
print("1. Hello")
print("2. File Transfer")
print("3. Calculator")
print("4. Exit")
choice = input("Enter your choice: ")
if choice == '1':
    hello_client(client_socket)
elif choice == '2':
    file_transfer_client(client_socket)
elif choice == '3':
    calculator_client(client_socket)
elif choice == '4':
    print("Goodbye!")
else:
    print("Invalid choice. Please select a valid option.")
client_socket.close()  # Close the socket when the client is done