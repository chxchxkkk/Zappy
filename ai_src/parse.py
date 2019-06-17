# ∼/B-PSU-403> ./zappy_ai –help
# USAGE: ./zappy_ai -p port -n name -h machine
# port is the port number
# name is the name of the team
# machine is the name of the machine; localhost by default
#
import argparse

import argparse
import sys

def parse_arguments():
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument('-p', dest='port', type=int)
    parser.add_argument('-n', dest='name', type=str)
    parser.add_argument('-h', dest='host', type=str, default='localhost')
    args = parser.parse_args()
    return args
