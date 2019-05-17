import socket
import sys
import asyncio
from ai_src.client_protocol.protocol import *


class CoreAi:
    def __init__(self, team_name, port, host='127.0.0.1'):
        self.team_name = team_name
        self.port = port
        self.host = host
        self.elapsed_actions = []
        self.is_running = True
        try:
            self.tcp_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        except ValueError:
            print(ValueError, file=sys.stderr)
            exit(84)
        server_address = (self.host, port)
        self.tcp_socket.connect(server_address)
        self.is_connected = False
        self.loop = asyncio.get_event_loop()
        task = self.loop.create_task(self.connect_to_server())
        self.loop.run_until_complete(task)

    def __del__(self):
        self.tcp_socket.close()

    async def connect_to_server(self):
        resp = await sendConnectionMessage(self.tcp_socket, self.team_name)
        self.elapsed_actions.append(resp)
        print(resp)
        print(self.elapsed_actions)

    def getElapsedActions(self):
        return self.elapsed_actions

    def clearElapsedActions(self):
        self.elapsed_actions = []
