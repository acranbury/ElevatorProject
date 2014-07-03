# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'clientui.ui'
#
# Created: Fri Jun 20 15:06:50 2014
#      by: PyQt4 UI code generator 4.11
#
# WARNING! All changes made in this file will be lost!

import ExtendedQLabel
import datetime
from PyQt4 import QtCore, QtGui

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

GET_DETAILED_REPORT = '00'
GET_SIMPLE_REPORT = '01'
CAR_FLOOR_1 = '20'
CAR_FLOOR_2 = '21'
CAR_FLOOR_3 = '22'
DOOR_OPEN = '23'
DOOR_CLOSE = '24'
EMERG_STOP = '25'
CALL_FLOOR_1_UP = '11'
CALL_FLOOR_1_DOWN = '10'
CALL_FLOOR_2_UP = '13'
CALL_FLOOR_2_DOWN = '12'
CALL_FLOOR_3_UP = '15'
CALL_FLOOR_3_DOWN = '14'

host = '142.156.193.184'
port = 1520

estop_active = False
    
def TCP_Connect():
    
    #s.close()
    
    #make a new socket after closing the previous one
    try:
        #create an AF_INET, STREAM socket (TCP)
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error, msg:
        print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message: ' + msg[1]
        sys.exit()
    
    print 'Socket Created!'
    
    try:
        remote_ip = socket.gethostbyname( str(ui.ip_editBx.text()))
    
    except socket.gaierror:
        # could not resolve
        print 'Hostname could not be resolved. Exiting'
        sys.exit()
    
    print 'IP address of ' + str(ui.ip_editBx.text()) + ' is ' + remote_ip
    
    # Connect to remote server
    s.connect((remote_ip, port))
    s.settimeout(1)
    
    # Authenticate
    TCP_Send_Message(str(ui.password_editBx.text()))

def TCP_Send_Message(message):
    try:
        # Send the message
        print 'sending tcp message ' + message
        s.sendall(message)
    except socket.error:
        # Send failed
        print 'Send failed'

        
def TCP_Get_Status():
    try:
        reply = s.recv(4096)
    except socket.timeout:
        print "Reply from server has timed out."
    CurFloor = reply[0] 
    
    ####Nick/Alan, can you fill these out when you have the report sorted out?
    DestFloor = 0 
    Direction = 0 
    ui.destFloorLbl.setText(str(DestFloor))
    ui.directionLbl.setText(str(Direction))
    ###########################################################################
    
    
    if CurFloor == '1':
        ui.curFloorLbl.setText('1')        
        ui.floor1Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        ui.floor1Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        ui.floor1Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))    
    elif CurFloor == '2': 
        ui.curFloorLbl.setText('2')       
        ui.floor2Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        ui.floor2Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        ui.floor2Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
    elif CurFloor == '3': 
        ui.curFloorLbl.setText('3')       
        ui.floor3Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        ui.floor3Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        ui.floor3Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
    else:        
        ui.textEdit.append("\nInvalid floor status data received.")
        
    
    
    
    
