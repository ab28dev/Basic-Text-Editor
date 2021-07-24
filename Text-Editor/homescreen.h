#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QFile>
#include <QMessageBox>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class HomeScreen; }
QT_END_NAMESPACE

class HomeScreen : public QMainWindow
{
    Q_OBJECT

public:
    HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

private slots:
    // Basic Action slots
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionExit_triggered();

    void on_actionBold_triggered();

    void on_actionAbout_triggered();

    void on_actionSubScript_triggered();

    void on_actionSuperScript_triggered();

    void on_textEdit_textChanged();

private:
    Ui::HomeScreen *ui;

    // To monitor changes in the textEdit (if text is changed)
    bool m_changed;
    // Store path for use in other functions
    QString m_path;

    // Create a new file
    void newFile();
    // Open existing file
    void openFile();
    // Save contents of the editor to a file
    void saveFile(QString path);
    // Save file as option
    void saveFileAs();
    // To check if the file is saved or not
    void checkSave();
    // For About Section
    void about_me();


    // QPaintDevice interface
public:
    //QPaintEngine *paintEngine() const override;

    // QWidget interface
protected:
    // Overriding CloseEvent for closing
    void closeEvent(QCloseEvent *event) override;
};
#endif // HOMESCREEN_H
