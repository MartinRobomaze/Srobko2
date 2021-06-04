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
#radio.openWritingPipe(pipes[0])
radio.openReadingPipe(0, pipes[1])
radio.printDetails()
radio.startListening()#pre prijem
#radio.stopListening()#pre vysielanie
    
su=open('srobko_data.txt','w')
#data=[159,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,200]
data=[0]*25
data[0]=159
data[1]=0
data[2]=0
data[3]=0
data[4]=0
data[5]=0
data[6]=0
data[7]=0
data[8]=0
data[9]=0
data[10]=0
data[11]=0
data[12]=0
data[13]=0
data[14]=0
data[15]=0
data[16]=0
data[17]=0
data[18]=0
data[19]=0
data[20]=0
data[21]=0
data[22]=0
data[23]=0
data[24]=200
r=''
#for i in range(25):
#   r=r+str(data[i])+' '
#su.write(r+'\n')

while(1): 
    while not radio.available(0):
         time.sleep(1 / 100)      
    text = []
    radio.read(text, radio.getDynamicPayloadSize())#nacita pole cisel
    r=''
    for i in range(len(text)):
        r=r+str(text[i])+' '
    su.write(r+'\n')
    print(r) 
