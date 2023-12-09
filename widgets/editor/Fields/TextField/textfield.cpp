#include "textfield.h"
#include "ui_textfield.h"
#include <QPushButton>
#include <QWebEngineView>
#include "widgets/editor/Fields/CharacterField//characterfield.h"
#include <QFileDialog>
#include <QMessageBox>

TextField::TextField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextField)
{
    ui->setupUi(this);
    connect(ui->remove, &QAbstractButton::clicked, this, &TextField::sendRemove);
    connect(ui->addCharacter, &QAbstractButton::clicked, this, &TextField::onCharacterClicked);
    connect(ui->preview, &QPushButton::clicked, this, &TextField::exportToBrowser);
    connect(ui->playSound, &QPushButton::clicked, this, &TextField::playSound);
    connect(ui->setSound, &QPushButton::clicked, this, &TextField::setSound);
    player->setAudioOutput(audio);
    //connect(editorTools, &EditorTools::characterEffectRequested, this, &TextField::applyCharacterEffect);
}

void TextField::onCharacterClicked() {
    if (characterFieldAdded) {
        // If already added, remove the widget
        removeCharacterWidget();
    } else {
        addCharacterWidget();
    }

    // Toggle the state
    characterFieldAdded = !characterFieldAdded;
}

void TextField::removeCharacterWidget() {
    if (characterField) {
        ui->above->removeWidget(characterField);
        data->setFieldType(Text);
        delete characterField;
        characterField = nullptr;
    }
}


void TextField::addCharacterWidget() {
    characterField = new CharacterField(this);
    data->setFieldType(TextCharacter);
    ui->above->addWidget(characterField);
}

void TextField::applyCharacterEffect(int effectNumber) {
//    if(effectNumber == 1) {
//        view->page()->runJavaScript("enlargeCharacter();");
//    }
//    else if(effectNumber == 2) {
//        view->page()->runJavaScript("wobbleCharacter();");
//    }
//    else if(effectNumber == 3) {
//        view->page()->runJavaScript("speedUpText();");
//    }
}


void TextField::exportToBrowser() {
    QString content = ui->textField->text();
    QString content2;
    if (characterField){
        content2 = characterField->getText();
    }
    emit previewRequested(content, content2, data);
}

TextField::~TextField()
{
    delete ui;
    delete audio;
    delete player;
}

QLineEdit* TextField::getTextField() {
    return ui->textField;
}

CharacterField* TextField::getCharacterField() {
    return characterField;
}

QPushButton* TextField::getPreview() {
    return ui->preview;
}

TextData* TextField::getData() {
    return data;
}

void TextField::setData(TextData* data) {
    this->data = data;
}

void TextField::sendRemove() {
    emit removeField(this);
}

void TextField::playSound() {
    player->stop();
    player->setPosition(0);

    // If soundFile has not been set, display a message box
    if (soundFile.isEmpty())
    {
        QMessageBox::warning(this, "Warning", "Please set a sound");
        return;
    }
    audio->setVolume(25);
    player->setSource(QUrl::fromLocalFile(soundFile));
    player->setLoops(1);
    player->play();
}

void TextField::setSound() {
    // Select an mp3 file using the file explorer
    QString fileName = QFileDialog::getOpenFileName(this, "Select an mp3 file");

    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    // Make sure the selected file is mp3
    if (fileName.split(".").last() != "mp3")
    {
        QMessageBox::warning(this, "Warning", "Please select an mp3 file");
        return;
    }

    soundFile = fileName;
    QString playToolTip = "Play sound: " + soundFile;
    ui->playSound->setToolTip(playToolTip);
}

void TextField::setSoundFile(QString fileName) {
    if (fileName == "")
        return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Sound file not valid: " + file.errorString());
        return;
    }

    // Make sure the selected file is mp3
    if (fileName.split(".").last() != "mp3")
    {
        QMessageBox::warning(this, "Warning", "Incorrect sound file, please select an mp3 file");
        return;
    }

    soundFile = fileName;
    QString playToolTip = "Play sound: " + soundFile;
    ui->playSound->setToolTip(playToolTip);
}

QString TextField::getSoundFile() {
    return soundFile;
}
