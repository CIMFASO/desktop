#ifndef UIVILLE_H
#define UIVILLE_H

#include <QDialog>
#include "models/ville.h"
#include "utils/formsvalidator.h"

namespace Ui {
class UIVille;
}

class UIVille : public QDialog
{
    Q_OBJECT

public:
    explicit UIVille(QWidget *parent = nullptr);
    ~UIVille();

    const Model::Ville &getVille() const;
    void setVille(const Model::Ville &newVille);

    const QString &getMode() const;
    void setMode(const QString &newMode);

signals:
    void create(const Model::Ville &t);
    void update(const Model::Ville &t);

private slots:
    void on_validerButton_clicked();
    void on_annulerButton_clicked();

private:
    Ui::UIVille *ui;
    Model::Ville ville;
    QString mode;
};

#endif // UIVILLE_H
