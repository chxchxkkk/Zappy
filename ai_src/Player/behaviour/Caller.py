from ..protocol.protocol import *


class Caller:
    def __init__(self, parent):
        self.parent = parent

    def execute(self):
        msg = self.parent.player.team_name + "_" + str(self.parent.player.level) + "_come"
        print("CALLIIIIIIIIIIIIIIIIING")
        return send_broadcast(self.parent.player.receiver.sock, msg)
