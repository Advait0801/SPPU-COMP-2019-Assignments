import socket

def hello_server(server_socket):
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")
        client_name = client_socket.recv(1024).decode()
        print(f"{client_name} is requesting the server")
        message = f"Hello, {client_name}!"
        client_socket.send(message.encode())
        client_socket.close()

def file_transfer_server(server_socket):
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")
        file_name = "Assignment_B4/sent_file.txt"
        with open(file_name, 'rb') as file:
            data = file.read(1024)
            while data:
                client_socket.send(data)
                data = file.read(1024)
        print(f"File '{file_name}' sent successfully.")
        client_socket.close()

def calculator_server(server_socket):
    while True:
        client_socket, client_address = server_socket.accept()
        print(f"Connection from {client_address}")
        expression = client_socket.recv(1024).decode()
        try:
            print(f"We received {expression}")
            result = str(eval(expression))
            print(f"The result is : {result}")
            client_socket.send(result.encode())
        except Exception as e:
            client_socket.send(str(e).encode())
        client_socket.close()


server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host = '127.0.0.1'  # Replace with your IP address or leave as '0.0.0.0' for any interface
port = 12345  # Replace with the appropriate port
server_socket.bind((host, port))
server_socket.listen(5)
print("Server is listening for incoming connections...")
while True:
    print("Select a service to start:")
    print("1. Hello")
    print("2. File Transfer")
    print("3. Calculator")
    print("4. Exit")
    choice = input("Enter your choice: ")
    if choice == '1':
        hello_server(server_socket)
    elif choice == '2':
        file_transfer_server(server_socket)
    elif choice == '3':
        calculator_server(server_socket)
    elif choice == '4':
        print("Goodbye!")
        break
    else:
        print("Invalid choice. Please select a valid option.")