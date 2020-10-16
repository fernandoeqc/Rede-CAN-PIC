 #importa a biblioteca serial encontrada no endereço: https://pypi.python.org/pypi/pyserial  
import serial  
 
arduino_uno = serial.Serial('COM1',9600)
print("criou serial")

""" arduino_uno.open()  
print("abriu serial") """

ligar_led='s'  
#loop para comunicação  
while(ligar_led =='s'):  
#ligar_led = raw_input('Informe qual led queres ligar (a, b, y ou r) para sair informe s: ')  
    cmd = input('Digite o comando:')
    arduino_uno.write(cmd) 
    print(cmd)



    """ defeito unincode """
#print(arduino_uno.readall()+'\n\n')  
#fecha comunicaçao  
arduino_uno.close()  