#ifndef CANDIDATS_H
#define CANDIDATS_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVBoxLayout>
class QSqlTableModel;

class candidats
{
    int CIN , TEL , IDF ;
    QString NOM , PRENOM ,MAIL ;
public:
    candidats(){};
    candidats(int , QString ,QString ,int , QString , int );

    //GETTERS
    int getcin(){return CIN;}
    QString getnom(){return NOM;}
    QString getprenom(){return PRENOM;}
    int gettel(){return TEL;}
    int getidf(){return IDF;}
    QString getmail(){return MAIL;}


    //SETTERS
    void setnom(QString n ){NOM = n ;}
    void setcin(int t ){CIN = t ;}
    void setprenom(QString e ){PRENOM = e ;}
    void settel(int f ){TEL = f ;}
    void setidf(int d ){IDF= d ;}
    void setmail(QString q ){MAIL = q ;}

    //FONCTIONS
    bool ajouter();
    bool modifier(int CIN);
    QSqlQueryModel * afficher();
    QSqlQueryModel * sort(const QString& column = "CIN", Qt::SortOrder order = Qt::AscendingOrder);
    QList<int> getAllCINS();
    QSqlQueryModel *sortCIN();
    bool supprimer(int, QSqlTableModel *model);
    candidats getcandidatsByCIN(int CIN);
    candidats getcandidatsByNom(QString NOM);
    QList<QString> getAllNoms();
};

#endif // CANDIDATS_H
