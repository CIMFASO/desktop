#include "documents.h"

#include <QMarginsF>
#include <QToolBar>
#include "utils/officineutils.h"
#include "utils/lettersconversionutils.h"
//#include "QZXing.h"
#include "utils.h"

using namespace Qpd;

Documents::Documents()
{

}

void Documents::footer(Document *doc, QString piedPage){

    QFont font = doc->painter->font();

    doc->font("Cambria",10,false,true);

    //int textWidth = doc->painter->fontMetrics().horizontalAdvance(*piedPage);

    doc->painter->drawText(doc->printer->pageRect().width()-75,doc->printer->pageRect().height()+10,
                           "Page : 1/"+QString::number(doc->pageCount));
    doc->painter->drawText(doc->getMargins().left(),doc->printer->pageRect().height()+10,
                           "CIMFASO");

    doc->painter->drawText(doc->printer->pageRect().width()/2-10/2,doc->printer->pageRect().height()+10,
                           piedPage);

    doc->font(font.family(),font.pixelSize());

    QObject::connect(doc,&Qpd::Document::newPageAdded,[=]{
        QFont font = doc->painter->font();
        /*doc->painter->drawLine(
               QPointF(doc->getMargins().left(),doc->printer->pageRect().height()-5),
               QPointF(doc->printer->pageRect().width(),doc->printer->pageRect().height()-5)
            );*/
        doc->font("Cambria",10,false,true);

        /*int textWidth = doc->painter->fontMetrics().horizontalAdvance(*piedPage);*/

        doc->painter->drawText(doc->printer->pageRect().width()-75,doc->printer->pageRect().height()+10,
                               "Page : "+ QString::number(doc->pages)+ "/"+QString::number(doc->pageCount));

        doc->painter->drawText(doc->getMargins().left(),doc->printer->pageRect().height()+10,
                               "CIMFASO");

        doc->painter->drawText(doc->printer->pageRect().width()/2-10/2,doc->printer->pageRect().height()+10,
                               piedPage);

        doc->font(font.family(),font.pixelSize());
    });
}

void Documents::test()
{
    int w,h;

    QPrinter printer(QPrinter::HighResolution);

    w = printer.pageRect().width();
    h = printer.pageRect().height();

    //printer.setOutputFormat(QPrinter::PdfFormat);
    QPrintPreviewDialog preview(&printer);
    preview.setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    QObject::connect(&preview,&QPrintPreviewDialog::paintRequested,[=](QPrinter *printer){

        QPainter painter(printer);
        /*if (! painter.begin(printer)) { // failed to open file
            qWarning("failed to open file, is it writable?");
            return ;
        }*/
        painter.drawText(QRectF(10,10,w-10,h-10),"Test",QTextOption(Qt::AlignCenter));
        if (! printer->newPage()) {
            qWarning("failed in flushing page to disk, disk full?");
            return ;
        }
        painter.drawText(QRectF(10,10,200,200),"Test 2 ",QTextOption(Qt::AlignCenter));
        painter.end();
    });
    preview.exec();
    //preview.showNormal();
}

void Documents::initPainter(Qpd::Document *doc,QPrinter *printer)
{
    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    doc->size.h = paintRect.height();
    doc->size.w = paintRect.width();
    //preview = new QPrintPreviewDialog(printer);
    //connect(preview,&QPrintPreviewDialog::paintRequested,[this](QPrinter *printer){

    doc->painter = new QPainter();

    doc->painter->begin(printer);

    QFont font(doc->defaultFontFamily);
    font.setPixelSize(doc->defaultFontPixelSize);
    doc->painter->setFont(font);

    QPen pen;
    pen.setColor(QColor(0, 0, 0, 254));
    pen.setStyle(Qt::SolidLine);
    pen.setCapStyle(Qt::FlatCap);
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setWidth(1);
    pen.setCosmetic(true);

    doc->painter->setBrush(Qt::NoBrush);
    doc->painter->setPen(pen);

    doc->painter->setRenderHints(
        QPainter::TextAntialiasing |
        QPainter::HighQualityAntialiasing,
        true
    );
    doc->painter->setRenderHints(
        QPainter::Antialiasing | QPainter::SmoothPixmapTransform,
        false
    );

    doc->position.x = doc->position.y = 0;
}

