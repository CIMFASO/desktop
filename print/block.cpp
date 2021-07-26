#include <cmath>
#include "block.h"

using namespace Qpd;

Block::Block(Document *root, Align talign, Options topts, QString const &objmark)
    : Stackable(root, talign, topts) {
    type = Type::BLOCK;
    if (!objmark.isEmpty()) {
        mark = objmark;
    }

    if (topts.width > 0) {
        setDelayedWidth(topts.width);
    } else {
        setBoundWidth(root->size.w);
    }

    this->currentPage = 0;

    setBoundHeight(topts.height > 0 ? topts.height : 0);
}

Block::Block(Document *root, Align talign, QDate date, Options topts)
    : Stackable(root, talign, topts) {
    type = Type::BLOCK;
    mark = "DATE OBJECT";

    options.setInlined();

    addCell(new Text(root, Position::INLINE, "\""))->
        addCell(new Text(root, Position::INLINE, date.toString("dd"), Options().setWidth(16).setUnderline()))->
        addCell(new Text(root, Position::INLINE, "\" "))->
        addCell(new Text(root, Position::CENTER, date.toString("MMMM"),
                         Options().setWidth(60).setUnderline().setInlined()))->
        addCell(new Text(root, Position::INLINE, " 20"))->
        addCell(new Text(root, Position::INLINE, date.toString("yy"), Options().setWidth(16).setUnderline()))->
        addCell(new Text(root, Position::INLINE, " г."));

    if (topts.width > 0) {
        setBoxWidth(topts.width);
    } else {
        setBoundWidth(root->size.w);
    }

    setBoundHeight(topts.height > 0 ? topts.height : 0);
}

Block::Block(Document *root, Align talign, Options topts, Text *text)
    : Stackable(root, talign, topts) {
    type = Type::BLOCK;
    addCell(text);
}

Block::Block(Document *root, QPointF start, Align talign, Options topts, Text *text)
    : Stackable(root, start,talign, topts)
{
    type = Type::BLOCK;
    addCell(text);
}

Block *Block::addCell(Stackable *stack, uint width) {
    return this->addCell(stack, Position::EMPTY, Align::EMPTY, width);
}

Block *Block::addCell(Stackable *stack, Position tpos) {
    return this->addCell(stack, tpos, Align::EMPTY, 0);
}

Block *Block::addCell(Stackable *stack, Align talign) {
    return this->addCell(stack, Position::EMPTY, talign, 0);
}

Block *Block::addCell(Stackable *stack, Position tpos, Align talign, uint width) {
    stack->setBlindMode(true);
    if (tpos != Position::EMPTY)
        stack->position = tpos;

    if (talign != Align::EMPTY) {
        stack->align = talign;
    }

    if (width > 0) {
        stack->resetDelayedWidth();
        stack->setBoxWidth(width);
    } else {
        stack->updateDelayedWidth();
    }

    cells.append(stack);
    calcDone = false;

    return this;
}

Block *Block::prependCell(Stackable *stack, uint width) {
    return this->prependCell(stack, Position::EMPTY, Align::EMPTY, width);
}

Block *Block::prependCell(Stackable *stack, Position tpos) {
    return this->prependCell(stack, tpos, Align::EMPTY, 0);
}

Block *Block::prependCell(Stackable *stack, Align talign) {
    return this->prependCell(stack, Position::EMPTY, talign, 0);
}

Block *Block::prependCell(Stackable *stack, Position tpos, Align talign, uint width) {
    stack->setBlindMode(true);
    if (tpos != Position::EMPTY) stack->position = tpos;
    if (talign != Align::EMPTY) {
        stack->align = talign;
    }

    if (width > 0) {
        stack->setBoxWidth(width);
    }

    cells.prepend(stack);
    calcDone = false;

    return this;
}

Block *Block::addStubCell(uint width) {
    Block *stubCell = new Block(root);

    if (width > 0) {
        stubCell->setBoxWidth(width);
    }

    cells.append(stubCell);

    return this;
}

int Block::getCellsCount() {
    return cells.count();
}

Stackable *Block::getCell(uint idx) {
    return cells.at(idx);
}

void Block::replaceCell(uint idx, Stackable *item, bool recalc) {
    Stackable *oldItem = cells.at(idx);

    item->pos.x = oldItem->pos.x;
    item->pos.y = oldItem->pos.y;
    item->position = oldItem->position;
    item->align = oldItem->align;
    item->options = oldItem->options;

    item->setContentWidth(oldItem->getContentWidth());
    item->setContentHeight(oldItem->getContentHeight());
    item->setBoundWidth(oldItem->getBoundWidth());
    item->setBoundHeight(oldItem->getBoundHeight());

    item->calcPosition();

    cells.replace(idx, item);
    if (recalc) {
        calcDone = false;
    }

    root->stack.removeAll(oldItem);
    delete oldItem;
}

void Block::draw() {
    draw(false);
}

