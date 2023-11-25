# Serveur IRC en C++98

## À propos du projet
Ce projet vise à reproduire le fonctionnement d'un serveur IRC (Internet Relay Chat) en utilisant C++ 98. Il est conçu pour fonctionner sans client IRC intégré et ne gère pas la communication de serveur à serveur.

## Fonctionnalités
- **Communication** : via TCP/IP (v4 ou v6).
- **Authentification** : par commande `PASS`, suivie des commandes `NICK` et `USER`.
- **Gestion des canaux** : connexion à des canaux, envoi et réception de messages privés.
- **Utilisateurs** : gestion des utilisateurs basiques et des opérateurs de canal avec des commandes spécifiques.

## Description des Commandes

Le serveur IRC gère plusieurs commandes essentielles pour l'interaction des utilisateurs avec le serveur et entre eux.

### Commandes Générales
- **AUTHENTIFICATION** : 
  - Utilisez `PASS` pour vous authentifier, puis `NICK` et `USER` pour définir votre nickname et username.

### Commandes de Canal
- **JOIN** : Rejoignez un canal avec `/join <#nomducanal>`.
- **PART** : Quittez un canal avec `/part <#nomducanal>`.
- **TOPIC** : Modifiez ou affichez le thème du canal avec `/topic <#nomducanal> <nouveau sujet>`.
- **NAMES** : Affichez les utilisateurs dans un canal avec `/names <#nomducanal>`.
- **LIST** : Liste tous les canaux disponibles avec `/list`.

### Commandes de Communication
- **PRIVMSG** : Envoyez un message privé avec `/privmsg <nom d'utilisateur> <message>`.
- **QUIT** : Déconnectez-vous du serveur avec `/quit`.

### Commandes des Opérateurs de Canal
- **KICK** : Éjectez un utilisateur d'un canal avec `/kick <#nomducanal> <nom d'utilisateur>`.
- **INVITE** : Invitez un utilisateur à rejoindre un canal avec `/invite <nom d'utilisateur> <#nomducanal>`.
- **MODE** : Modifiez les paramètres d'un canal avec `/mode <#nomducanal> <+/-modes>`. Les options incluent :
  - `i` : Canal sur invitation uniquement.
  - `t` : Restrictions sur la commande TOPIC.
  - `k` : Définir/supprimer le mot de passe du canal.
  - `o` : Statut d'opérateur.
  - `l` : Limite d'utilisateurs pour le canal.

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

### Connexion au Serveur IRC via irssi

#### Ajout du Serveur à la Liste des Serveurs

Pour ajouter le serveur IRC à votre liste dans irssi, utilisez la commande suivante :

```bash
/SERVER ADD -network <name> <address> <port> [<password>]
```
Configuration des Options de Connexion
Après avoir ajouté le serveur, configurez les options de connexion avec cette commande :

```bash
/SERVER MODIFY -nocap -notls -notls_verify <name>
```
Connexion au Serveur
```bash
/connect <name>
```

Accéder aux Logs d'irssi
Pour ouvrir un fichier de log et enregistrer votre session IRC, utilisez :
```bash
/RAWLOG OPEN log.txt
```

