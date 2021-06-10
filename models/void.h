#ifndef VOID_H
#define VOID_H

#include <QUrlQuery>

namespace Model {
class Void
{
public:
    Void();

    QUrlQuery toUrlQuery() const;
};
}
#endif // VOID_H
