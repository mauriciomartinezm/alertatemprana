import serial
import requests
import threading

arduino = serial.Serial('COM5', 9600)  # Ajusta el puerto según sea necesario
reading = ["0", "0", "0"]
commands = ["Apagar primero", "Apagar segundo", "Apagar tercero"]  # Para almacenar los comandos de encendido/apagado

# Función para enviar los datos al servidor
def enviar_datos(diccionario):
    try:
        response = requests.post("https://alertatempranaapi.onrender.com/recibir_datos", json=diccionario)
        # Puedes descomentar para ver la respuesta del servidor
        # print(response.text)
    except Exception as e:
        print(f"Error al enviar datos: {e}")

while True:
    if arduino.in_waiting > 0:
        try:
            data = arduino.readline().decode('utf-8', errors='ignore').strip()  # Ignora los bytes inválidos
        except UnicodeDecodeError:
            print("Error al decodificar los datos recibidos")
            continue  # Ignora este ciclo y espera nuevos datos
        
        # Procesar datos de los sensores
        if data.startswith("1er sensor"):
            value = data.split(": ")[1]  # Extraer el valor
            reading[0] = value
        elif data.startswith("2do sensor"):
            value = data.split(": ")[1]
            reading[1] = value
        elif data.startswith("3er sensor"):
            value = data.split(": ")[1]
            reading[2] = value
        
        # Procesar comandos de encendido/apagado
        if "Encender primer LED" in data:
            commands[0] = "Encender primero"
        elif "Apagar primer LED" in data:
            commands[0] = "Apagar primero"
        elif "Encender segundo" in data:
            commands[1] = "Encender segundo"
        elif "Apagar segundo LED" in data:
            commands[1] = "Apagar segundo"
        elif "Encender tercer LED y activar zumbador" in data:
            commands[2] = "Encender tercero"
        elif "Apagar tercer LED y zumbador" in data:
            commands[2] = "Apagar tercero"

        # Preparar los datos para enviar al servidor
        diccionario = {
            'sensor_values': reading,
            'commands': commands
        }
        print(diccionario)

        # Ejecutar la petición en un hilo separado para no bloquear la lectura del puerto serial
        threading.Thread(target=enviar_datos, args=(diccionario)).start()
