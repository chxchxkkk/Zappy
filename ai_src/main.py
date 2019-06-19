from parse import parse_arguments
import sys
from Player.Player import Player
from Player.Receiver import Receiver
from Player.protocol.protocol import get_socket

if __name__ == '__main__':
    args = parse_arguments()
    print(args)
    if args.name is None or args.port is None:
        sys.exit(84)
    else:
        print(type(args.port))
        print(type(args.host))
        sock = get_socket(args.port, args.host)
        receiver = Receiver(sock)
        player = Player(receiver, args.name)
        player.update()
        receiver.set_receiving(False)
