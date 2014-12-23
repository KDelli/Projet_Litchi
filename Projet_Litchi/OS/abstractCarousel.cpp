#include "abstractCarousel.h"

void AbstractCarousel::addToGroup(QGraphicsItem *item)
{
    items << item;
    QGraphicsItemGroup::addToGroup(item);
}


void AbstractCarousel::removeFromGroup(QGraphicsItem *item)
{
    items.removeAll(item);
    QGraphicsItemGroup::removeFromGroup(item);
}

void AbstractCarousel::rescale(qreal sx, qreal sy)
{
    this->setTransform(QTransform().translate(0, 0).scale(sx, sy).translate(0, 0));

    /*a = a*sy;
    b = b*sy;
    phi = phi*sy;

    QVariant startValue = mAngleAnimator->startValue();
    QVariant endValue = mAngleAnimator->endValue();

    mAngleAnimator->setStartValue(endValue);
    mAngleAnimator->start();
    mAngleAnimator->setStartValue(startValue);*/
}
