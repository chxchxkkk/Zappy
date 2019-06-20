from .Pendings import Actions
from .Receiver import Receiver
from .Resource import Resource
from .protocol.protocol import *
from .behaviour.Behaviour import FoodBehaviour


class Player:
    def __init__(self, receiver: Receiver, team_name: str):
        print('Je construis le Joueur')
        self.team_name = team_name
        self.remaining_connections = None
        self.map_size = None
        self.receiver = receiver
        self.is_running = True
        self.pending_action = Actions.NONE
        self.is_connected = False
        self.behaviour = None
        self.tile_info = None
        self.action_function_map = {Actions.FORWARD: self.forward_action,
                                    Actions.LOOK: self.parse_look,
                                    Actions.INVENTORY: self.parse_inventory}
        self.inventory = {Resource.FOOD: 10,
                          Resource.DERAUMERE: 0,
                          Resource.LINEMATE: 0,
                          Resource.MENDIANE: 0,
                          Resource.PHIRAS: 0,
                          Resource.SIBUR: 0,
                          Resource.THYSTAME: 0}
        data = self.receiver.pop()
        while self.is_connected is False:
            if data == "WELCOME":
                self.is_running = self.connect_protocol()
                if self.is_running is False:
                    return
            data = self.receiver.pop()
        self.behaviour = FoodBehaviour(self)

    def update(self):
        should_check_inv = 0
        while self.is_running:
            if self.pending_action == Actions.NONE:
                if should_check_inv == 5:
                    self.check_inventory()
                self.behaviour.execute_strategy()
            data = self.receiver.pop()
            if data == "dead":
                print("dead")
                self.is_running = False
                return
            if data != "":
                # print(data)
                self.update_player_data(data)

    def wait_for_data(self):
        data = self.receiver.pop()
        while data == "":
            data = self.receiver.pop()
        return data

    def reset(self):
        self.pending_action = Actions.NONE

    def update_player_data(self, data):
        self.action_function_map[self.pending_action](data)
        if self.pending_action != self.pending_action.NONE:
            self.reset()
        # if self.pending_action == Actions.LOOK and data[0] == '[':
        #     self.parse_look(data)
        #     self.reset()

    def parse_inventory(self, data):
        data = data.replace('[ ', '').replace(' ]', '').replace(', ', ',')
        items = data.split(',')
        for item in items:
            item = item.split(' ')
            self.inventory[Resource(item[0])] = int(item[1])

    def parse_look(self, data):
        data = data.replace('[', '').replace(']', '')
        tiles = data.split(',')
        self.tile_info = []
        i = 0
        for tile in tiles:
            self.tile_info.append(self.init_tile())
            resources = tile.split(' ')
            for resource in resources:
                if resource != "" and resource != "player":
                    self.tile_info[i][Resource(resource)] += 1
            i += 1

    @staticmethod
    def init_tile():
        return {Resource.FOOD: 0,
                Resource.DERAUMERE: 0,
                Resource.LINEMATE: 0,
                Resource.MENDIANE: 0,
                Resource.PHIRAS: 0,
                Resource.SIBUR: 0,
                Resource.THYSTAME: 0}

    def connect_protocol(self):
        print('connected :)')
        send_team_name(self.receiver.sock, self.team_name)
        data = self.wait_for_data()
        if data == "ko":
            return False
        self.remaining_connections = int(data)
        print(self.remaining_connections)
        data = self.wait_for_data()
        self.map_size = list(map(int, data.split()))
        print(self.map_size)
        self.is_connected = True
        return True

    def forward_action(self, data):
        self.tile_info = None

    def check_inventory(self):
        get_inventory(self.receiver.sock)
        self.pending_action = Actions.INVENTORY
