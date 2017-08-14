#!/bin/bash
while true
do
    python3 ~/Sites/harduino/serial_and_display/serialcom.py "CPU TemperaturesC0-"$(sensors | grep "Core 0" | cut -d + -f 2 | cut -d . -f1)"C ** C1-"$(sensors | grep "Core 1" | cut -d + -f 2 | cut -d . -f1)"C"
	sleep 0.5
done
