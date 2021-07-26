#ifndef DOCUMENTS_H
#define DOCUMENTS_H

#include <QObject>
#include <QStandardItemModel>
#include <QTableView>
#include "print/document.h"
#include "print/text.h"
#include "print/table.h"
#include "print/block.h"
#include "print/image.h"
#include "utils/prixformat.h"
#include <QPrintPreviewWidget>
#include <QMap>
#include <QMapIterator>
#include "models/autorisation.h"

class Documents
{
public:
    Documents();
    void test();
    void initPainter(Qpd::Document *doc, QPrinter *printer);
    void autorisation(Model::Autorisation a);
    bool getShowPreview() const;
    void setShowPreview(bool value);
    void footer(Qpd::Document *doc, QString piedPage="");
private:
    bool showPreview = true;
};

#endif // DOCUMENTS_H
