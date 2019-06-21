from .Resource import Resource


class Elevation:
    resources_per_level = [
        {Resource.LINEMATE: 1},
        {Resource.LINEMATE: 1, Resource.DERAUMERE: 1, Resource.SIBUR: 1},
        {Resource.LINEMATE: 2, Resource.SIBUR: 1, Resource.PHIRAS: 2},
        {Resource.LINEMATE: 1, Resource.DERAUMERE: 1, Resource.SIBUR: 2, Resource.PHIRAS: 1},
        {Resource.LINEMATE: 1, Resource.DERAUMERE: 2, Resource.SIBUR: 1, Resource.MENDIANE: 3},
        {Resource.LINEMATE: 1, Resource.DERAUMERE: 2, Resource.SIBUR: 3, Resource.PHIRAS: 1},
        {Resource.LINEMATE: 2, Resource.DERAUMERE: 2, Resource.SIBUR: 3, Resource.MENDIANE: 2, Resource.PHIRAS: 1,
         Resource.THYSTAME: 1},
    ]

    players_per_level = [1, 2, 2, 4, 4, 6, 6]

    @classmethod
    def find_required_resources(cls, player_level):
        return cls.resources_per_level[player_level - 1]

    @classmethod
    def find_required_players(cls, player_level):
        return cls.players_per_level[player_level - 1]
