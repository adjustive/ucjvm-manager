#ifndef METHODSVIEW_H
#define METHODSVIEW_H

#include <QDialog>

#include "JVMClass.h"

namespace Ui {
class MethodsView;
}

class MethodsView : public QDialog
{
    Q_OBJECT
    
public:
    explicit MethodsView(JVMClass classData, QWidget *parent = 0);
    ~MethodsView();
    
private:
    Ui::MethodsView *ui;
    JVMClass classData;
};

#endif // METHODSVIEW_H
