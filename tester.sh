#!/bin/bash
./zappy_server &
cd graphical_client
./graphical_client 4242 127.0.0.1 > log &
cd ..
./zappy_ai -p 4242 -n Team1
