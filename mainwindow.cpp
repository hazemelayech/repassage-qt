#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formation.h"
#include"candidats.h"
#include "qrcode.h"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
using namespace qrcodegen;
#include<QInputDialog>
#include<QSqlQuery>
#include<QSqlError>
#include <QTableView>
#include <QStyledItemDelegate>
#include <QPainter>
#include<QMessageBox>
#include<QSqlTableModel>
#include<QFileDialog>
#include<QInputDialog>
#include<QSqlRecord>
#include<QPixmap>
#include<QDialog>
#include<QDialogButtonBox>
#include<QSqlField>
#include<QPdfWriter>
#include<QDesktopServices>
#include<QProgressDialog>
#include <QtWidgets>
#include<QThread>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QCoreApplication>
#include <QLineEdit>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QRegExpValidator>
#include <QRegularExpressionValidator>

#include <QColor>
#include <QMap>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QTextCharFormat>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //formation
    formationModel = new QSqlTableModel(this);
    formationModel->setTable("formation");
    formationModel->select();


    formationModel->setHeaderData(0, Qt::Horizontal, "ID");


    for (int i = 0; i < formationModel->columnCount(); ++i) {
        ui->comboBox_mod->addItem(formationModel->headerData(i, Qt::Horizontal).toString());
        ui->comboBox_2->addItem(formationModel->headerData(i, Qt::Horizontal).toString());

    }

     ui->tableView_3->setModel(tmp.afficher());
    //connect(ui->ajout, &QPushButton::clicked, this, &MainWindow::on_ajout_clicked);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimer_clicked);
    //connect(ui->modifier, &QPushButton::clicked, this, &MainWindow::on_modifier_clicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_modifier_2_clicked_submitmod);
    connect(ui->refresh, &QPushButton::clicked, this, &MainWindow::on_Retour_21_clicked_refresh);
    connect(ui->tableView_3->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked_2(int)));
    setupComboBoxIDS();





   //candidates
   candidatesModel = new QSqlTableModel(this);
   candidatesModel->setTable("CANDIDATS");
   candidatesModel->select();

   candidatesModel->setHeaderData(0, Qt::Horizontal, "CIN");


   for (int i = 0; i < candidatesModel->columnCount(); ++i) {
       ui->comboBoxc->addItem(candidatesModel->headerData(i, Qt::Horizontal).toString());
       ui->comboBoxc_noms->addItem(candidatesModel->headerData(i, Qt::Horizontal).toString());

   }

 /*  for (int i = 0; i < candidatesModel->columnCount(); ++i) {
       ui->comboBoxc_noms->addItem(candidatesModel->headerData(i, Qt::Horizontal).toString());
   }
*/

   ui->tableView_2->setModel(cmp.afficher());
   connect(ui->ajoutc, &QPushButton::clicked, this, &MainWindow::on_ajoutC_clicked);
   connect(ui->supprimerc, &QPushButton::clicked, this, &MainWindow::on_supprimerC_clicked);
  connect(ui->modifierc, &QPushButton::clicked, this, &MainWindow::on_modifierC_clicked);
   connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_modifierC_2_clicked_submitmod);
   connect(ui->refreshc, &QPushButton::clicked, this, &MainWindow::on_Retour_21_clicked_refreshC);
 //  connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked_2C(int)));
      connect(ui->tableView_2->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked_2C(int)));
   setupComboBoxCINS();
connect(ui->modifier_submit, &QPushButton::clicked, this, &MainWindow::on_modifierC_2_clicked_submitmod);
connect(ui->pdfc, &QPushButton::clicked, this, &MainWindow::on_pdfC_clicked);
  connect(ui->statc, &QPushButton::clicked, this, &MainWindow::on_statC_clicked);
connect(ui->rechc, &QPushButton::clicked, this, &MainWindow::on_rechC);
connect(ui->rechf, &QPushButton::clicked, this, &MainWindow::on_rechf);
connect(ui->tableView_2, SIGNAL(clicked(const QModelIndex&)), this, SLOT(on_tableView_2_clicked(const QModelIndex&)));
connect(ui->tableView_2, &QTableView::clicked, this, &MainWindow::on_tableView_2_clicked);
connect(ui->menu_1, &QPushButton::clicked, this, &MainWindow::on_menu_1_clicked);
connect(ui->menu_2, &QPushButton::clicked, this, &MainWindow::on_menu_2_clicked);

QString globalStyle = "QLabel {"
                         "font-size: 14px;"
                         "color: #333333;"
                         "font-weight: bold;"
                         "}"
                         "QLineEdit {"
                         "background-color: #F0F0F0;"
                         "border: 1px solid #CCCCCC;"
                         "border-radius: 6px;"
                         "padding: 6px;"
                         "font-size: 14px;"
                         "color: #333333;"
                         "}"
                         "QLineEdit:focus {"
                         "border-color: #4CAF50;"
                         "box-shadow: 0 0 5px rgba(76, 175, 80, 0.5);"
                         "}";

   // Applying the stylesheet to the entire MainWindow
   this->setStyleSheet(globalStyle);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_con_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_for_menu_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_menu_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_menu_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
