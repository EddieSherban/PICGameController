import serial
import keyboard
from pynput.keyboard import Key, Controller

serialPort= serial.Serial(port= "COM4",baudrate=9600,bytesize=8,stopbits=serial.STOPBITS_ONE,timeout=2)
flag= True
controlList=[]
keyPresses = ['w','a','d','s','up','left','down','right','z','n','space','enter']

while flag:
    try:
        if keyboard.is_pressed('q'):
            flag= False
    except:
        flag= True

    line = str(serialPort.readline())
    line = line[2:]
    line = line.split('\\')
    controlList = list(line[0])
    print(controlList)

    for i in range(len(controlList)):
        if controlList[i] == '1':
            keyboard.press(keyPresses[i])
        else:
            keyboard.release(keyPresses[i])

serialPort.close()
