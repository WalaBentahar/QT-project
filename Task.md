# Application de Gestion Logistique — Livraison

## Description

Cette application desktop, développée en C++/Qt et connectée à une base Oracle 11g, permet de gérer les opérations logistiques d'une entreprise de livraison : gestion des clients, des commandes, et suivi opérationnel.  
Le projet est structuré autour de trois modules principaux : **Clients**, **Commandes**, et **Statistiques**, qui sont reliés de façon relationnelle.

---

## Modèle de Données

### 1. Tables et Relations

#### Table: `CLIENT`

- **ID_CLIENT** (_int, PK, auto-incrément_)
- **NOM** (_varchar2(50)_)
- **PRENOM** (_varchar2(50)_)
- **ADRESSE** (_varchar2(100)_)
- **TELEPHONE** (_varchar2(20)_)
- **EMAIL** (_varchar2(100)_)

#### Table: `COMMANDE`

- **ID_COMMANDE** (_int, PK, auto-incrément_)
- **ID_CLIENT** (_int, FK → CLIENT.ID_CLIENT_)
- **DATE_COMMANDE** (_date_)
- **ADRESSE_LIVRAISON** (_varchar2(100)_)
- **STATUT** (_varchar2(30)_)
- **MONTANT** (_number(10,2)_)

#### Séquences Oracle

- `SEQ_CLIENT` : pour l'auto-incrément de `ID_CLIENT`
- `SEQ_COMMANDE` : pour l'auto-incrément de `ID_COMMANDE`

#### Relation

- **Un client peut avoir plusieurs commandes** (`CLIENT 1,N COMMANDE`)
- **Chaque commande appartient à un seul client**

---

## Fonctions et Opérations

### A. CRUD (Create, Read, Update, Delete)

#### Pour les Clients

- **Ajouter** un client (formulaire de saisie avec validation)
- **Modifier** les informations d'un client (formulaire d'édition)
- **Supprimer** un client
- **Consulter** la liste des clients (masquage des IDs)

#### Pour les Commandes

- **Créer** une commande pour un client sélectionné
- **Mettre à jour** une commande (statut, infos livraison, etc.)
- **Supprimer** une commande
- **Afficher** les commandes avec montant visible (masquage des IDs)

---

## Fonctions Avancées

### Opérations de Tri et Recherche

- **Tri des clients** selon 3 critères :

  - Nom
  - Ville/adresse
  - Nombre de commandes

- **Recherche des clients** par champ unique recherchant dans 3 critères :

  - Nom du client
  - Prénom du client
  - Adresse du client

- **Recherche des commandes** par champ unique recherchant dans :

  - Adresse de livraison
  - Statut de la commande
  - Montant (recherche numérique)

- **Tri des commandes** selon 3 critères :
  - Date de commande
  - Montant
  - Statut

### Exportation PDF

- **Exporter une liste de commandes en PDF** avec design moderne utilisant CSS et statistiques complètes

### Module Statistiques

- **Tableau de bord interactif** avec visualisations de données
- **Graphiques animés** : secteurs, barres, et courbes
- **Cartes statistiques** avec animations de comptage
- **Métriques clés** : total clients, commandes, chiffre d'affaires
- **Analyse temporelle** : évolution mensuelle des commandes et revenus
- **Répartition des statuts** : visualisation en camembert

---

## Interfaces Utilisateur

### Clients

- **Formulaire d'ajout/modification** avec validation en temps réel :
  - Nom/Prénom : alphabétique uniquement
  - Téléphone : 8 chiffres exactement
  - Email : format valide requis
  - Indications visuelles d'erreur (bordures rouges, messages)
- **Grille/liste** des clients avec tri et recherche en temps réel
- **Recherche multi-critères** par nom, prénom ou adresse
- **Masquage des colonnes ID** pour une interface propre

### Commandes

- **Formulaire d'ajout/modification** avec :
  - Sélection du client via ComboBox
  - Champ date élargi avec calendrier popup
  - Validation des champs obligatoires
- **Table des commandes** avec colonne montant visible
- **Recherche unifiée** par champ unique (adresse, statut, montant)
- **Tri par boutons dédiés** avec 3 critères
- **Actions via menu contextuel** (modifier, supprimer, exporter)

### Statistiques

- **Tableau de bord moderne** avec cartes statistiques animées
- **Graphiques interactifs** :
  - Graphique en secteurs pour la répartition des statuts
  - Graphique en barres pour les tendances mensuelles
  - Graphique linéaire pour l'évolution du chiffre d'affaires
- **Animations fluides** avec courbes d'atténuation
- **Actualisation en temps réel** des données
- **Design cohérent** avec le thème de l'application

---

## Fonctionnalités Techniques Implémentées

- **Interface moderne** avec dégradés gris et rose
- **Validation en temps réel** avec feedback visuel
- **Masquage intelligent des colonnes ID**
- **Recherche multi-critères optimisée** (nom, prénom, adresse pour clients)
- **Export PDF avec statistiques et design CSS**
- **Gestion d'erreurs complète**
- **Menu contextuels pour actions rapides**
- **Feedback utilisateur en temps réel** avec compteur de résultats
- **Visualisations de données animées** avec graphiques personnalisés
- **Tableau de bord statistiques** avec métriques clés

---

## Notes techniques

- Les ID auto-incrémentés sont gérés via SEQUENCE Oracle
- Interface responsive avec Qt 6
- Validation côté client et serveur
- Gestion des erreurs SQL avec messages utilisateur
- Style moderne avec gradients et animations
- Recherche insensible à la casse avec UPPER()

---

## Auteurs

- [Wala]

---
