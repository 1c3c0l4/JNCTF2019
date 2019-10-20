#!/usr/bin/python3
import time
import socket
import sys
serversocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 
host = "0.0.0.0"
port = 20000
BUFSIZ = 1024
serversocket.bind((host, port))
serversocket.listen(5)
dic=['prosperity','democracy','civility','harmony','freedom','equality','justice','rule_of_law','patriotism','dedication','integrity','friendship']
while True:
   try:
      clientsocket,addr = serversocket.accept()
      start=int(time.time())
      msg='Welcome to the SocketGame, then we will read the rules of the game:please send the socialist core values in 3 seconds, a group of two characters, you can get the flag after success!'+ "\n"
      clientsocket.send(msg.encode()) 
      for i in dic:
          now=int(time.time())
          if now-start>3:
             clientsocket.send("Timeout!".encode())
             clientsocket.close()
          s="Follow me,input "+i+'\n'
          clientsocket.send(s.encode())
          tem=clientsocket.recvfrom(BUFSIZ)
          tem=str(tem[0].decode()).replace("\n",'')
          print(len(tem),len(i))
          if tem!=i:
             clientsocket.send("Wrong,gameover!".encode())
             clientsocket.close()
      with open("/flag",'r',encoding='utf-8') as f:
         flag=f.readline().replace("\n",'')
      clientsocket.send(flag.encode())
      clientsocket.close()
   except:
      continue
