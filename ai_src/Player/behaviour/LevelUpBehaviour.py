from copy import deepcopy
from Player.behaviour import CollectResources
from Player.behaviour.Caller import Caller
from ..protocol.protocol import *
from ..Elevation import Elevation
from .IncantationBehaviour import Incantation
from .CollectResources import CollectResources

resources = [Resource.DERAUMERE, Resource.MENDIANE, Resource.PHIRAS, Resource.SIBUR, Resource.THYSTAME,
             Resource.LINEMATE]


class LevelUpBehaviour:
    def __init__(self, player):
        self.player = player
        self.player_level = player.level
        self.required_resources_for_level_up = deepcopy(Elevation.find_required_resources(self.player_level))
        for resource in resources:
            self.required_resources_for_level_up[resource] -= self.player.inventory[resource]
        self.required_player = deepcopy(Elevation.find_required_players(self.player_level))
        self.current_strategy = None
        self.is_setting_resources = False

    def execute_strategy(self):
        print(self.enough_players())
        if self.is_setting_resources:
            pass
        elif not self.enough_resources():
            print("mode collect")
            if type(self.current_strategy) is not CollectResources:
                self.current_strategy = CollectResources(self)
        elif not self.enough_players():
            print("mode caller")
            if type(self.current_strategy) is not Caller:
                self.current_strategy = Caller(self)
            self.player.actionQueue += [look]
        else:
            print("mode incantation")
            if type(self.current_strategy) is not Incantation:
                self.current_strategy = Incantation(self)
                self.is_setting_resources = True
        return self.current_strategy.execute()

    def enough_players(self):
        if self.player.player_on_tile >= self.required_player:
            return True
        return False

    def enough_resources(self):
        for resource in resources:
            if self.required_resources_for_level_up[resource] > self.player.inventory[resource]:
                return False
        return True

    def reset_data_for_level_up(self):
        self.player_level = self.player.level
        self.required_resources_for_level_up = deepcopy(Elevation.find_required_resources(self.player_level))
        for resource in resources:
            self.required_resources_for_level_up[resource] -= self.player.inventory[resource]
        self.required_player = deepcopy(Elevation.find_required_players(self.player_level))