void Block::draw(bool last) {
    Q_UNUSED(last);
    int cellCount = cells.count();
    if (cellCount == 0) return;

    if (!calcDone) {
        calcPosition();
    }

    if (!this->fitH()) {
        this->newPage();
    }

    pos.y += options.margins.top;
    pos.x += options.margins.left;

    if (options.border.top > 0) {
        QPen origPen = root->painter->pen();
        QPen copyPen = origPen;
        copyPen.setWidth(options.border.top);
        copyPen.setColor(options.border.color);

        qreal correction = qreal(options.border.top - 1) / 2;

        root->painter->setPen(copyPen);
        root->painter->drawLine(
            QPointF(pos.x, pos.y + correction),
            QPointF(pos.x + getBoxWidth(), pos.y + correction)
        );
        root->painter->setPen(origPen);
    }
    if (options.border.left > 0) {
        QPen origPen = root->painter->pen();
        QPen copyPen = origPen;
        copyPen.setWidth(options.border.left);
        copyPen.setColor(options.border.color);

        qreal correction = qreal(options.border.left - 1) / 2;

        root->painter->setPen(copyPen);
        root->painter->drawLine(
            QPointF(pos.x + correction, pos.y),
            QPointF(pos.x + correction, pos.y + getBoxHeight())
        );
        root->painter->setPen(origPen);
    }
    if (options.border.right > 0) {
        QPen origPen = root->painter->pen();
        QPen copyPen = origPen;
        copyPen.setWidth(options.border.right);
        copyPen.setColor(options.border.color);

        qreal correction = qreal(options.border.right - 1) / 2;

        root->painter->setPen(copyPen);
        root->painter->drawLine(
            QPointF(pos.x + getBoxWidth() - correction, pos.y),
            QPointF(pos.x + getBoxWidth() - correction, pos.y + getBoxHeight())
        );
        root->painter->setPen(origPen);
    }
    if (options.border.bottom > 0) {
        QPen origPen = root->painter->pen();
        QPen copyPen = origPen;
        copyPen.setWidth(options.border.bottom);
        copyPen.setColor(options.border.color);

        qreal correction = qreal(options.border.top - 1) / 2;

        root->painter->setPen(copyPen);
        root->painter->drawLine(
            QPointF(pos.x, pos.y + getBoxHeight() - correction),
            QPointF(pos.x + getBoxWidth(), pos.y + getBoxHeight() - correction)
        );
        root->painter->setPen(origPen);
    }

    qreal startY = pos.y;
    qreal startH = getBoxHeight();

    Stackable *cellLast = cells.last();

    pos.y += options.border.top + options.padding.top;
    pos.x += options.border.left + options.padding.left;

    qreal startX = pos.x;
    qreal posX = pos.x;

    auto rows = rowCount();

    for (Stackable *c : cells) {

        if (rows == 1 && !c->options.inlined &&
            (c->options.header ? c->getHeight() < getBoxHeight() : c->getHeight() < getContentHeight())) {

            if (c->options.header) {
                c->setBoxHeight(getBoxHeight());
            } else {
                c->setBoxHeight(getContentHeight());
            }
        }
        qreal x = 0;
        qreal y = pos.y;

        qreal cellContentW = c->getContentWidth();
        qreal cellBoxW = c->getBoxWidth();
        qreal childsW = c->getChildsWidth();

        if (c->options.inlined && c->getBoundWidth() > 0) {
            cellBoxW = c->getBoundWidth();
        }

        if (c->options.row) {
            if (options.border.bottom > 0) {

                cellContentW = c->getContentWidth();
                cellBoxW = c->getBoxWidth();

                qreal correction = (options.border.bottom - 1) / 2;
                if (correction == 0) correction = 0.5;

                qreal loffst = options.padding.left + correction;
                qreal roffst = options.padding.right + correction;

                QPen origPen = root->painter->pen();
                QPen copyPen = origPen;
                copyPen.setWidth(options.border.bottom);
                copyPen.setColor(options.border.color);

                root->painter->setPen(copyPen);
                root->painter->drawLine(
                    QPointF(posX - loffst, pos.y + c->getHeight() + options.padding.bottom + correction),
                    QPointF(posX + c->getBoxWidth() + roffst,
                            pos.y + c->getHeight() + options.padding.bottom + correction)
                );
                root->painter->setPen(origPen);
            }
        } else if (!c->options.header) {
            if (c->align == Align::LEFT) {
                x = 0;
            } else if (c->align == Align::RIGHT) {
                if (c->type == Type::BLOCK) {
                    x = (cellContentW - childsW);
                } else {
                    x = (cellBoxW - cellContentW);
                }

            } else if (c->align == Align::CENTER) {
                if (c->type == Type::BLOCK) {
                    x = ((cellContentW / 2) - (childsW / 2)) - c->pos.x;
                } else {
                    x = ((cellBoxW / 2) - (cellContentW / 2)) - c->pos.x;
                }
            } else {
                x = c->pos.x;
            }
        }


        if (c->options.header) {
            y -= options.border.top + options.padding.top;
            x -= options.border.left + options.padding.left;
        }

        c->pos.x = posX + x;
        c->pos.y = y;

        c->draw();

        if (c->options.header) {
            if (c->type == Type::BLOCK) {
                posX += c->getWidth() - options.padding.right - options.border.right;
            } else {
                posX += c->getWidth() + options.padding.right;
            }
        } else {
            posX += c->getWidth() + options.padding.right;
        }

        uint borderHorizontalBiggest = qMax(options.border.right, options.border.left);
        if (c != cellLast && !c->options.row) {
            if (borderHorizontalBiggest > 0) {
                QPen origPen = root->painter->pen();
                QPen copyPen = origPen;
                copyPen.setWidth(borderHorizontalBiggest);
                copyPen.setColor(options.border.color);

                qreal correction = (borderHorizontalBiggest - 1) / 2;

                root->painter->setPen(copyPen);
                root->painter->drawLine(
                    QPointF(posX + correction, startY),
                    QPointF(posX + correction, startY + (!options.header ? startH : startH - 1))
                );
                root->painter->setPen(origPen);
            }
        }

        posX += borderHorizontalBiggest + options.padding.left;

        if (c->options.row) {
            startH -= c->getHeight() + options.padding.top + options.padding.bottom +
                      qMax(options.border.top, options.border.bottom);
            pos.y += c->getHeight() + options.padding.bottom + qMax(options.border.top, options.border.bottom) +
                     options.padding.top;
            startY = pos.y - options.border.top - options.padding.top;

            posX = startX;
        }
    }

    if (!blindMode) {
        root->position.y += getBoxHeight() + options.margins.bottom;
        root->position.x = 0;
    }
}

