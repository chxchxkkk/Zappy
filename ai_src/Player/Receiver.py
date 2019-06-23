import socket
import queue
import threading
import select

RECV_SIZE = 4096


class Receiver:
    def __init__(self, sock: socket.socket):
        self.sock = sock
        self.is_receiving = True
        self.messages = queue.Queue()
        self.response = queue.Queue()
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
                    self.add_to_queue(msg)

    def add_to_queue(self, msg):
        if "message" in msg:
            self.messages.put(msg)
        else:
            self.response.put(msg)

    def pop(self):
        if self.response.empty():
            return ""
        else:
            return self.response.get()

    def pop_msg(self):
        if self.messages.empty():
            return ""
        else:
            return self.messages.get()

    def set_receiving(self, value):
        self.is_receiving = value
