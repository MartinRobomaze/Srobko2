import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev

class Controller():
    
    def __init__(self):
        # initialize radio
        GPIO.setmode(GPIO.BCM)
        pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
        radio = NRF24(GPIO, spidev.SpiDev())
        radio.begin(0, 17)
        radio.setPayloadSize(32) 
        radio.setChannel(0x66)
        radio.setDataRate(NRF24.BR_250KBPS)
        radio.setPALevel(NRF24.PA_LOW)
        radio.setAutoAck(True)
        radio.enableDynamicPayloads()
        radio.enableAckPayload()
        radio.openWritingPipe(pipes[0])
        radio.openReadingPipe(1, pipes[1])
            

    def setRadio(self, transmitting=True):
        radio.printDetails()
        radio.startListening()
        if transmitting:
            radio.stopListening()
        

    def sendData(self, filename):
        buffer = []
        with open(filename,"r") as file:
            for data in file:
                data = data.strip().split()
                buffer = [int(i) for i in data]
                print(buffer)
                radio.write(buffer)
                time.sleep(0.01)
