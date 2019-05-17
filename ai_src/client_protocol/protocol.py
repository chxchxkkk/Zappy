import socket
import sys

RECV_SIZE = 4096
EVENT_FAIL = 0
EVENT_CONNECTED = 1


async def sendConnectionMessage(sock: socket.socket, team_name):
    print('connecting to server ...')
    data = sock.recv(RECV_SIZE).decode()
    data = data.split('\n')
    if data[0] != 'WELCOME':
        print('Failed to connect to server', file=sys.stderr)
        exit(84)
    msg = str.encode(team_name + '\n')
    sock.send(msg)
    data = sock.recv(RECV_SIZE).decode()
    data = data.split('\n')
    if data[0] == 'ko':
        print('Please verify your teamName', file=sys.stderr)
    try:
        client_num = int(data[0])
        x = [int(i) for i in data[1].split()]
        resp = (EVENT_CONNECTED, x[0], x[1], client_num)
        return resp
    except ValueError:
        print('Failed to connect to server', file=sys.stderr)
        exit(84)
