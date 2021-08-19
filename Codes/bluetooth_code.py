#!/usr/bin/env python
import time
import serial
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
pump=23
GPIO.setup(pump,GPIO.OUT)
ser = serial.Serial(
    port = '/dev/rfcomm0',
    baudrate = 9600,
    parity = serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize = serial.EIGHTBITS,
    timeout=11
    )

while 1:
    x=ser.readline().strip()
    print('Received:%s'%x)
