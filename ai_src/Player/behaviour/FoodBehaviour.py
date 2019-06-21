from ..protocol.protocol import *
from .PathFinding import PathFinding


class FoodBehaviour:
    def __init__(self, player):
        self.player = player

    def execute_strategy(self):
        if self.player.tile_info is None:
            return look(self.player.receiver.sock)
        elif self.player.tile_info[0][Resource.FOOD] != 0:
            self.player.tile_info[0][Resource.FOOD] -= 1
            return take_resource(self.player.receiver.sock, Resource.FOOD)
        else:
            try:
                self.player.actionQueue = PathFinding.find_actions_to_resource(self.player.tile_info, Resource.FOOD)
            except:
                self.player.actionQueue = PathFinding.go_elsewhere()
            return Action.NONE
