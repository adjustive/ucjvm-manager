#include "Bitmap2DEditor.h"
#include "ui_Bitmap2DEditor.h"

Bitmap2DEditor::Bitmap2DEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bitmap2DEditor)
{
    ui->setupUi(this);
}

Bitmap2DEditor::~Bitmap2DEditor()
{
    delete ui;
}
