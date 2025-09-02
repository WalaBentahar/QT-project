#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDate>
#include <QSqlQuery>

class Commande
{
private:
    int id_commande;
    int id_client;
    QDate date_commande;
    QString adresse_livraison;
    QString statut;
    double montant;

public:
    // Constructors
    Commande();
    Commande(int id_client, QDate date_commande, QString adresse_livraison, QString statut, double montant);
    Commande(int id, int id_client, QDate date_commande, QString adresse_livraison, QString statut, double montant);

    // Getters
    int getId() const { return id_commande; }
    int getIdClient() const { return id_client; }
    QDate getDateCommande() const { return date_commande; }
    QString getAdresseLivraison() const { return adresse_livraison; }
    QString getStatut() const { return statut; }
    double getMontant() const { return montant; }

    // Setters
    void setId(int id) { id_commande = id; }
    void setIdClient(int id) { id_client = id; }
    void setDateCommande(const QDate &date) { date_commande = date; }
    void setAdresseLivraison(const QString &adresse) { adresse_livraison = adresse; }
    void setStatut(const QString &statut) { this->statut = statut; }
    void setMontant(double montant) { this->montant = montant; }

    // Database operations
    bool ajouter();
    bool modifier();
    bool supprimer();
    static QSqlQuery afficher();
    static QSqlQuery afficherParClient(int id_client);
    static QSqlQuery rechercherParDate(const QDate &dateDebut, const QDate &dateFin);
    static QSqlQuery rechercherParStatut(const QString &statut);
    static QSqlQuery rechercherParMontant(double montantMin, double montantMax);
    static QSqlQuery trierPar(const QString &critere);
    static Commande getLastAddedCommand();
    static bool getLastCommandWithClientInfo(int &commandId, QDate &commandDate,
                                             QString &deliveryAddress, QString &status,
                                             double &amount, QString &clientName,
                                             QString &clientEmail);
};

#endif // COMMANDE_H
