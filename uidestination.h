#ifndef UIDESTINATION_H
#define UIDESTINATION_H

#include <QDialog>
#include "models/destination.h"
#include "utils/formsvalidator.h"

namespace Ui {
class UIDestination;
}

class UIDestination : public QDialog
{
    Q_OBJECT

public:
    explicit UIDestination(QWidget *parent = nullptr);
    ~UIDestination();

    void setMode(const QString &value);
    void setDestination(const Model::Destination &value);

signals:
    void create(const Model::Destination &d);
    void update(const Model::Destination &d);

private slots:
    void on_validerButton_clicked();

private:
    Ui::UIDestination *ui;
    QString mode;
    Model::Destination destination;
};

#endif // UIDESTINATION_H
