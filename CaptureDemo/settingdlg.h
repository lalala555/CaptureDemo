#ifndef SETTINGDLG_H
#define SETTINGDLG_H

#include <QDialog>

namespace Ui {
class SettingDlg;
}

class SettingDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDlg(QWidget *parent = nullptr);
    ~SettingDlg();

    void setValue(QList<QString> m_cache);

private slots:
    void on_OkBtn_clicked();
    void on_CloseBtn_clicked();
    void on_CloseBtn_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();

private:
    Ui::SettingDlg *ui;
public:
    QString path;
    QString OSDText;
};

#endif // SETTINGDLG_H