// FORMATION
void MainWindow::on_ajout_clicked() {
    // Input validation
    if (ui->id->text().isEmpty() || ui->nom->text().isEmpty() || ui->type->text().isEmpty() ||
        ui->prix->text().isEmpty() || ui->nbrs->text().isEmpty() || ui->nbrsh->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validate numeric inputs
    int id = ui->id->text().toInt();
    float prix = ui->prix->text().toFloat();
    int nbrs = ui->nbrs->text().toInt();
    int NBRHS = ui->nbrsh->text().toInt();

    if (id <= 0 || prix <= 0 || nbrs <= 0 || NBRHS <= 0) {
        QMessageBox::warning(this, "Input Error", "ID, price, number of students, and number of hours must be positive.");
        return;
    }

    // Validate dates
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();
    QDate today = QDate::currentDate();

    if (dd <= today) {
        QMessageBox::warning(this, "Input Error", "The start date must be later than today.");
        return;
    }

    if (df <= dd) {
        QMessageBox::warning(this, "Input Error", "The end date must be later than the start date.");
        return;
    }

    // Log action if inputs are valid
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString action = "ajouter un formation";
    QString logEntry = timestamp + " - " + action + "\n";

    QFile file("formationlog.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
    }

    // Continue with adding the formation after validation
    QString nom = ui->nom->text();
    QString type = ui->type->text();

    formation f(id, nom, type, nbrs, NBRHS, prix, dd, df);
    bool test = f.ajouter();

    if (test) {
        ui->tableView_3->setModel(tmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Ajout effectué.\n" "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        // Clear the fields after a successful insert
        ui->id->clear();
        ui->nom->clear();
        ui->type->clear();
        ui->nbrs->clear();
        ui->nbrsh->clear();
        ui->prix->clear();
        ui->dd->clear();
        ui->df->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n" "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

/*
void MainWindow::on_ajout_clicked() {

   QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "ajouter un formation";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    int id = ui->id->text().toInt();
    QString nom = ui->nom->text();
    QString type = ui->type->text();
    float prix = ui->prix->text().toInt();
    int nbrs = ui->nbrs->text().toInt();
    int NBRHS = ui->nbrsh->text().toInt();
    QDate dd = ui->dd->date();
    QDate df = ui->df->date();

    formation f(id, nom, type, nbrs, NBRHS, prix, dd, df);
    bool test = f.ajouter();

    if (test) {
        ui->tableView_3->setModel(tmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Ajout effectué.\n" "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        // Clear the fields after a successful insert
        ui->id->clear();
        ui->nom->clear();
        ui->type->clear();
        ui->nbrs->clear();
        ui->nbrsh->clear();
        ui->prix->clear();
        ui->dd->clear();
        ui->df->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n" "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

*/
void MainWindow::on_supprimer_clicked() {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "supprimer un formation";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    QModelIndexList selectedRows = ui->tableView_3->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a row to delete.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete the selected row(s)?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    for (const QModelIndex& index : selectedRows) {
        int row = index.row();
        int ID = ui->tableView_3->model()->data(ui->tableView_3->model()->index(row, 0)).toInt();
        bool test = tmp.supprimer(ID, formationModel);

        if (test) {
            ui->tableView_3->model()->removeRow(row);
        } else {
            QMessageBox::critical(this, "Error", "Deletion failed for some rows.");
        }
    }
    QMessageBox::information(this, "Success", "Deletion completed.");

}


void MainWindow::on_modifier_2_clicked_submitmod() {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "modifier un formation";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    QString selectedIDText = ui->comboBox_mod->currentText();
    int selectedID = selectedIDText.toInt();
    formation f;
    formation fr = f.getformationByID(selectedID);
    ui->idm->setText(QString::number(fr.getid()));
    ui->nomm->setText(fr.getnom());
    ui->typem->setText(fr.gettype());
    ui->prixm->setText(QString::number(fr.getprix()));
   //ui-nbrshm_2->setText(QString::number(fr.getnbrs()));
    ui->nbrshm->setText(QString::number(fr.getNBRHS()));
    ui->dd->setDate(fr.getdd());
ui->df->setDate(fr.getdf());

    for (int i = 0; i < formationModel->rowCount(); ++i) {
            ui->tableView_3->showRow(i);
        }

}

void MainWindow::setupComboBoxIDS() {

    formation Instance;
    QList<int> ids = Instance.getAllIDS();
    ui->comboBox_mod->clear();
    for (int ID : ids) {
        ui->comboBox_mod->addItem(QString::number(ID));
    }
}

void MainWindow::on_Retour_21_clicked_refresh()
{
    formationModel->select();
    for (int i = 0; i < formationModel->rowCount(); ++i) {
            ui->tableView_3->showRow(i);
        }
          ui->tableView_3->setModel(formationModel);


}
void MainWindow::on_modifier_clicked()
{
    // Input validation
    if (ui->idm->text().isEmpty() || ui->nomm->text().isEmpty() || ui->typem->text().isEmpty() ||
        ui->prixm->text().isEmpty() || ui->nbrsm->text().isEmpty() || ui->nbrshm->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validate numeric inputs
    int updatedid = ui->idm->text().toInt();
    float updatedPrix = ui->prixm->text().toFloat();
    int updatednbrs = ui->nbrsm->text().toInt();
    int updatednbrhs = ui->nbrshm->text().toInt();

    if (updatedid <= 0 || updatedPrix <= 0 || updatednbrs <= 0 || updatednbrhs <= 0) {
        QMessageBox::warning(this, "Input Error", "ID, price, number of students, and number of hours must be positive.");
        return;
    }

    // Validate dates
    QDate updateddd = ui->ddm->date();
    QDate updateddf = ui->dfm->date();
    QDate today = QDate::currentDate();

    if (updateddd <= today) {
        QMessageBox::warning(this, "Input Error", "The start date must be later than today.");
        return;
    }

    if (updateddf <= updateddd) {
        QMessageBox::warning(this, "Input Error", "The end date must be later than the start date.");
        return;
    }

    // Log action if inputs are valid
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString action = "modifier un formation";
    QString logEntry = timestamp + " - " + action + "\n";

    QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
    }

    // Create a formation object and fetch the formation details by ID
    formation eqi;
    formation eq = eqi.getformationByID(updatedid);

    QString updatedNom = ui->nomm->text();
    QString updatedType = ui->typem->text();

    // Update the formation object with the new values
    eqi.setid(updatedid);
    eqi.setnom(updatedNom);
    eqi.settype(updatedType);
    eqi.setprix(updatedPrix);
    eqi.setnbrs(updatednbrs);
    eqi.setNBRHS(updatednbrhs);
    eqi.setdd(updateddd);
    eqi.setdf(updateddf);

    // Attempt to modify the formation record in the database
    bool modR = eqi.modifier(updatedid);

    // Show the appropriate message box based on the success or failure of the operation
    if (modR) {
        QMessageBox::information(this, "Succès", "Formation modifiée avec succès.");
        // Clear the input fields after successful modification
        ui->idm->clear();
        ui->nomm->clear();
        ui->typem->clear();
        ui->prixm->clear();
        ui->nbrsm->clear();
        ui->nbrshm->clear();
        ui->ddm->clear();
        ui->dfm->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la formation.");
    }
}

/*
void MainWindow::on_modifier_clicked()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "modifier un formation";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/yassi/OneDrive - ESPRIT/Desktop/taches qt/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    static int callCount = 0;
     callCount++;
     qDebug() << "on_modifier_clicked called " << callCount << " times";
    qDebug() << "Modify button clicked";

    // Get the selected ID from the combo box
    QString selectedidText = ui->comboBox_mod->currentText();
    int selectedid = selectedidText.toInt();
    qDebug() << "Selected ID: " << selectedid;

    // Create a formation object and fetch the formation details by ID
    formation eqi;
    formation eq = eqi.getformationByID(selectedid);

    // Get updated values from the UI
    int updatedid = ui->idm->text().toInt();
    QString updatedNom = ui->nomm->text();
    QString updatedType = ui->typem->text();
    float updatedPrix = ui->prixm->text().toFloat();
    int updatednbrs = ui->nbrsm->text().toInt();
    int updatednbrhs = ui->nbrshm->text().toInt();
    QDate updateddd = ui->ddm->date();
    QDate updateddf = ui->dfm->date();

    qDebug() << "Updated ID: " << updatedid;
    qDebug() << "Updated Name: " << updatedNom;
    qDebug() << "Updated Type: " << updatedType;
    qDebug() << "Updated Price: " << updatedPrix;
    qDebug() << "Updated NBRS: " << updatednbrs;
    qDebug() << "Updated NBRHS: " << updatednbrhs;
    qDebug() << "Updated Start Date: " << updateddd;
    qDebug() << "Updated End Date: " << updateddf;

    // Update the formation object with the new values
    eqi.setid(updatedid);
    eqi.setnom(updatedNom);
    eqi.settype(updatedType);
    eqi.setprix(updatedPrix);
    eqi.setnbrs(updatednbrs);
    eqi.setNBRHS(updatednbrhs);
    eqi.setdd(updateddd);
    eqi.setdf(updateddf);

    // Attempt to modify the formation record in the database
    bool modR = eqi.modifier(selectedid);

    // Show the appropriate message box based on the success or failure of the operation
    if (modR) {
        QMessageBox::information(this, "Succès", "Formation modifiée avec succès.");
        // Clear the input fields after successful modification
        ui->idm->clear();
        ui->nomm->clear();
        ui->typem->clear();
        ui->prixm->clear();
        ui->nbrsm->clear();
        ui->nbrshm->clear();
        ui->ddm->clear();
        ui->dfm->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la formation.");
    }
}

*/

void MainWindow::onHeaderClicked_2(int logicalIndex) {
    if (ui->tableView_3) {

        QSqlQueryModel *existingModel = qobject_cast<QSqlQueryModel*>(ui->tableView_3->model());

        if (existingModel) {

            QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
            proxyModel->setSourceModel(existingModel);
            ui->tableView_3->setModel(proxyModel);
            ui->tableView_3->setSortingEnabled(true);
            QString sortAttribute = existingModel->headerData(logicalIndex, Qt::Horizontal).toString();
            proxyModel->sort(logicalIndex, Qt::AscendingOrder);
        } else {
            qDebug() << "Existing model is not of type QSqlQueryModel.";
        }
    } else {
        qDebug() << "QTableView (tableView_3) not found.";
    }
}
void MainWindow::on_pdf_clicked()
{

    QString filePath = "C:/Users/DELL/Desktop/formation/formation_report.pdf";
    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    if (pdf.resolution() <= 0) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer QPainter.");
        return;
    }

    int yPos = 400; // Initial vertical position

    // Define fonts
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont normalFont("Arial", 10);

    // Draw the title
    painter.setFont(titleFont);
    painter.drawText(200, yPos, "Rapport de Formation");
    yPos += 50; // Adjust vertical spacing

    // Draw table headers
    painter.setFont(headerFont);
    painter.drawText(100, yPos, "ID");
    painter.drawText(300, yPos, "Nom");
    painter.drawText(500, yPos, "Prix");
    yPos += 60; // Adjust vertical spacing

    QSqlQuery query;
    query.prepare("SELECT ID, NOM, PRIX FROM formation");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête SQL.\n" + query.lastError().text());
        return;
    }

    // Draw table data
    while (query.next())
    {
        painter.setFont(normalFont);
        painter.drawText(100, yPos, query.value(0).toString());
        painter.drawText(300, yPos, query.value(1).toString());
        painter.drawText(500, yPos, QString::number(query.value(2).toFloat(), 'f', 2));
        yPos += 60; // Adjust vertical spacing
    }

    // Adjust the page size if needed
    pdf.setPageMargins(QMarginsF(10, 10, 10, 10));

    painter.end();

    int response = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}
void MainWindow::on_stat_clicked()
{
    // Fetch data from the database
    QSqlQueryModel *model = tmp.afficher();

    // Create a bar series to hold the data
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // List to hold the categories (formation names with their respective hours)
    QStringList categories;

    // Loop through each row of the model
    for (int i = 0; i < model->rowCount(); ++i) {
        // Get the formation name
        QString formationName = model->data(model->index(i, 1)).toString();

        // Get the number of hours (NBRSH)
        int nbrsh = model->data(model->index(i, 4)).toInt();

        // Create a new bar set with the name of the formation
        QtCharts::QBarSet *set = new QtCharts::QBarSet(formationName);

        // Add the number of hours to the bar set
        *set << nbrsh;

        // Add the bar set to the series
        series->append(set);

        // Add the category (formation name with its hours) to the list
        categories << QString("%1 (%2 hrs)").arg(formationName).arg(nbrsh);
    }

    // Create a bar chart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique sur le nombre d'heures des formations");
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);

    // Create and configure the x-axis with the categories
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create and configure the y-axis
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Nombre des heures (NBRSH)");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create a chart view to display the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set up a new window to display the chart
    QDialog *chartDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    chartDialog->setLayout(layout);

    // Show the chart window
    chartDialog->exec();
}
/*
void MainWindow::setcourseDatesFormatting()
{
    // Define the text format for course dates
    QTextCharFormat startFormat;
    startFormat.setBackground(Qt::green); // Color for start dates

    QTextCharFormat endFormat;
    endFormat.setBackground(Qt::red); // Color for end dates

    // Query course dates from the database
    QSqlQuery query("SELECT DD, DF FROM formation");
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Query execution failed.\n" + query.lastError().text());
        return;
    }

    // Fetch start and end dates from the query result and apply the text format
    while (query.next()) {
        QDate startDate = query.value(6).toDate(); // Get start date
        QDate endDate = query.value(7).toDate();   // Get end date

        if (startDate.isValid()) {
            // Apply the text format with the start color to each start date in the calendar widget
            ui->ca->setDateTextFormat(startDate, startFormat);
            qDebug() << "Set text format for start date:" << startDate.toString("yyyy-MM-dd");
        }

        if (endDate.isValid()) {
            // Apply the text format with the end color to each end date in the calendar widget
            ui->ca->setDateTextFormat(endDate, endFormat);
            qDebug() << "Set text format for end date:" << endDate.toString("yyyy-MM-dd");
        }
    }

    // Update the calendar widget display
    ui->ca->update();
}

void MainWindow::handleCalendarClick(const QDate& date) {
    // Query the database to retrieve emission information for the clicked date
    QSqlQuery query_emission;
    query_emission.prepare("SELECT * FROM formation WHERE DD = ?");
    query_emission.addBindValue(date.toString("yyyy-MM-dd"));

    if (query_emission.exec() && query_emission.next()) {
        // Retrieve emission information
        QString id = query_emission.value(0).toString();
        QString nom = query_emission.value(1).toString();
        QString typee = query_emission.value(2).toString();
       QString DF = query_emission.value(7).toString();


            // Display the emission and employee information
            QString infoMessage = "formation: " + id + "\n";
            infoMessage += "Nom: " + nom + "\n";
            infoMessage += "Type: " + typee + "\n";
            infoMessage += "df: " + DF + "\n";

            // Display the information
            QMessageBox::information(this, "Emission Information", infoMessage);
        } else {
            QMessageBox::information(this, "No Employee", "No employee found for the selected emission.");
        }

}
*/





// CANDIDATES

void MainWindow::on_ajoutC_clicked() {
    // Input validation
    if (ui->cin->text().isEmpty() || ui->nomc->text().isEmpty() || ui->prenomc->text().isEmpty() ||
        ui->tel->text().isEmpty() || ui->mail->text().isEmpty() || ui->idf->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validate numeric inputs
    int cin = ui->cin->text().toInt();
    int tel = ui->tel->text().toInt();
    int idf = ui->idf->text().toInt();

    if (cin <= 0 || tel <= 0 || idf <= 0) {
        QMessageBox::warning(this, "Input Error", "CIN, telephone, and formation ID must be positive.");
        return;
    }

    // Validate email format
    QString mail = ui->mail->text();
    QRegExp emailRegex("^\\S+@\\S+\\.\\S+$");  // Simple email regex
    if (!emailRegex.exactMatch(mail)) {
        QMessageBox::warning(this, "Input Error", "Invalid email format.");
        return;
    }

    // Log action if inputs are valid
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString action = "ajouter un candidat";
    QString logEntry = timestamp + " - " + action + "\n";

    QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
    }

    // Retrieve other inputs
    QString nom = ui->nomc->text();
    QString prenom = ui->prenomc->text();

    // Create the candidate object
    candidats C(cin, nom, prenom, tel, mail, idf);
    bool test = C.ajouter();

    if (test) {
        ui->tableView_2->setModel(cmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Ajout effectué.\n" "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        // Clear the fields after a successful insert
        ui->cin->clear();
        ui->nomc->clear();
        ui->prenomc->clear();
        ui->tel->clear();
        ui->mail->clear();
        ui->idf->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n" "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

/*
void MainWindow::on_ajoutC_clicked() {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "ajouter un condida";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/yassi/OneDrive - ESPRIT/Desktop/taches qt/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    int cin = ui->cin->text().toInt();
    QString nom = ui->nomc->text();
    QString prenom = ui->prenomc->text();
    int tel = ui->tel->text().toInt();
    QString mail = ui->mail->text();
    int idf = ui->idf->text().toInt();


    candidats C(cin, nom, prenom, tel, mail, idf);
    bool test = C.ajouter();

    if (test) {
        ui->tableView_2->setModel(cmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                  QObject::tr("Ajout effectué.\n" "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        // Clear the fields after a successful insert
        ui->cin->clear();
        ui->nom->clear();
        ui->prenomc->clear();
        ui->tel->clear();
        ui->mail->clear();
        ui->idf->clear();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              QObject::tr("Ajout non effectué.\n" "Cliquez sur Annuler pour quitter."),
                              QMessageBox::Cancel);
    }
}

*/
void MainWindow::on_supprimerC_clicked() {
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "supprimer un condida";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    QModelIndexList selectedRows = ui->tableView_2->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please select a row to delete.");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete the selected row(s)?",
                                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }
    for (const QModelIndex& index : selectedRows) {
        int row = index.row();
        int CIN = ui->tableView_2->model()->data(ui->tableView_3->model()->index(row, 0)).toInt();
        bool test = cmp.supprimer(CIN, candidatesModel);

        if (test) {
            ui->tableView_2->model()->removeRow(row);
        } else {
            QMessageBox::critical(this, "Error", "Deletion failed for some rows.");
        }
    }
    QMessageBox::information(this, "Success", "Deletion completed.");

}
void MainWindow::on_modifierC_2_clicked_submitmod() {

    QString selectedCINText = ui->comboBoxc->currentText();
    int selectedCIN = selectedCINText.toInt();
    candidats f;
    candidats fr = f.getcandidatsByCIN(selectedCIN);
    ui->cinm->setText(QString::number(fr.getcin()));
    ui->nomcm->setText(fr.getnom());
    ui->prenomcm->setText(fr.getprenom());
    ui->telm->setText(QString::number(fr.gettel()));
   ui->mailm->setText(fr.getmail());
   ui->idfm->setText(QString::number(fr.getidf()));


    for (int i = 0; i < candidatesModel->rowCount(); ++i) {
            ui->tableView_2->showRow(i);
        }

}
void MainWindow::setupComboBoxCINS() {

    candidats Instance;
    QList<int> cins = Instance.getAllCINS();
    ui->comboBoxc->clear();
    for (int CIN : cins) {
        ui->comboBoxc->addItem(QString::number(CIN));
    }
}

void MainWindow::on_Retour_21_clicked_refreshC()
{
    candidatesModel->select();
    for (int i = 0; i < candidatesModel->rowCount(); ++i) {
            ui->tableView_2->showRow(i);
        }
          ui->tableView_2->setModel(candidatesModel);


}

void MainWindow::on_modifierC_clicked() {
    // Input validation
    if (ui->cinm->text().isEmpty() || ui->nomcm->text().isEmpty() || ui->prenomcm->text().isEmpty() ||
        ui->telm->text().isEmpty() || ui->mailm->text().isEmpty() || ui->idfm->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields must be filled out.");
        return;
    }

    // Validate numeric inputs
    int updatedcin = ui->cinm->text().toInt();
    int updatedtel = ui->telm->text().toInt();
    int updatedidf = ui->idfm->text().toInt();

    if (updatedcin <= 0 || updatedtel <= 0 || updatedidf <= 0) {
        QMessageBox::warning(this, "Input Error", "CIN, telephone, and formation ID must be positive.");
        return;
    }

    // Validate email format
    QString updatedmail = ui->mailm->text();
    QRegExp emailRegex("^\\S+@\\S+\\.\\S+$");  // Simple email regex
    if (!emailRegex.exactMatch(updatedmail)) {
        QMessageBox::warning(this, "Input Error", "Invalid email format.");
        return;
    }

    // Log action if inputs are valid
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    QString action = "modifier un candidat";
    QString logEntry = timestamp + " - " + action + "\n";

    QFile file("C:/Users/DELL/Desktop/formation/formationlog.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << logEntry;
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
    }

    // Retrieve the updated values from the UI
    QString updatedNom = ui->nomcm->text();
    QString updatedprenom = ui->prenomcm->text();

    // Create the candidate object and set updated values
    candidats eqi;
    eqi.setcin(updatedcin);
    eqi.setnom(updatedNom);
    eqi.setprenom(updatedprenom);
    eqi.settel(updatedtel);
    eqi.setmail(updatedmail);
    eqi.setidf(updatedidf);

    // Attempt to modify the candidate record in the database
    bool modR = eqi.modifier(updatedcin);

    // Show the appropriate message box based on the success or failure of the operation
    if (modR) {
        QMessageBox::information(this, "Succès", "Candidat modifié avec succès.");
        // Clear the input fields after successful modification
        ui->cinm->clear();
        ui->nomcm->clear();
        ui->prenomcm->clear();
        ui->telm->clear();
        ui->mailm->clear();
        ui->idfm->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du candidat.");
    }
}


/*
void MainWindow::on_modifierC_clicked()
{
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

        // Define the action you want to log
        QString action = "modifier un condida";

        // Combine the timestamp and action
        QString logEntry = timestamp + " - " + action + "\n";

        // Write the log entry to the file
        QFile file("C:/Users/yassi/OneDrive - ESPRIT/Desktop/taches qt/formationlog.txt");
        if (file.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&file);
            out << logEntry;
            file.close();
        } else {
            QMessageBox::warning(this, "Error", "Failed to open log file for writing.");
        }
    static int callCount = 0;
     callCount++;
     qDebug() << "on_modifier_clicked called " << callCount << " times";
    qDebug() << "Modify button clicked";

    // Get the selected ID from the combo box
    QString selectedcinText = ui->comboBoxc->currentText();
    int selectedcin = selectedcinText.toInt();
    qDebug() << "Selected cin: " << selectedcin;

    // Create a formation object and fetch the formation details by ID
    candidats eqi;
    candidats eq = eqi.getcandidatsByCIN(selectedcin);

    // Get updated values from the UI
    int updatedcin = ui->cinm->text().toInt();
    QString updatedNom = ui->nomcm->text();
    QString updatedprenom = ui->prenomcm->text();
    int updatedtel = ui->telm->text().toInt();
    QString updatedmail = ui->mailm->text();
    int updatedidf = ui->idfm->text().toInt();


    qDebug() << "Updated cin: " << updatedcin;
    qDebug() << "Updated Name: " << updatedNom;
    qDebug() << "Updated pre: " << updatedprenom;
    qDebug() << "Updated tel: " << updatedtel;
    qDebug() << "Updated mail: " << updatedmail;
    qDebug() << "Updated idf: " << updatedidf;


    // Update the formation object with the new values
    eqi.setcin(updatedcin);
    eqi.setnom(updatedNom);
    eqi.setprenom(updatedprenom);
    eqi.settel(updatedtel);
    eqi.setmail(updatedmail);
    eqi.setidf(updatedidf);


    // Attempt to modify the formation record in the database
    bool modR = eqi.modifier(selectedcin);

    // Show the appropriate message box based on the success or failure of the operation
    if (modR) {
        QMessageBox::information(this, "Succès", "Formation modifiée avec succès.");
        // Clear the input fields after successful modification
        ui->cinm->clear();
        ui->nomcm->clear();
        ui->prenomcm->clear();
        ui->telm->clear();
        ui->mailm->clear();
        ui->idfm->clear();

    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la modification de la formation.");
    }
}
*/
/*
void MainWindow::onHeaderClicked_2C(int logicalIndex) {
    if (ui->tableView_2) {

        QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(ui->tableView_2->model());
        QSqlQueryModel *existingModel = qobject_cast<QSqlQueryModel*>(proxyModel ? proxyModel->sourceModel() : ui->tableView_2->model());

        if (existingModel) {

            if (!proxyModel) {
                proxyModel = new QSortFilterProxyModel(this);
                proxyModel->setSourceModel(existingModel);
                ui->tableView_2->setModel(proxyModel);
                ui->tableView_2->setSortingEnabled(true);
            }

            proxyModel->sort(logicalIndex, Qt::AscendingOrder);
        } else {
            qDebug() << "Existing model is not of type QSqlQueryModel.";
        }
    } else {
        qDebug() << "QTableView (tableView_2) not found.";
    }
}

*/
void MainWindow::onHeaderClicked_2C(int logicalIndex) {
    if (ui->tableView_2) {

        QSortFilterProxyModel *proxyModel = qobject_cast<QSortFilterProxyModel*>(ui->tableView_2->model());
        QSqlQueryModel *existingModel = qobject_cast<QSqlQueryModel*>(proxyModel ? proxyModel->sourceModel() : ui->tableView_2->model());

        if (existingModel) {

            if (!proxyModel) {
                proxyModel = new QSortFilterProxyModel(this);
                proxyModel->setSourceModel(existingModel);
                ui->tableView_2->setModel(proxyModel);
                ui->tableView_2->setSortingEnabled(true);
            }

            QString columnName = existingModel->headerData(logicalIndex, Qt::Horizontal).toString();
            proxyModel->sort(logicalIndex, Qt::AscendingOrder);

            // Optionally, if you want to re-query the database and get sorted data from SQL:
            // QSqlQueryModel *sortedModel = cmp.sort(columnName);
            // proxyModel->setSourceModel(sortedModel);
        } else {
            qDebug() << "Existing model is not of type QSqlQueryModel.";
        }
    } else {
        qDebug() << "QTableView (tableView_2) not found.";
    }
}
void MainWindow::on_statC_clicked()
{
    // Create a QSqlQuery to aggregate the number of candidates per IDF
    QSqlQuery query;
    query.prepare("SELECT IDF, COUNT(*) as candidate_count FROM candidats GROUP BY IDF");

    if (!query.exec()) {
        // Handle error
        qDebug() << "Error fetching data:" << query.lastError();
        return;
    }

    // Create a bar series to hold the data
    QtCharts::QBarSeries *series = new QtCharts::QBarSeries();

    // List to hold the categories (IDFs)
    QStringList categories;

    // Loop through each row of the query result
    while (query.next()) {
        // Get the IDF
        int idf = query.value(0).toInt();

        // Get the number of candidates
        int candidate_count = query.value(1).toInt();

        // Create a new bar set with the IDF name
        QtCharts::QBarSet *set = new QtCharts::QBarSet(QString("IDF %1").arg(idf));

        // Add the candidate count to the bar set
        *set << candidate_count;

        // Add the bar set to the series
        series->append(set);

        // Add the category (IDF) to the list
        categories << QString("IDF %1").arg(idf);
    }

    // Create a bar chart and add the series
    QtCharts::QChart *chart = new QtCharts::QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique sur le nombre de candidats par IDF");
    chart->setAnimationOptions(QtCharts::QChart::AllAnimations);

    // Create and configure the x-axis with the categories
    QtCharts::QBarCategoryAxis *axisX = new QtCharts::QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Create and configure the y-axis
    QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis();
    axisY->setTitleText("Nombre des candidats");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create a chart view to display the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Set up a new window to display the chart
    QDialog *chartDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    chartDialog->setLayout(layout);

    // Show the chart window
    chartDialog->exec();
}
void MainWindow::on_pdfC_clicked()
{

    QString filePath = "C:/Users/DELL/Desktop/formation/candidates_report.pdf";
    QPdfWriter pdf(filePath);
    pdf.setPageSize(QPageSize(QPageSize::A4));
    pdf.setResolution(300);

    if (pdf.resolution() <= 0) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    QPainter painter(&pdf);

    if (!painter.isActive()) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer QPainter.");
        return;
    }

    int yPos = 400; // Initial vertical position

    // Define fonts
    QFont titleFont("Arial", 18, QFont::Bold);
    QFont headerFont("Arial", 12, QFont::Bold);
    QFont normalFont("Arial", 10);

    // Draw the title
    painter.setFont(titleFont);
    painter.drawText(200, yPos, "Rapport des Candidats");
    yPos += 50; // Adjust vertical spacing

    // Draw table headers
    painter.setFont(headerFont);
    painter.drawText(50, yPos, "CIN");
    painter.drawText(150, yPos, "Nom");
    painter.drawText(300, yPos, "Prenom");
    painter.drawText(450, yPos, "Tel");
    painter.drawText(600, yPos, "Mail");
    painter.drawText(750, yPos, "IDF");
    yPos += 60; // Adjust vertical spacing

    QSqlQuery query;
    query.prepare("SELECT CIN, NOM, PRENOM, TEL, MAIL, IDF FROM candidats");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête SQL.\n" + query.lastError().text());
        return;
    }

    // Draw table data
    while (query.next())
    {
        painter.setFont(normalFont);
        painter.drawText(50, yPos, query.value(0).toString());
        painter.drawText(150, yPos, query.value(1).toString());
        painter.drawText(300, yPos, query.value(2).toString());
        painter.drawText(450, yPos, query.value(3).toString());
        painter.drawText(600, yPos, query.value(4).toString());
        painter.drawText(750, yPos, query.value(5).toString());
        yPos += 60; // Adjust vertical spacing

        // Check if the yPos exceeds the page height, create a new page if necessary
        if (yPos > pdf.height() - 100) {
            pdf.newPage();
            yPos = 400; // Reset the vertical position
        }
    }

    // Adjust the page size if needed
    pdf.setPageMargins(QMarginsF(10, 10, 10, 10));

    painter.end();

    int response = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
    }
}
void MainWindow::on_rechC()
{
    QString selectedAttribute = ui->comboBoxc_noms->currentText();
    int columnIndex = candidatesModel->fieldIndex(selectedAttribute);
    QString searchValue = QInputDialog::getText(this, "Search", "Enter the value to search for:");

    ui->tableView_2->clearSelection();

    if (searchValue.isEmpty()) {

        for (int i = 0; i < candidatesModel->rowCount(); ++i) {
            ui->tableView_2->showRow(i);
        }
    } else {

        for (int i = 0; i < candidatesModel->rowCount(); ++i) {
            if (candidatesModel->data(candidatesModel->index(i, columnIndex)).toString() == searchValue) {
                ui->tableView_2->showRow(i);
            } else {
                ui->tableView_2->hideRow(i);
            }
        }
    }
}