void Documents::autorisation(Model::Autorisation a)
{
    auto doc = new Qpd::Document();
    doc->printer = new QPrinter();
    doc->printer->setPageSize(QPageSize(QPageSize::A5));
    QPageLayout layout;
    layout.setUnits(QPageLayout::Millimeter);
    doc->printer->setPageLayout(layout);
    doc->setPageMargins(QMarginsF(20,20,20,20));

    QPrintPreviewDialog preview(doc->printer);
    preview.setWindowFlag(Qt::WindowType::WindowMinMaxButtonsHint);
    QObject::connect(&preview,&QPrintPreviewDialog::paintRequested,[=]{

        initPainter(doc,doc->printer);

        footer(doc);

        //doc->font("Cambria",16);

        //(new Block(doc))->addCell(new Text(doc,Position::CENTER,Officine::RaisonSociale()))->draw();

        (new Block(doc))->addCell(new Image(doc,Position::LEFT,QImage(":/images/logo-cimfaso.PNG"),500,100))->draw();
        /*Block *b2 = new Block(doc,Options().setHeader(true));
        doc->font("Cambria",25,true);
        b2->addCell(new Text(doc,Position::CENTER,"CIMFASO",Options().setFillWidth(true)));
        b2->draw();
        doc->font("Cambria",16);
        Block *b1 = new Block(doc,Options().setHeader(true));
        b1->addCell(new Text(doc,Position::CENTER,"Zone industrielle Kossodo - 10 PB 13140 Ouagadougou 10",Options().setFillWidth(true)));
        b1->addCell(new Text(doc,Position::CENTER,"Tél: (+226) 25 35 50 30 / 40 - BURKINA FASO",Options().setFillWidth(true)));
        b->addCell(b1);
        b->draw();*/

        ////////////
        doc->font("Cambria",18,true);
        (new Block(doc))->addCell(new Text(doc,Position::CENTER,"AUTORISATION DE CHARGEMENT N° "+a.getNumAutorisation(),Options().setMarginTop(80).setMarginBottom(60)))->draw();
        doc->font("Cambria",14,true);

        auto table = new Table(doc);

        doc->font("Cambria",15);

        Block *tableRow = new Block(doc);
        tableRow->addCell(new Text(doc,Position::LEFT,"DATE :"));
        tableRow->addCell(new Text(doc,Position::RIGHT,Utils::dateFormat(QDate::currentDate())));
        table->addRow(tableRow);

        Block *tableRow1 = new Block(doc);
        tableRow1->addCell(new Text(doc,Position::LEFT,"TRANSPORTEUR : "));
        tableRow1->addCell(new Text(doc,Position::RIGHT,a.getTransporteur().getNom()));
        table->addRow(tableRow1);

        Block *tableRow2 = new Block(doc);
        tableRow2->addCell(new Text(doc,Position::LEFT,"CONTACT TRANSP. :"));
        tableRow2->addCell(new Text(doc,Position::RIGHT,a.getTransporteur().getTelephone()));
        table->addRow(tableRow2);

        Block *tableRow3 = new Block(doc);
        tableRow3->addCell(new Text(doc,Position::LEFT,"PRODUIT : "));
        tableRow3->addCell(new Text(doc,Position::RIGHT,a.getProduit()));
        table->addRow(tableRow3);

        Block *tableRow4 = new Block(doc);
        tableRow4->addCell(new Text(doc,Position::LEFT,"CHAUFFEUR : "));
        tableRow4->addCell(new Text(doc,Position::RIGHT,a.getChauffeur()));
        table->addRow(tableRow4);

        Block *tableRow5 = new Block(doc);
        tableRow5->addCell(new Text(doc,Position::LEFT,"CONTACT CHAUFFEUR : "));
        tableRow5->addCell(new Text(doc,Position::RIGHT,a.getContactChauffeur()));
        table->addRow(tableRow5);

        Block *tableRow9 = new Block(doc);
        tableRow9->addCell(new Text(doc,Position::LEFT,"LIEU CHARGEMENT : "));
        tableRow9->addCell(new Text(doc,Position::RIGHT,a.getLieuChargement()));
        table->addRow(tableRow9);

        Block *tableRow6 = new Block(doc);
        tableRow6->addCell(new Text(doc,Position::LEFT,"DESTINATION : "));
        tableRow6->addCell(new Text(doc,Position::RIGHT,a.getDestination()));
        table->addRow(tableRow6);

        Block *tableRow7 = new Block(doc);
        tableRow7->addCell(new Text(doc,Position::LEFT,"N° CAMION : "));
        tableRow7->addCell(new Text(doc,Position::RIGHT,a.getCamion()));
        table->addRow(tableRow7);

        table->draw();

        (new Block(doc,Options().setMarginTop(100)))->addCell((new Block(doc,Align::EMPTY))->addCell(new Text(doc,Position::RIGHT,"Imprimé le : " + Utils::dateTimeFormat(QDateTime::currentDateTime()),Options().setMarginRight(100))))->draw();
        doc->printEnd();

    });

    preview.exec();
}

bool Documents::getShowPreview() const
{
    return showPreview;
}

void Documents::setShowPreview(bool value)
{
    showPreview = value;
}
