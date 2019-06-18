import socket
from ..Resource import Resource

RECV_SIZE = 4096


def forward(sock: socket.socket):
    msg = str.encode("Forward\n")

    sock.send(msg)
    response = sock.recv(RECV_SIZE).decode()
    print(response)


def get_socket(port: int, host_name: str):
    sock = socket.socket()
    sock.connect((host_name, port))
    return sock


def send_team_name(sock: socket.socket, team_name: str):
    msg = str.encode(team_name + '\n')
    sock.send(msg)


def turn_right(sock: socket.socket):
    msg = str.encode("Right\n")
    sock.send(msg)


def turn_left(sock: socket.socket):
    msg = str.encode("Left\n")
    sock.send(msg)


def get_inventory(sock: socket.socket):
    msg = str.encode("Inventory\n")
    sock.send(msg)


def send_broadcast(sock: socket.socket, message: str):
    msg = str.encode(message + "\n")
    sock.send(msg)


def fork(sock: socket.socket):
    msg = str.encode("Fork\n")
    sock.send(msg)


def eject(sock: socket.socket):
    msg = str.encode("Eject\n")
    sock.send(msg)


def take_resource(sock: socket.socket, resource: Resource):
    msg = str.encode("Take " + str(resource) + "\n")
    sock.send(msg)


def set_resouce(sock: socket.socket, resource: Resource):
    msg = str.encode("Set " + str(resource) + "\n")
    sock.send(msg)


def incantation(sock: socket.socket):
    msg = str.encode("Incantation\n")
    sock.send(msg)
