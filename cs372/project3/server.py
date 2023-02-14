import sys
import socket
import threading

users = {}
addresses = {}

def connTh(socket):
    #accept the connection
    while True:
        client, address = socket.accept()
        print("A user has connected.")
        addresses[client] = address
        threading.Thread(target=clientTh, args=(client,)).start()

def clientTh(client):
    user = getUsername(client)

    print("User set its nickname to", user + "!")
    users[client] = user

    client.send("Type /q to exit chat or keep typing message".encode("utf8"))
    broadcast(user + " has joined the chat room!")

    #checks if message is /q or keep sending messages
    while True:
        message = client.recv(2048).decode("utf8")

        if message == "/q":
            print(user + " has left the chat.")
            broadcast(user + " has left the chat.")

            break

        else:
            print(user + ": " + message)
            broadcast(message, user)

def getUsername(client):
    #username
    client.send("Please enter your username:".encode("utf8"))
    username = client.recv(2048).decode("utf8")
    
    return username

def broadcast(message, sentBy = ""):
    #send message to all clients
    if sentBy == "":
        for user in users:
            user.send(message.encode("utf8"))
    else:
        for user in users:
            user.send("{}: {}".format(sentBy, message).encode("utf8"))

def main():
    if len(sys.argv) != 3:
        print("Invalid command. Type: python server.py [host] [port]")
        exit()

    else:
        host = str(sys.argv[1])
        port = int(sys.argv[2])

        #creates the socket
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        #bind to host and port
        server.bind((host, port))

        server.listen()
        print("Server is listening on host", host, "and port", port)

        #accept connection and start
        connThread = threading.Thread(target=connTh, args=(server,))
        connThread.start()
        connThread.join()

        #closes server
        server.close()

if __name__ == "__main__":
    main()
