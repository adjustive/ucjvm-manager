#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QDialog>

#include "JVMConfig.h"

namespace Ui {
class ConfigView;
}

class ConfigView : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigView(JVMConfig config, QWidget *parent = 0);
    ~ConfigView();
    
private:
    Ui::ConfigView *ui;
    JVMConfig config;
};

#endif // CONFIGVIEW_H
