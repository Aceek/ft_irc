#!/bin/bash

SERVER_HOST="localhost"
SERVER_PORT=6138
NUM_CONNECTIONS=30  # Changer le nombre de connexions simulées selon vos besoins

# Vérifiez si netcat est installé
if ! command -v nc &> /dev/null; then
    echo "Netcat (nc) n'est pas installé. Veuillez l'installer avant d'exécuter ce script."
    exit 1
fi

# Boucle pour créer plusieurs connexions simultanées
for ((i = 1; i <= NUM_CONNECTIONS; i++)); do
    echo "Connexion $i au serveur sur le port $SERVER_PORT..."

    # Générez un nom de nick unique en ajoutant un numéro d'incrémentation
    NICK="nickname$i"

    # Générez un nom d'utilisateur unique en ajoutant un numéro d'incrémentation
    USER="username$i"

    # Envoie la commande "PASS bonjour", "NICK <nickname>", et "USER <username> :<realName>"
    echo -e "PASS bonjour\r\nNICK $NICK\r\nUSER $USER :realName" | nc $SERVER_HOST $SERVER_PORT &
done

# Attendez un peu pour permettre aux connexions de s'établir
sleep 1

# Attendez que toutes les connexions se terminent (pour éviter de fermer prématurément les connexions)
wait
