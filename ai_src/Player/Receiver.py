import socket
import queue
import threading
import select

RECV_SIZE = 4096


class Receiver:
    def __init__(self, sock: socket.socket):
        self.sock = sock
        self.is_receiving = True
        self.queue = queue.Queue(maxsize=100)
        self.mutex = threading.Lock()
        self.worker = threading.Thread(target=self.recv)
        self.worker.start()

    def __del__(self):
        self.worker.join()

    def recv(self):
        while self.is_receiving:
            ready = select.select([self.sock], [], [], 1)
            if ready[0]:
                data = self.sock.recv(RECV_SIZE).decode()
                data = data.split('\n')
                for msg in data:
                    self.mutex.acquire()
                    self.queue.put(msg)
                    self.mutex.release()

    def pop(self):
        if self.queue.empty():
            return ""
        else:
            self.mutex.acquire()
            data = self.queue.get()
            self.mutex.release()
            return data

    def set_receiving(self, value):
        self.is_receiving = value
