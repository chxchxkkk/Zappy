from ..protocol.protocol import *


class Caller:
    def __init__(self, parent):
        self.parent = parent

    def __del__(self):
        msg = self.parent.player.team_name + "_" + str(self.parent.player.level) + "_stop"
        # print("STOP CALLING")
        # send_broadcast(self.parent.player.receiver.sock, msg)
        # self.parent.player.receiver.pop()

    def execute(self):
        msg = self.parent.player.team_name + "_" + str(self.parent.player.level) + "_come"
        print("CALLIIIIIIIIIIIIIIIIING")
        return send_broadcast(self.parent.player.receiver.sock, msg)
