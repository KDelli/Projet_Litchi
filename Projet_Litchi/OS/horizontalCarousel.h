#ifndef HORIZONTALCAROUSEL_H
#define HORIZONTALCAROUSEL_H

#include "abstractCarousel.h"

class HorizontalCarousel : public AbstractCarousel//, public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

 public:
    HorizontalCarousel(const int duration, const double ellipseSemiMajorAxis = 550, const double ellipseSemiMinorAxis = 50, const int ellipseAngle = 1);
    virtual ~HorizontalCarousel();

 public slots:
    void doAnimation(const QVariant& angle);
};

#endif
