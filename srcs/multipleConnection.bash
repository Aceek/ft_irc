#!/bin/bash

SERVER_HOST="localhost"
SERVER_PORT=6138
NUM_CONNECTIONS=5  # Changer le nombre de connexions simulées selon vos besoins

# Vérifiez si netcat est installé
if ! command -v nc &> /dev/null; then
    echo "Netcat (nc) n'est pas installé. Veuillez l'installer avant d'exécuter ce script."
    exit 1
fi

# Boucle pour créer plusieurs connexions simultanées
for ((i = 1; i <= NUM_CONNECTIONS; i++)); do
    echo "Connexion $i au serveur sur le port $SERVER_PORT..."
    nc $SERVER_HOST $SERVER_PORT &
done

# Attendez un peu pour permettre aux connexions de s'établir
sleep 1

# Si vous voulez envoyer des données au serveur depuis chaque connexion, vous pouvez le faire ici.
# Par exemple, pour envoyer "Hello, Server!" suivi d'un retour à la ligne depuis chaque connexion :
for ((i = 1; i <= NUM_CONNECTIONS; i++)); do
    echo "pass bonjour" | nc $SERVER_HOST $SERVER_PORT &
done

# Attendez que toutes les connexions se terminent (pour éviter de fermer prématurément les connexions)
wait
