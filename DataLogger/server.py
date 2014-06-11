#!/usr/bin/python           # This is server.py file

import socket
import sys
from thread import *

HOST = ''                   # Symbolic name meaning all available interfaces
PORT = 8888                 # Arbitrary non-privilieged port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
print 'Socket created'

try:
    s.bind((HOST, PORT))
except socket.error, msg:
    print 'Bind failed. Error Code: ' + str(msg[0]) + ' Message: ' + msg[1]
    sys.exit()

print 'Socket bind complete'

s.listen(10)
print 'Socket now listening'

# Function for handling connections. This will be used to create threads
def clientThread(conn):
    # Sending message to connected client
    conn.send('Welcome to the server. Type something and hit enter\n')

    # Infinite loope so that function does not terminate and thread does not end
    while True:
        # Receiving from client
        data = conn.recv(1024)
        reply = 'OK...' + data
        if not data:
            break

        conn.sendall(reply)

    # Came out of loop
    conn.close()

# Now keep talking with the client
while 1:
    # Wait to accept a connection - blocking call
    conn, addr = s.accept()
    print 'Connected with ' + addr[0] + ':' + str(addr[1])

    # Start a new thread (function, (args))
    start_new_thread(clientThread, (conn,))

s.close()
