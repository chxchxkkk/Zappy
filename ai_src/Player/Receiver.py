import socket
import queue
import threading
import select
import sys

RECV_SIZE = 4096


class Receiver:
    def __init__(self, sock: socket.socket):
        self.sock = sock
        self.is_receiving = True
        self.queue = queue.Queue()
        self.worker = threading.Thread(target=self.recv)
        self.worker.start()

    def __del__(self):
        self.is_receiving = False
        self.worker.join()

    def recv(self):
        while self.is_receiving:
            ready = select.select([self.sock], [], [], 1)
            if ready[0]:
                data = self.sock.recv(RECV_SIZE).decode()
                data = data.split('\n')
                for msg in data:
                    # to handle sigkill (otherwise queue.put does not stop)
                    if not self.is_receiving:
                        exit(84)
                    self.queue.put(msg)

    def pop(self):
        if self.queue.empty():
            return ""
        else:
            data = self.queue.get()
            return data

    def set_receiving(self, value):
        self.is_receiving = value
