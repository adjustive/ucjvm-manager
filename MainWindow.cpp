#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "JVMConfig.h"
#include "JVMClassModel.h"
#include "MessageModel.h"
#include "FieldsView.h"
#include "MethodsView.h"
#include "Linker.h"
#include "JavaName.h"
#include "ConfigView.h"
#include "Bitmap2DDialog.h"
#include "Bitmap3DDialog.h"
#include "Bitmap2D.h"
#include "Bitmap3D.h"

#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QInputDialog>


static MessageModel messageModel;

static void msgHandler(QtMsgType type, char const *message)
{
    fprintf(stderr, "[%s] {%s} %s\n",
            QTime::currentTime().toString(Qt::ISODate).toUtf8().constData(),
            MessageModel::msgTypeString(type),
            message);
    messageModel.append(type, message);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , resourceEditors(this)
{
    ui->setupUi(this);

    ui->messageView->setModel(&messageModel);
    connect(&messageModel, SIGNAL(messageAdded()), ui->messageView, SLOT(scrollToBottom()));
    qInstallMsgHandler(msgHandler);

    QDir config;
    config.setPath(":/data/jvmconfig");

    foreach (QFileInfo entry, config.entryInfoList(QStringList("*.cfg")))
    {
        JVMConfig cfg(entry.filePath());
        QString name = QString("%1 @ 0x%0").arg(cfg.baseAddress(), 0, 16).arg(cfg.configName());
        ui->config->addItem(name, QVariant::fromValue(cfg));
    }

    ui->resourceList->setModel(&resourceModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QString MainWindow::classPath(QString file) const
{
    QString path = ui->path->text() + "/bin";
    if (!file.isEmpty())
        path += "/" + file;
    return path;
}

QString MainWindow::resourcePath(QString file) const
{
    QString path = ui->path->text() + "/res";
    if (!file.isEmpty())
    {
        path += "/";
        if (file != ".")
            path += file;
    }
    return path;
}


void MainWindow::on_pathSearch_clicked()
{
    QFileDialog dialog(this);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.exec();

    if (dialog.result() != 0)
    {
        QStringList files = dialog.selectedFiles();
        if (!files.empty())
        {
            Q_ASSERT(files.size() == 1);
            ui->path->setText(files.front());
        }
    }
}

static void findFiles(QString const &suffix, QList<QFileInfo> &files, QDir const &dir)
{
    foreach (QFileInfo info, dir.entryInfoList())
    {
        if (info.isFile() && info.fileName()[0] != '.' && (suffix.isEmpty() || info.suffix() == suffix))
            files.append(info);
        if (info.isDir() && info.fileName()[0] != '.')
            findFiles(suffix, files, QDir(info.filePath()));
    }
}

void MainWindow::loadClasses(QDir path)
{
    QList<QFileInfo> files;
    findFiles("class", files, path);
    JVMClassList classList(files);

    delete ui->classList->model();
    ui->classList->setModel(new JVMClassModel(classList, this));

    connect(ui->classList->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(onClassSelectionChanged(QModelIndex,QModelIndex)));
}

static QString getFileName(QFileInfo const &info)
{
    return info.fileName();
}

void MainWindow::loadResources(QDir path)
{
    QList<QFileInfo> files;
    findFiles("", files, path);

    QStringList strings;
    std::transform(files.begin(), files.end(), std::back_inserter(strings), getFileName);

    resourceModel.setStringList(strings);
}

void MainWindow::on_load_clicked()
{
    loadClasses(QDir(classPath()));
    loadResources(QDir(resourcePath()));
}


static QString prependString(QString prefix, QString string)
{
    return prefix + string;
}


void MainWindow::on_link_clicked()
{
    if (JVMClassModel *classModel = qobject_cast<JVMClassModel *>(ui->classList->model()))
    {
        JVMConfig config = qvariant_cast<JVMConfig>(ui->config->itemData(ui->config->currentIndex()));
        JVMClassList classList = classModel->classes();
        QStringList resourceFiles = resourceModel.stringList();
        std::transform(resourceFiles.begin(), resourceFiles.end(), resourceFiles.begin(),
                       std::bind1st(
                           std::ptr_fun(prependString),
                           resourcePath(".")));
        qDebug() << resourceFiles;

        Linker linker(config, classList, resourceFiles);
        linker.link();
    }
    else
    {
        QMessageBox::warning(this, tr("No classes loaded"), tr("Press the Load button before the Link button"));
    }
}

void MainWindow::onClassSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    JVMClass const &currentClass = qvariant_cast<JVMClass>(current.data(Qt::UserRole));

    ui->minorVersion->setText(QString("%0").arg(currentClass.minorVersion()));
    ui->majorVersion->setText(QString("%0").arg(currentClass.majorVersion()));

    ui->className->setText(JavaName::demangle(currentClass.name()));

    QString superclassName = currentClass.superName();
    if (superclassName.isEmpty())
        ui->superclassName->setText("-");
    else
        ui->superclassName->setText(QString("<a href='%0'>%0</a>").arg(JavaName::demangle(superclassName)));

    ui->flags->setText(currentClass.flagsString());

    ui->interfaceCount->setText(QString("%0").arg(currentClass.interfaceCount()));
    ui->fieldCount->setText(QString("%0").arg(currentClass.fieldCount()));
    ui->methodCount->setText(QString("%0").arg(currentClass.methodCount()));

    ui->showInterfaces->setEnabled(currentClass.interfaceCount() != 0);
    ui->showFields->setEnabled(currentClass.fieldCount() != 0);
    ui->showMethods->setEnabled(currentClass.methodCount() != 0);

    ui->staticDataSize->setText(QString("%0").arg(currentClass.staticDataSize()));
    ui->instanceDataSize->setText(QString("%0").arg(currentClass.instanceDataSize()));
    ui->inheritedStaticDataSize->setText(QString("%0").arg(currentClass.inheritedStaticDataSize()));
    ui->inheritedInstanceDataSize->setText(QString("%0").arg(currentClass.inheritedInstanceDataSize()));
}

void MainWindow::on_showFields_clicked()
{
    JVMClass const &currentClass = qvariant_cast<JVMClass>(ui->classList->currentIndex().data(Qt::UserRole));
    FieldsView view(currentClass);
    view.exec();
}

void MainWindow::on_showMethods_clicked()
{
    JVMClass const &currentClass = qvariant_cast<JVMClass>(ui->classList->currentIndex().data(Qt::UserRole));
    MethodsView view(currentClass);
    view.exec();
}

void MainWindow::on_action_Edit_JVMConfig_triggered()
{
    JVMConfig config = qvariant_cast<JVMConfig>(ui->config->itemData(ui->config->currentIndex()));
    ConfigView view(config);
    view.exec();
}

void MainWindow::on_action_File_New_Bitmap2D_triggered()
{
    QString fileName = resourceEditors.newResource("b2d", resourcePath());
    if (!fileName.isEmpty())
        resourceModel.setStringList(resourceModel.stringList() << fileName);
}

void MainWindow::on_action_File_New_Bitmap3D_triggered()
{
    QString fileName = resourceEditors.newResource("b3d", resourcePath());
    if (!fileName.isEmpty())
        resourceModel.setStringList(resourceModel.stringList() << fileName);
}


void MainWindow::on_resourceList_doubleClicked(const QModelIndex &index)
{
    resourceEditors.editResource(resourcePath(qvariant_cast<QString>(index.data())));
}

void MainWindow::on_action_Edit_Resource_triggered()
{
    foreach (QModelIndex index, ui->resourceList->selectionModel()->selectedIndexes())
        resourceEditors.editResource(resourcePath(qvariant_cast<QString>(index.data())));
}


void MainWindow::on_superclassName_linkActivated(const QString &link)
{
    JVMClassModel *model = qobject_cast<JVMClassModel *>(ui->classList->model());
    Q_ASSERT(model != NULL);

    QModelIndex index = model->byName(link);
    Q_ASSERT(index.isValid());

    ui->classList->selectionModel()->setCurrentIndex(index, QItemSelectionModel::SelectCurrent);
}