class Ui_Client(object):
    def setupUi(self, Client):
        Client.setObjectName(_fromUtf8("Client"))
        Client.resize(547, 626)
        self.centralwidget = QtGui.QWidget(Client)
        self.centralwidget.setObjectName(_fromUtf8("centralwidget"))
        self.reportGrpBx = QtGui.QGroupBox(self.centralwidget)
        self.reportGrpBx.setGeometry(QtCore.QRect(10, 10, 311, 571))
        self.reportGrpBx.setObjectName(_fromUtf8("reportGrpBx"))
        self.textEdit = QtGui.QTextEdit(self.reportGrpBx)
        self.textEdit.setGeometry(QtCore.QRect(10, 60, 291, 501))
        self.textEdit.setObjectName(_fromUtf8("textEdit"))
        self.getReportBtn = QtGui.QPushButton(self.reportGrpBx)
        self.getReportBtn.setGeometry(QtCore.QRect(100, 30, 81, 23))
        self.getReportBtn.setObjectName(_fromUtf8("getReportBtn"))
        self.getDiagnosticBtn = QtGui.QPushButton(self.reportGrpBx)
        self.getDiagnosticBtn.setGeometry(QtCore.QRect(10, 30, 81, 23))
        self.getDiagnosticBtn.setObjectName(_fromUtf8("getDiagnosticBtn"))
        self.saveBtn = QtGui.QPushButton(self.reportGrpBx)
        self.saveBtn.setGeometry(QtCore.QRect(230, 30, 75, 23))
        self.saveBtn.setObjectName(_fromUtf8("saveBtn"))
        self.statusGrpBx = QtGui.QGroupBox(self.centralwidget)
        self.statusGrpBx.setGeometry(QtCore.QRect(330, 10, 211, 291))
        self.statusGrpBx.setObjectName(_fromUtf8("statusGrpBx"))
        self.label = QtGui.QLabel(self.statusGrpBx)
        self.label.setGeometry(QtCore.QRect(20, 40, 71, 16))
        self.label.setObjectName(_fromUtf8("label"))
        self.label_2 = QtGui.QLabel(self.statusGrpBx)
        self.label_2.setGeometry(QtCore.QRect(20, 60, 61, 16))
        self.label_2.setObjectName(_fromUtf8("label_2"))
        self.label_3 = QtGui.QLabel(self.statusGrpBx)
        self.label_3.setGeometry(QtCore.QRect(20, 80, 46, 13))
        self.label_3.setObjectName(_fromUtf8("label_3"))
        self.groupBox = QtGui.QGroupBox(self.statusGrpBx)
        self.groupBox.setGeometry(QtCore.QRect(10, 20, 191, 91))
        self.groupBox.setObjectName(_fromUtf8("groupBox"))
        self.curFloorLbl = QtGui.QLabel(self.groupBox)
        self.curFloorLbl.setGeometry(QtCore.QRect(100, 20, 46, 13))
        self.curFloorLbl.setText(_fromUtf8(""))
        self.curFloorLbl.setObjectName(_fromUtf8("curFloorLbl"))
        self.destFloorLbl = QtGui.QLabel(self.groupBox)
        self.destFloorLbl.setGeometry(QtCore.QRect(100, 40, 46, 13))
        self.destFloorLbl.setText(_fromUtf8(""))
        self.destFloorLbl.setObjectName(_fromUtf8("destFloorLbl"))
        self.directionLbl = QtGui.QLabel(self.groupBox)
        self.directionLbl.setGeometry(QtCore.QRect(100, 60, 46, 13))
        self.directionLbl.setText(_fromUtf8(""))
        self.directionLbl.setObjectName(_fromUtf8("directionLbl"))
        self.FloorStatusGrpBx = QtGui.QGroupBox(self.statusGrpBx)
        self.FloorStatusGrpBx.setGeometry(QtCore.QRect(10, 120, 191, 161))
        self.FloorStatusGrpBx.setObjectName(_fromUtf8("FloorStatusGrpBx"))
        self.label_5 = QtGui.QLabel(self.FloorStatusGrpBx)
        self.label_5.setGeometry(QtCore.QRect(140, 20, 46, 13))
        self.label_5.setObjectName(_fromUtf8("label_5"))
        self.label_6 = QtGui.QLabel(self.FloorStatusGrpBx)
        self.label_6.setGeometry(QtCore.QRect(80, 20, 46, 13))
        self.label_6.setObjectName(_fromUtf8("label_6"))
        self.label_4 = QtGui.QLabel(self.FloorStatusGrpBx)
        self.label_4.setGeometry(QtCore.QRect(20, 20, 46, 13))
        self.label_4.setObjectName(_fromUtf8("label_4"))
        self.floor1Up = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor1Up.setGeometry(QtCore.QRect(10, 40, 51, 51))
        self.floor1Up.setText(_fromUtf8(""))
        self.floor1Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        self.floor1Up.setObjectName(_fromUtf8("floor1Up"))
        self.floor2Up = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor2Up.setGeometry(QtCore.QRect(70, 40, 51, 51))
        self.floor2Up.setText(_fromUtf8(""))
        self.floor2Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        self.floor2Up.setObjectName(_fromUtf8("floor2Up"))
        self.floor3Up = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor3Up.setGeometry(QtCore.QRect(130, 40, 51, 51))
        self.floor3Up.setText(_fromUtf8(""))
        self.floor3Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
        self.floor3Up.setObjectName(_fromUtf8("floor3Up"))
        self.floor1Down = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor1Down.setGeometry(QtCore.QRect(10, 100, 51, 51))
        self.floor1Down.setText(_fromUtf8(""))
        self.floor1Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
        self.floor1Down.setObjectName(_fromUtf8("floor1Down"))
        self.floor2Down = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor2Down.setGeometry(QtCore.QRect(70, 100, 51, 51))
        self.floor2Down.setText(_fromUtf8(""))
        self.floor2Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
        self.floor2Down.setObjectName(_fromUtf8("floor2Down"))
        self.floor3Down = ExtendedQLabel.ExtendedQLabel(self.FloorStatusGrpBx)
        self.floor3Down.setGeometry(QtCore.QRect(130, 100, 51, 51))
        self.floor3Down.setText(_fromUtf8(""))
        self.floor3Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
        self.floor3Down.setObjectName(_fromUtf8("floor3Down"))
        self.groupBox_2 = QtGui.QGroupBox(self.centralwidget)
        self.groupBox_2.setGeometry(QtCore.QRect(330, 310, 211, 211))
        self.groupBox_2.setObjectName(_fromUtf8("groupBox_2"))
        self.floor1Lbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.floor1Lbl.setGeometry(QtCore.QRect(20, 20, 51, 51))
        self.floor1Lbl.setText(_fromUtf8(""))
        self.floor1Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.floor1Lbl.setObjectName(_fromUtf8("floor1Lbl"))
        self.floor2Lbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.floor2Lbl.setGeometry(QtCore.QRect(80, 20, 51, 51))
        self.floor2Lbl.setText(_fromUtf8(""))
        self.floor2Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.floor2Lbl.setObjectName(_fromUtf8("floor2Lbl"))
        self.floor3Lbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.floor3Lbl.setGeometry(QtCore.QRect(140, 20, 51, 51))
        self.floor3Lbl.setText(_fromUtf8(""))
        self.floor3Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.floor3Lbl.setObjectName(_fromUtf8("floor3Lbl"))
        self.EStopLbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.EStopLbl.setGeometry(QtCore.QRect(140, 120, 51, 51))
        self.EStopLbl.setText(_fromUtf8(""))
        self.EStopLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.EStopLbl.setObjectName(_fromUtf8("EStopLbl"))
        self.DoorOpenLbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.DoorOpenLbl.setGeometry(QtCore.QRect(80, 120, 51, 51))
        self.DoorOpenLbl.setText(_fromUtf8(""))
        self.DoorOpenLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.DoorOpenLbl.setObjectName(_fromUtf8("DoorOpenLbl"))
        self.DoorCloseLbl = ExtendedQLabel.ExtendedQLabel(self.groupBox_2)
        self.DoorCloseLbl.setGeometry(QtCore.QRect(20, 120, 51, 51))
        self.DoorCloseLbl.setText(_fromUtf8(""))
        self.DoorCloseLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
        self.DoorCloseLbl.setObjectName(_fromUtf8("DoorCloseLbl"))
        self.label_7 = QtGui.QLabel(self.groupBox_2)
        self.label_7.setGeometry(QtCore.QRect(150, 80, 46, 13))
        self.label_7.setObjectName(_fromUtf8("label_7"))
        self.label_8 = QtGui.QLabel(self.groupBox_2)
        self.label_8.setGeometry(QtCore.QRect(90, 80, 46, 13))
        self.label_8.setObjectName(_fromUtf8("label_8"))
        self.label_9 = QtGui.QLabel(self.groupBox_2)
        self.label_9.setGeometry(QtCore.QRect(30, 80, 46, 13))
        self.label_9.setObjectName(_fromUtf8("label_9"))
        self.label_10 = QtGui.QLabel(self.groupBox_2)
        self.label_10.setGeometry(QtCore.QRect(20, 180, 61, 16))
        self.label_10.setObjectName(_fromUtf8("label_10"))
        self.label_11 = QtGui.QLabel(self.groupBox_2)
        self.label_11.setGeometry(QtCore.QRect(150, 180, 46, 13))
        self.label_11.setObjectName(_fromUtf8("label_11"))
        self.label_12 = QtGui.QLabel(self.groupBox_2)
        self.label_12.setGeometry(QtCore.QRect(80, 180, 51, 16))
        self.label_12.setObjectName(_fromUtf8("label_12"))
        self.ip_btn = QtGui.QPushButton(self.centralwidget)
        self.ip_btn.setGeometry(QtCore.QRect(330, 530, 75, 23))
        self.ip_btn.setObjectName(_fromUtf8("ip_btn"))
        self.ip_editBx = QtGui.QLineEdit(self.centralwidget)
        self.ip_editBx.setGeometry(QtCore.QRect(410, 530, 101, 20))
        self.ip_editBx.setObjectName(_fromUtf8("ip_editBx"))
        self.password_btn = QtGui.QPushButton(self.centralwidget)
        self.password_btn.setGeometry(QtCore.QRect(330, 560, 75, 23))
        self.password_btn.setObjectName(_fromUtf8("password_btn"))
        self.password_editBx = QtGui.QLineEdit(self.centralwidget)
        self.password_editBx.setGeometry(QtCore.QRect(410, 560, 101, 20))
        self.password_editBx.setObjectName(_fromUtf8("password_editBx"))
        Client.setCentralWidget(self.centralwidget)
        self.menubar = QtGui.QMenuBar(Client)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 547, 21))
        self.menubar.setObjectName(_fromUtf8("menubar"))
        Client.setMenuBar(self.menubar)
        self.statusbar = QtGui.QStatusBar(Client)
        self.statusbar.setObjectName(_fromUtf8("statusbar"))
        Client.setStatusBar(self.statusbar)

        self.retranslateUi(Client)
        QtCore.QMetaObject.connectSlotsByName(Client)          
    ## EVENT HANDLERS

    ## Door Close handler
    def DoorCloseClicked(self):
        #print "Door Closed pressed!"
        self.DoorCloseLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
        #### SEND DOOR CLOSE TO server 
        TCP_Send_Message(DOOR_CLOSE)
        TCP_Get_Status() 
    
    ## Door Open handler
    def DoorOpenClicked(self):        
        #print "Door Open pressed!"
        self.DoorOpenLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
        #### SEND DOOR OPEN TO server       
        TCP_Send_Message(DOOR_OPEN)
        TCP_Get_Status() 
    
    ## Emergency Stop handler
    def EStopClicked(self):  
        global estop_active
        print "Emergency Stop pressed!" 
        if estop_active == False:
            estop_active = True
            ## Set ESTOP bright
            self.EStopLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
            ## Then set all other buttons dark
            self.DoorOpenLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
            self.DoorCloseLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
            self.floor1Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
            self.floor2Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
            self.floor3Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
            
            ## Set Up/Down buttons to dark as well.
            self.floor1Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
            self.floor2Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
            self.floor3Up.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowUp_scaled.png")))
            self.floor1Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
            self.floor2Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
            self.floor3Down.setPixmap(QtGui.QPixmap(_fromUtf8("darkArrowDown_scaled.png")))
            #### SEND ESTOP TO server    
            TCP_Send_Message(EMERG_STOP)
            TCP_Get_Status() 
        else:   
            estop_active = False     
            ## Set ESTOP dark
            self.EStopLbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonDark.png")))
    
    ## Floor 1 (car) button handler    
    def floor1Clicked(self):
        #print "Floor 1 inside car pressed!" 
        self.floor1Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
        #### SEND floor 1 pressed (from car) to server
        TCP_Send_Message(CAR_FLOOR_1)
        TCP_Get_Status() 
        

    
    ## Floor 2 (car) button handler    
    def floor2Clicked(self):
        #print "Floor 2 inside car pressed!" 
        self.floor2Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
        #### SEND floor 2 pressed (from car) to server
        TCP_Send_Message(CAR_FLOOR_2)
        TCP_Get_Status() 
    
    ## Floor 3 (car) button handler    
    def floor3Clicked(self):
        #print "Floor 3 inside car pressed!" 
        self.floor3Lbl.setPixmap(QtGui.QPixmap(_fromUtf8("buttonLight.png")))
        #### SEND floor 3 pressed (from car) to server
        TCP_Send_Message(CAR_FLOOR_3)
        TCP_Get_Status() 
      
    ## Floor 1 (call up) button handler    
    def floor1UpClicked(self):
        #print "Floor 1 pressed up!" 
        self.floor1Up.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowUp_scaled.png")))
        #### SEND floor 1 has called up to server.
        TCP_Send_Message(CALL_FLOOR_1_UP)
        TCP_Get_Status() 
    
    ## Floor 2 (call up) button handler    
    def floor2UpClicked(self):
        #print "Floor 2 pressed up!" 
        self.floor2Up.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowUp_scaled.png")))
        #### SEND floor 2 has called up to server.
        TCP_Send_Message(CALL_FLOOR_2_UP)
        TCP_Get_Status() 
        
    ## Floor 3 (call up) button handler    
    def floor3UpClicked(self):
        #print "Floor 3 pressed up!" 
        self.floor3Up.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowUp_scaled.png")))
        #### SEND floor 3 has called up to server.
        TCP_Send_Message(CALL_FLOOR_3_UP)
        TCP_Get_Status() 
        
    ## Floor 1 (call down) button handler    
    def floor1DownClicked(self):
        #print "Floor 1 pressed down!" 
        self.floor1Down.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowDown_scaled.png")))
        #### SEND floor 1 has called down to server.
        TCP_Send_Message(CALL_FLOOR_1_DOWN)
        TCP_Get_Status() 
    
    ## Floor 2 (call down) button handler    
    def floor2DownClicked(self):
        #print "Floor 2 pressed down!" 
        self.floor2Down.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowDown_scaled.png")))
        #### SEND floor 2 has called down to server.
        TCP_Send_Message(CALL_FLOOR_2_DOWN)
        TCP_Get_Status() 
    
    ## Floor 3 (call down) button handler    
    def floor3DownClicked(self):
        #print "Floor 3 pressed down!" 
        self.floor3Down.setPixmap(QtGui.QPixmap(_fromUtf8("lightArrowDown_scaled.png")))
        #### SEND floor 3 has called down to server.
        TCP_Send_Message(CALL_FLOOR_3_DOWN)
        TCP_Get_Status() 
        
    def saveReport(self):
        #print "Save Report button pressed" 
        # Open File
        report = open("Report " + str(datetime.date.now()) + ".log\n\n", 'w')
        # Save Report Data into a file.
        report.write("Filename: " + report.name + ui.textEdit.toPlainText())
        report.close()
        
    def getReport(self):
        print "Get Report button pressed"
        #### SEND request to server for data.
        TCP_Send_Message(GET_SIMPLE_REPORT)
        
        # Now receive data
        try:
            reply = s.recv(4096)
        except socket.timeout:
            print "Reply from server has timed out."
        
        ui.textEdit.clear()
        ui.textEdit.insertPlainText(reply)
        
    def getDiagnostic(self):
        print "Get Diagnostic Report button pressed"  
        #### SEND request to server for data. 
        TCP_Send_Message(GET_DETAILED_REPORT)
        
        # Now receive data
        try:
            reply = s.recv(4096)
        except socket.timeout:
            print "Reply from server has timed out."
        ui.textEdit.clear()
        ui.textEdit.insertPlainText(reply)
        
        #simply print the report wherever needed
    
    
    def retranslateUi(self, Client):
        Client.setWindowTitle(_translate("Client", "Remote Diagnostic Tool", None))
        self.reportGrpBx.setTitle(_translate("Client", "Reports", None))
        self.getReportBtn.setText(_translate("Client", "Get Report", None))
        self.getDiagnosticBtn.setText(_translate("Client", "Get Diagnostic", None))
        self.saveBtn.setText(_translate("Client", "Save As...", None))
        self.statusGrpBx.setTitle(_translate("Client", "Status", None))
        self.label.setText(_translate("Client", "Current Floor:", None))
        self.label_2.setText(_translate("Client", "Destination:", None))
        self.label_3.setText(_translate("Client", "Direction:", None))
        self.groupBox.setTitle(_translate("Client", "Car Status", None))
        self.curFloorLbl.setText(_translate("Client", "0", None))
        self.destFloorLbl.setText(_translate("Client", "0", None))
        self.directionLbl.setText(_translate("Client", "None", None))
        self.FloorStatusGrpBx.setTitle(_translate("Client", "Floor Status", None))
        self.label_5.setText(_translate("Client", "Floor 3:", None))
        self.label_6.setText(_translate("Client", "Floor 2:", None))
        self.label_4.setText(_translate("Client", "Floor 1:", None))
        self.groupBox_2.setTitle(_translate("Client", "Car Commands", None))
        self.label_7.setText(_translate("Client", "Floor 3", None))
        self.label_8.setText(_translate("Client", "Floor 2", None))
        self.label_9.setText(_translate("Client", "Floor 1", None))
        self.label_10.setText(_translate("Client", "Door Close", None))
        self.label_11.setText(_translate("Client", "E-Stop", None))
        self.label_12.setText(_translate("Client", "Door Open", None))
        self.ip_btn.setText(_translate("Client", "Set IP", None))
        self.ip_editBx.setText(_translate("Client", "142.156.193.184", None))
        self.password_btn.setText(_translate("Client", "Set Password", None))
        self.password_editBx.setText(_translate("Client", "ESEsem6", None))


