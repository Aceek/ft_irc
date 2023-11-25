# Serveur IRC en C++98

## À propos du projet
Ce projet vise à reproduire le fonctionnement d'un serveur IRC (Internet Relay Chat) en utilisant C++ 98. Il est conçu pour fonctionner sans client IRC intégré et ne gère pas la communication de serveur à serveur.

## Fonctionnalités
- **Communication** : via TCP/IP (v4 ou v6).
- **Authentification** : par commande `PASS`, suivie des commandes `NICK` et `USER`.
- **Gestion des canaux** : connexion à des canaux, envoi et réception de messages privés.
- **Utilisateurs** : gestion des utilisateurs basiques et des opérateurs de canal avec des commandes spécifiques.

## Intégration avec Irssi
Le serveur est optimisé pour une utilisation avec le client IRC Irssi. Des scripts Perl sont nécessaires pour rediriger certaines commandes personnalisées directement au serveur.

### Configuration des Scripts pour Irssi
- **Script d'Autochargement (`autoload_on_localhost.pl`)** : 
  - Placez dans `~/.irssi/scripts/autorun/`.
- **Script de Commande Personnalisée (`custom_command.pl`)** :
  - Placez dans `~/.irssi/scripts/`.

## Compilation et Lancement
### Compilation
Exécutez dans le répertoire racine du projet :
```bash
make
```
## Lancement
Pour lancer le serveur, utilisez la commande suivante en spécifiant le port et le mot de passe :

```bash
./ft_irc <port> <password>
```
Remplacez <port> par le numéro de port sur lequel le serveur doit écouter et <password> par le mot de passe nécessaire pour la connexion des clients.
