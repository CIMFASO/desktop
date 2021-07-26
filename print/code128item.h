#ifndef CODE128ITEM_H
#define CODE128ITEM_H

#include "code128.h"
#include <QPrinter>

class Code128Item
{
    bool m_TextVisible;
    float m_Width;
    float m_Height;
    QString m_Text;
    QString m_Designation;
    Code128::BarCode m_Code;
    int m_CodeLength;
    bool m_HighDPI;
    QPrinter mPrinter;

public:
    Code128Item();
    void setText(const QString & text, const QString &designation, const double &prix =0);
    void setWidth( float width );
    void setHeight( float height );
    void setTextVisible( bool visible );
    void setHighDPI(bool highDPI);
    void paint(int &copies);
    void configurePage();
    bool printerConfigured;
    bool configurePrinter(QString printerName = QString());
    QStringList getAvailablePrinters();



};
#endif // CODE128ITEM_H
