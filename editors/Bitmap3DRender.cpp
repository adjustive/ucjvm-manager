#include "Bitmap3DRender.h"

#include "Bitmap3D.h"

#include <qglbuilder.h>
#include <qglcube.h>
#include <qglsphere.h>


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
    Q_D(Bitmap3DRender);
    delete d->scene;
    delete d_ptr;
}


QGLMaterial *Bitmap3DRender::material(QColor color)
{
    Q_D(Bitmap3DRender);

    QGLMaterial *material = d->materials.material(color.name());
    if (material == NULL)
    {
        material = new QGLMaterial;
        material->setColor(color);
        material->setObjectName(color.name());
        d->materials.addMaterial(material);
    }

    return material;
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
                QColor color = d->bitmap->pixel(x + width, y + height, z + depth);
                if (color != Qt::transparent)
                {
                    builder << QGL::Faceted << QGLSphere(0.1f, 1);
                    builder.currentNode()->setPosition(QVector3D(
                                                           x / d->scale,
                                                           y / d->scale,
                                                           z / d->scale));

                    builder.currentNode()->setMaterial(material(color));
                }
            }
        }
    }

    delete d->scene;
    d->scene = builder.finalizedSceneNode();
    d->scene->setEffect(QGL::LitDecalTexture2D);
}


static void drawBox(QGLPainter *painter, float width, float height, float depth)
{
    QVector3D const vertices[] = {
        /* 0 = 000 */ QVector3D( width,  height,  depth),
        /* 1 = 001 */ QVector3D( width,  height, -depth),
        /* 2 = 010 */ QVector3D( width, -height,  depth),
        /* 3 = 011 */ QVector3D( width, -height, -depth),
        /* 4 = 100 */ QVector3D(-width,  height,  depth),
        /* 5 = 101 */ QVector3D(-width,  height, -depth),
        /* 6 = 110 */ QVector3D(-width, -height,  depth),
        /* 7 = 111 */ QVector3D(-width, -height, -depth),
    };

    int const indices[][2] = {
        // back
        { 7, 3 },
        { 3, 1 },
        { 1, 5 },
        { 5, 7 },

        // front
        { 6, 2 },
        { 2, 0 },
        { 0, 4 },
        { 4, 6 },

        // right side
        { 1, 0 },
        { 2, 3 },

        // left side
        { 5, 4 },
        { 6, 7 },
    };

    QVector3DArray vertexData;

    for (size_t i = 0; i < sizeof indices / sizeof indices[1]; i++)
    {
        vertexData
            << vertices[indices[i][0]]
            << vertices[indices[i][1]];
    }

    int lineCount = vertexData.size();

    painter->setColor(Qt::white);
    painter->setVertexAttribute(QGL::Position, vertexData);
    painter->draw(QGL::Lines, lineCount);
}

void Bitmap3DRender::paintGL(QGLPainter *painter)
{
    Q_D(Bitmap3DRender);

    if (d->bitmap == NULL)
        return;

    createScene();

    painter->modelViewMatrix().rotate(20.0, 0.5, 1.0, 0.0);

    if (strcmp(reinterpret_cast<char const *>(glGetString(GL_VERSION)), "3.3.0 NVIDIA 302.17") != 0)
    {
        drawBox(painter,
                (d->bitmap->width () / 2 + 1) / d->scale,
                (d->bitmap->height() / 2 + 1) / d->scale,
                (d->bitmap->depth () / 2 + 1) / d->scale);
    }

    d->scene->draw(painter);
}
