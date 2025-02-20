import socket
import mysql.connector

# Parámetros de conexión a MySQL
db_config = {
    "host": "localhost",
    "user": "root",  # Si tienes otro usuario, cámbialo
    "password": "Grupo_02",  # Coloca la contraseña de MySQL aquí
    "database": "sensores"
}

# Conectar a MySQL
try:
    db_conn = mysql.connector.connect(**db_config)
    cursor = db_conn.cursor()
    print("Conectado a MySQL correctamente.")
except mysql.connector.Error as err:
    print(f"Error al conectar con MySQL: {err}")
    exit()

# Parámetros de conexión con ESP32
ESP32_IP = "192.168.4.1"  # IP del ESP32 en modo Access Point
PORT = 5000

# Crear socket cliente
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((ESP32_IP, PORT))

try:
    while True:
        data = client_socket.recv(1024).decode().strip()
        if data:
            voltage, current, temperature, rpm = map(float, data.split(","))
            print(f"V: {voltage}V, I: {current}mA, T: {temperature}°C, RPM: {rpm}")

            # Insertar datos en MySQL
            sql = "INSERT INTO mediciones (voltaje, corriente, temperatura, presion) VALUES (%s, %s, %s, %s)"
            values = (voltage, current, temperature, pressure)
            cursor.execute(sql, values)
            db_conn.commit()  # Guardar los cambios en la base de datos

except KeyboardInterrupt:
    client_socket.close()
    cursor.close()
    db_conn.close()
