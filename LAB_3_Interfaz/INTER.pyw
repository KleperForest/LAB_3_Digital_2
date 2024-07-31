from tkinter import  Tk, Label, Button, Entry
import serial,time
import threading

#------------
# GUI design
#------------

root = Tk()

root.title("LAB3")

root.iconbitmap("UVG.ico")  #se coloca el icono 
root.resizable(0,0)  #poner bloqueado el acceso a redimensionar 
root.geometry("400x400")
#---------------------------------------------------------


Runpot = True

cambio = 1   #Variable de multiplexación de potenciometros
bloqueoUART = 1  #Variable de bloqueo de UART normal

#------------
# Reading potenciometers
#------------

entry1 = Entry(root, bg='#fdf2e9')
entry1.place(x=200,y=70, width = 30, height = 30)

entry2 = Entry(root, bg='#fdf2e9')
entry2.place(x=200,y=120, width = 30, height = 30)

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
            mensaje = arduino.readline().decode('utf-8')     #Si se recibe un mensaje del atmega328p
        
        if (cambio == 0):
            entry1.delete(0,'end')
            entry1.insert(0,mensaje)
            cambio = 1
            
            
        else:
            entry2.delete(0,'end')
            entry2.insert(0,mensaje)
            cambio = 0
            
#---------------------------------------------------------        
        
    
    
#------------
# Configure arduino
#------------
hilo1 = threading.Thread(target = pots, daemon = True)

arduino = serial.Serial('COM3', 9600)
hilo1.start()

#---------------------------------------------------------





#------------
# Contador de 8 bits
#------------
def contador():      #Funcion que se activa cuando se presiona el boton del contador
     n1 = entry.get()
     n2 = 0
     
     
     if n1.isdigit():  # Verifica si n1 es un número
         n2 = int(n1)
         
     else:
         lbl158.delete(0,'end')
         lbl158.insert(0,"Debe ser un número")  # Mensaje de error
         return  # Sale de la función si la entrada no es válida
     if n2 > 255:
         lbl158.delete(0,'end')
         lbl158.insert(0,"El número debe ser de 0 a 255")
         return
         
                #Dividir el numero en 3 numeros individuales
     millares = int(n2/1000)
     centenas = int((n2-(millares*1000))/100)
     decenas = int((n2- (millares*1000 + centenas*100))/10)
     unidades = int(n2-(millares*1000 + centenas*100 + decenas*10))
     
     arduino.write(bytes('A', 'utf-8'))  #Decirle a Arduino que se va a enviar algo al contador
     time.sleep(0.1)
     
                             #Enviarle individualmente el valor del numero separado a arduino
     if (centenas == 0):
          arduino.write(bytes('0', 'utf-8'))
          
     elif (centenas == 1):
         arduino.write(bytes('1', 'utf-8'))
    
     elif (centenas == 2):
          arduino.write(bytes('2', 'utf-8'))
          
     elif (centenas == 3):
         arduino.write(bytes('3', 'utf-8'))
         
     elif (centenas == 4):
         arduino.write(bytes('4', 'utf-8'))
    
     elif (centenas == 5):
          arduino.write(bytes('5', 'utf-8'))
          
     elif (centenas == 6):
         arduino.write(bytes('6', 'utf-8'))
    
     elif (centenas == 7):
         arduino.write(bytes('7', 'utf-8'))
    
     elif (centenas == 8):
          arduino.write(bytes('8', 'utf-8'))
          
     elif (centenas == 9):
         arduino.write(bytes('9', 'utf-8'))
         
     time.sleep(0.1)
    
     if (decenas == 0):
          arduino.write(bytes('0', 'utf-8'))
          
     elif (decenas == 1):
         arduino.write(bytes('1', 'utf-8'))
    
     elif (decenas == 2):
          arduino.write(bytes('2', 'utf-8'))
          
     elif (decenas == 3):
         arduino.write(bytes('3', 'utf-8'))
         
     elif (decenas == 4):
         arduino.write(bytes('4', 'utf-8'))
    
     elif (decenas == 5):
          arduino.write(bytes('5', 'utf-8'))
          
     elif (decenas == 6):
         arduino.write(bytes('6', 'utf-8'))
    
     elif (decenas == 7):
         arduino.write(bytes('7', 'utf-8'))
    
     elif (decenas == 8):
          arduino.write(bytes('8', 'utf-8'))
          
     elif (decenas == 9):
         arduino.write(bytes('9', 'utf-8'))
         
     time.sleep(0.1)
    
     if (unidades == 0):
          arduino.write(bytes('0', 'utf-8'))
          
     elif (unidades == 1):
         arduino.write(bytes('1', 'utf-8'))
    
     elif (unidades == 2):
          arduino.write(bytes('2', 'utf-8'))
          
     elif (unidades == 3):
         arduino.write(bytes('3', 'utf-8'))
         
     elif (unidades == 4):
         arduino.write(bytes('4', 'utf-8'))
    
     elif (unidades == 5):
          arduino.write(bytes('5', 'utf-8'))
          
     elif (unidades == 6):
         arduino.write(bytes('6', 'utf-8'))
    
     elif (unidades == 7):
         arduino.write(bytes('7', 'utf-8'))
    
     elif (unidades == 8):
          arduino.write(bytes('8', 'utf-8'))
          
     elif (unidades == 9):
         arduino.write(bytes('9', 'utf-8'))
     lbl158.delete(0,'end')    
     lbl158.insert(0,"Mostrando número")
         
#---------------------------------------------------------
     
     
#------------
# widgets in GUI
#------------

lbl = Label(root, text = "LAB_3", bg = '#800080', fg = "white")
lbl.pack()  #Ubicar el dato

eperatorLabel1 = Label(root, text="////////////////////////////////////////////////////////////////////////////", fg = 'black')
eperatorLabel1.pack()  #Ubicar el dato

lbl1 = Label(root, text = "ADC 1:", bg = "#00FFFF")
lbl1.place(x=50,y=70, width = 130, height = 30)

lbl1 = Label(root, text = "ADC 2:", bg = "#00FFFF")
lbl1.place(x=50,y=120, width = 130, height = 30)

btn = Button(root, text = "SEND", command = contador, bg = "red", fg = "white")  #colocar el boton de envio de  numero al contador
btn.place(x=50,y=200)

entry = Entry(root, bg='#fdf2e9')
entry.place(x=200,y=200, width = 100, height = 30)

lbl15 = Label(root, text = "Comentario:", bg = "yellow")
lbl15.place(x=50,y=250, width = 130, height = 30)

lbl158 = Entry(root, bg='#fdf2e9')
lbl158.place(x=200,y=250, width = 180, height = 30)

#---------------------------------------------------------

root.mainloop()  #Bucle infinito










