#ifndef RESOURCEVISITOR_H
#define RESOURCEVISITOR_H

class Bitmap2D;
class Bitmap3D;

class ResourceVisitor
{
public:
    ResourceVisitor();

    virtual void visit(Bitmap2D &bitmap) = 0;
    virtual void visit(Bitmap3D &bitmap) = 0;
};

#endif // RESOURCEVISITOR_H
