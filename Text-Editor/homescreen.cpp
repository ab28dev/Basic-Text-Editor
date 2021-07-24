#include "homescreen.h"
#include "ui_homescreen.h"
#include "about.h"

HomeScreen::HomeScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);

    // Default values for start up
    m_path = "";
    m_changed = false;
    newFile();
}

HomeScreen::~HomeScreen()
{
    delete ui;
}


// Trigger - Create a new file
void HomeScreen::on_actionNew_triggered()
{
    checkSave();
    newFile();
}


// Trigger - Open existing file
void HomeScreen::on_actionOpen_triggered()
{
    checkSave();
    openFile();
}


// Trigger - Save contents of the editor to a file
void HomeScreen::on_actionSave_triggered()
{
    saveFile(m_path);
}


// Trigger - Save file as option
void HomeScreen::on_actionSave_As_triggered()
{
    saveFileAs();
}


// Trigger - Exit the Editor
void HomeScreen::on_actionExit_triggered()
{
    close();
}


// Trigger - Bold text
void HomeScreen::on_actionBold_triggered()
{
    // Get the current font properties
    QFont font = ui->textEdit->currentFont();
    // Change the bold property of the font accordingly
    font.bold() ? font.setBold(false) : font.setBold(true);
    //Set the font top the textEdit
    ui->textEdit->setCurrentFont(font);
}


// Trigger - Subscript
void HomeScreen::on_actionSubScript_triggered()
{
    // Get the current format of the text
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    // Check if the the format is already SubScript
    if(format.verticalAlignment() == QTextCharFormat::AlignSubScript)
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    else
        format.setVerticalAlignment(QTextCharFormat::AlignSubScript);

    // Set the updated format to the textEdit
    ui->textEdit->mergeCurrentCharFormat(format);
}


void HomeScreen::on_actionSuperScript_triggered()
{
    // Get the current format of the text
    QTextCharFormat format = ui->textEdit->currentCharFormat();
    // Check if the the format is already SuperScript
    if(format.verticalAlignment() == QTextCharFormat::AlignSuperScript)
        format.setVerticalAlignment(QTextCharFormat::AlignNormal);
    else
        format.setVerticalAlignment(QTextCharFormat::AlignSuperScript);

    // Set the updated format to the textEdit
    ui->textEdit->mergeCurrentCharFormat(format);

}


// Trigger - About section
void HomeScreen::on_actionAbout_triggered()
{
    about_me();
}


// Text Changed - if text inside of editor is changed
void HomeScreen::on_textEdit_textChanged()
{
    m_changed = true;
}

// Creates New File
void HomeScreen::newFile()
{
    // Clear contents of the Editor
    ui->textEdit->clear();

    ui->statusbar->showMessage("New File");
    m_path = "";
    m_changed = false;
}

// Open Existing File
void HomeScreen::openFile()
{
    // Open File Dialog and store path
    QString path = QFileDialog::getOpenFileName(this,"Open File");
    // If file is not selected
    if(path.isEmpty())
        return;

    // If file selected, open the file present at path.
    QFile file(path);
    // If error opening file in ReadOnly Mode
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }

    // Set stream
    QTextStream stream(&file);
    // Read the file and set it to TextEdit as HTML
    ui->textEdit->setHtml(stream.readAll());
    file.close();

    // Update m_path
    m_path = path;
    ui->statusbar->showMessage(m_path);
    // No change
    m_changed = false;
}

// Save the text as a file
void HomeScreen::saveFile(QString path)
{
    // If the file is new, call saveFileAs() to save it
    if(path.isEmpty())
    {
        saveFileAs();
        return;
    }

    // If file already exist, update the contents
    // If file selected, open the file present at path.
    QFile file(path);
    // Check if there is some error while opening the file in WriteOnly mode
    if(!file.open(QIODevice::WriteOnly))    // means - the file must not be opened in any program - nor for reading - nor for writing!
    {
        QMessageBox::critical(this, "Error", file.errorString());
        ui->statusbar->showMessage(m_path);
        // Call saveFileAs to save it as a new file
        saveFileAs();
        return;
    }

    // Otherwise, Set Stream
    QTextStream stream(&file);
    // Send the text from textEdit to stream, as HTML
    stream << ui->textEdit->toHtml();
    file.close();

    // Update path
    m_path = path;
    ui->statusbar->showMessage(m_path);
    m_changed = false;
}

// Save file as option
void HomeScreen::saveFileAs()
{
   // Open File dialog and get the path
   QString path = QFileDialog::getSaveFileName(this, "Save File");
   if(path.isEmpty())
       return;
   // Call saveFile() if the path is not empty
   saveFile(path);
}

// Check if file is saved
void HomeScreen::checkSave()
{
    // If m_changed is false, means no update has been made, so return
    if(!m_changed)
        return;

    // If there is some update in file then
    // Show message box and ask if user wants to save the file, check the value returned
    QMessageBox::StandardButton value = QMessageBox::question(this, "Save File?", "You have un-saved changes, Do you want to save?");

    // If user does not wants to save the file
    if(value != QMessageBox::StandardButton::Yes)
        return;

    // If user wants to save the file and the path is not set, i.e. the file is new
    if(m_path.isEmpty())
    {
        saveFileAs();
    }
    // If user wants to save the file and the path is set, i.e. the file exists already
    else
    {
        saveFile(m_path);
    }
}

void HomeScreen::about_me()
{
    // Create instance of the class
    About about;
    // Set Modal
    about.setModal(true);
    // Execute it
    about.exec();
}

// Override close event from windows to alert about saving file
void HomeScreen::closeEvent(QCloseEvent *event)
{
    // CHeck if file is unsaved before closing
    checkSave();
    event->accept();
}

