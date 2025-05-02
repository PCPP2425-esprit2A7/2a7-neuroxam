#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QSqlError>

namespace Ui {
class Dialog;  // Matches the UI form class
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
        int getLoggedInUserId() const { return userId; }

private slots:
   // Make sure the button's objectName is Login_2
    void onForgotPasswordClicked();
      void on_Login_clicked();

    void on_Login_2_clicked();

private:
    bool sendSMS(const QString &phoneNumber, const QString &message);

private:
    Ui::Dialog *ui;
    bool authenticated;
    int userId = -1;
};

#endif // LOGDIALOG_H