void Block::calcPosition() {
    calcPosition(0);
}

void Block::calcPosition(qreal width) {
    if (width > 0) {
        setBoundWidth(width);
    }

    int cellCount = cells.count();
    if (cellCount == 0) {
        calcDone = true;
        return;
    }

    if (!customWidth && !options.fluid) {
        setBoxWidth(getBoundWidth());
    }

    setContentHeight(0);
    if (options.fluid) {
        setContentWidth(0);
    }
    setChildsHeight(0);
    setChildsWidth(0);

    uint workingCells = 0;
    qreal fixedWidth = 0;

    for (Stackable *c : cells) {
        if (c->customWidth) {
            fixedWidth += c->getWidth();
        } else if (!c->options.row) {
            workingCells++;
        }
    }

    qreal extendedHeight = 0;

    uint passedCells = 0;
    for (Stackable *c : cells) {
        bool consumeChildWidth = false;
        if (c->options.row) {
            c->setBoxWidth(
                getBoundWidth()
                + (getPaddingsHorizontal() - options.padding.left - options.padding.right)
                + (getBordersHorizontal() - options.border.left - options.border.right)
            );

            c->calcPosition();

            extendedHeight += c->getHeight();

            if (cells.size() == 1 && options.fluid) {
                setContentWidth(c->getWidth());
            }

            continue;
        } else if (!c->customWidth) {
            qreal workingWidth = 0;
            if (customWidth) {
                workingWidth = getBoundWidth() - fixedWidth;
            } else {
                workingWidth = getBoundWidth() - getPaddingsHorizontal() - getBordersHorizontal() - fixedWidth;
            }

            qreal freeCellWidth = workingWidth / workingCells;

            workingCells--;

            if (c->options.inlined) {
                c->setBoundWidth(freeCellWidth);
            } else {
                c->setBoxWidth(freeCellWidth);
            }

            consumeChildWidth = true;
        }

        qreal accountingWidth = 0;
        qreal accountingHeight = 0;

        if (c->options.header) {
            accountingWidth = c->getWidth();
            c->setContentHeight(
                c->getContentHeight() + options.border.top + options.border.bottom + options.padding.top +
                options.padding.bottom);
            c->setContentWidth(
                c->getContentWidth() + options.border.left + options.border.right + options.padding.left +
                options.padding.right);
            c->setBoundWidth(c->getContentWidth());
        }

        c->calcPosition();

        if (!c->options.header) {
            accountingWidth = c->getWidth();
            accountingHeight = c->getHeight();
        } else {
            accountingHeight = c->getHeight() - getPaddingsVertical() - getBordersVertical();
        }

        setChildsWidth(getChildsWidth() + accountingWidth);

        if (options.fluid) {
            setContentWidth(getContentWidth() + accountingWidth);
        }
        if (consumeChildWidth) {
            fixedWidth += accountingWidth;
        }

        qreal h = accountingHeight;
        if (h > getContentHeight()) {

            setContentHeight(h);
            setChildsHeight(h);
        }

        passedCells++;
    }

    if (extendedHeight > 0) {
        setContentHeight(getContentHeight() + extendedHeight);
    }

    pos.x = 0;
    pos.y = root->position.y;

    calcDone = true;
}
