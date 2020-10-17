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

canvas1 = tk.Canvas(root, width=400, height=300)
canvas1.pack()

entry1 = tk.Entry(root)
canvas1.create_window(200, 140, window=entry1)

label1 = None


def delButton():
    label1.destroy()


def getSquareRoot():
    global label1

    if label1 is not None:
        label1.destroy()
        print("destruido")

    x1 = entry1.get()

    label1 = tk.Label(root, text=x1)
    label1.pack(pady=10)
    print(label1)
    #canvas1.create_window(200, 230, window=label1)


send_button = tk.Button(text='Get the Square Root', command=getSquareRoot)
canvas1.create_window(200, 180, window=send_button)

delete_button = tk.Button(text='Delete the label', command=delButton)
canvas1.create_window(200, 210, window=delete_button)




""" print("Press a key (Escape key to exit):")
root.bind_all('<Key>', keypress)
# don't show the tk window
root.withdraw() """
root.mainloop()
