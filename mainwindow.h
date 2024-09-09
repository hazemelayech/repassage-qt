#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"candidats.h"
#include <QMainWindow>
#include<QSqlTableModel>
#include"formation.h"
#include<QComboBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots :
    // FORMATION
    void on_ajout_clicked();

    void on_modifier_clicked();

    void on_rech();
    void on_rechf();
    void on_Retour_21_clicked_refresh();

    void setupComboBoxIDS();


    void on_supprimer_clicked();
     void onHeaderClicked_2(int logicalIndex);
    void setupComboBoxNoms();
    void on_pdf_clicked();
    void on_stat_clicked();
    void on_tableView_3_clicked(const QModelIndex &index);
    void on_modifier_2_clicked_submitmod();
  QByteArray generatePDF(const QString &ID);
  void handleCalendarClick(const QDate& date);
 void setcourseDatesFormatting();

 // CANDIDATES
 void on_ajoutC_clicked();

 void on_modifierC_clicked();

 void on_rechC();
 void on_Retour_21_clicked_refreshC();

 void setupComboBoxCINS();


 void on_supprimerC_clicked();
  void onHeaderClicked_2C(int logicalIndex);
 void setupComboBoxNomsC();
 void on_pdfC_clicked();
 void on_statC_clicked();
 void on_tableView_2_clicked(const QModelIndex &index);
 void on_modifierC_2_clicked_submitmod();
QByteArray generatePDFC(const QString &ID);
void on_envoyer_clicked();

void on_con_menu_clicked();

void on_for_menu_clicked();

void on_menu_2_clicked();

void on_menu_1_clicked();

public:
    MainWindow(QWidget *parent = nullptr);
    void colorCourseDates();
      void setEmissionDatesFormatting();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
     QStringList files;
     QSqlTableModel * formationModel;
     QComboBox *idComboBox;
     QComboBox *nomComboBox;
     QSqlTableModel *model;

      /*///////////////////////////////////////////////////////*/
      formation tmp ;

      // candidates
      QSqlTableModel * candidatesModel;
      QComboBox *cinComboBox;
      QComboBox *nomcComboBox;
      QSqlTableModel *modelc;

      candidats cmp ;
};
#endif // MAINWINDOW_H
