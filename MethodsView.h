#ifndef METHODSVIEW_H
#define METHODSVIEW_H

#include <QDialog>

#include "Class.h"

namespace Ui {
class MethodsView;
}

class MethodsView : public QDialog
{
    Q_OBJECT
    
public:
    explicit MethodsView(Class classData, QWidget *parent = 0);
    ~MethodsView();
    
private:
    Ui::MethodsView *ui;
    Class classData;
};

#endif // METHODSVIEW_H
