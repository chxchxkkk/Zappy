from .. import Player
from ..Pendings import Action
from ..protocol.protocol import *
from ..Resource import Resource


class FoodBehaviour:
    def __init__(self, player: Player):
        self.player = player

    def execute_strategy(self):
        if self.player.tile_info is None:
            look(self.player.receiver.sock)
            self.player.pending_action = Action.LOOK
        elif self.player.tile_info[0][Resource.FOOD] != 0:
            self.player.tile_info[0][Resource.FOOD] -= 1
            take_resource(self.player.receiver.sock, Resource.FOOD)
            self.player.pending_action = Action.TAKE
        else:
            forward(self.player.receiver.sock)
            self.player.pending_action = Action.FORWARD


class LevelUpBehaviour:
    def __init__(self, player: Player):
        self.player = player
        pass

    def execute_strategy(self):
        turn_right(self.player.receiver.sock)
        pass
