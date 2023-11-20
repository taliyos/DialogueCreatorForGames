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
QString TextField::generateHtml(const QString& content, const QString& content2, TextData* textData) {

    QString newContent = content;
    // 1 = wobble
    if (textData->hasFieldEffect(1))
        newContent = "<effect type=\"wobble\">" + content + "</effect>";
    // 2 = enlarge
    else if (textData->hasFieldEffect(2))
        newContent = "<effect type=\"enlarge\">" + content + "</effect>";
    // 3 = speedUp
    else if (textData->hasFieldEffect(3))
        newContent = "<effect type=\"speedUp\">" + content + "</effect>";
    // 4 = bold
    else if (textData->hasFieldEffect(4))
        newContent = "<effect type=\"bold\">" + content + "</effect>";
    // 5 = typed
    else if (textData->hasFieldEffect(5))
        newContent = "<effect type=\"typed\">" + content + "</effect>";

    if (newContent == content)
    {
        const map<pair<int,int>, list<int>> textEffects = textData->getTextEffects();
        int totalAddedChars = 0;
        for(map<pair<int,int>,list<int>>::const_iterator it = textEffects.begin(); it != textEffects.end(); it++)
        {
            int start = it->first.first;
            int end = it->first.second;
            int tag = it->second.front();

            QString string1 = "";
            QString string2 = "</effect>";
            if (tag == 1)
                string1 = "<effect type=\"wobble\">";
            else if (tag == 2)
                string1 = "<effect type=\"enlarge\">";
            else if (tag == 3)
                string1 = "<effect type=\"speedUp\">";
            else if (tag == 4)
                string1 = "<effect type=\"bold\">";
            else if (tag == 5)
                string1 = "<effect type=\"typed\">";

            newContent.insert(start + totalAddedChars, string1);
            totalAddedChars += string1.length();
            newContent.insert(end + totalAddedChars,string2);
            totalAddedChars += string2.length();
        }
    }

    QString base64Image;
    QString fullHtml;

    fullHtml += "<!DOCTYPE html>";
    fullHtml += "<html><head><title>Dialogue Preview</title>";
    fullHtml += R"(<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>)";
    fullHtml += R"(
        <script>
        $(document).ready(function() {
               applyEffectsFromTags();
        });

        function applyEffectsFromTags() {
            // Check for the 'wobble' effect
            $('effect[type="wobble"]').each(function() {
                let content = $(this).text();
                $(this).replaceWith('<span class="wobbled">' + content + '</span>');
            });

            // Check for the 'enlarge' effect
            $('effect[type="enlarge"]').each(function() {
                let content = $(this).text();
                $(this).replaceWith('<span class="enlarged">' + content + '</span>');
            });

            // Check for the 'speedUp' effect
            $('effect[type="speedUp"]').each(function() {
                let content = $(this).text();
                let wrappedContent = '';
                let delay = 1;
                let delayIncrement = 0.2;

                for(let i = 0; i < content.length; i++) {
                    let char = content[i] === ' ' ? '&nbsp;' : content[i];  // Replace space with &nbsp;
                    wrappedContent += '<span style="animation-delay:' + delay + 's">' + char + '</span>';
                    delay += delayIncrement;
                }

                $(this).replaceWith('<span class="sped-up">' + wrappedContent + '</span>');
            });

            $('effect[type="typed"]').each(function() {
                let content = $(this).text();
                let wrappedContent = '';
                let delay = 1;
                let delayIncrement = 0.2;

                for(let i = 0; i < content.length; i++) {
                    let char = content[i] === ' ' ? '&nbsp;' : content[i];  // Replace space with &nbsp;
                    wrappedContent += '<span style="animation-delay:' + delay + 's">' + char + '</span>';
                    delay += delayIncrement;
                }

                $(this).replaceWith('<span class="typed">' + wrappedContent + '</span>');
            });

            // Check for 'bold' effect
            $('effect[type="bold"]').each(function() {
                let content = $(this).text();
                $(this).replaceWith('<span class="bold">' + content + '</span>');
            });
        }
        </script>

        <style>
        .enlarged { font-size: 150%; }
        @keyframes shake {
            0%, 100% { transform: translateX(0); }
            10%, 30%, 50%, 70%, 90% { transform: translateX(-10px); }
            20%, 40%, 60%, 80% { transform: translateX(10px); }
        }

        .wobbled {
            display: inline-block;
            animation: shake 0.5s infinite;
        }

        @keyframes flyInCharacter {
            0% { transform: translateY(100%); opacity: 0; }
            70% { transform: translateY(0); opacity: 1; }
            100% { transform: translateY(0); opacity: 1; }
        }

        .sped-up span {
            display: inline-block;  /* makes spans sit side-by-side */
            animation: flyInCharacter 2s infinite;  /* Adjust time for how long you want the animation to last */
            transform: translateY(100%);
            opacity: 0;
        }

        @keyframes typing {
          from {opacity: 0;}
          to {opacity: 1;}
        }

        .typed span {
            opacity: 0;
            overflow: hidden;
            display: inline-block;
            animation: typing 0.05s forwards;
        }

        @keyframes bolden {
          0%, 80%, 100% {font-weight: 300;}
          20% {transition: font-weight 500ms ease-in-out; font-weight: 900;}
        }

        .bold {
            display: inline-block;
            animation: bolden 1.5s infinite;
        }

        </style>
    )";

    fullHtml += R"(
    <style>
        body {
            background-image: url('data:image/jpg;base64,)" + base64Image + R"(');
            background-size: contain;
            background-repeat: no-repeat;
            background-position: center center;
            font-family: Arial, sans-serif;
            height: 100vh;
            overflow: hidden; // Hide any overflow content
            margin: 12px;
        }

        .dialogue-container {
            position: relative;
            width: 100%;
            height: 100vh;
            display: flex;
            flex-direction: column;
            justify-content: top;
            align-items: left;
        }

        .dialogue-box {
            background: white;
            border-radius: 15px;
            padding: 1rem;
            width: 450px;
            height: 160px;
            box-shadow: 5px 5px rgba(0,0,0,0.2);
            font-size: 24px;
            margin: 0 auto;
            margin-top: 10px;
        }

        .character-box {
            background: white;
            border-radius: 15px;
            padding: 1rem;
            width: 300px; /* Adjust width as necessary */
            height: 20px; /* Adjust height as necessary */
            box-shadow: 5px 5px rgba(0,0,0,0.2);
            font-size: 24px;
            z-index: 2;
        }


    </style>
    )";

    // ... (The rest of your styles remain the same)

    fullHtml += "</head><body>";
    fullHtml += R"(<div class='dialogue-container'>)"; // This wraps both boxes
    if (content2 != "") fullHtml += R"(<div class='character-box'>)" + content2 + R"(</div>)";
    fullHtml += R"(<div class='dialogue-box'>)" + newContent + R"(</div>)";
    fullHtml += R"(</div>)"; // Close .dialogue-container
    fullHtml += "</body></html>";

    return fullHtml;
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
