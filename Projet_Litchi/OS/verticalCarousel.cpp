#include "verticalCarousel.h"

#include <list>

const double pi = 3.14159265;

VerticalCarousel::VerticalCarousel(const int duration, const double ellipseSemiMajorAxis, const double ellipseSemiMinorAxis, const int ellipseAngle)
{
    mAngleAnimator = new variantAnimator;

    mAngleAnimator->setEasingCurve(QEasingCurve::Linear); /*Change Linear and get some change's effects*/
    connect(mAngleAnimator, SIGNAL(valueChanged(const QVariant&)), SLOT(doAnimation(const QVariant&)));

    mAngleAnimator->setStartValue(150);
    mAngleAnimator->setEndValue(155);
    mAngleAnimator->setDuration(1);
    mAngleAnimator->start();
    mAngleAnimator->setDuration(duration);

    a = ellipseSemiMajorAxis;
    b = ellipseSemiMinorAxis;
    phi = ellipseAngle;
}

void VerticalCarousel::doAnimation(const QVariant& angle)
{
    if (!scene())
        return;

    const int steps = items.count();
    qreal step = angle.toFloat();

    foreach(QGraphicsItem* i, items)
    {
        step += 360/steps;

        const double alpha = step * (pi/180.0); /*Converts degree  into radians*/
        const double beta = phi * (pi/180.0);

        double x = (a * cos(alpha) * cos(beta)) - (b * sin(alpha) * sin(beta)); /*reverse both sign will change the rotation way*/
        double y = (a * cos(alpha) * sin(beta)) + (b * sin(alpha) * cos(beta));

        /* Scaling and Fading */
        {
            /*Setting paramenters*/
            const qreal range = b;     /* y range [-b,b]    -> total size*/
            const qreal max = 3.4;     /* bigger value at b -> max size on foregrond*/
            const qreal min = 0.4;     /* lower value at -b -> minimal size on backgroud*/

            /*Linear equation: y = mx +c*/

            qreal adjustedY = 0.5*y - 0.1*b; /*0.5*y - 0.1*b*/
            qreal scaleFactor = ((max - min)/range)* adjustedY + min;

            i->setScale(scaleFactor);
            i->setOpacity(qBound(0.0, scaleFactor, 1.0));
        }

        /* Stack position */
        {
            /*Setting paramenters*/
            const qreal range = 2 * b; /* y range [-b,b]*/
            const qreal max = 1.0;     /* bigger value at b*/
            const qreal min = 0.0;     /*lower value at -b*/

            /*Linear equation: y = mx +c*/
            qreal adjustedY = y + b;
            qreal z = ((max - min)/range)* adjustedY + min;

            i->setZValue(z);
        }

        /* Moving items using the item's center as origin */
        {
            x += i->sceneBoundingRect().width() / -2;
            y += i->sceneBoundingRect().height() / 1;

            i->setPos(y, x);

            /*Bounding rectangle is in item coordinates, so it is not affected by transformations such as scale*/
        }
    }
}

VerticalCarousel::~VerticalCarousel()
{
    int i;
    for(i = 0; i < items.count(); i++)
    {
        QGraphicsItem* item = items.at(i);
        delete item;
    }
    delete mAngleAnimator;;
}
