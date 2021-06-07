import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
 
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
radio.openWritingPipe(pipes[1])
radio.openReadingPipe(1, pipes[1])
radio.printDetails()
radio.startListening()#pre prijem 
#radio.stopListening()#pre vysielanie
def poslat():
    radio.stopListening()#pre vysielanie    
    su=open('srobko_data.txt','r')
    buf=[0]*25
    for data in su:    
        data=data.strip()
        #print(data)
        data=data.split()
        for i in range(len(data)):
            buf[i]=int(data[i])
        print(buf)
        radio.write(buf)  
    su.close()
    prijem()
def prijem():
    radio.startListening()#pre prijem 
  #while(1): 
    while not radio.available(0):
        time.sleep(1 / 100)        
    text = []
    radio.read(text, radio.getDynamicPayloadSize()+1)
    for i in range (len(text)-1):
        print(text[i],end =' ')
    print()
    if text[0]==1:
        poslat()
    time.sleep(0.2)
def cas():
    prijem()
    pl.after(1,cas)
import tkinter
pl=tkinter.Canvas()
pl.pack()
cas()

