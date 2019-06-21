from .PathFinding import *


class CollectResources:
    def __init__(self, parent):
        self.parent = parent
        self.resources_to_find = parent.required_resources

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
            for rsc in self.resources_to_find:
                if tile_info[tile_idx][rsc]:
                    return rsc, tile_idx
        raise
