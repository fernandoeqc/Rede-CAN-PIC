import pyHook
import pythoncom

def tecla_pressionada(evento):
   # print("Alguma tecla pressionada")
    print (chr(evento.Ascii))

hook = pyHook.HookManager()
hook.KeyDown = tecla_pressionada #sem ()
hook.HookKeyboard()

pythoncom.PumpMessages() #cria loop infinito e espera mensagens do SO