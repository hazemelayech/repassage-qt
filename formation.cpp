#include "formation.h"
#include "candidats.h"
#include<QDebug>
#include<QDebug>
#include<QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QVBoxLayout>
formation::formation(int ID, QString NOM ,QString TYPE ,int NBRS, int NBRHS , float PRIX, QDate DD  ,QDate DF)
{
    this->ID=ID;
    this->NOM=NOM;
    this->TYPE=TYPE;
    this->NBRS=NBRS;
    this->NBRHS=NBRHS;
    this->PRIX=PRIX;

    this->DD=DD;
    this->DF=DF;
}
bool formation::ajouter(){
    QSqlQuery query;
    QString res = QString::number(ID);
    QString res1 = QString::number(PRIX);
    QString res2 = QString::number(NBRS);
    QString res3 = QString::number(NBRHS);

    query.prepare("INSERT INTO formation (ID, NOM, TYPE, NBRS, NBRHS, PRIX, DD, DF) "
                  "VALUES (:ID, :NOM, :TYPE, :NBRS, :NBRHS, :PRIX, :DD, :DF)");

    query.bindValue(":ID",res);
    query.bindValue(":NOM",NOM);
    query.bindValue(":TYPE",TYPE);
    query.bindValue(":NBRS",res2);
    query.bindValue(":NBRHS",res3);
    query.bindValue(":PRIX",res1);
    query.bindValue(":DD",DD);
    query.bindValue(":DF",DF);

    return  query.exec();
}


bool formation::supprimer(int ID, QSqlTableModel *model)
{
    QSqlQuery query;
    QString res = QString::number(ID);
    query.prepare("DELETE FROM formation WHERE ID= :ID");
    query.bindValue(":ID", res);
    bool deletionSuccess = query.exec();
    if (model)
    {
        model->select();
    }
    return deletionSuccess;
}
QSqlQueryModel * formation::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM formation");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NBRS"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("NBRHS"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRIX"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("DD"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("DF"));

    return model;
}

bool formation::modifier(int ID)
{
    QSqlQuery query;
    QString res = QString::number(ID);
    QString res1 = QString::number(NBRS);
    QString res2 = QString::number(NBRHS);
    QString res3 = QString::number(PRIX);

    query.prepare("UPDATE formation SET ID=:ID, NOM=:NOM, TYPE=:TYPE, NBRS=:NBRS, NBRHS=:NBRHS, PRIX=:PRIX, DD=:DD, DF=:DF WHERE ID = :ID");
    query.bindValue(":ID", res);
    query.bindValue(":NOM", NOM);
    query.bindValue(":TYPE", TYPE);
    query.bindValue(":NBRS", res1);
    query.bindValue(":NBRHS", res2);
    query.bindValue(":PRIX", res3);
    query.bindValue(":DD", DD);
    query.bindValue(":DF", DF);

    qDebug() << "SQL Query: " << query.lastQuery();

    if (query.exec()) {
        qDebug() << "Modification successful!";
        return true;
    } else {
        qDebug() << "Modification failed. Error: " << query.lastError().text();
        return false;
    }
}

QList<int> formation::getAllIDS() {
    QList<int> IDS;
    QSqlQuery query("SELECT ID FROM formation");
    while (query.next()) {
        IDS.append(query.value(0).toInt());
    }
    return IDS;
}
QList<QString> formation::getAllNoms() {
    QList<QString> noms;
    QSqlQuery query("SELECT NOM FROM formation");
    while (query.next()) {
        noms.append(query.value(0).toString());
    }
    return noms;
}
formation formation::getformationByID(int ID)
{    QSqlQuery query;
    query.prepare("SELECT * FROM formation WHERE ID = :ID");
    query.bindValue(":ID", ID);

    if (query.exec() && query.next()) {
        int ID = query.value(0).toInt();
        QString NOM = query.value(1).toString();
        QString TYPE = query.value(2).toString();
        int NBRS = query.value(3).toInt();
        int NBRHS = query.value(4).toInt();
        float PRIX = query.value(5).toFloat();
        QDate DD = query.value(6).toDate();
        QDate DF = query.value(7).toDate();

        return formation(ID, NOM, TYPE, NBRS, NBRHS, PRIX, DD, DF);
    } else {
        return formation();
    }
}
formation formation::getformationByNom(QString NOM) {
    QSqlQuery query;
    query.prepare("SELECT * FROM formation WHERE NOM = :NOM");
    query.bindValue(":NOM", NOM);

    if (query.exec() && query.next()) {
        int ID = query.value(0).toInt();
        QString NOM = query.value(1).toString();
        QString TYPE = query.value(2).toString();
        int NBRS = query.value(3).toInt();
        int NBRHS = query.value(4).toInt();
        float PRIX = query.value(5).toFloat();
        QDate DD = query.value(6).toDate();
        QDate DF = query.value(7).toDate();

        return formation(ID, NOM, TYPE, NBRS, NBRHS, PRIX, DD, DF);
    } else {
        return formation();
    }
}

QSqlQueryModel *formation::sort()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM formation ORDER BY ID ASC;");
    return model;
}
