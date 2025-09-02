#include "commande.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Commande::Commande() : id_commande(0), id_client(0), montant(0.0) {}

Commande::Commande(int id_client, QDate date_commande, QString adresse_livraison, QString statut, double montant)
    : id_commande(0), id_client(id_client), date_commande(date_commande),
      adresse_livraison(adresse_livraison), statut(statut), montant(montant) {}

Commande::Commande(int id, int id_client, QDate date_commande, QString adresse_livraison, QString statut, double montant)
    : id_commande(id), id_client(id_client), date_commande(date_commande),
      adresse_livraison(adresse_livraison), statut(statut), montant(montant) {}

bool Commande::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO COMMANDE (ID_COMMANDE, ID_CLIENT, DATE_COMMANDE, ADRESSE_LIVRAISON, STATUT, MONTANT) "
                  "VALUES (SEQ_COMMANDE.NEXTVAL, :id_client, :date_commande, :adresse_livraison, :statut, :montant)");
    query.bindValue(":id_client", id_client);
    query.bindValue(":date_commande", date_commande);
    query.bindValue(":adresse_livraison", adresse_livraison);
    query.bindValue(":statut", statut);
    query.bindValue(":montant", montant);

    if (query.exec())
    {
        QSqlQuery idQuery;
        idQuery.prepare("SELECT SEQ_COMMANDE.CURRVAL FROM DUAL");
        if (idQuery.exec() && idQuery.next())
        {
            id_commande = idQuery.value(0).toInt();
        }
        qDebug() << "Commande ajoutée avec succès. ID:" << id_commande;
        return true;
    }
    qDebug() << "Erreur ajout commande:" << query.lastError().text();
    qDebug() << "Query:" << query.lastQuery();
    return false;
}

bool Commande::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE COMMANDE SET ID_CLIENT = :id_client, DATE_COMMANDE = :date_commande, "
                  "ADRESSE_LIVRAISON = :adresse_livraison, STATUT = :statut, MONTANT = :montant "
                  "WHERE ID_COMMANDE = :id");
    query.bindValue(":id_client", id_client);
    query.bindValue(":date_commande", date_commande);
    query.bindValue(":adresse_livraison", adresse_livraison);
    query.bindValue(":statut", statut);
    query.bindValue(":montant", montant);
    query.bindValue(":id", id_commande);

    bool success = query.exec();
    if (!success)
    {
        qDebug() << "Erreur modification commande:" << query.lastError().text();
        qDebug() << "Query:" << query.lastQuery();
    }
    else
    {
        qDebug() << "Commande modifiée avec succès. ID:" << id_commande;
    }
    return success;
}

bool Commande::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDE WHERE ID_COMMANDE = :id");
    query.bindValue(":id", id_commande);
    return query.exec();
}

QSqlQuery Commande::afficher()
{
    QSqlQuery query;
    query.prepare("SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
                  "ORDER BY c.DATE_COMMANDE DESC");
    query.exec();
    return query;
}

QSqlQuery Commande::afficherParClient(int id_client)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE ID_CLIENT = :id_client ORDER BY DATE_COMMANDE DESC");
    query.bindValue(":id_client", id_client);
    query.exec();
    return query;
}

QSqlQuery Commande::rechercherParDate(const QDate &dateDebut, const QDate &dateFin)
{
    QSqlQuery query;
    query.prepare("SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
                  "WHERE c.DATE_COMMANDE BETWEEN :date_debut AND :date_fin "
                  "ORDER BY c.DATE_COMMANDE DESC");
    query.bindValue(":date_debut", dateDebut);
    query.bindValue(":date_fin", dateFin);
    query.exec();
    return query;
}

QSqlQuery Commande::rechercherParStatut(const QString &statut)
{
    QSqlQuery query;
    query.prepare("SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
                  "WHERE UPPER(c.STATUT) LIKE UPPER(:statut) "
                  "ORDER BY c.DATE_COMMANDE DESC");
    query.bindValue(":statut", "%" + statut + "%");
    query.exec();
    return query;
}

QSqlQuery Commande::rechercherParMontant(double montantMin, double montantMax)
{
    QSqlQuery query;
    query.prepare("SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
                  "WHERE c.MONTANT BETWEEN :montant_min AND :montant_max "
                  "ORDER BY c.DATE_COMMANDE DESC");
    query.bindValue(":montant_min", montantMin);
    query.bindValue(":montant_max", montantMax);
    query.exec();
    return query;
}

QSqlQuery Commande::trierPar(const QString &critere)
{
    QSqlQuery query;
    QString sql = "SELECT c.*, cl.NOM, cl.PRENOM FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT ";

    if (critere == "date")
    {
        sql += "ORDER BY c.DATE_COMMANDE DESC";
    }
    else if (critere == "montant")
    {
        sql += "ORDER BY c.MONTANT DESC";
    }
    else if (critere == "statut")
    {
        sql += "ORDER BY c.STATUT ASC";
    }
    else
    {
        sql += "ORDER BY c.ID_COMMANDE DESC";
    }

    query.prepare(sql);
    query.exec();
    return query;
}

bool Commande::getLastCommandWithClientInfo(int &commandId, QDate &commandDate,
                                            QString &deliveryAddress, QString &status,
                                            double &amount, QString &clientName,
                                            QString &clientEmail)
{
    QSqlQuery query;
    query.prepare("SELECT c.ID_COMMANDE, c.DATE_COMMANDE, c.ADRESSE_LIVRAISON, c.STATUT, c.MONTANT, "
                  "cl.NOM, cl.PRENOM, cl.EMAIL "
                  "FROM COMMANDE c "
                  "JOIN CLIENT cl ON c.ID_CLIENT = cl.ID_CLIENT "
                  "WHERE c.ID_COMMANDE = (SELECT MAX(ID_COMMANDE) FROM COMMANDE)");

    if (query.exec() && query.next())
    {
        commandId = query.value(0).toInt();
        commandDate = query.value(1).toDate();
        deliveryAddress = query.value(2).toString();
        status = query.value(3).toString();
        amount = query.value(4).toDouble();
        clientName = query.value(5).toString() + " " + query.value(6).toString();
        clientEmail = query.value(7).toString();
        return true;
    }
    return false;
}

Commande Commande::getLastAddedCommand()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM COMMANDE WHERE ID_COMMANDE = (SELECT MAX(ID_COMMANDE) FROM COMMANDE)");

    if (query.exec() && query.next())
    {
        Commande cmd;
        cmd.id_commande = query.value(0).toInt();
        cmd.id_client = query.value(1).toInt();
        cmd.date_commande = query.value(2).toDate();
        cmd.adresse_livraison = query.value(3).toString();
        cmd.statut = query.value(4).toString();
        cmd.montant = query.value(5).toDouble();
        return cmd;
    }
    return Commande();
}
