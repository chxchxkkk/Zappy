from Player.behaviour import CollectResources
from ..Pendings import *
from ..Elevation import Elevation
from .IncantationBehaviour import Incantation
from .CollectResources import CollectResources


class LevelUpBehaviour:
    def __init__(self, player):
        self.player = player
        self.player_level = player.level
        self.required_resources = self.required_resources_for_level_up = Elevation.find_required_resources(self.player_level)
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
            # TODO: Make Group behaviour to allow player to group with others
            print('needs player')
            return Action.NONE
        return self.current_strategy.execute()
