import bluetooth

bt_addr = "20:15:08:03:83:73"
port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bt_addr, port))

while 1:
	tosend = raw_input()
	if tosend!='q':
		sock.send(tosend)
	else:
		break;

sock.close()
