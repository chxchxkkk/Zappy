import sys
import signal
from parse import parse_arguments
from Player.Player import Player
from Player.Receiver import Receiver
from Player.protocol.protocol import get_socket


receiver = None


def signal_handler(sig, frame):
    receiver.__del__()
    print("force exit", file=sys.stderr)
    exit(84)


if __name__ == '__main__':
    args = parse_arguments()
    if args.name is None or args.port is None:
        sys.exit(84)
    signal.signal(signal.SIGINT, signal_handler)
    sock = get_socket(args.port, args.host)
    receiver = Receiver(sock)
    player = Player(receiver, args.name)
    player.update()
    print('set receeiving false')
    receiver.set_receiving(False)
