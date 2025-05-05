#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr); // Ensure constructor is correct
    ~Dialog();

private slots:
    void handleLogin();
    void onForgotPasswordClicked();
    void on_Login_2_clicked();

private:
    Ui::Dialog *ui;
    bool authenticated;
    bool sendSMS(const QString &phoneNumber, const QString &message);
};

#endif // LOGDIALOG_H
