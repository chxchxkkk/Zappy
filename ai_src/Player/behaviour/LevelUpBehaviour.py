from ..Player import *
from .PathFinding import *
from ..Elevation import Elevation
from .IncantationBehaviour import Incantation


class CollectResources:
    def __init__(self, parent: LevelUpBehaviour):
        self.parent = parent
        self.resources_to_find = parent.required_resources

    def execute(self):
        if self.parent.player.tile_info is None:
            return look(self.parent.player.receiver.sock)
        elif self.parent.player.tile_info[0][Resource.FOOD] != 0:
            self.parent.player.tile_info[0][Resource.FOOD] -= 1
            return take_resource(self.parent.player.receiver.sock, Resource.FOOD)
        else:
            try:
                self.parent.player.actionQueue = PathFinding.find_actions_to_resource(self.parent.player.tile_info, Resource.FOOD)
            except:
                self.parent.player.actionQueue = PathFinding.go_elsewhere()
            return Action.NONE


class LevelUpBehaviour:
    def __init__(self, player: Player):
        self.player = player
        self.player_level = player.level
        self.required_resources_for_level_up = Elevation.find_required_resources(self.player_level)
        self.required_players = Elevation.find_required_players(self.player_level) - 1
        for resource in self.required_resources:
            self.required_resources[resource] -= self.player.inventory[resource]
        self.required_resources = {k: v for (k, v) in self.required_resources.items() if v > 0}
        self.current_strategy = self

    def execute_strategy(self):
        if not self.required_resources and not self.required_players:
            if type(self.current_strategy) is not Incantation:
                self.current_strategy = Incantation(self)
        elif self.required_resources:
            if type(self.current_strategy) is not CollectResources:
                self.current_strategy = CollectResources(self)
        elif self.required_players:
            if type(self.current_strategy) is not Group:
                self.current_strategy = Group()
        return self.current_strategy.execute()
