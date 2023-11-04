#include "textfield.h"
#include "ui_textfield.h"
#include <QPushButton>
#include <QWebEngineView>
#include "widgets/editor/Fields/CharacterField//characterfield.h"

TextField::TextField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextField)
{
    ui->setupUi(this);
    connect(ui->remove, &QAbstractButton::clicked, this, &TextField::sendRemove);
    connect(ui->addCharacter, &QAbstractButton::clicked, this, &TextField::onCharacterClicked);
    connect(ui->preview, &QPushButton::clicked, this, &TextField::exportToBrowser);
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
        ui->AboveFieldLayout->removeWidget(characterField);
        delete characterField;
        characterField = nullptr;
    }
}


void TextField::addCharacterWidget() {
    characterField = new CharacterField(this);
    ui->AboveFieldLayout->addWidget(characterField);
}
QString TextField::generateHtml(const QString& content, TextData* textData) {

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
            margin: 0;  // Ensure no default margins
            overflow: hidden; // Hide any overflow content
        }

        .dialogue-box {
            position: absolute;
            top: 0;
            left: 0;
            background: #ECEFF1;
            border-radius: 100px;
            padding: 1rem;
            width: 390px;
            height: 160px;
            box-shadow: 10px 10px rgba(0,0,0,0.2);
            font-size: 24px;
        }
    </style>
    )";

    fullHtml += "</head><body>";
    fullHtml += "<div class='dialogue-box'>" + newContent + "</div>";
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
    emit previewRequested(content, data);
}

TextField::~TextField()
{
    delete ui;
}

QLineEdit* TextField::getTextField() {
    return ui->textField;
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
