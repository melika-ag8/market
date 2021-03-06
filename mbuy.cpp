#include "mbuy.h"
#include "ui_mbuy.h"
#include <mfbuy.h>
#include <memberr.h>

#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <QList>

mbuy::mbuy(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mbuy)
{
    ui->setupUi(this);
}

mbuy::~mbuy()
{
    delete ui;
}

class products
{
public:
    QStringList name ;
    QStringList group ;
    QStringList company ;
    QStringList supply ;
    QStringList price ;
};

void mbuy::on_buy_clicked()
{
    mfbuy * mfb = new mfbuy (this) ;
    mfb->show();
    hide();

    products products ;

    QFile file("products.txt");

    QTextStream s(&file);

    file.open( QFile::Text | QFile::ReadOnly );

    while (!s.atEnd())
    {
        QStringList a = s.readLine().split(' ');
        products.name.append(a[0]);
        products.group.append(a[1]);
        products.company.append(a[2]);
        products.supply.append(a[3]);
        products.price.append(a[4]);
    }

    file.close();

    for (int i = 0 ; i < products.name.size() ; i++ )
    {
        if ( this->ui->name->toPlainText() == products.name[i] )
        {
            QString s = QString::number( products.supply[i].toUInt() - this->ui->needline->text().toUInt());
            products.supply[i] = s ;
            break;
        }
    }

    file.open( QFile::Text | QFile::WriteOnly );

    for (int i = 0 ; i < products.name.size() ; i++ )
    {
        s << products.name[i] << " " << products.group[i] << " " << products.company[i] << " " << products.supply[i] << " " << products.price[i] << endl ;
    }
}

void mbuy::on_cancel_clicked()
{
    memberr * c = new memberr (this);
    c->show();
    hide();
}

void mbuy::on_calculate_clicked()
{
    QString p = QString::number( this->ui->needline->text().toUInt() * this->ui->price->toPlainText().toDouble() ) ;
    this->ui->totalpriceline->setText( p );
}

void mbuy::on_searchline_textChanged(const QString & m )
{int r = 0 ;

    products products ;

    QFile file("products.txt");

    QTextStream s(&file);

    file.open( QFile::Text | QFile::ReadOnly );

    while (!s.atEnd())
    {
        QStringList a = s.readLine().split(' ');
        products.name.append(a[0]);
        products.group.append(a[1]);
        products.company.append(a[2]);
        products.supply.append(a[3]);
        products.price.append(a[4]);
    }

    for (int i = 0 ; i < 20 ; ++i )
    {
        for (int i = 0 ; i < 20 ; ++i )
        {
            ui->show->removeRow(i);
        }
    }
    for (int i = 0 ; i <  products.name.size() ; i++ )
    {
        QString f = products.name[i] ;
        if ( f.contains( m ) )
        {
            this->ui->show->insertRow(r);
            QTableWidgetItem * group = new QTableWidgetItem ;
            QTableWidgetItem * name = new QTableWidgetItem ;
            QTableWidgetItem * supply = new QTableWidgetItem ;
            QTableWidgetItem * price = new QTableWidgetItem ;
            QTableWidgetItem * company = new QTableWidgetItem ;

            group->setText(products.group[i]);
            name->setText(products.name[i]);
            supply->setText(products.supply[i]);
            price->setText(products.price[i]);
            company->setText(products.company[i]);

            group->setTextAlignment(Qt::AlignCenter);
            name->setTextAlignment(Qt::AlignCenter);
            supply->setTextAlignment(Qt::AlignCenter);
            price->setTextAlignment(Qt::AlignCenter);
            company->setTextAlignment(Qt::AlignCenter);

            this->ui->show->setItem(r,0,name);
            this->ui->show->setItem(r,1,group);
            this->ui->show->setItem(r,2,company);
            this->ui->show->setItem(r,3,supply);
            this->ui->show->setItem(r,4,price);

            r++;
        }
    }
}

void mbuy::on_show_cellDoubleClicked(int row, int column)
{products products ;

    QFile file("products.txt");

    QTextStream s(&file);

    file.open( QFile::Text | QFile::ReadOnly );

    while (!s.atEnd())
    {
        QStringList a = s.readLine().split(' ');
        products.name.append(a[0]);
        products.group.append(a[1]);
        products.company.append(a[2]);
        products.supply.append(a[3]);
        products.price.append(a[4]);
    }

    QString t = this->ui->show->item(row,0)->text();
    int i = products.name.indexOf(t);

    this->ui->name->setText( products.name[i] );
    this->ui->group->setText( products.group[i] );
    this->ui->supply->setText( products.supply[i] );
    this->ui->price->setText( products.price[i] );
    this->ui->company->setText( products.company[i] );
}

void mbuy::on_YES_clicked()
{
    QString p = QString::number( (this->ui->needline->text().toUInt() * this->ui->price->toPlainText().toDouble()) + 5 ) ;
    this->ui->totalpriceline->setText( p );

    QFile file("productbuy.txt");
    QTextStream d(&file);

    file.open( QFile::Append | QFile::WriteOnly );
    d << this->ui->name->toPlainText() << " " << this->ui->price->toPlainText() << " "
      << this->ui->needline->text() << " " << " delivery yes" << " " << this->ui->totalpriceline->toPlainText() << endl;
}

void mbuy::on_no_clicked()
{
    QString p = QString::number( (this->ui->needline->text().toUInt() * this->ui->price->toPlainText().toDouble()) ) ;
    this->ui->totalpriceline->setText( p );

    QFile file("productbuy.txt");
    QTextStream d(&file);

    file.open( QFile::Append | QFile::WriteOnly );
    d << this->ui->name->toPlainText() << " " << this->ui->price->toPlainText() << " "
      << this->ui->needline->text() << " " << " delivery no" << " " << this->ui->totalpriceline->toPlainText() << endl;
}
