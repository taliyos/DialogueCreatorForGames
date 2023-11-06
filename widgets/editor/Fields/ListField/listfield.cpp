#include "listfield.h"
#include "ui_listfield.h"
#include "widgets/editor/Fields/CharacterField//characterfield.h"

ListField::ListField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListField)
{
    ui->setupUi(this);
    connect(ui->remove, &QAbstractButton::clicked, this, &ListField::sendRemove);
    connect(ui->addCharacter, &QAbstractButton::clicked, this, &ListField::onCharacterClicked);
    connect(ui->preview, &QPushButton::clicked, this, &ListField::exportToBrowser);
    //connect(editorTools, &EditorTools::characterEffectRequested, this, &TextField::applyCharacterEffect);
    connect(this, &ListField::updateRequested, this, &ListField::updateUI);
}

void ListField::onCharacterClicked() {
    if (characterFieldAdded) {
        // If already added, remove the widget
        removeCharacterWidget();
    } else {
        addCharacterWidget();
    }

    // Toggle the state
    characterFieldAdded = !characterFieldAdded;
}

void ListField::removeCharacterWidget() {
    if (characterField) {
        ui->AboveFieldLayout->removeWidget(characterField);
        delete characterField;
        characterField = nullptr;
    }
}


void ListField::addCharacterWidget() {
    characterField = new CharacterField(this);
    ui->AboveFieldLayout->addWidget(characterField);
}


QString ListField::generateHtml(const QString& content) {
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
    fullHtml += "<div class='dialogue-box'>" + content + "</div>";
    fullHtml += "</body></html>";

    return fullHtml;
}

void ListField::applyCharacterEffect(int effectNumber) {
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


void ListField::exportToBrowser() {
    QString content = QString::fromStdString(data->getText());
    emit previewRequested(content);
}

ListField::~ListField()
{
    delete ui;
}

QComboBox* ListField::getComboBox() {
    return ui->comboBox;
}

QPushButton* ListField::getPreview() {
    return ui->preview;
}

ListData* ListField::getData() {
    return data;
}

void ListField::setData(ListData* data) {
    this->data = data;
}

void ListField::sendRemove() {
    emit removeField(this);
}

void ListField::updateUI()
{
    // clear the options
    ui->comboBox->clear();
    // add the options
    list<string> dataOptions = data->toList();
    for(string s : dataOptions)
    {
        ui->comboBox->addItem(QString::fromStdString(s));
    }
}
