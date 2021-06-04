import RPi.GPIO as GPIO
from python_libs.lib_nrf24 import NRF24
import time
import spidev

class Controller():

    def __init__(self):
        # initialize radio
        GPIO.setmode(GPIO.BCM)
        self.pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
        self.radio = NRF24(GPIO, spidev.SpiDev())
        self.radio.begin(0, 17)
        self.radio.setPayloadSize(32) 
        self.radio.setChannel(0x66)
        self.radio.setDataRate(NRF24.BR_250KBPS)
        self.radio.setPALevel(NRF24.PA_LOW)
        self.radio.setAutoAck(True)
        self.radio.enableDynamicPayloads()
        self.radio.enableAckPayload()
        self.radio.openWritingPipe(self.pipes[0])
        self.radio.openReadingPipe(1, self.pipes[1])


    def setRadio(self, transmitting=True):
        self.radio.printDetails()
        self.radio.startListening()
        if transmitting:
            self.radio.stopListening()


    def sendData(self, filename):
        buffer = []
        with open(filename,"r") as file:
            for data in file:
                data = data.strip().split()
                buffer = [int(i) for i in data]
                print(buffer)
                self.radio.write(buffer)
                time.sleep(0.01)
