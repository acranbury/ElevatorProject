#!/usr/bin/python           # This is server.py file

import SocketServer
from threading import Thread

class service(SocketServer.BaseRequestHandler):
    def handle(self):
        data = 'dummy'
        print "Client connected with ", self.client_address
        while len(data):
            data = self.request.recv(1024)
            self.request.send(data)
            
        print "Client Exited"
        self.request.close()

class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

server = ThreadedTCPServer(('',1520), service)
server.serve_forever()