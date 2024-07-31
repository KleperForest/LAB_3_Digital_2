from tkinter import Tk, Label, Button, Entry
import serial
import time
import threading

#------------
# GUI design
#------------

root = Tk()
root.title("LAB3")
root.iconbitmap("UVG.ico")  #se coloca el icono
root.resizable(0, 0)  #poner bloqueado el acceso a redimensionar
root.geometry("400x400")

#---------------------------------------------------------

Runpot = True
cambio = 1  # Variable de multiplexación de potenciometros
bloqueoUART = 1  # Variable de bloqueo de UART normal

#------------
# Reading potenciometers
#------------

entry1 = Entry(root, bg='#fdf2e9')
entry1.place(x=200, y=70, width=30, height=30)

entry2 = Entry(root, bg='#fdf2e9')
entry2.place(x=200, y=120, width=30, height=30)

def pots():
    global cambio
    global bloqueoUART
    
    while Runpot:
        if bloqueoUART == 0:
            arduino.write(bytes('R', 'utf-8'))
            bloqueoUART = 1
            time.sleep(0.3)
        else:
            arduino.write(bytes('Q', 'utf-8'))
            time.sleep(0.1)
            mensaje = arduino.readline().decode('utf-8')  # Si se recibe un mensaje del atmega328p
        
        if cambio == 0:
            entry1.delete(0, 'end')
            entry1.insert(0, mensaje)
            cambio = 1
        else:
            entry2.delete(0, 'end')
            entry2.insert(0, mensaje)
            cambio = 0

#--------------------------------------------------------- 

#------------
# Configure arduino
#------------
arduino = serial.Serial('COM3', 9600)
hilo1 = threading.Thread(target=pots, daemon=True)
hilo1.start()

#---------------------------------------------------------

#------------
# Contador de 8 bits
#------------
def contador():  # Funcion que se activa cuando se presiona el boton del contador
    n1 = entry.get()
    
    if not n1.isdigit():
        lbl158.delete(0, 'end')
        lbl158.insert(0, "Debe ser un número")  # Mensaje de error
        return  # Sale de la función si la entrada no es válida
    
    n2 = int(n1)
    if n2 > 255:
        lbl158.delete(0, 'end')
        lbl158.insert(0, "El número debe ser de 0 a 255")
        return
    
    # Dividir el numero en 3 numeros individuales
    centenas = int((n2 % 1000) / 100)
    decenas = int((n2 % 100) / 10)
    unidades = n2 % 10
    
    arduino.write(bytes('A', 'utf-8'))  # Decirle a Arduino que se va a enviar algo al contador
    time.sleep(0.1)
    
    # Enviar los valores individuales a Arduino
    for digit in (centenas, decenas, unidades):
        arduino.write(bytes(str(digit), 'utf-8'))
        time.sleep(0.1)
    
    lbl158.delete(0, 'end')
    lbl158.insert(0, "Mostrando número")

#---------------------------------------------------------

#------------
# widgets in GUI
#------------

lbl = Label(root, text="LAB_3", bg='#800080', fg="white")
lbl.pack()  # Ubicar el dato

separatorLabel1 = Label(root, text="////////////////////////////////////////////////////////////////////////////", fg='black')
separatorLabel1.pack()  # Ubicar el dato

lbl1 = Label(root, text="ADC 1:", bg="#00FFFF")
lbl1.place(x=50, y=70, width=130, height=30)

lbl2 = Label(root, text="ADC 2:", bg="#00FFFF")
lbl2.place(x=50, y=120, width=130, height=30)

btn = Button(root, text="SEND", command=contador, bg="red", fg="white")  # colocar el boton de envio de número al contador
btn.place(x=50, y=200)

entry = Entry(root, bg='#fdf2e9')
entry.place(x=200, y=200, width=100, height=30)

lbl15 = Label(root, text="Comentario:", bg="yellow")
lbl15.place(x=50, y=250, width=130, height=30)

lbl158 = Entry(root, bg='#fdf2e9')
lbl158.place(x=200, y=250, width=180, height=30)

#---------------------------------------------------------

root.mainloop()  # Bucle infinito
