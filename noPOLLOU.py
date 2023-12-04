#!/usr/bin/env python3


import socket
import time

def simulate_client(host, port, send_interval=1):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        try:
            while True:
                # Envoyer des données
                s.sendall(b'Hello, server')
                time.sleep(send_interval)  # Attendre avant d'envoyer à nouveau
        except KeyboardInterrupt:
            pass

if __name__ == "__main__":
    simulate_client('127.0.0.1', 6138)
