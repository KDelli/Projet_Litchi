#ifndef HORIZONTALCAROUSEL_H
#define HORIZONTALCAROUSEL_H

#include "abstractCarousel.h"

class HorizontalCarousel : public AbstractCarousel//, public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

 public:
    HorizontalCarousel(int duration, double ellipseSemiMajorAxis = 550, double ellipseSemiMinorAxis = 50, int ellipseAngle = 1);
    virtual ~HorizontalCarousel();

 public slots:
    void doAnimation(const QVariant& angle);
};

#endif
