import RPi.GPIO as GPIO
from python_libs.lib_nrf24 import NRF24
import time
import spidev
from threading import Thread
from queue import Queue


class RadioController():
    def __init__(self):
        # initialize radio
        GPIO.setmode(GPIO.BCM)
        self.pipes = [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1],
                      [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
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
        self.stopping_queue = Queue(maxsize=1)

    def setRadio(self, transmitting: bool):
        # self.radio.printDetails()
        self.radio.startListening()
        if transmitting:
            self.radio.stopListening()

    def sendData(self, filename):
        buffer = []
        with open(filename, "r") as file:
            for data in file:
                data = data.strip().split()
                buffer = [int(i) for i in data]
                print(buffer)
                self.radio.write(buffer)
                time.sleep(0.01)

    def receiveData(self, filename):
        self.setRadio(transmitting=False)
        thread = Thread(target=self.receivingThread, args=(filename,))
        thread.start()

    def receivingThread(self, filename):
        with open("movements/" + filename + ".rbm", "w") as file:
            while True:
                if not self.stopping_queue.empty():
                    if self.stopping_queue.get() == "STOP":
                        break
                while not self.radio.available(0):
                    time.sleep(1 / 100)
                data = []
                self.radio.read(data, self.radio.getDynamicPayloadSize())
                file.write(" ".join(map(str, data)) + '\n')
                time.sleep(0.01)

    def stopReceiving(self):
        self.stopping_queue.put("STOP")

    def sendData(self, filename):
        self.setRadio(transmitting=True)
        thread = Thread(target=self.sendingThread, args=(filename,))
        thread.start()

    def sendingThread(self, filename):
        with open("movements/" + filename + ".rbm", "r") as file:
            for line in file:
                if not self.stopping_queue.empty():
                    if self.stopping_queue.get() == "STOP":
                        break
                print(line.strip())
                self.radio.write(line.strip())
                time.sleep(0.01)
    
    def stopSending(self):
        self.stopping_queue.put("STOP")
