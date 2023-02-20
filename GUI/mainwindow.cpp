#include <QProgressBar>
#include <QLabel>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const std::string &title, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	assert(m_progress = ui->centralWidget->findChild<QProgressBar*>("progressBar"));
	assert(m_progress_label = ui->centralWidget->findChild<QLabel*>("progressLabel"));
	assert(m_codes_label = ui->centralWidget->findChild<QLabel*>("codesLabel"));
	assert(m_path_label = ui->centralWidget->findChild<QLabel*>("pathLabel"));
	
	ui->title->setText(("Welcome " + title + " Learning !").c_str());
	setWindowTitle(title.c_str());

	connect(this, SIGNAL(UpdateProgressSignal(int, int)), this, SLOT(UpdateProgress(int, int)));
	connect(this, SIGNAL(UpdateCodesSignal(const QString&)), this, SLOT(UpdateCodes(const QString&)));
	connect(this, SIGNAL(UpdatePathSignal(const QString&)), this, SLOT(UpdatePath(const QString&)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateProgress(int value, int max) {
	m_progress->setMaximum(max);
	m_progress->setValue(value);
	m_progress_label->setText(QString::number(value) + "/" + QString::number(max));
}

void MainWindow::UpdateCodes(const QString &codes) {
	m_codes_label->setText(codes);
}

void MainWindow::UpdatePath(const QString &path) {
	m_path_label->setText(path);
}
