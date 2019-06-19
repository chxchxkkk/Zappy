from .Pendings import Actions
from .Receiver import Receiver
from .protocol.protocol import send_team_name
from .behaviour.Behaviour import FoodBehaviour


class Player:
    def __init__(self, receiver: Receiver, team_name: str):
        print('Je construit le Joueur')
        self.team_name = team_name
        self.remaining_connections = None
        self.map_size = None
        self.receiver = receiver
        self.is_running = True
        self.pending_action = Actions.NONE
        self.is_connected = False
        self.behaviour = None
        data = self.receiver.pop()
        while self.is_connected is False:
            if data == "WELCOME":
                self.is_running = self.connect_protocol()
                if self.is_running is False:
                    return
            data = self.receiver.pop()
        self.behaviour = FoodBehaviour(self)

    def update(self):
        while self.is_running:
            data = self.receiver.pop()
            if data == "dead":
                self.is_running = False
            if data != "" and data != "dead":
                self.update_player_data(data)
                self.behaviour.execute_strategy()

    def wait_for_data(self):
        data = self.receiver.pop()
        while data == "":
            data = self.receiver.pop()
        return data

    def update_player_data(self, data):
        if self.pending_action == Actions.FORWARD and data == "ok":
            print('forward')

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

