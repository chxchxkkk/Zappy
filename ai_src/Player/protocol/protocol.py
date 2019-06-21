import socket

from Player.Pendings import Action
from ..Resource import Resource

RECV_SIZE = 4096


def get_socket(port: int, host_name: str):
    sock = socket.socket()
    sock.connect((host_name, port))
    return sock


def send_team_name(sock: socket.socket, team_name: str):
    msg = str.encode(team_name + '\n')
    sock.send(msg)


def forward(sock: socket.socket):
    msg = str.encode("Forward\n")
    sock.send(msg)
    return Action.FORWARD


def turn_right(sock: socket.socket):
    msg = str.encode("Right\n")
    sock.send(msg)
    return Action.RIGHT


def turn_left(sock: socket.socket):
    msg = str.encode("Left\n")
    sock.send(msg)
    return Action.LEFT


def get_inventory(sock: socket.socket):
    msg = str.encode("Inventory\n")
    sock.send(msg)
    return Action.INVENTORY


def send_broadcast(sock: socket.socket, message: str):
    msg = str.encode(message + "\n")
    sock.send(msg)
    return Action.BROADCAST


def fork(sock: socket.socket):
    msg = str.encode("Fork\n")
    sock.send(msg)
    return Action.FORK


def eject(sock: socket.socket):
    msg = str.encode("Eject\n")
    sock.send(msg)
    return Action.EJECT


def take_resource(sock: socket.socket, resource: Resource):
    msg = str.encode("Take " + resource.value + "\n")
    sock.send(msg)
    return Action.TAKE


def set_resource(sock: socket.socket, resource: Resource):
    msg = str.encode("Set " + resource.value + "\n")
    sock.send(msg)
    return Action.SET


def incantation(sock: socket.socket):
    msg = str.encode("Incantation\n")
    sock.send(msg)
    return Action.INCANTATION


def look(sock: socket.socket):
    msg = str.encode("Look\n")
    sock.send(msg)
    return Action.LOOK
