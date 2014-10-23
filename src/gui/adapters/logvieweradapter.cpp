#include "logvieweradapter.h"
#include "ui_logvieweradapter.h"
#include <QFileDialog>
#include <QSyntaxHighlighter>
#include <QFont>
#include <QFile>

LogViewerAdapter::LogViewerAdapter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogViewerAdapter)
{
    ui->setupUi(this);
}

LogViewerAdapter::~LogViewerAdapter()
{
    delete ui;
}

void LogViewerAdapter::on_btn_open_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                     "",
                                                     tr("Files (*.*)"));

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(10);

    ui->txt_log->setFont(font);

    highlighter = new CustomHighlighter(ui->txt_log->document());

    QFile file(fileName);
    if(file.open(QFile::ReadOnly | QFile::Text))
        ui->txt_log->setPlainText(file.readAll());
}
