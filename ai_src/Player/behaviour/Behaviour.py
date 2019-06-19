from .. import Player


class FoodBehaviour:
    def __init__(self, player: Player):
        self.player = player
        self.must_look = True
        self.must_forward = False
        self.must_take = False

    def execute_strategy(self):
        pass


class LevelUpBehaviour:
    def __init__(self, player: Player):
        self.player = player
        pass

    def execute_stragey(self):
        pass
