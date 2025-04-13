#ifndef EMAILDIALOG_H
#define EMAILDIALOG_H

#include <QDialog>

namespace Ui {
class EmailDialog;  // forward declaration
}

class EmailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EmailDialog(QWidget *parent = nullptr);
    ~EmailDialog();

private slots:
    void onEnvoyerClicked();

private:
    Ui::EmailDialog *ui;
    void envoyerEmail(QString email, QString sujet, QString message);
};

#endif // EMAILDIALOG_H
