import socket
import matplotlib.pyplot as plt
from collections import deque

# Parámetros de conexión
ESP32_IP = "192.168.4.1"  # IP del ESP32 en modo Access Point
PORT = 12345

# Configurar la ventana de gráficos
plt.ion()  # Modo interactivo para gráficos en tiempo real
fig, ax = plt.subplots()
ax.set_title('Monitor de Sensores')
ax.set_xlabel('Tiempo (s)')
ax.set_ylabel('Valor')
line_voltage, = ax.plot([], [], label="Voltaje (V)", color='blue')
line_current, = ax.plot([], [], label="Corriente (mA)", color='red')
line_temp, = ax.plot([], [], label="Temperatura (°C)", color='green')
line_pressure, = ax.plot([], [], label="Presión (hPa)", color='purple')

# Inicializar las listas de datos
time_data = deque(maxlen=10)
voltage_data = deque(maxlen=10)
current_data = deque(maxlen=10)
temp_data = deque(maxlen=10)
pressure_data = deque(maxlen=10)

# Crear socket cliente
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((ESP32_IP, PORT))

print("Conectado al ESP32. Recibiendo datos...")

try:
    while True:
        data = client_socket.recv(1024).decode().strip()
        if data:
            # Separar los datos recibidos
            voltage, current, temperature, pressure = map(float, data.split(","))
            print(f"Voltaje: {voltage:.2f} V, Corriente: {current:.2f} mA, Temp: {temperature:.2f} °C, Presión: {pressure:.2f} hPa")

            # Añadir datos a las listas
            time_data.append(len(time_data))  # Tiempo en segundos
            voltage_data.append(voltage)
            current_data.append(current)
            temp_data.append(temperature)
            pressure_data.append(pressure)

            # Actualizar gráficos
            line_voltage.set_data(time_data, voltage_data)
            line_current.set_data(time_data, current_data)
            line_temp.set_data(time_data, temp_data)
            line_pressure.set_data(time_data, pressure_data)

            # Ajustar los ejes y actualizar la gráfica
            ax.relim()
            ax.autoscale_view()
            ax.legend(loc='upper left')

            # Redibujar y actualizar la gráfica
            plt.draw()
            plt.pause(0.05)  # Pausa corta para actualizar el gráfico

except KeyboardInterrupt:
    print("\nDesconectando...")
    client_socket.close()
    plt.ioff()  # Apagar modo interactivo
    plt.show()  # Mostrar el gráfico final
