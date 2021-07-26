#include "image.h"

using namespace Qpd;


Image::Image(Document *root, Position tpos, QImage const &image, int w, int h, Options opts) :
    Stackable(root,image,tpos, opts) {
    type = Type::TEXT;
    imgWidth  = w;
    imgHeight = h;
    options.setBorder(0);
    options.setPadding(0);

    if (opts.width > 0) {
        customWidth = true;
    }

    setBoundWidth(opts.width);
    setBoundHeight(opts.height);
}

void Image::draw() {
    draw(false);
}

void Image::draw(bool last) {
    if (!calcDone) {
        calcPosition();
    }
    if (!blindMode && !fitH()) {
        newPage();
    }

    pos.y += options.margins.top;
    pos.x += options.margins.left;
    root->painter->setPen(options.textColor.color);

    QFont origFont;
    QFont copyFont;
    if (options.underline > 0) {
        origFont = root->painter->font();
        copyFont = origFont;
        copyFont.setUnderline(true);
        root->painter->setFont(copyFont);
    }

    (imgWidth == 0 && imgHeight == 0) ? root->painter->drawImage(QPoint(int(pos.x),int(pos.y)),image) :
                root->painter->drawImage(QRect(int(pos.x),int(pos.y),imgWidth,imgHeight),image);

    if (options.underline > 0) {
        root->painter->setFont(origFont);
    }

    if (options.boundline > 0) {
        root->painter->drawLine(
            QPointF(pos.x, pos.y + textRect.height()),
            QPointF(pos.x + getContentWidth(), pos.y + textRect.height())
        );
    }

    if (!blindMode) {
        if (!options.inlined || !this->fitW() || last) {
            root->position.y += getHeight();
        }
        if (options.inlined) {
            root->position.x += getWidth();
        }
    }
    qDebug() << "Drawed text at " << pos.x << ":" << pos.y << " with size ch: "
             << getContentHeight() << "cw: " << getContentWidth() << "bh" << getBoxHeight() << "bw" << getBoxWidth() <<
             "rh" << textRect.height() << "rw" << textRect.width() << "bnh" << getBoundHeight()
             << "bnw" << getBoundWidth() << "customW" << customWidth << "txt:" << textData;
}

void Image::calcPosition() {
    calcPosition(0);
}

void Image::calcPosition(qreal width) {
    if (width > 0) {
        customWidth = true;
        setBoundWidth(qMin(root->size.w, width));
    }

    textRect = root->painter->boundingRect(
        0,
        int(root->position.y),
        int(getBoundWidth()),
        0,
        getImageOpts(),
        textData
    );

    if (!customWidth && options.inlined) {
        setContentWidth(textRect.width());
    } else {
        setContentWidth(getBoundWidth());
    }

    setContentHeight(textRect.height());

    qDebug() << "-- Calc TEXT will consume w: " << textRect.width() << " against cw: " << getContentWidth() << ", bw: "
             << getBoxWidth() << " and bndW: " << getBoundWidth() << " %@ " << textData << " customW: " << customWidth
             << " inlined: " << options.inlined;
    qDebug() << "-- Calc TEXT will consume h: " << textRect.height() << " against ch: " << getContentHeight()
             << " bh: " << getBoxHeight()
             << " bndH: " << getBoundHeight()
             << " TH: " << getHeight()
             << " margL: " << options.margins.left
             << " margR: " << options.margins.right
             << " margT: " << options.margins.top
             << " margB: " << options.margins.bottom;

    if (options.underline) {
        setContentHeight(getContentHeight() + 1);
    }
    if (options.boundline) {
        setContentHeight(getContentHeight() + 1);
    }

    qreal x = 0;
    qreal y = 0;

    if (position == Position::LEFT) {
        x = 0;
    } else if (position == Position::RIGHT) {
        x = getBoxWidth() - getContentWidth();
    } else if (position == Position::CENTER) {
        x = (getBoxWidth() / 2) - (getContentWidth() / 2);
    } else {
        x = root->position.x;
    }

    pos.x = x;
    pos.y = root->position.y + y;

    calcDone = true;
}

uint Image::getImageOpts() {

    int imgOpts = Qt::AlignLeft;

    if (position == Position::LEFT) {
        imgOpts |= Qt::AlignLeft;
    } else if (position == Position::RIGHT) {
        imgOpts |= Qt::AlignRight;
    } else if (position == Position::CENTER) {
        imgOpts |= Qt::AlignCenter;
    }

    return (uint) imgOpts;
}
