import bluetooth

bt_addr = "20:15:08:03:83:73"
port = 1
sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
sock.connect((bt_addr, port))

count = 0

while 1:
	count+=1
