# importa a biblioteca serial encontrada no endereço: https://pypi.python.org/pypi/pyserial
import serial
import tkinter as tk

arduino_uno = serial.Serial('COM1', 9600, timeout=0.5)
print("criou serial")

root = tk.Tk()

canvas1 = tk.Canvas(root, width=400, height=300)
canvas1.pack()

entry1 = tk.Entry(root)
canvas1.create_window(200, 140, window=entry1)

label1 = None


def delButton():
    label1.destroy()


def sendCommand():
    global label1

    if label1 is not None:
        label1.destroy()

    cmd = entry1.get()

    arduino_uno.write(cmd.encode())
    print(cmd)

    label1 = tk.Label(root, text=cmd)
    label1.pack(pady=10)
    # canvas1.create_window(200, 230, window=label1)


send_button = tk.Button(text='Get the Square Root', command=sendCommand)
canvas1.create_window(200, 180, window=send_button)

delete_button = tk.Button(text='Delete the label', command=delButton)
canvas1.create_window(200, 210, window=delete_button)

# root.mainloop()

while True:
    root.update()

    print("inicio")
    cc = str(arduino_uno.readline())
    print(cc[2:][:-5])
    print("fim")
    



# fecha comunicaçao
arduino_uno.close()
print("fim")
