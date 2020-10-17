# importa a biblioteca serial encontrada no endereço: https://pypi.python.org/pypi/pyserial
import serial
import tkinter as tk

""" arduino_uno = serial.Serial('COM1', 9600)
print("criou serial")

#arduino_uno.open()  
#print("abriu serial")

ligar_led = 's'

# loop para comunicação
while(ligar_led == 's'):

    # ligar_led = raw_input('Informe qual led queres ligar (a, b, y ou r) para sair informe s: ')
    cmd = input('Digite o comando:')

    arduino_uno.write(cmd.encode())
    print(cmd)

# print(arduino_uno.readall()+'\n\n')
# fecha comunicaçao
arduino_uno.close()
 """


def keypress(event):
    if event.keysym == 'Escape':
        root.destroy()
    x = event.char
    if x == "w":
        print("blaw blaw blaw")
    elif x == "a":
        print("blaha blaha blaha")
    elif x == "s":
        print("blash blash blash")
    elif x == "d":
        print("blad blad blad")
    else:
        print(x)


root = tk.Tk()
print("Press a key (Escape key to exit):")
root.bind_all('<Key>', keypress)
# don't show the tk window
root.withdraw()
root.mainloop()