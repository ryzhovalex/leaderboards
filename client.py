import socket
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("localhost", 3000))
while 1:
    s.send("0 alex 100500".encode("utf-8"))
    # print("Sent: ", sent)
    # print("Recv: ", s.recv(512).decode("utf-8"))
    time.sleep(1)
