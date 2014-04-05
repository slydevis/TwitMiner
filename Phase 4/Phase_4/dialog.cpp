#include <QAbstractItemModel>
#include <QStandardItem>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "dialog.h"
#include "ui_dialog.h"

std::vector<std::string> Explode(std::string str, char delimiteur)
{
    std::vector<std::string> Tab;
    std::string buffer;
    for(int i = 0;str[i] != '\0'; ++i)
    {

        if(str[i] != delimiteur) buffer += str[i];
        if(str[i] == delimiteur || str[i+1] == '\0')
        {
            Tab.push_back(buffer);
            buffer = "";
        }
    }
    return Tab;
}

QString getConf(QString str)
{
    QString tmp;

    for(unsigned i = str.size() - 1; i > 0; --i)
    {
        if(str.at(i) != ' ')
            tmp.push_back(str.at(i));
        else break;
    }

    QString tmp2;

    for(int i = tmp.size(); i > 0; --i)
        tmp2.push_back(tmp.at(i - 1));

    return tmp2;
}

QString getItems(QString str)
{
    QString tmp;
    for(int i = 0; i < str.size(); ++i)
    {
        if(str.at(i + 2) != '-')
            tmp.push_back(str.at(i));
        else break;
    }
    return tmp;
}

QString getFreq(QString str, QString item)
{
    return str;
}

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

void Dialog::createWindows() {
    // Init all tab

    QFile isAsso(this->cheminFicAsso);
    std::vector<QString> TabConf;
    std::vector<QString> TabItem;
    if(isAsso.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&isAsso);
        while(!flux.atEnd())
        {
            QString tmp = flux.readLine();
            QString conf = getConf(tmp);
            QString items = getItems(tmp);
            TabConf.push_back(conf);
            TabItem.push_back(items);
        }
        isAsso.close();
    }
    else std::cout << "Y a une erreur à l'ouverture du fichier" << std::endl;

    QFile isFreq(cheminFicFeq);
    std::vector<QString> TabFreq;
    if(isFreq.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&isFreq);
        while(!flux.atEnd())
        {
            QString tmp = flux.readLine();
            for(unsigned i = 0; i < TabItem.size(); ++i)
                TabFreq.push_back(getFreq(tmp, TabItem.at(i)));
        }
    }
    else std::cout << "Y a une erreur à l'ouverture du fichier" << std::endl;

    // Création de la fenetre

    QStandardItemModel *model = new QStandardItemModel(1,1,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Confiance")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Item")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Fréquence")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lift")));
    QString conf = TabConf.at(0);
    QStandardItem *firstRow = new QStandardItem(conf);
    QString item = TabItem.at(0);
    QStandardItem *secondRow = new QStandardItem(item);
    QString freq = TabFreq.at(0);
    QStandardItem *thirdRow = new QStandardItem(freq);
    model->setItem(0,0, firstRow);
    model->setItem(0,1, secondRow);
    model->setItem(0,2, thirdRow);
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
}

Dialog::~Dialog()
{
    delete ui;
}
