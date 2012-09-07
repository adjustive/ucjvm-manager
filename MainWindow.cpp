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
    if (superclassName == "-")
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

template<typename Resource>
void MainWindow::saveResource(Resource &resource, QString path)
{
    QFile file(path);
    if (!file.open(QFile::WriteOnly))
    {
        QMessageBox::warning(0, tr("Cannot write file"), tr("Unable to open file `%0' for writing").arg(file.fileName()));
    }
    else
    {
        QDataStream stream(&file);
        resource.save(stream);
    }
}

template<typename Editor>
void MainWindow::saveResourceAs(typename Editor::ResourceType &resource, QString path)
{
    QFileDialog fileDialog(0, tr("Save resource as"), path, Editor::fileFilter);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setDefaultSuffix(Editor::fileSuffix);

    if (fileDialog.exec() == QDialog::Accepted)
        saveResource(resource, fileDialog.selectedFiles().at(0));
}

template<typename Editor>
void MainWindow::newResource(typename Editor::ResourceType &resource)
{
    Editor editor(resource);

    if (editor.exec() == QDialog::Accepted)
        saveResourceAs<Editor>(resource, resourcePath());
}

void MainWindow::on_action_File_New_Bitmap2D_triggered()
{
    QStringList sizes = QStringList()
            << "32x16"
            << "64x64";

    bool ok;
    QString size = QInputDialog::getItem(this, tr("Bitmap size"), tr("Bitmap size"), sizes, 0, false, &ok);
    if (ok)
    {
        QStringList splitSize = size.split('x');
        Q_ASSERT(splitSize.size() == 2);
        int width  = splitSize.at(0).toInt();
        int height = splitSize.at(1).toInt();

        Bitmap2D bitmap(width, height);
        newResource<Bitmap2DDialog>(bitmap);
    }
}

void MainWindow::on_action_File_New_Bitmap3D_triggered()
{
    QStringList sizes = QStringList()
            << "8x8x8"
            << "16x16x16"
            << "32x32x32";

    bool ok;
    QString size = QInputDialog::getItem(this, tr("Bitmap size"), tr("Bitmap size"), sizes, 0, false, &ok);
    if (ok)
    {
        QStringList splitSize = size.split('x');
        Q_ASSERT(splitSize.size() == 3);
        int width  = splitSize.at(0).toInt();
        int height = splitSize.at(1).toInt();
        int depth  = splitSize.at(2).toInt();

        Bitmap3D bitmap(width, height, depth);
        newResource<Bitmap3DDialog>(bitmap);
    }
}


template<typename Editor>
bool MainWindow::editResource(QFileInfo const &resourceFileInfo, QDataStream &stream)
{
    typedef typename Editor::ResourceType Resource;

    if (resourceFileInfo.suffix() == Editor::fileSuffix)
    {
        Resource resource(stream);
        Editor editor(resource);

        if (editor.exec() == QDialog::Accepted)
            saveResource(resource, resourceFileInfo.absoluteFilePath());

        return true;
    }

    return false;
}

void MainWindow::editResource(QString path)
{
    QFileInfo resourceFileInfo(path);
    Q_ASSERT(resourceFileInfo.exists());

    QFile resourceFile(resourceFileInfo.absoluteFilePath());
    if (!resourceFile.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, tr("Cannot read file"), tr("Unable to open file `%0' for reading").arg(resourceFile.fileName()));
        return;
    }

    QDataStream stream(&resourceFile);

    if (editResource<Bitmap2DDialog>(resourceFileInfo, stream))
        return;
    if (editResource<Bitmap3DDialog>(resourceFileInfo, stream))
        return;
}

void MainWindow::on_resourceList_doubleClicked(const QModelIndex &index)
{
    editResource(resourcePath(qvariant_cast<QString>(index.data())));
}

void MainWindow::on_action_Edit_Resource_triggered()
{
    foreach (QModelIndex index, ui->resourceList->selectionModel()->selectedIndexes())
        editResource(resourcePath(qvariant_cast<QString>(index.data())));
}


void MainWindow::on_superclassName_linkActivated(const QString &link)
{
    JVMClassModel *model = qobject_cast<JVMClassModel *>(ui->classList->model());
    Q_ASSERT(model != NULL);

    QModelIndex index = model->byName(link);
    Q_ASSERT(index.isValid());

    ui->classList->selectionModel()->setCurrentIndex(index, QItemSelectionModel::SelectCurrent);
}
