#ifndef UITARIFLISTVIEW_H
#define UITARIFLISTVIEW_H

#include <QDialog>

namespace Ui {
class UITarifListView;
}

class UITarifListView : public QDialog
{
    Q_OBJECT

public:
    explicit UITarifListView(QWidget *parent = nullptr);
    ~UITarifListView();

private:
    Ui::UITarifListView *ui;
};

#endif // UITARIFLISTVIEW_H
