import random
from .. import Player
from ..protocol.protocol import *
from ..Resource import Resource


def find_tile_with_resource(tile_info, resource):
    return tile_info.index(next(tile for tile in tile_info if tile[resource]))


def find_vector_to_tile(tile_id):
    i = 0
    for y in range(0, 8):
        for x in range(-y, y + 1):
            if i == tile_id:
                return y, x
            i += 1
    raise


def find_instructions(vector_to_tile):
    if vector_to_tile == -1:
        return [turn_left]
    instructions = []
    for y in range(0, vector_to_tile[0]):
        instructions += [forward]
    if vector_to_tile[1] != 0:
        instructions += [turn_left if vector_to_tile[1] < 0 else turn_right]
    for x in range(0, abs(vector_to_tile[1])):
        instructions += [forward]
    return instructions


def find_actions_to_food(tile_info):
    print("finding actions")
    a = find_instructions(find_vector_to_tile(find_tile_with_resource(tile_info, Resource.FOOD)))
    print(a)
    return a


def go_elsewhere():
    go_elsewhere.turn_nb += 1
    if go_elsewhere.turn_nb == 4:
        go_elsewhere.turn_nb = 0
        return [forward]
    return [random.choice([turn_left, turn_right])]


go_elsewhere.turn_nb = 0


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
            try:
                self.player.actionQueue = find_actions_to_food(self.player.tile_info)
            except:
                self.player.actionQueue = go_elsewhere()


class LevelUpBehaviour:
    def __init__(self, player: Player):
        self.player = player
        pass

    def execute_strategy(self):
        turn_right(self.player.receiver.sock)
        pass
