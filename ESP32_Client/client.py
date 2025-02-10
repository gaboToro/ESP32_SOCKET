import socket
import matplotlib.pyplot as plt
from collections import deque

# Parámetros de conexión
ESP32_IP = "192.168.4.1"  # IP del ESP32 en modo Access Point
PORT = 12345

# Configurar la ventana de gráficos
plt.ion()  # Modo interactivo para gráficos en tiempo real
fig, ax = plt.subplots()
ax.set_title('Monitor de Voltaje y Corriente')
ax.set_xlabel('Tiempo (s)')
ax.set_ylabel('Valor')
line_voltage, = ax.plot([], [], label="Voltaje (V)", color='blue')
line_current, = ax.plot([], [], label="Corriente (mA)", color='red')

# Inicializar las listas de datos
time_data = deque(maxlen=10)
voltage_data = deque(maxlen=10)
current_data = deque(maxlen=10)

# Crear socket cliente
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((ESP32_IP, PORT))

print("Conectado al ESP32. Recibiendo datos...")

try:
    while True:
        data = client_socket.recv(1024).decode().strip()
        if data:
            voltage, current = map(float, data.split(","))
            print(f"Voltaje: {voltage:.2f} V, Corriente: {current:.2f} mA")

            # Añadir datos a las listas
            time_data.append(len(time_data))  # Tiempo en segundos
            voltage_data.append(voltage)
            current_data.append(current)

            # Actualizar gráficos
            line_voltage.set_data(time_data, voltage_data)
            line_current.set_data(time_data, current_data)

            # Ajustar los ejes y actualizar la gráfica
            ax.relim()
            ax.autoscale_view()
            ax.legend(loc='upper left')
            plt.pause(0.1)  # Pausa corta para actualizar el gráfico

except KeyboardInterrupt:
    print("\nDesconectando...")
    client_socket.close()
    plt.ioff()  # Apagar modo interactivo
    plt.show()  # Mostrar el gráfico final
