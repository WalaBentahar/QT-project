#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class Client
{
private:
    int id_client;
    QString nom;
    QString prenom;
    QString adresse;
    QString telephone;
    QString email;

public:
    // Constructors
    Client();
    Client(QString nom, QString prenom, QString adresse, QString telephone, QString email);
    Client(int id, QString nom, QString prenom, QString adresse, QString telephone, QString email);

    // Getters
    int getId() const { return id_client; }
    QString getNom() const { return nom; }
    QString getPrenom() const { return prenom; }
    QString getAdresse() const { return adresse; }
    QString getTelephone() const { return telephone; }
    QString getEmail() const { return email; }

    // Setters
    void setId(int id) { id_client = id; }
    void setNom(const QString &nom) { this->nom = nom; }
    void setPrenom(const QString &prenom) { this->prenom = prenom; }
    void setAdresse(const QString &adresse) { this->adresse = adresse; }
    void setTelephone(const QString &telephone) { this->telephone = telephone; }
    void setEmail(const QString &email) { this->email = email; }

    // Database operations
    bool ajouter();
    bool modifier();
    bool supprimer();
    static QSqlQuery afficher();
    static QSqlQuery rechercherParNom(const QString &recherche); // Now searches in nom, prenom, and adresse
    static QSqlQuery trierPar(const QString &critere);
    static int getNombreCommandes(int idClient);
};

#endif // CLIENT_H
