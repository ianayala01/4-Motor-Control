#!/bin/bash

# this script runs the motors to move the car into a specified direction
# press ctrl + c between key presses. The script isn't smart enough to kill the current process
# made this for testing purposes

while true; do

    read -n 1 -s -r key

    case "$key" in

	# press 8 to go forward
        8)
		echo "Going Forward"
		sudo ./fwd
		;;

	# press 7 to go diagonal: fwd/left
	7)
		echo "Going NW"
		sudo ./fwdLeft
		;;

	# press 4 to go left
        4)
		echo "Going Left"
		sudo ./left
		;;

	# you get the idea...
	1)
		echo "Going SW"
		sudo ./bckLeft
		;;

	2)
		echo "Going Back"
		sudo ./bck
		;;

	3)
		echo "Going SE"
		sudo ./bckRight
		;;

	6)
		echo "Going Right"
		sudo ./right
		;;

	9)
		echo "going NE"
		sudo ./fwdRight
		;;
	5)
		exit 0
		;;

        +)
		echo "turning right"
		sudo ./spinRight
		;;
	-)
		echo "turning left"
		sudo ./spinLeft
		;;
	0)
		echo "woooooooooooo"
		sudo ./donut
		;;
    esac
done
