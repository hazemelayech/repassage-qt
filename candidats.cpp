#include "candidats.h"
#include<QDebug>
#include<QDebug>
#include<QSqlError>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QVBoxLayout>
candidats::candidats(int CIN , QString NOM  ,QString PRENOM ,int TEL , QString MAIL , int IDF )
{
  this->CIN=CIN;
    this->NOM=NOM;
    this->PRENOM=PRENOM;
    this->TEL=TEL;
    this->MAIL=MAIL;
    this->IDF=IDF;
}

bool candidats::ajouter(){
    QSqlQuery query;
    QString res = QString::number(CIN);
    QString res1 = QString::number(TEL);
    QString res2 = QString::number(IDF);

    query.prepare("INSERT INTO CANDIDATS (CIN, NOM, PRENOM, TEL, MAIL, IDF) "
                  "VALUES (:CIN, :NOM, :PRENOM, :TEL, :MAIL, :IDF)");

    query.bindValue(":CIN",res);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":TEL",res1);
    query.bindValue(":MAIL",MAIL);
    query.bindValue(":IDF",res2);


    return  query.exec();
}

bool candidats::supprimer(int CIN, QSqlTableModel *model)
{
    QSqlQuery query;
    QString res = QString::number(CIN);
    query.prepare("DELETE FROM CANDIDATS WHERE CIN= :CIN");
    query.bindValue(":CIN", res);
    bool deletionSuccess = query.exec();
    if (model)
    {
        model->select();
    }
    return deletionSuccess;
}

QSqlQueryModel * candidats::afficher(){
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM CANDIDATS");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("PRENOM"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("TEL"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("MAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("IDF"));


    return model;
}

bool candidats::modifier(int CIN)
{
    QSqlQuery query;
    QString res = QString::number(CIN);
    QString res1 = QString::number(TEL);
    QString res2 = QString::number(IDF);

    query.prepare("UPDATE CANDIDATS SET CIN=:CIN, NOM=:NOM, PRENOM=:PRENOM, TEL=:TEL, MAIL=:MAIL, IDF=:IDF WHERE CIN = :CIN");
    query.bindValue(":CIN",res);
    query.bindValue(":NOM",NOM);
    query.bindValue(":PRENOM",PRENOM);
    query.bindValue(":TEL",res1);
    query.bindValue(":MAIL",MAIL);
    query.bindValue(":IDF",res2);

    qDebug() << "SQL Query: " << query.lastQuery();

    if (query.exec()) {
        qDebug() << "Modification successful!";
        return true;
    } else {
        qDebug() << "Modification failed. Error: " << query.lastError().text();
        return false;
    }
}
QList<int> candidats::getAllCINS() {
    QList<int> CINS;
    QSqlQuery query("SELECT CIN FROM CANDIDATS");
    while (query.next()) {
        CINS.append(query.value(0).toInt());
    }
    return CINS;
}
QList<QString> candidats::getAllNoms() {
    QList<QString> noms;
    QSqlQuery query("SELECT NOM FROM CANDIDATS");
    while (query.next()) {
        noms.append(query.value(0).toString());
    }
    return noms;
}
candidats candidats::getcandidatsByCIN(int CIN)
{    QSqlQuery query;
    query.prepare("SELECT * FROM CANDIDATS WHERE CIN = :CIN");
    query.bindValue(":CIN", CIN);

    if (query.exec() && query.next()) {
        int CIN = query.value(0).toInt();
        QString NOM = query.value(1).toString();
        QString PRENOM = query.value(2).toString();
        int TEL = query.value(3).toInt();
        QString MAIL = query.value(4).toString();
        int IDF = query.value(5).toInt();



        return candidats(CIN, NOM, PRENOM, TEL, MAIL, IDF);
    } else {
        return candidats();
    }
}
candidats candidats::getcandidatsByNom(QString NOM) {
    QSqlQuery query;
    query.prepare("SELECT * FROM CANDIDATS WHERE NOM = :NOM");
    query.bindValue(":NOM", NOM);

    if (query.exec() && query.next()) {
        int CIN = query.value(0).toInt();
        QString NOM = query.value(1).toString();
        QString PRENOM = query.value(2).toString();
        int TEL = query.value(3).toInt();
        QString MAIL = query.value(4).toString();
        int IDF = query.value(5).toInt();

        return candidats(CIN, NOM, PRENOM, TEL, MAIL, IDF);
    } else {
        return candidats();
    }
}
QSqlQueryModel *candidats::sort(const QString& column, Qt::SortOrder order) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QString query = QString("SELECT * FROM CANDIDATS ORDER BY %1 %2;")
                        .arg(column)
                        .arg(order == Qt::AscendingOrder ? "ASC" : "DESC");
    model->setQuery(query);
    return model;
}

