from ..protocol.protocol import *
import random
from ..Elevation import *
from copy import deepcopy

resources = [Resource.LINEMATE, Resource.THYSTAME, Resource.SIBUR, Resource.PHIRAS, Resource.MENDIANE, Resource.DERAUMERE]


class Incantation:
    def __init__(self, parent):
        self.parent = parent
        self.resources_to_put_down = Elevation.find_required_resources(self.parent.player.level)

    def execute(self):
        if self.parent.player.tile_info is None:
            return look(self.parent.player.receiver.sock)
        elif not self.tile_empty():
            queue = []
            queue += [look]
            self.parent.player.actionQueue = queue
            return self.take_resource()
        elif not self.empty_resource():
            for resource in resources:
                if self.resources_to_put_down[resource] == 0:
                    continue
                self.resources_to_put_down[resource] -= 1
                return set_resource(self.parent.player.receiver.sock, resource)
        else:
            print("incanting...")
            self.parent.player.actionQueue += [look]
            return incantation(self.parent.player.receiver.sock)

    def empty_resource(self):
        for resource in resources:
            if self.resources_to_put_down[resource] != 0:
                return False
        return True

    def take_resource(self):
        info = self.parent.player.tile_info[0]
        for resource in resources:
            if info[resource] != 0:
                return take_resource(self.parent.player.receiver.sock, resource)

    def tile_empty(self):
        info = self.parent.player.tile_info[0]
        for resource in resources:
            if info[resource] != 0:
                return False
        return True
