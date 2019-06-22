from .behaviour.FoodBehaviour import FoodBehaviour
from .behaviour.LevelUpBehaviour import LevelUpBehaviour
from .protocol.protocol import *
from .Pendings import *
from .Receiver import *
from .Resource import *
import os
from .behaviour.FindPlayerBehaviour import FindPlayerBehaviour


class Player:
    def __init__(self, receiver: Receiver, team_name: str):
        print('Je construis le Joueur')
        self.where_to_go = None
        self.team_name = team_name
        self.remaining_connections = None
        self.map_size = None
        self.player_on_tile = 0
        self.receiver = receiver
        self.is_running = True
        self.pending_action = Action.NONE
        self.is_connected = False
        self.level = 1
        self.must_come = False
        self.behaviour = None
        self.tile_info = None
        self.tick_count = 0
        self.tick_value = {Action.FORWARD: 7,
                           Action.RIGHT: 7,
                           Action.LEFT: 7,
                           Action.LOOK: 7,
                           Action.INVENTORY: 1,
                           Action.BROADCAST: 7,
                           Action.FORK: 42,
                           Action.EJECT: 7,
                           Action.TAKE: 7,
                           Action.SET: 7,
                           Action.INCANTATION: 300,
                           Action.NONE: 0}
        self.action_function_map = {Action.FORWARD: self.forward_action,
                                    Action.RIGHT: self.right_action,
                                    Action.LEFT: self.left_action,
                                    Action.LOOK: self.parse_look,
                                    Action.INVENTORY: self.parse_inventory,
                                    Action.TAKE: (lambda _: 0),
                                    Action.SET: (lambda _: 0),
                                    Action.BROADCAST: (lambda _: 0),
                                    Action.INCANTATION: self.incantation_action,
                                    Action.FORK: self.connect_new_player}
        self.inventory = {Resource.FOOD: 10,
                          Resource.DERAUMERE: 0,
                          Resource.LINEMATE: 0,
                          Resource.MENDIANE: 0,
                          Resource.PHIRAS: 0,
                          Resource.SIBUR: 0,
                          Resource.THYSTAME: 0}
        self.actionQueue = []
        data = self.receiver.pop()
        while self.is_connected is False:
            if data == "WELCOME":
                self.is_running = self.connect_protocol()
                if self.is_running is False:
                    return
            data = self.receiver.pop()
        self.behaviour = LevelUpBehaviour(self)

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

    def wait_for_data(self):
        data = self.receiver.pop()
        while data == "":
            data = self.receiver.pop()
        return data

    @staticmethod
    def init_tile():
        return {Resource.FOOD: 0,
                Resource.DERAUMERE: 0,
                Resource.LINEMATE: 0,
                Resource.MENDIANE: 0,
                Resource.PHIRAS: 0,
                Resource.SIBUR: 0,
                Resource.THYSTAME: 0}

    # TODO: Handling "ko" answers
    def update(self):
        while self.is_running:
            if self.pending_action == Action.NONE:
                self.start_action()
            data = self.receiver.pop()
            if data == "ko":
                print("ko")
            if data == "dead":
                print("dead")
                self.is_running = False
            elif "Elevation underway" in data:
                print('lol j\'incante')
            elif "message" in data:
                data = data.split()
                self.interpret_broadcast(data[2], data[1].replace(',', ''))
            elif data != "":
                self.update_player_data(data)

    def interpret_broadcast(self, msg, direction):
        data = msg.split('_')
        print('Jai recu : ' + msg)
        if len(data) == 3:
            if data[0] == self.team_name and data[1] == str(self.level):
                if data[2] == "come" and not self.must_come and type(self.behaviour) is not FoodBehaviour:
                    self.where_to_go = direction
                    self.must_come = True
                    self.behaviour = FindPlayerBehaviour(self)
                pass

    def start_action(self):
        if self.tick_count > 5:  # 126 tick -> -1 food
            self.check_behaviour()
        elif self.actionQueue:
            self.pending_action = self.actionQueue.pop(0)(self.receiver.sock)
        else:
            self.pending_action = self.behaviour.execute_strategy()

    def check_behaviour(self):
        self.pending_action = get_inventory(self.receiver.sock)
        if self.inventory[Resource.FOOD] > 15 and not self.must_come:
            self.behaviour = LevelUpBehaviour(self)
        # elif self.must_come:
        #     self.behaviour = FindPlayerBehaviour(self)
        elif self.inventory[Resource.FOOD] < 5:
            self.behaviour = FoodBehaviour(self)
        self.tick_count = 0

    def reset(self):
        self.pending_action = Action.NONE

    def update_player_data(self, data):
        # TODO SI ON T'AS EJECT OU BROADCAST
        if self.pending_action != self.pending_action.NONE:
            self.action_function_map[self.pending_action](data)
            self.tick_count += self.tick_value[self.pending_action]
            self.reset()

    def parse_inventory(self, data):
        data = data.replace('[ ', '').replace(' ]', '').replace(', ', ',')
        items = data.split(',')
        for item in items:
            item = item.split()
            self.inventory[Resource(item[0])] = int(item[1])

    def parse_look(self, data):
        data = data.replace('[', '').replace(']', '')
        tiles = data.split(',')
        self.tile_info = []
        i = 0
        self.player_on_tile = 0
        for tile in tiles:
            self.tile_info.append(self.init_tile())
            resources = tile.split(' ')
            for resource in resources:
                if resource != "" and resource != "player":
                    self.tile_info[i][Resource(resource)] += 1
                    pass
                if resource == "player" and i == 0:
                    self.player_on_tile += 1
            i += 1

    def forward_action(self, _):
        self.tile_info = None
        self.player_on_tile = 0
        self.where_to_go = None

    def left_action(self, _):
        self.tile_info = None
        self.player_on_tile = 0
        self.where_to_go = None

    def right_action(self, _):
        self.tile_info = None
        self.player_on_tile = 0
        self.where_to_go = None

    def incantation_action(self, data):
        if "Current level: " in data:
            self.level += 1
            if self.level == 3:
                print('WOW LE NIVEAU 3 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!')
            print('new level : ', self.level)
            self.actionQueue = [fork]
            self.must_come = False
            self.behaviour.reset_data_for_level_up()

    def connect_new_player(self, _):
        print("CONNECT")
