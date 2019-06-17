from parse import parse_arguments
import socket


if __name__ == '__main__':
    args = parse_arguments()

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((args.host, args.port))
    print("Connection on {}".format(args.port))

    print("Close")
    sock.close()
