import RPi.GPIO as GPIO
from python_libs.lib_nrf24 import NRF24
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
radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])
radio.printDetails()
radio.startListening()#pre prijem
radio.stopListening()#pre vysielanie

data=[159,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200]
    
with open('srobko_data.txt','w') as file:
    file.write(" ".join(map(str, data)) + '\n')

radio.write(data)# poslat data
time.sleep(0.01)

import time,tkinter
pl=tkinter.Canvas()
pl.pack()
def zapis(event):
    tl=event.keysym
    global data,su,datax
    su=open('srobko_data.txt','a')
    time.sleep(0.02)
    r=''
    if tl=='Up':
        data[(datax)]+=1
        if data[(datax)]>180:data[(datax)]=180
    if tl=='Down':
        data[(datax)]-=1
        if data[(datax)]<0:data[(datax)]=0
    for i in range(25):
        r=r+str(data[i])+' '
    radio.write(data)# poslat data
    time.sleep(0.01) 
    su.write(r+'\n')
    su.close()
def ktore(event):
    global datax
    x=int(event.keysym[3])
    if 1<=x<=9:datax=x
pl.bind_all('<Key>',ktore)#ktore data
pl.bind_all('<Up>',zapis)#+1
pl.bind_all('<Down>',zapis)#-1

