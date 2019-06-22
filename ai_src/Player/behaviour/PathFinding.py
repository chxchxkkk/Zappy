import random
from builtins import staticmethod

from Player import Elevation
from ..protocol.protocol import *

queue_list = {1: [forward],
              2: [forward, turn_left, forward],
              3: [turn_left, forward],
              4: [turn_left, forward, turn_left, forward],
              5: [turn_left, turn_left, forward],
              6: [turn_right, forward, turn_right, forward],
              7: [turn_right, forward],
              8: [forward, turn_right, forward]}


class PathFinding:
    turn_nb = 0
    max_player_range = len(Elevation.Elevation.players_per_level)

    @staticmethod
    def find_tile_with_resource(tile_info, resource):
        return tile_info.index(next(tile for tile in tile_info if tile[resource]))

    @staticmethod
    def find_vector_to_tile(tile_id):
        i = 0
        for y in range(0, PathFinding.max_player_range):
            for x in range(-y, y + 1):
                if i == tile_id:
                    return y, x
                i += 1
        raise

    @staticmethod
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

    @staticmethod
    def find_instructions_to_direction(direction):
        return queue_list[direction]

    @staticmethod
    def find_actions_to_resource(tile_info, resource):
        a = PathFinding.find_instructions(
            PathFinding.find_vector_to_tile(PathFinding.find_tile_with_resource(tile_info, resource)))
        return a

    @staticmethod
    def find_actions_to_tile(tile_idx):
        a = PathFinding.find_instructions(PathFinding.find_vector_to_tile(tile_idx))
        return a

    @classmethod
    def go_elsewhere(cls):
        cls.turn_nb += 1
        if cls.turn_nb == 4:
            cls.turn_nb = 0
            return [forward]
        return [random.choice([turn_left, turn_right])]

    @classmethod
    def reset_pathfinding(cls):
        cls.turn_nb = 0
