from .PathFinding import *

resources = [Resource.DERAUMERE, Resource.MENDIANE, Resource.PHIRAS, Resource.SIBUR, Resource.THYSTAME, Resource.LINEMATE]


class CollectResources:
    def __init__(self, parent):
        self.parent = parent
        self.resources_to_find = parent.required_resources_for_level_up

    def execute(self):
        if self.parent.player.tile_info is None:
            return look(self.parent.player.receiver.sock)
        try:
            resource, tile_idx = self.find_tile_with_resource(self.parent.player.tile_info)
            if tile_idx == 0:
                self.parent.player.tile_info[0][resource] -= 1
                return take_resource(self.parent.player.receiver.sock, resource)
            else:
                self.parent.player.actionQueue = PathFinding.find_actions_to_tile(tile_idx)
        except:
            self.parent.player.actionQueue = PathFinding.go_elsewhere()
        return Action.NONE

    def find_tile_with_resource(self, tile_info):
        for tile_idx in range(0, len(tile_info)):
            for resource in resources:
                if self.resources_to_find[resource] > 0:
                    if tile_info[tile_idx][resource]:
                        return resource, tile_idx
        raise
