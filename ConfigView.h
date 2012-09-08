#ifndef CONFIGVIEW_H
#define CONFIGVIEW_H

#include <QDialog>

#include "Config.h"

namespace Ui {
class ConfigView;
}

class ConfigView : public QDialog
{
    Q_OBJECT
    
public:
    explicit ConfigView(Config config, QWidget *parent = 0);
    ~ConfigView();
    
private:
    Ui::ConfigView *ui;
    Config config;
};

#endif // CONFIGVIEW_H
