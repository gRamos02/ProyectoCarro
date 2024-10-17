from inputs import get_gamepad
import os
import sys
import serial
import time

ser = serial.Serial('COM6', 9600)  
time.sleep(2)

#Estado de botones
left_trigger = 0
right_trigger = 0
left_reverse = False
right_reverse = False

def send_command(command):
    ser.write(command.encode())
    print(f"Comando enviado: {command}")

def process_input():
    global left_trigger, right_trigger, left_reverse, right_reverse
    while True:
        events = get_gamepad()
        for event in events:
            if event.code == "ABS_Z":  # Left trigger
                if event.state != left_trigger:  # Check for state change
                    left_trigger = event.state
                    if left_trigger > 0:
                        send_command(f"i:{left_trigger}")  # Send forward with speed
                    else:
                        send_command("stopA")  # Stop left motor when trigger released

            elif event.code == "ABS_ZR":  # Right trigger
                if event.state != right_trigger:
                    right_trigger = event.state
                    if right_trigger > 0:
                        send_command(f"d:{right_trigger}")  # Send forward with speed
                    else:
                        send_command("stopB")  # Stop right motor when trigger released

            elif event.code == "BTN_TL":  # Reverse left motor
                if event.state != left_reverse:
                    left_reverse = event.state
                    if left_reverse:
                        send_command("rl")  # Reverse left motor
                    else:
                        send_command("stopA")  # Stop left motor when button released

            elif event.code == "BTN_TR":  # Reverse right motor
                if event.state != right_reverse:
                    right_reverse = event.state
                    if right_reverse:
                        send_command("rd")  # Reverse right motor
                    else:
                        send_command("stopB")  # Stop right motor when button released

if __name__ == '__main__':
    try:
        process_input()
    except KeyboardInterrupt:
        print("Control zeteado")
        try:
            sys.exit(130)
        except SystemExit:
            os._exit(130)
