import sys
import argparse
from ai_src.graphical_client.graphical import Graphical
from ai_src.ai.core import CoreAi


def display_help():
    print("USAGE:", sys.argv[0], "-p port -n name -h machine")
    print("\tport\tis the port number")
    print("\tname\tis the name of the team")
    print("\tmachine\tis the name of the machine; localhost by default")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument("-p", "--port", type=int, help="Port number")
    parser.add_argument("-n", "--name", type=str, help="Name of the team")
    parser.add_argument("-h", type=str, help="Name of the machine")
    parser.add_argument("-g", action="store_true")
    parser.add_argument("--help", action="store_true")
    args = parser.parse_args()
    if args.help:
        display_help()
    elif args.name and args.port:
        print(args)
        if args.h is None:
            args.h = "127.0.0.1"
        if args.g:
            graphical = Graphical(args.port, args.name, args.h)
            graphical.run()
        else:
            core = CoreAi(args.name, args.port, args.h)
            core.start()
            core.join()
        exit(0)
    else:
        exit(84)
