import socket
from time import sleep
from sys import argv
from os import kill,getpid
from signal import SIGSEGV

if len(argv) != 3:
	print "%s host port"
	exit()

host = argv[1]
port = int(argv[2])

s = socket.socket()
s.connect((host, port))
data = raw_input()
s.send(data)
s.close()

result = open("afl_sync").read(1)
if result == 'e':
	exit()
elif result == 'c':
	kill(getpid(), SIGSEGV)
