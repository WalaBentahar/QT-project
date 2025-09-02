#include "client.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

Client::Client() : id_client(0) {}

Client::Client(QString nom, QString prenom, QString adresse, QString telephone, QString email)
    : id_client(0), nom(nom), prenom(prenom), adresse(adresse), telephone(telephone), email(email) {}

Client::Client(int id, QString nom, QString prenom, QString adresse, QString telephone, QString email)
    : id_client(id), nom(nom), prenom(prenom), adresse(adresse), telephone(telephone), email(email) {}

bool Client::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO CLIENT (ID_CLIENT, NOM, PRENOM, ADRESSE, TELEPHONE, EMAIL) "
                  "VALUES (SEQ_CLIENT.NEXTVAL, :nom, :prenom, :adresse, :telephone, :email)");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);

    if (query.exec())
    {
        // Get the generated ID
        QSqlQuery idQuery;
        idQuery.prepare("SELECT SEQ_CLIENT.CURRVAL FROM DUAL");
        if (idQuery.exec() && idQuery.next())
        {
            id_client = idQuery.value(0).toInt();
        }
        return true;
    }
    qDebug() << "Erreur ajout client:" << query.lastError().text();
    return false;
}

bool Client::modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE CLIENT SET NOM = :nom, PRENOM = :prenom, ADRESSE = :adresse, "
                  "TELEPHONE = :telephone, EMAIL = :email WHERE ID_CLIENT = :id");
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":adresse", adresse);
    query.bindValue(":telephone", telephone);
    query.bindValue(":email", email);
    query.bindValue(":id", id_client);

    return query.exec();
}

bool Client::supprimer()
{
    QSqlQuery query;
    query.prepare("DELETE FROM CLIENT WHERE ID_CLIENT = :id");
    query.bindValue(":id", id_client);
    return query.exec();
}

QSqlQuery Client::afficher()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT ORDER BY NOM");
    query.exec();
    return query;
}

QSqlQuery Client::rechercherParNom(const QString &recherche)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM CLIENT WHERE "
                  "UPPER(NOM) LIKE UPPER(:recherche) OR "
                  "UPPER(PRENOM) LIKE UPPER(:recherche) OR "
                  "UPPER(ADRESSE) LIKE UPPER(:recherche) "
                  "ORDER BY NOM, PRENOM");
    query.bindValue(":recherche", "%" + recherche + "%");
    query.exec();
    return query;
}

QSqlQuery Client::trierPar(const QString &critere)
{
    QSqlQuery query;
    QString sql = "SELECT * FROM CLIENT ORDER BY ";

    if (critere == "nom")
    {
        sql += "NOM";
    }
    else if (critere == "adresse")
    {
        sql += "ADRESSE";
    }
    else if (critere == "commandes")
    {
        sql = "SELECT c.*, COUNT(cmd.ID_COMMANDE) as nb_commandes "
              "FROM CLIENT c LEFT JOIN COMMANDE cmd ON c.ID_CLIENT = cmd.ID_CLIENT "
              "GROUP BY c.ID_CLIENT, c.NOM, c.PRENOM, c.ADRESSE, c.TELEPHONE, c.EMAIL "
              "ORDER BY nb_commandes DESC";
    }
    else
    {
        sql += "ID_CLIENT";
    }

    query.prepare(sql);
    query.exec();
    return query;
}

int Client::getNombreCommandes(int idClient)
{
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM COMMANDE WHERE ID_CLIENT = :id");
    query.bindValue(":id", idClient);
    if (query.exec() && query.next())
    {
        return query.value(0).toInt();
    }
    return 0;
}
