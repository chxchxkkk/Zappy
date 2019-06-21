from .LevelUpBehaviour import LevelUpBehaviour
from ..protocol.protocol import *
import random


class Incantation:
    def __init__(self, parent: LevelUpBehaviour):
        self.parent = parent
        self.resources_to_put_down = parent.required_resources_for_level_up

    def execute_strategy(self):
        if self.resources_to_put_down:
            resource = random.choice(list(self.resources_to_put_down.items()))
            self.resources_to_put_down[resource] -= 1
            return set_resource(self.parent.player.receiver.sock, self.resources_to_put_down.keys()[0])
        else:
            return incantation(self.parent.player.receiver.sock)
