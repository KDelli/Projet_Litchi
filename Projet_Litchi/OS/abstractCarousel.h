#ifndef ABSTRACTCAROUSEL_H
#define ABSTRACTCAROUSEL_H

#include "variantAnimator.h"

#include <QGraphicsItem>
#include <QList>

class AbstractCarousel : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT

     public:
        void addToGroup(QGraphicsItem* item);
        void removeFromGroup (QGraphicsItem* item);
        void rescale(qreal sx, qreal sy);
        variantAnimator *mAngleAnimator;

     protected:
        double a; /*Ellipse semi-major axis*/
        double b; /*Ellipse semi-minor axis*/
        double phi; /*Ellipse angle*/

    QList <QGraphicsItem*> items; /*ChildItem() cannot be used because of dynamic graphicsitem Z value*/
};

#endif // ABSTRACTCAROUSEL_H
