from pwn import *
import time, hashlib, subprocess

ok = 0
while (ok == 0):
	try:
		conn = remote('dbleaks.dctf18-finals.def.camp', 13021)
		data = conn.recvuntil('You need')[:-8]
		data = eval(data)
		ok = 1
	except:
		time.sleep(1)

pers = {}
salts = {}
hashes = {}
control = "279146358279"

for message in data[0]:
	pers[message[0]] = message[1]
	hashes[message[0]] = message[2]
	salts[message[0]] = message[3]

for message in data[1]:
    if 'happy birthday' in message[1].lower():
	id = message[0]
	LL = message[2].split('/')[0]
	ZZ = message[2].split('/')[1]

	sex = "0"
	if (pers[id][-1:] == 'A'):
		sex = "1"
	
	print ("Calling Engine...")
	
	process = (subprocess.Popen(["./engine", ZZ, LL, sex, hashes[id], salts[id]], stdout=subprocess.PIPE))
	stdout = process.stdout
	cnp = stdout.readline()[2:-1]
	conn.sendline(cnp)
	print (conn.recv())