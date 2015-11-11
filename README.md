# godHands
Rc Car with raspberryPi and Cam

This Project is for graduation by changyeon.

How To Start :

0. need Apache
1. start mjpg-streamer
    nohup sh start-mjpg.sh&
2. modify ./godHands/www/index.html
    change to your IP
3. start GCM Server
    nohup ./godHands/www/c/doorServer 7880&
4. enter the webServer or setup Application.
