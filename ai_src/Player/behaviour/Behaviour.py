from .. import Player
from ..protocol.protocol import *
from ..Resource import Resource


def find_tile_with_resource(tile_info, resource):
    return tile_info.indexof(next(tile for tile in tile_info if tile[resource]))


def find_vector_to_tile(tile_id):
    return []


def find_instructions(path_to_food):
    return path_to_food


def find_actions_to_food(tile_info):
    find_instructions(find_vector_to_tile(find_tile_with_resource(tile_info, Resource.FOOD)))
    return [forward]


class FoodBehaviour:
    def __init__(self, player: Player):
        self.player = player

    def execute_strategy(self):
        if self.player.tile_info is None:
            self.player.pending_action = look(self.player.receiver.sock)
        elif self.player.tile_info[0][Resource.FOOD] != 0:
            self.player.tile_info[0][Resource.FOOD] -= 1
            self.player.pending_action = take_resource(self.player.receiver.sock, Resource.FOOD)
        else:
            self.player.actionQueue = find_actions_to_food(self.player.tile_info)


class LevelUpBehaviour:
    def __init__(self, player: Player):
        self.player = player
        pass

    def execute_strategy(self):
        turn_right(self.player.receiver.sock)
        pass
