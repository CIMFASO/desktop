#ifndef IMAGE_H
#define IMAGE_H

#include "base.h"
#include "document.h"
#include "stackable.h"

namespace Qpd {
    class Document;
    class Stackable;

    class Image : public Stackable
    {
    public:
        Image();

        static constexpr int AlignCenter = Qt::AlignCenter;
        static constexpr int AlignLeft = Qt::AlignLeft;
        static constexpr int AlignRight = Qt::AlignRight;

        Image(Document *root, Position tpos, QImage const &image,int w = 0,int h = 0, Options opts = Options());

        void draw(bool last) override;

        void draw() override;

        void calcPosition(qreal width) override;

        void calcPosition() override;

        uint getImageOpts();

    private:
        int imgWidth = 0;
        int imgHeight = 0;
    };
}

#endif // IMAGE_H
