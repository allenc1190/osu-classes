import sys
import socket
import threading

global status

def send(socket):
    #sends message
    while status:
        if status:
            message = input('>')
            socket.send(message.encode("utf8"))
        else:
            print("Unable to send message")
            break

def receive(socket):
    #receives message
    while status:
        if status:
            message = socket.recv(2048).decode()
            print(message)
        else:
            print("Unable to reach server")
            break

def main():

    if len(sys.argv) != 3:
        print("Invalid command. Type: python client.py [host] [port]")
        exit()

    else:
        host = str(sys.argv[1])
        port = int(sys.argv[2])

        #Creates the socket
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        #connect to host and port
        server.connect((host, port))

        #sending and recieving 
        receiveTh = threading.Thread(target=receive, args=(server,))
        sendTh = threading.Thread(target=send, args=(server,))

        #start
        receiveTh.start()
        sendTh.start()

        #while both threads are still active
        while True:
            if receiveTh.is_alive() and sendTh.is_alive():
                continue
            else:
                break

        #close socket
        server.close()
        print("\nYou can now close the application.")

#end
status = True

if __name__ == "__main__":
    main()
