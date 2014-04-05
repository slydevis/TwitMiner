#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <string>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit Dialog(QWidget *parent = 0);
    QString getFicAsso(void) { return cheminFicAsso; }
    void setFicAsso(QString str) { cheminFicAsso = str; }
    QString getFicFreq(void) { return cheminFicFeq; }
    void setFicFreq(QString str) { cheminFicFeq = str; }
    QString getFicTrad(void) { return cheminFicTrad; }
    void setFicTrad(QString str) { cheminFicTrad = str; }
    void createWindows();
    ~Dialog();
    
private:
    Ui::Dialog *ui;

    QString cheminFicAsso;
    QString cheminFicFeq;
    QString cheminFicTrad;
};

#endif // DIALOG_H
