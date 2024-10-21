import serial
import time
from inputs import get_gamepad
import serial.tools.list_ports

# Inicialización del puerto serie (Bluetooth)
port = "COM6"  # Cambia esto según tu sistema
bluetooth = serial.Serial(port, 9600, timeout=1)
time.sleep(1)  # Breve espera para inicializar correctamente el puerto

# Función para manejar el envío de datos al Bluetooth
def send_data_to_bluetooth(right_value, left_value):
    right_value = round(right_value * -255)  # Escalar a 255 y invertir
    left_value = round(left_value * -255)  # Escalar a 255 y invertir
    message = f"{right_value} {left_value}\n"
    if bluetooth.is_open:
        bluetooth.write(message.encode())
        print(f"Enviando: {message}")

# Función para procesar la entrada del controlador
def process_gamepad_input():
    last_left_value = 0
    last_right_value = 0
    while True:
        events = get_gamepad()
        for event in events:
            if event.code == "ABS_RY":  # Thumbstick derecho (eje Y)
                right_value = event.state / 32767.0
                if right_value != last_right_value:
                    send_data_to_bluetooth(right_value, last_left_value)
                    last_right_value = right_value

            elif event.code == "ABS_Y":  # Thumbstick izquierdo (eje Y)
                left_value = event.state / 32767.0
                if left_value != last_left_value:
                    send_data_to_bluetooth(last_right_value, left_value)
                    last_left_value = left_value

# Función para manejar los datos recibidos del Arduino
def read_from_bluetooth():
    while bluetooth.is_open:
        try:
            if bluetooth.in_waiting > 0:
                received_data = bluetooth.readline().decode().strip()
                print(f"Datos recibidos del Arduino: {received_data}")
        except Exception as e:
            print(f"Error al leer del puerto serie: {e}")

# Iniciar el procesamiento
if __name__ == "__main__":
    try:
        print("Comenzando...")
        process_gamepad_input()  # Inicia el procesamiento del gamepad
    except KeyboardInterrupt:
        print("Terminando...")
    finally:
        if bluetooth.is_open:
            bluetooth.close()  # Cerrar el puerto serial
