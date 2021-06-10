#ifndef COMBOBOXMODEL_H
#define COMBOBOXMODEL_H

#include <QObject>

namespace Model {
    class ComboBoxModel
    {
    public:
        ComboBoxModel(){};
        virtual ~ComboBoxModel(){}

        virtual QString getLabel() const = 0;
        virtual int getId() const = 0;
    };
}
#endif // COMBOBOXMODEL_H
