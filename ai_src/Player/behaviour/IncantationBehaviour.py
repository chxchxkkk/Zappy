from ..protocol.protocol import *
import random
from copy import deepcopy


class Incantation:
    def __init__(self, parent):
        self.parent = parent
        self.resources_to_put_down = deepcopy(parent.required_resources_for_level_up)

    def execute(self):
        if self.resources_to_put_down:
            resource = random.choice([*self.resources_to_put_down])
            self.resources_to_put_down[resource] -= 1
            if self.resources_to_put_down[resource] == 0:
                self.resources_to_put_down.pop(resource)
            print("settings rsc: ", resource)
            return set_resource(self.parent.player.receiver.sock, resource)
        else:
            print("incanting...")
            return incantation(self.parent.player.receiver.sock)
