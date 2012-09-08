#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QStringListModel>
class QDir;
class QFileInfo;

#include "ResourceEditor.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QString classPath(QString file = QString()) const;
    QString resourcePath(QString file = QString()) const;

    void loadClasses(QDir path);
    void loadResources(QDir path);

private slots:
    void on_pathSearch_clicked();

    void on_load_clicked();
    void on_link_clicked();

    void onClassSelectionChanged(QModelIndex const &current, QModelIndex const &previous);

    void on_showFields_clicked();
    void on_showMethods_clicked();

    void on_action_Edit_JVMConfig_triggered();

    void on_action_File_New_Bitmap2D_triggered();
    void on_action_File_New_Bitmap3D_triggered();

    void on_resourceList_doubleClicked(const QModelIndex &index);

    void on_action_Edit_Resource_triggered();

    void on_superclassName_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    QStringListModel resourceModel;
    ResourceEditor::Collection resourceEditors;
};

#endif // MAINWINDOW_H
