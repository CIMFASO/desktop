#include "code128item.h"

#include <QPainter>
#include "code128.h"
#include <QSizeF>
#include <QDebug>
#include <QtPrintSupport/QPrinterInfo>


Code128Item::Code128Item() :
    m_TextVisible(true),
    m_Width(0),
    m_Height(0),
    m_CodeLength(0),
    m_HighDPI(true)
{

}

void Code128Item::setText(const QString &text,const QString &designation, const double &prix)
{
    m_Code = Code128::encode(text);
    m_Text = QString::number(prix) + " FCFA";
    m_Designation = designation;

    m_CodeLength = 0;
    for (int i=0;i<m_Code.length();i++)
    {
        m_CodeLength+=m_Code[i];
    }
}

void Code128Item::setWidth(float width)
{
    m_Width = width*8;
}

void Code128Item::setHeight(float height)
{
    m_Height = height*8;
}

void Code128Item::setTextVisible(bool visible)
{
    m_TextVisible = visible;
}

void Code128Item::setHighDPI(bool highDPI)
{
    m_HighDPI = highDPI;
}

void Code128Item::paint(int &copies)
{
    int pageCount = copies;
    QPainter *painter = new QPainter();
    painter->begin(&mPrinter);
    while(pageCount > 0){
        float lineWidth = m_Width / m_CodeLength;
        /*
         * This code tries to fit the barcode right inside the width. If the code
         * is too long this means that the bar width goes below one pixel. Which in
         * turn means we get no barcode. On printers this is not a problem too fast
         * as they have 600 DPI usually. Screens with 96 DPI run out faster.
         *
         */

        if ( !m_HighDPI )
        {
            lineWidth = qRound(lineWidth);
            if ( lineWidth < 1 )
            {
                lineWidth = 1;
            }
        }

        painter->setFont(QFont("Cambria",9));

        float fontHeight = painter->fontMetrics().height();

        float left = 0;

        QRectF box(0,0,m_Width, fontHeight);
        painter->drawText(box, m_Designation, Qt::AlignHCenter | Qt::AlignVCenter);


        for (int i=0;i<m_Code.length();i++)
        {
            float width = m_Code[i] * lineWidth;

            if ( i % 2 == 0 )
            {
                QRectF bar(left, fontHeight, width, m_Height - 2*fontHeight );
                painter->fillRect(bar, Qt::SolidPattern);
            }

            left+= width;
        }

        if ( m_TextVisible )
        {
            QRectF box(0, m_Height - fontHeight , left, fontHeight);
            painter->drawText(box, m_Text, Qt::AlignHCenter | Qt::AlignVCenter);
        }
        --pageCount;
        mPrinter.newPage();
    }
    painter->end();
}

void Code128Item::configurePage()
{
    mPrinter.setColorMode(QPrinter::GrayScale);
    mPrinter.setResolution(203);
    mPrinter.setPageMargins(5,5,5,5, QPrinter::Millimeter);
    mPrinter.setOrientation(QPrinter::Portrait);
}

bool Code128Item::configurePrinter(QString printerName)
{
    bool printerAvailable = getAvailablePrinters().contains(printerName);
    if(printerAvailable)
    {
        mPrinter.setPrinterName(printerName);
        configurePage();

    }
    else //If the printer is unavailable, generate pdf instead
    {
        mPrinter.setOutputFormat(QPrinter::PdfFormat);
        configurePage();
    }

    printerConfigured = true;

    return printerAvailable;
}

QStringList Code128Item::getAvailablePrinters()
{
    QStringList availablePrinters;

    QPrinterInfo pInfo;
    foreach (QPrinterInfo info, pInfo.availablePrinters()) {
        availablePrinters << info.printerName();
    }

    return availablePrinters;
}

