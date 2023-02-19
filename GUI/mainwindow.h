#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QProgressBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const std::string &title, QWidget *parent = nullptr);
    ~MainWindow();

signals:
	void UpdateProgressMaxSignal(int max);
	void UpdateProgressValueSignal(int value);     

private slots:
	void UpdateProgressMax(int max);
	void UpdateProgressValue(int value);
private:
    Ui::MainWindow *ui;
	QProgressBar *m_progress = NULL;
};

#endif // MAINWINDOW_H
