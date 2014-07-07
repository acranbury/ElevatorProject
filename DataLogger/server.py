#!/usr/bin/python           # This is server.py file

import SocketServer
import threading
import serial

logfilename = "/Users/alan/logfile.txt"


def GetElevatorStatus():
    currentFloor = "1"
    return currentFloor

# basic serial log structure for now, no fancy stuff yet
def serialLog():
    serialData = ser.read(10)
    # if we got stuff back, log it
    # need to do some fancier stuff eventually
    if len(serialData) > 0:
        logfile.write(serialData + '\n')
    
    # do we want this? allows controller to kill server
    if serialData == "Exit":
        return 1
    else:
        return 0


class service(SocketServer.BaseRequestHandler):
    def handle(self):
        data = 'dummy'
        print "Client connected with ", self.client_address
        
        password = self.request.recv(1024)
        while password != "ESEsem6":
            self.request.send("Wrong Password: " + password) 
            password = self.request.recv(1024)                   
        
        while len(data):
            data = self.request.recv(1024)
            cmd = data[:2]
            print cmd
            
            if cmd == "00":
                print "Detailed Report Sent"
                detailed = open("detailed.txt", 'r')
                #simpleLogFileData = file.read()
                self.request.send(detailed.read())
                detailed.close()
            elif cmd == "01":
                print "Simple Report Sent"
                simple = open("simple.txt", 'r')
                self.request.send(simple.read())
                simple.close()
            elif cmd == "10":
                self.request.send(GetElevatorStatus())
            elif cmd == "11":
                self.request.send(GetElevatorStatus())
            elif cmd == "12":
                self.request.send(GetElevatorStatus())
            elif cmd == "13":
                self.request.send(GetElevatorStatus())
            elif cmd == "14":
                self.request.send(GetElevatorStatus())
            elif cmd == "15":
                self.request.send(GetElevatorStatus())
            elif cmd == "20":
                self.request.send(GetElevatorStatus())
            elif cmd == "21":
                self.request.send(GetElevatorStatus())
            elif cmd == "22":
                self.request.send(GetElevatorStatus())
            elif cmd == "23":
                self.request.send(GetElevatorStatus())
            elif cmd == "24":
                self.request.send(GetElevatorStatus())
            elif cmd == "25":
                self.request.send(GetElevatorStatus())
            elif cmd == "30":
                self.request.send(GetElevatorStatus())
            elif cmd == "31":
                self.request.send(GetElevatorStatus())
            elif cmd == "32":
                self.request.send(GetElevatorStatus())
            elif cmd == "33":
                self.request.send(GetElevatorStatus())
            else:
                self.request.send("error :")
                self.request.send(cmd)
            
        print "Client Exited"
        self.request.close()

class ThreadedTCPServer(SocketServer.ThreadingMixIn, SocketServer.TCPServer):
    pass

if __name__ == "__main__":
    server = ThreadedTCPServer(('', 1520), service)
    
    # start a thread with the server running in it
    # server will then spawn a new thread for each connection
    server_thread = threading.Thread(target=server.serve_forever())
    
    # set the thread to exit when the main thread exits
    server_thread.daemon = True
    server_thread.start()
    print "Server running in thread: ", server_thread.name
    
    # to open a specific port on Windows, replace '0' with 'COM#'
    ser = serial.Serial(0, 19200, timeout=5)
    print "Serial port used: ", ser.name
    
    # open log file in append mode
    logfile = open(logfilename, 'a')
    
    # log stuff while the system is still running
    while serialLog() == 0:
        pass