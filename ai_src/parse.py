import argparse


def parse_arguments():
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument('-p', dest='port', type=int)
    parser.add_argument('-n', dest='name', type=str)
    parser.add_argument('-h', dest='host', type=str, default='localhost')
    args = parser.parse_args()
    return args
