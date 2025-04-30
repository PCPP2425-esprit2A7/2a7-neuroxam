#ifndef DIALOGID_H
#define DIALOGID_H

#include <QDialog>

namespace Ui {
class DialogID;
}

class DialogID : public QDialog
{
    Q_OBJECT

public:
    explicit DialogID(QWidget *parent = nullptr);
    ~DialogID();
    int getID() const;

private:
    Ui::DialogID *ui;
};

#endif // DIALOGID_H
