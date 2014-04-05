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
    // On vérifie si on est bon si non on return ""

    QString tmp;
    for(int i = 0; i < str.size() - 1; ++i)
    {
        if(str.at(i + 1) == '(' || str.at(i) == '(') break;
        else {
            tmp.push_back(str.at(i));
        }
    }

    // On extract la fréquence
    if(tmp == item)
    {
        QString freq;
        for(int i = 0; i < str.size() - 1; ++i)
        {
            if(str.at(i) == '(')
            {
                for(int j = i+1; i < str.size() - 1; ++j)
                {
                    freq    .push_back(str.at(j));
                    if(str.at(j+1) == ')') break;
                }
                break;
            }
        }
        return freq;
    }
    else return "";
    return str;
}

QString getLift(QString Item, QString Conf)
{
    // On construit l'Item cherché
    QString ItemCherche;
    bool remplir = false;
    for(int i = 0; i < Item.size(); ++i)
    {
        if(Item.at(i) == ' ' && remplir == false)
        {
            remplir = true;
            i++;
        }
        if(remplir) ItemCherche.push_back(Item.at(i));
    }

    // On cherche la fréquence associé

    QString Freq;

    QFile isLift("ressources.nette");
    if(isLift.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream flux(&isLift);
        while(!flux.atEnd())
        {
            QString tmp = flux.readLine();
            Freq.push_back(getFreq(tmp, ItemCherche));
        }
        isLift.close();
    }
    QString Lift;
    float lifting;
    lifting = Freq.toFloat() * Conf.toFloat();
    Lift = QString::number(lifting, 'f', 6);
    return Lift;

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
    std::vector<QString> TabLift;
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
            {
                if(getFreq(tmp, TabItem.at(i)) != "")
                    TabFreq.push_back(getFreq(tmp, TabItem.at(i)));
            }
        }
    }
    else std::cout << "Y a une erreur à l'ouverture du fichier" << std::endl;

    for(unsigned i = 0; i < TabItem.size(); ++i)
    {
        TabLift.push_back(getLift(TabItem.at(i), TabConf.at(i)));
    }

    // Création de la fenetre

    QStandardItemModel *model = new QStandardItemModel(1,1,this);
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Confiance")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Item")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Fréquence")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Lift")));

    for(unsigned i = 0; i < TabConf.size(); ++i)
    {
        QString conf = TabConf.at(i);
        QStandardItem *firstRow = new QStandardItem(conf);
        model->setItem(i,0, firstRow);
    }

    for(unsigned i = 0; i < TabItem.size(); ++i)
    {
        QString item = TabItem.at(i);
        QStandardItem *secondRow = new QStandardItem(item);
        model->setItem(i,1, secondRow);
    }

    for(unsigned i = 0; i < TabFreq.size(); ++i)
    {
        QString freq = TabFreq.at(i);
        QStandardItem *thirdRow = new QStandardItem(freq);
        model->setItem(i,2, thirdRow);
    }

    for(unsigned i = 0; i < TabLift.size(); ++i)
    {
        QString lift = TabLift.at(i);
        QStandardItem *fourthRow = new QStandardItem(lift);
        model->setItem(i,3, fourthRow);
    }

    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,100);
}

Dialog::~Dialog()
{
    delete ui;
}
