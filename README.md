# Ft_p
42 - Project #22

## Résumé
Ce projet consiste à implémenter un client et un serveur permettant le
transfert de fichier en réseau TCP/IP.

## Partie Obligatoire

Ce projet consiste à faire un client et un serveur FTP (File Transfert Protocol) qui
permettent d’envoyer et recevoir des fichiers entre un ou plusieurs clients et le serveur.  
Vous êtes néammoins libre du choix du protocole à utiliser (vous n’êtes pas obligé
de respecter les RFC définissant FTP, vous pouvez inventer votre propre protocole de
transfert de fichier).  Vous devrez par contre quelque soit votre choix absolument obtenir
une cohérence entre votre client et votre serveur. Ils doivent communiquer correctement
ensemble.  
La communication entre le client et le serveur se fera en TCP/IP (v4).  
Pouvoir faire un ls, cd, pwd permet de faire ces commandes dans le serveur et de
les afficher côté client.

## Partie bonus

- Gestion des droits utilisateurs
- lls, lcd, lpwd
- mkdir, lmkdir
- Affichage côté serveur
- Prompt pour le client
