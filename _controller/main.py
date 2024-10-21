from inputs import get_gamepad
import os
import sys
import serial
import time

print("Start")
port="COM7" 
bluetooth=serial.Serial(port, 9600)#Start communications with the bluetooth unit
print("Conectado")
bluetooth.flushInput() #This gives the bluetooth a little kick

#Estado de botones
left_trigger = 0
right_trigger = 0
left_reverse = False
right_reverse = False

def send_command(command):
    bluetooth.write(f"{command}\n".encode())
    print(f"Comando enviado: {command}")

def process_input():
    print("Procesado entrada...")
    global left_trigger, right_trigger, left_reverse, right_reverse
    while True:
        events = get_gamepad()
        for event in events:
            print(event.code);
            if event.code == "ABS_Z": 
                if event.state != left_trigger:  
                    left_trigger = event.state
                    if left_trigger > 0:
                        send_command(f"r")  
                    else:
                        send_command("stop")  

            elif event.code == "ABS_RZ":  
                if event.state != right_trigger:
                    right_trigger = event.state
                    if right_trigger > 0:
                        send_command(f"d")  
                    else:
                        send_command("stop")  

            elif event.code == "BTN_TL":  
                if event.state != left_reverse:
                    left_reverse = event.state
                    if left_reverse:
                        send_command("lt")  
                    else:
                        send_command("stop")  

            elif event.code == "BTN_TR":  
                if event.state != right_reverse:
                    right_reverse = event.state
                    if right_reverse:
                        send_command("rt")  
                    else:
                        send_command("stop")
        # time.sleep(0.5) 


if __name__ == '__main__':
    try:
        process_input()
    except KeyboardInterrupt:
        print("Control zeteado")
        try:
            sys.exit(130)
            bluetooth.close()
        except SystemExit:
            os._exit(130)
            bluetooth.close()
