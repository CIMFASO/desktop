#include "table.h"

using namespace Qpd;

uint Table::rowCount() {
    return uint(rows.count());
}

Table *Table::addRow(Block *row) {
    row->updateDelayedWidth();
    rows.append(row);
    return this;
}

void Table::draw() {
    if (rows.isEmpty()) return;

    uint tableBorder = 1;
    uint tablePadding = 5;

    Block *first = rows.first();
    first->options.setBorder(tableBorder);
    first->options.setPadding(tablePadding);

    auto fcells = first->getStack();
    for (auto cl : *fcells) {
        if (cl->options.header && cl->type == Type::BLOCK) {
            cl->options.setBorder(tableBorder);
            cl->options.setPadding(tablePadding);
        }
    }

    first->draw();

    for (Block *c : rows) {
        if (c == first) continue;

        c->options.setBorder(tableBorder);
        c->options.setPadding(tablePadding);

        int cells = c->getCellsCount();
        for (uint i = 0; i < cells; i++) {
            qreal ccellWidth = first->getCell(i)->getContentWidth();
            qreal zcellWidth = c->getCell(i)->getContentWidth();

            if (ccellWidth != zcellWidth) {
                if (c->getCell(i)->type == Type::TEXT) {
                    c->getCell(i)->setBoxWidth(ccellWidth);
                } else {
                    c->getCell(i)->setContentWidth(ccellWidth);
                }
            }

            if (c->getCell(i)->options.header && c->getCell(i)->type == Type::BLOCK) {
                c->getCell(i)->options.setBorder(tableBorder);
                c->getCell(i)->options.setPadding(tablePadding);
            }
        }

        c->calcPosition();
        c->draw();
    }

    first->root->position.y += bottomMargin;
}
