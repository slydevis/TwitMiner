#include <QApplication>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include "dialog.cpp"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dia;
    dia.setFicAsso("ressources.txt");
    dia.setFicFreq("ressources.nette");
    dia.setFicTrad("ressources.trad");
    dia.createWindows();
    dia.show();
    return a.exec();
}
