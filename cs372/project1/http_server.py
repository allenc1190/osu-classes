from socket import *

#source from https://www.binarytides.com/python-socket-programming-tutorial/

# create socket
s = socket(AF_INET, SOCK_STREAM)

port = 8001

#connect host with port
s.bind(('127.0.0.1', port))

data = "HTTP/1.1 200 OK\r\n"\
"Content-Type: text/html; charset=UTF-8\r\n\r\n"\
"<html>Congratulations! You've downloaded the first Wireshark lab file!</html>\r\n"

#start listening to socket
s.listen(1)

print("The server on port", port, "is listening.")

while True:
    socket_conn, address = s.accept()
    recv_msg = socket_conn.recv(4096)

    # print data
    print("Recieved:" + format(str(recv_msg)))
    send_msg = data
    socket_conn.send(send_msg.encode())

    # follow the output
    print("\nSending>>>>>>>>>>>>\n" + data + "\n<<<<<<<<<<<")

    socket_conn.close()
    break