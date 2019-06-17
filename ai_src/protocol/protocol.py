import socket

RECV_SIZE = 4096


def forward(sock: socket.socket):
    msg = str.encode("Forward\n")

    sock.send(msg)
    response = sock.recv(RECV_SIZE).decode()
    print(response)
