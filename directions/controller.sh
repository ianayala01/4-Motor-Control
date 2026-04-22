#!/bin/bash

while true; do
    # -n 1: Read only one character
    # -s: Silent mode (don't echo the key pressed)
    # -r: Do not allow backslashes to escape characters
    read -n 1 -s -r key

    case "$key" in

        8)
		echo "Going Forward"
		sudo ./fwd
		;;

	7)
		echo "Going NW"
		sudo ./fwdLeft
		;;

        4)
		echo "Going Left"
		sudo ./left
		;;

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
