#ifndef LOGDIALOG_H
#define LOGDIALOG_H

#include <QDialog>
#include <QSqlError>

namespace Ui {
class logdialog;  // Matches the UI form class
}

class logdialog : public QDialog
{
    Q_OBJECT

public:
    explicit logdialog(QWidget *parent = nullptr);
    ~logdialog();
    int getLoggedInUserId() const { return userId; }

private slots:
    void on_Login_clicked();

    void on_Login_2_clicked();

    void on_forgotPasswordBtn_clicked();

private:
    bool sendSMS(const QString &phoneNumber, const QString &message);

private:
    Ui::logdialog *ui;
    bool authenticated;
    int userId = -1;
};

#endif // LOGDIALOG_H
