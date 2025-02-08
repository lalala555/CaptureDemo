#include "settingdlg.h"
#include "ui_settingdlg.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QCheckBox>
#include <QListWidget>
#include <QListWidgetItem>

SettingDlg::SettingDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDlg)
    ,path("")
    ,OSDText("")
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    ui->stackedWidget->setCurrentIndex(0);
   // ui->OkBtn->setIcon(QIcon(":/prefix1/test.png"));
  //  ui->OkBtn->setStyleSheet("border-image:url(:/prefix1/test.png)");
    ui->radioButton_2->hide();
}

SettingDlg::~SettingDlg()
{
    delete ui;
}

void SettingDlg::setValue(QList<QString> m_cache)
{
    if(m_cache.size() < 1)
        return;
    path = m_cache.at(0);
    OSDText = m_cache.at(1);
    ui->lineEdit_3->setText(OSDText);
    int index = path.lastIndexOf("/");
    QString left = path.left(index);
    QString right = path.right(path.size() - index - 1);
    ui->lineEdit->setText(left);
    ui->lineEdit_2->setText(right);
}

void SettingDlg::on_OkBtn_clicked()
{
    if(ui->lineEdit->text() == ""|| ui->lineEdit_2->text() == "")
    {
        QMessageBox box;
        box.setText("Please enter the file save path and project save path in full. ");
        box.exec();
        return;
    }

  path = ui->lineEdit->text() +"/" + ui->lineEdit_2->text();
  OSDText = ui->lineEdit_3->text();
  QDialog::accept();
}

void SettingDlg::on_CloseBtn_clicked()
{
    QDialog::reject();
}

void SettingDlg::on_CloseBtn_2_clicked()
{
    close();
}

void SettingDlg::on_pushButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Save Path"), QDir::currentPath());
    if(!dir.isEmpty()){
        ui->lineEdit->setText(dir);
    }
}

void SettingDlg::on_pushButton_2_clicked()
{
//      QCheckBox * pBox = new QCheckBox("lalala");
//      QListWidgetItem * item = new QListWidgetItem();
//      pBox->set
////pBox->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
//    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
//               ui->listWidget->addItem(item);
//               ui->listWidget->setItemWidget(item, pBox);
    QListWidgetItem *pListItem = new QListWidgetItem("lalala");
        pListItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable);
    ui->listWidget->addItem(pListItem);
}

void SettingDlg::on_radioButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void SettingDlg::on_radioButton_2_clicked()
{
      ui->stackedWidget->setCurrentIndex(1);
}
