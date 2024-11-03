import socket
import time

s = None
while 1:
    try:
        if s is None:
            s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.connect(("localhost", 3000))
    except Exception:
        pass
    else:
        s.send("0 alex 100500".encode("utf-8"))
        s.close()
        s = None
        # print("Sent: ", sent)
        # print("Recv: ", s.recv(512).decode("utf-8"))
    time.sleep(1)
