#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "JVMConfig.h"
#include "JVMClassModel.h"
#include "MessageModel.h"
#include "FieldsView.h"
#include "MethodsView.h"
#include "Linker.h"
#include "ConfigView.h"
#include "Bitmap2DDialog.h"
#include "Bitmap3DDialog.h"
#include "Bitmap2D.h"
#include "Bitmap3D.h"

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

    foreach (QFileInfo entry, config.entryInfoList(QStringList() << "*.cfg"))
    {
        JVMConfig cfg(entry.filePath());
        QString name = QString("%1 @ 0x%0").arg(cfg.baseAddress(), 0, 16).arg(cfg.configName());
        ui->config->addItem(name, QVariant::fromValue(cfg));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_load_clicked()
{
    JVMClassList classList(QDir(ui->path->text() + "/bin"));

    delete ui->classList->model();
    ui->classList->setModel(new JVMClassModel(classList));

    connect(ui->classList->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            SLOT(onClassSelectionChanged(QModelIndex,QModelIndex)));
}

void MainWindow::on_link_clicked()
{
    if (JVMClassModel *classModel = qobject_cast<JVMClassModel *>(ui->classList->model()))
    {
        JVMConfig config = qvariant_cast<JVMConfig>(ui->config->itemData(ui->config->currentIndex()));
        JVMClassList classList = classModel->classes();

        Linker linker(config, classList);
        linker.link();
    }
    else
    {
        QMessageBox::warning(this, "No classes loaded", "Press the Load button before the Link button");
    }
}

void MainWindow::onClassSelectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(previous);

    JVMClass const &currentClass = qvariant_cast<JVMClass>(current.data(Qt::UserRole));

    ui->minorVersion->setText(QString("%0").arg(currentClass.minorVersion()));
    ui->majorVersion->setText(QString("%0").arg(currentClass.majorVersion()));

    ui->className->setText(currentClass.name());
    ui->superclassName->setText(currentClass.superName());

    ui->flags->setText(currentClass.flagsString());

    ui->interfaceCount->setText(QString("%0").arg(currentClass.interfaceCount()));
    ui->fieldCount->setText(QString("%0").arg(currentClass.fieldCount()));
    ui->methodCount->setText(QString("%0").arg(currentClass.methodCount()));

    ui->showInterfaces->setEnabled(currentClass.interfaceCount() != 0);
    ui->showFields->setEnabled(currentClass.fieldCount() != 0);
    ui->showMethods->setEnabled(currentClass.methodCount() != 0);
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

void MainWindow::on_action_Edit_Bitmap2D_triggered()
{
    QStringList sizes = QStringList()
            << "32x16"
            << "64x64";

    QString size = QInputDialog::getItem(this, "Bitmap size", "Bitmap size", sizes, 0, false);
    QStringList splitSize = size.split('x');
    Q_ASSERT(splitSize.size() == 2);
    int width  = splitSize.at(0).toInt();
    int height = splitSize.at(1).toInt();

    Bitmap2D bitmap(width, height);
    Bitmap2DDialog editor(bitmap);
    editor.exec();
}

void MainWindow::on_action_Edit_Bitmap3D_triggered()
{
    QStringList sizes = QStringList()
            << "8x8x8"
            << "16x16x16"
            << "32x32x32";

    QString size = QInputDialog::getItem(this, "Bitmap size", "Bitmap size", sizes, 0, false);
    QStringList splitSize = size.split('x');
    Q_ASSERT(splitSize.size() == 3);
    int width  = splitSize.at(0).toInt();
    int height = splitSize.at(1).toInt();
    int depth  = splitSize.at(2).toInt();

    Bitmap3D bitmap(width, height, depth);
    Bitmap3DDialog editor(bitmap);
    editor.exec();
}
