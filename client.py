import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("localhost", 3000))
sent = s.send("wow".encode("utf-8"))
print(sent)
