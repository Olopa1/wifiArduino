import socket
import time

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect(("192.168.0.102",7070))

toSend = ""
while toSend != "stop":
    toSend = input("Wprowadz tekst: ")
    s.send(toSend.encode())
s.close()
time.sleep(20)

