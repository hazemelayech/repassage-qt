#ifndef FORMATION_H
#define FORMATION_H
#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QVBoxLayout>
class QSqlTableModel;

class formation
{
    QString NOM , TYPE;
    int  ID ,NBRS , NBRHS ;
    float PRIX ;
    QDate DD , DF ;
public:
    formation(){};
    formation(int , QString ,QString ,int , int , float, QDate ,QDate );

    //GETTERS
    int getid(){return ID;}
    QString getnom(){return NOM;}
    QString gettype(){return TYPE;}
    int getnbrs(){return NBRS;}
    int getNBRHS(){return NBRHS;}
    float getprix(){return PRIX;}
    QDate getdd(){return DD;}
    QDate getdf(){return DF;}

    //SETTERS
    void setnom(QString n ){NOM = n ;}
    void setid(int t ){ID = t ;}
    void settype(QString e ){TYPE = e ;}
    void setnbrs(int f ){NBRS = f ;}
    void setNBRHS(int d ){NBRHS = d ;}
    void setprix(float q ){PRIX = q ;}
    void setdd(QDate m ){DD = m ;}
    void setdf(QDate p ){DF = p ;}

    //FONCTIONS
    bool ajouter();
    bool modifier(int ID);
    QSqlQueryModel * afficher();
    QSqlQueryModel *sort();
    QList<int> getAllIDS();
    QSqlQueryModel *sortID();
    bool supprimer(int, QSqlTableModel *model);
    formation getformationByID(int ID);
    formation getformationByNom(QString nom);
    QList<QString> getAllNoms();
};

#endif // FORMATION_H
