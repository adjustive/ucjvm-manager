#include "Bitmap3DRender.h"

#include "Bitmap3D.h"

#include <qglbuilder.h>
#include <qglcube.h>
#include <qglsphere.h>

#define TESTING 0


struct Bitmap3DRenderPrivate
{
    Bitmap3D *bitmap;
    QGLSceneNode *scene;
    QGLMaterialCollection materials;
    float scale;
};


Bitmap3DRender::Bitmap3DRender(QWidget *parent)
    : QGLView(parent)
    , d_ptr(new Bitmap3DRenderPrivate)
{
    Q_D(Bitmap3DRender);
    d->bitmap = NULL;
    d->scene = NULL;
    d->scale = 5.0f;
}

Bitmap3DRender::~Bitmap3DRender()
{
    delete d_ptr;
}


void Bitmap3DRender::setBitmap(Bitmap3D &bitmap)
{
    Q_D(Bitmap3DRender);
    d->bitmap = &bitmap;
}


void Bitmap3DRender::createScene()
{
    Q_D(Bitmap3DRender);
    Q_ASSERT(d->bitmap != NULL);

    QGLBuilder builder(&d->materials);

    int const width  = d->bitmap->width () / 2;
    int const height = d->bitmap->height() / 2;
    int const depth  = d->bitmap->depth () / 2;

    for (int z = -depth; z < depth; z++)
    {
        for (int y = -height; y < depth; y++)
        {
            for (int x = -width; x < width; x++)
            {
#if !TESTING
                QColor color = d->bitmap->pixel(x + width, y + height, z + depth);
                if (color != Qt::transparent)
#endif
                {
                    builder << QGL::Faceted << QGLSphere(0.1f, 1);
                    builder.currentNode()->setPosition(QVector3D(
                                                           x / d->scale,
                                                           y / d->scale,
                                                           z / d->scale));

#if !TESTING
                    QGLMaterial *material = d->materials.material(color.name());
                    if (material == NULL)
                    {
                        material = new QGLMaterial;
                        material->setColor(color);
                        material->setObjectName(color.name());
                        d->materials.addMaterial(material);
                    }

                    builder.currentNode()->setMaterial(material);
#endif
                }
            }
        }
    }

    delete d->scene;
    d->scene = builder.finalizedSceneNode();
    d->scene->setEffect(QGL::LitDecalTexture2D);
#if TESTING
    QGLMaterial *material = new QGLMaterial;
    material->setColor(Qt::gray);
    d->scene->setMaterial(material);
#endif
}


static void drawLine(QGLPainter *painter, QVector3D start, QVector3D end)
{
    QVector3DArray vertices;
    vertices.append(start);
    vertices.append(end);
    painter->setColor(Qt::white);
    painter->setVertexAttribute(QGL::Position, vertices);
    painter->draw(QGL::Lines, 2);
}


void Bitmap3DRender::paintGL(QGLPainter *painter)
{
    Q_D(Bitmap3DRender);

    if (d->bitmap == NULL)
        return;

    createScene();

    painter->modelViewMatrix().rotate(20.0, 0.5, 1.0, 0.0);
    d->scene->draw(painter);

    float const width  = (d->bitmap->width () / 2 + 1) / d->scale;
    float const height = (d->bitmap->height() / 2 + 1) / d->scale;
    float const depth  = (d->bitmap->depth () / 2 + 1) / d->scale;

    QVector3D const vertices[] = {
        /* 0 */ QVector3D(width, height, depth),
        /* 1 */ QVector3D(width, height, -depth),
        /* 2 */ QVector3D(width, -height, depth),
        /* 3 */ QVector3D(width, -height, -depth),
        /* 4 */ QVector3D(-width, height, depth),
        /* 5 */ QVector3D(-width, height, -depth),
        /* 6 */ QVector3D(-width, -height, depth),
        /* 7 */ QVector3D(-width, -height, -depth),
    };

    int const indices[][2] = {
        { 7, 3 },
        { 3, 1 },
        { 1, 5 },
        { 5, 7 },

        { 6, 2 },
        { 2, 0 },
        { 0, 4 },
        { 4, 6 },

        { 1, 0 },
        { 0, 2 },
        { 2, 3 },

        { 5, 4 },
        { 4, 6 },
        { 6, 7 },
    };

#if 0
    for (size_t i = 0; i < sizeof indices / sizeof indices[0]; i++)
    {
        int (&index)[2] = indices[i];
        QVector3D start(width  * (1 - 2 * !!(index[0] & 4)),
                        height * (1 - 2 * !!(index[0] & 2)),
                        depth  * (1 - 2 * !!(index[0] & 1)));
        QVector3D end(width  * (1 - 2 * !!(index[1] & 4)),
                      height * (1 - 2 * !!(index[1] & 2)),
                      depth  * (1 - 2 * !!(index[1] & 1)));
        drawLine(painter, start, end);
    }
#else
    for (size_t i = 0; i < sizeof indices / sizeof indices[1]; i++)
        drawLine(painter, vertices[indices[i][0]], vertices[indices[i][1]]);
#endif
}