if __name__ == "__main__":
    import sys
    import socket               # Import socket module
    
       
    #first we need to create a tcp connection to the server
    try:
        #create an AF_INET, STREAM socket (TCP)
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error, msg:
        print 'Failed to create socket. Error code: ' + str(msg[0]) + ' , Error message: ' + msg[1]
        sys.exit()
    
    print 'Socket Created!'
        
    try:
        remote_ip = socket.gethostbyname( host )
    
    except socket.gaierror:
        # could not resolve
        print 'Hostname could not be resolved. Exiting'
        sys.exit()
    
    print 'IP address of ' + host + ' is ' + remote_ip
    
    # Connect to remote server
    s.connect((remote_ip, port))
    s.settimeout(1)
    
    print 'Socket connected to ' + host + ' on ip ' + remote_ip
    
    # Authenticate
    TCP_Send_Message('wrong password')

    
    app = QtGui.QApplication(sys.argv)
    Client = QtGui.QMainWindow()
    ui = Ui_Client()
    ui.setupUi(Client)
    
        
    ## Event Handlers connections
    Client.connect(ui.DoorCloseLbl, QtCore.SIGNAL('clicked()'), ui.DoorCloseClicked)
    Client.connect(ui.DoorOpenLbl, QtCore.SIGNAL('clicked()'), ui.DoorOpenClicked)
    Client.connect(ui.EStopLbl, QtCore.SIGNAL('clicked()'), ui.EStopClicked)
    Client.connect(ui.floor1Lbl, QtCore.SIGNAL('clicked()'), ui.floor1Clicked)
    Client.connect(ui.floor2Lbl, QtCore.SIGNAL('clicked()'), ui.floor2Clicked)
    Client.connect(ui.floor3Lbl, QtCore.SIGNAL('clicked()'), ui.floor3Clicked)
    Client.connect(ui.floor1Up, QtCore.SIGNAL('clicked()'), ui.floor1UpClicked)
    Client.connect(ui.floor2Up, QtCore.SIGNAL('clicked()'), ui.floor2UpClicked)
    Client.connect(ui.floor3Up, QtCore.SIGNAL('clicked()'), ui.floor3UpClicked)
    Client.connect(ui.floor1Down, QtCore.SIGNAL('clicked()'), ui.floor1DownClicked)
    Client.connect(ui.floor2Down, QtCore.SIGNAL('clicked()'), ui.floor2DownClicked)
    Client.connect(ui.floor3Down, QtCore.SIGNAL('clicked()'), ui.floor3DownClicked)
    Client.connect(ui.getDiagnosticBtn, QtCore.SIGNAL('clicked()'), ui.getDiagnostic)
    Client.connect(ui.getReportBtn, QtCore.SIGNAL('clicked()'), ui.getReport)
    Client.connect(ui.saveBtn, QtCore.SIGNAL('clicked()'), ui.saveReport)
    Client.connect(ui.ip_btn, QtCore.SIGNAL('clicked()'), TCP_Connect)
    Client.connect(ui.password_btn, QtCore.SIGNAL('clicked()'), TCP_Connect)
        
    Client.show()
    sys.exit(app.exec_())  
    s.close()  



