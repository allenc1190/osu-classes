import socket

#source from https://www.binarytides.com/python-socket-programming-tutorial/

#creating the socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

host = "gaia.cs.umass.edu"

#connecting to host at port 80
s.connect((host, 80))

#sending request to the host and file
s.send("GET /wireshark-labs/HTTP-wireshark-file3.html HTTP/1.1\r\nHost: gaia.cs.umass.edu\r\n\r\n")

print('Request: GET /wireshark-labs/INTRO-wireshark-file3.html HTTP/1.1')
print('Host: ' + host + '\n')

#the data that the request gets back
data = s.recv(9999)

#printing the data
print "[RECV] - length:", len(data)
print(data)

#close socket
s.close()
