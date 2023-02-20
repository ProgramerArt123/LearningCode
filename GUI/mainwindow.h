#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QProgressBar;
class QLabel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const std::string &title, QWidget *parent = nullptr);
    ~MainWindow();

signals:
	void UpdateProgressSignal(int value, int max);
	void UpdateCodesSignal(const QString &codes);
	void UpdatePathSignal(const QString &path);
private slots:
	void UpdateProgress(int value, int max);
	void UpdateCodes(const QString &codes);
	void UpdatePath(const QString &path);
private:
    Ui::MainWindow *ui;
	QProgressBar *m_progress = NULL;
	QLabel *m_progress_label = NULL;
	QLabel *m_codes_label = NULL;
	QLabel *m_path_label = NULL;
};

#endif // MAINWINDOW_H
