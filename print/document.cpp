#include "document.h"
#include "text.h"
#include "block.h"
#include "table.h"
#include <QSettings>
#include <QPrinterInfo>
#include <QThread>

using namespace Qpd;

Document::Document(QObject *parent) :
    QObject(parent),
    orientation(QPageLayout::Portrait)
{

}

Document::~Document() {
    for (Stackable *item : stack) {
        delete item;
    }

    delete painter;
    delete printer;
}

void Document::printStart(bool pdf, QString const &pdfFilename) {
    printer = new QPrinter();
    QSettings s;
    QString p = s.value("printer").toString();
    if(!p.isEmpty())
        printer->setPrinterName(p);

    setPageMargins(margins);
    printer->setPageOrientation(orientation);
    printer->setResolution(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A6);
    printer->setPaperSize(QPrinter::A6);

    emit printingStart();

    if (pdf) {
        printer->setOutputFormat(QPrinter::PdfFormat);
        printer->setOutputFileName(pdfFilename);
        printer->setFontEmbeddingEnabled(true);
    } else {
        QPrintDialog printDialog(printer);
        if(!p.isEmpty())
        {
            goto print;
        }
        else
        {
            if(printDialog.exec() == QDialog::Accepted)
            {
                goto print;
            }
        }

        //printer->setOutputFormat(QPrinter::NativeFormat);
    }

 print:
    if (!printer->isValid()) {
        qDebug() << "Printer is INVALID in printRun";
        return;
    }


    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.h = paintRect.height();
    size.w = paintRect.width();

    qDebug() << "set sizes for painting to: " << size.h << " x " << size.w;

    //preview = new QPrintPreviewDialog(printer);
    //connect(preview,&QPrintPreviewDialog::paintRequested,[this](QPrinter *printer){

        this->pages = 0;

        painter = new QPainter(printer);

        bool printStarted = painter->begin(printer);

        if (!printStarted) {
            qDebug() << "Painter is not ACTIVE, probably due to not valid printer";
            return;
        }

        QFont font(defaultFontFamily);
        font.setPixelSize(defaultFontPixelSize);
        painter->setFont(font);

        QPen pen;
        pen.setColor(QColor(0, 0, 0, 254));
        pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(Qt::FlatCap);
        pen.setJoinStyle(Qt::MiterJoin);
        pen.setWidth(1);
        pen.setCosmetic(true);

        painter->setBrush(Qt::NoBrush);
        painter->setPen(pen);

        painter->setRenderHints(
            QPainter::TextAntialiasing |
            QPainter::HighQualityAntialiasing,
            true
        );
        painter->setRenderHints(
            QPainter::Antialiasing | QPainter::SmoothPixmapTransform,
            false
        );

        position.x = position.y = 0;
    //});
    //preview->exec();
}

void Document::printEnd() {
    painter->end();
    emit printingEnd();
    pageCount = pages;
    pages = 1;
    deleteLater();
}

bool Document::switchOrientation(Orientation newOrientation) {
    if (newOrientation != Orientation::Landscape && newOrientation != Orientation::Portrait) {
        newOrientation = Orientation::Portrait;
    }

    QPageLayout::Orientation translate;
    if (newOrientation == Orientation::Portrait) {
        translate = QPageLayout::Portrait;
    } else {
        translate = QPageLayout::Landscape;
    }

    bool switchResult = printer->setPageOrientation(translate);
    if (switchResult) {
        this->newPage();

        QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
        size.w = paintRect.width();
        size.h = paintRect.height();
    }

    return switchResult;
}

bool Document::setPageMargins(QMarginsF margins) {
    bool setMargins = printer->setPageMargins(margins);

    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.w = paintRect.width();
    size.h = paintRect.height();

    return setMargins;
}

bool Document::setPageMargins(QMarginsF margins, QPageLayout::Unit unit) {
    bool setMargins = printer->setPageMargins(margins, unit);

    QRectF paintRect = printer->pageLayout().paintRectPixels(printer->resolution());
    size.w = paintRect.width();
    size.h = paintRect.height();

    return setMargins;
}

void Document::newPage() {
    printer->newPage();
    position.x = position.y = 0;
    pages++;
    emit newPageAdded();
}

void Document::font(QString const &fontName, int pixelSize, bool bold, bool italic) {
    if (pixelSize == 0) {
        pixelSize = defaultFontPixelSize;
    }

    QFont font(fontName);
    font.setPixelSize(pixelSize);
    font.setBold(bold);
    font.setItalic(italic);

    painter->setFont(font);
}

uint Document::getPageCount() const {
    return pages;
}

void Document::setPageSize(const QPageSize size)
{
    this->pageSize = size;
}

QMarginsF Document::getMargins() const
{
    return margins;
}

void Document::setMargins(const QMarginsF &value)
{
    margins = value;
}

QPageLayout::Orientation Document::getOrientation() const
{
    return orientation;
}

void Document::setOrientation(const QPageLayout::Orientation &value)
{
    orientation = value;
}

QPageSize Document::getPageSize() const
{
    return pageSize;
}
