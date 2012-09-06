#include "Bitmap2DView.h"
#include "Bitmap2D.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QKeyEvent>

#include <QDebug>


static QPoint roundToZero(QPointF posF)
{
    return QPoint(posF.x(), posF.y());
}


struct Bitmap2DViewPrivate
{
    Bitmap2D *bitmap;
    int zoom;

    QPoint mouseOrigin;
    QPoint offset;
    QColor color;
};


Bitmap2DView::Bitmap2DView(QWidget *parent)
    : QWidget(parent)
    , d_ptr(new Bitmap2DViewPrivate)
{
    Q_D(Bitmap2DView);
    d->bitmap = NULL;
    d->zoom = 10;
    d->color = Qt::white;

    connect(this, SIGNAL(changed()), SLOT(repaint()));
}

Bitmap2DView::~Bitmap2DView()
{
    delete d_ptr;
}


void Bitmap2DView::setBitmap(Bitmap2D &bitmap)
{
    Q_D(Bitmap2DView);

    d->bitmap = &bitmap;
    emit changed();
}


QColor Bitmap2DView::color() const
{
    Q_D(const Bitmap2DView);
    return d->color;
}


void Bitmap2DView::setColor(QColor color)
{
    Q_D(Bitmap2DView);
    d->color = color;
}


void Bitmap2DView::paintEvent(QPaintEvent *event)
{
    Q_D(Bitmap2DView);
    Q_UNUSED(event);

    if (d->bitmap == NULL)
        return;

    QPainter painter;
    painter.begin(this);

//    painter.fillRect(event->rect(), Qt::white);

    painter.translate(d->offset);

    drawBitmap(painter);
    drawGrid(painter);

    painter.end();
}

void Bitmap2DView::drawBitmap(QPainter &painter)
{
    Q_D(Bitmap2DView);
    Q_ASSERT(d->bitmap != NULL);

    QSize const canvasSize = d->bitmap->canvasSize();

    for (int y = 0; y < canvasSize.height(); y++)
        for (int x = 0; x < canvasSize.width(); x++)
        {
            QRect rect(x * d->zoom, y * d->zoom, d->zoom, d->zoom);
            painter.fillRect(rect, d->bitmap->pixel(QPoint(x, y)));
        }
}

void Bitmap2DView::drawGrid(QPainter &painter)
{
    Q_D(Bitmap2DView);
    Q_ASSERT(d->bitmap != NULL);

    QSize const canvasSize = d->bitmap->canvasSize();
    painter.drawRect(QRect(QPoint(0, 0), canvasSize * d->zoom));
    if (d->zoom >= 5)
    {
        for (int i = 0; i < canvasSize.width(); i++)
            painter.drawLine(i * d->zoom, 0,
                             i * d->zoom, canvasSize.height() * d->zoom);

        for (int i = 0; i < canvasSize.height(); i++)
            painter.drawLine(0, i * d->zoom,
                             canvasSize.width() * d->zoom, i * d->zoom);
    }
}


void Bitmap2DView::mousePressEvent(QMouseEvent *event)
{
    Q_D(Bitmap2DView);

    if (d->bitmap == NULL)
        return;

    setFocus();

    if (event->buttons().testFlag(Qt::MiddleButton))
    {
        d->mouseOrigin = event->pos();
    }
    else if (event->buttons().testFlag(Qt::LeftButton))
    {
        QPoint pixel = roundToZero((event->posF() - d->offset) / d->zoom);
        if (!d->bitmap->contains(pixel))
            return;
        d->bitmap->setPixel(pixel, d->color);

        emit changed();
    }
    else if (event->buttons().testFlag(Qt::RightButton))
    {
        QPoint pixel = roundToZero((event->posF() - d->offset) / d->zoom);
        if (!d->bitmap->contains(pixel))
            return;
        d->bitmap->setPixel(pixel, Qt::transparent);

        emit changed();
    }
}

void Bitmap2DView::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(Bitmap2DView);

    if (d->bitmap == NULL)
        return;

    if (event->buttons().testFlag(Qt::MiddleButton))
    {
        d->offset += event->pos() - d->mouseOrigin;
        d->mouseOrigin = event->pos();

        repaint();
    }
}


void Bitmap2DView::keyPressEvent(QKeyEvent *event)
{
    Q_D(Bitmap2DView);

    if (d->bitmap == NULL)
        return;

    if (event->key() == '+')
        d->zoom = qMin(d->zoom + 1, 10);
    else if (event->key() == '-')
        d->zoom = qMax(d->zoom - 1, 1);

    repaint();
}
