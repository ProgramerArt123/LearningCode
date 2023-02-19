#include <QProgressBar>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const std::string &title, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	
	assert(m_progress = ui->centralWidget->findChild<QProgressBar*>("progressBar"));
	
	ui->title->setText(("Welcome " + title + " Learning !").c_str());
	setWindowTitle(title.c_str());

	connect(this, SIGNAL(UpdateProgressMaxSignal(int)), this, SLOT(UpdateProgressMax(int)));
	connect(this, SIGNAL(UpdateProgressValueSignal(int)), this, SLOT(UpdateProgressValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UpdateProgressMax(int max) {
	m_progress->setMaximum(max);
}

void MainWindow::UpdateProgressValue(int value) {
	m_progress->setValue(value);
}
