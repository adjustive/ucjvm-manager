#ifndef FIELDSVIEW_H
#define FIELDSVIEW_H

#include <QDialog>

#include "JVMClass.h"

namespace Ui {
class FieldsView;
}

class FieldsView : public QDialog
{
    Q_OBJECT
    
public:
    explicit FieldsView(JVMClass classData, QWidget *parent = 0);
    ~FieldsView();
    
private:
    Ui::FieldsView *ui;
    JVMClass classData;
};

#endif // FIELDSVIEW_H
