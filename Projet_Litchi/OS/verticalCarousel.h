#ifndef VERTICALCAROUSEL_H
#define VERTICALCAROUSEL_H

#include "abstractCarousel.h"

class VerticalCarousel : public AbstractCarousel//, public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

 public:
    VerticalCarousel(int duration, double ellipseSemiMajorAxis = 550, double ellipseSemiMinorAxis = 50, int ellipseAngle = 0);
    virtual ~VerticalCarousel();

 public slots:
    void doAnimation(const QVariant& angle);
};

#endif
