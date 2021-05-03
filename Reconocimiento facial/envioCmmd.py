import requests
from datetime import  date
import socket


today = date.today()
hostname = socket.gethostname()

ip_address = socket.gethostbyname(hostname)


def enviar(comando):

    if comando == 1:
        requests.post("ec2-18-233-166-171.compute-1.amazonaws.com:3002/api/cmmdLWR", json={'date': today.strftime("%y-%m-%d"),
                                                                 'ip_origin': ip_address})
    if comando == 2:
        requests.post("http://localhost:3000/api/cmmdFRW", json={'date': today.strftime("%y-%m-%d"),
                                                                 'ip_origin': ip_address})
    if comando == 3:
        requests.post("http://localhost:3000/api/cmmdLWR", json={'date': today.strftime("%y-%m-%d"),
                                                                 'ip_origin': ip_address})
    if comando == 4:
        requests.post("http://localhost:3000/api/cmmdRWR", json={'date': today.strftime("%y-%m-%d"),
                                                                 'ip_origin': ip_address})


# formato de la fecha
print(today.strftime("%y-%m-%d"))

# envio la IP del equipo host
print(ip_address)
enviar(1)