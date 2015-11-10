export LD_LIBRARY_PATH=.
export mjpg_PATH=/home/pi/godHands/mjpg-test/mjpg-streamer/mjpg-streamer-experimental
$mjpg_PATH/mjpg_streamer -i "$mjpg_PATH/input_raspicam.so -x 640 -y 360 -fps 20" -o "$mjpg_PATH/output_http.so -w $mjpg_PATH/www"