#include <QtNetwork>
#include <QFile>
void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    if (index.isValid()) {
        // Get the CIN value from the clicked row
        QString cinValue = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 0)).toString();

        // Get the Nom value from the clicked row (assuming Nom is in column 1)
        QString nomValue = ui->tableView_2->model()->data(ui->tableView_2->model()->index(index.row(), 1)).toString();

        // Concatenate CIN and Nom into a single string
        QString qrContent = "CIN: " + cinValue + "\nNom: " + nomValue;

        // Generate the QR code for the concatenated string
        QrCode qr = QrCode::encodeText(qrContent.toUtf8().data(), QrCode::Ecc::MEDIUM);

        // Create the QR code image
        int size = qr.getSize();
        QImage image(size, size, QImage::Format_RGB32);
        QRgb black = qRgb(0, 0, 0);
        QRgb white = qRgb(255, 255, 255);
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                image.setPixel(x, y, qr.getModule(x, y) ? black : white);
            }
        }

        // Display the QR code image in a QLabel
        ui->qrLabel->setPixmap(QPixmap::fromImage(image.scaled(100, 100, Qt::KeepAspectRatio, Qt::FastTransformation)));
    }
}

void MainWindow::on_rechf()
{
    QString selectedAttribute = ui->comboBox_2->currentText();
    int columnIndex = formationModel->fieldIndex(selectedAttribute);
    QString searchValue = QInputDialog::getText(this, "Search", "Enter the value to search for:");

    ui->tableView_3->clearSelection();

    if (searchValue.isEmpty()) {

        for (int i = 0; i < formationModel->rowCount(); ++i) {
            ui->tableView_3->showRow(i);
        }
    } else {

        for (int i = 0; i < formationModel->rowCount(); ++i) {
            if (formationModel->data(formationModel->index(i, columnIndex)).toString() == searchValue) {
                ui->tableView_3->showRow(i);
            } else {
                ui->tableView_3->hideRow(i);
            }
        }
    }
}




