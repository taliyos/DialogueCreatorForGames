#include "inputlistfield.h"
#include "ui_inputlistfield.h"

InputListField::InputListField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputListField)
{
    ui->setupUi(this);
    connect(ui->remove, &QAbstractButton::clicked, this, &InputListField::sendRemoveRequest);
    connect(ui->preview, &QPushButton::clicked, this, &InputListField::exportToBrowser);
    //connect(editorTools, &EditorTools::characterEffectRequested, this, &TextField::applyCharacterEffect);

    // on index selection, request an update
    connect(ui->index, &QComboBox::currentIndexChanged, this, &InputListField::setIndex);

    // make the options non-selectable
    getListWidget()->setEnabled(false);
}

// TODO: THIS NEEDS TO BE CHANGED. NOT SURE WHAT WE WANT IN THE HTML
QString InputListField::generateHtml(const QString& content, const QString& content2, InputListData* textData) {

    QString newContent = QString::fromStdString("");
    QList<QString> options = content.split('\n');
    newContent = content;

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
            background-size: contain;
            background-repeat: no-repeat;
            background-position: center center;
            font-family: Arial, sans-serif;
            height: 100vh;
            margin: 0;  // Ensure no default margins
            overflow: hidden; // Hide any overflow content
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
            background: #ECEFF1;
            border-radius: 15px;
            padding: 1rem;
            width: 390px;
            height: 160px;
            box-shadow: 10px 10px rgba(0,0,0,0.2);
            font-size: 24px;
            margin-top: 10px;
        }

        .dialogue-list {
            background: #ECEFF1;
            border-radius: 4px;
            padding: 1rem;
            width: 200px;
            height: auto;
            box-shadow: 5px 5px rgba(0,0,0,0.2);
            font-size: 18px;
            margin-top: 10px;

            display: flex;
            flex-direction: column;
            gap: 8px;
        }

        .dialogue-item {
            padding: 6px;
            background: white;
            border-radius: 4px;
        }

        .dialogue-item:hover {
            background: #a3a3a3;
            cursor: pointer;
        }

        .character-box {
            background: #ECEFF1;
            border-radius: 15px;
            padding: 1rem;
            width: 300px; /* Adjust width as necessary */
            height: 20px; /* Adjust height as necessary */
            box-shadow: 10px 10px rgba(0,0,0,0.2);
            font-size: 24px;
            z-index: 2;
        }


    </style>
    )";

    // ... (The rest of your styles remain the same)

    fullHtml += "</head><body>";
    fullHtml += R"(<div class='dialogue-container'>)"; // This wraps both boxes
    fullHtml += R"(<div class='dialogue-list'>)";
    for (int i = 0; i < options.count() - 1; i++) {
            fullHtml += R"(<div class='dialogue-item'>)" + options[i] + R"(</div>)";
    }
    fullHtml += R"(</div></div>)"; // Close .dialogue-container
    fullHtml += "</body></html>";

    return fullHtml;
}


void InputListField::exportToBrowser() {
    QString content = "";
    list<string> dataOptions = data->toList();
    for(string s : dataOptions)
    {
        content += (QString::fromStdString(s + "\n"));
    }
    emit previewRequested(content, nullptr, data);
}

InputListField::~InputListField()
{
    delete ui;
}

QListWidget* InputListField::getListWidget() {
    return ui->listWidget;
}

QPushButton* InputListField::getPreview() {
    return ui->preview;
}

InputListData* InputListField::getData() {
    return data;
}

void InputListField::setData(InputListData* data) {
    this->data = data;
    qDebug() << "InputListField: Called setData(), settings? " << (data->getSettings() != nullptr);
    // listen to listsettings for updates
    connect(data->getSettings(), &InputListSettings::updateField, this, &InputListField::updateDataAndUI);
    // have listsettings listen for requests
    connect(this, &InputListField::updateRequested, data->getSettings(), &InputListSettings::sendUpdateField);
    // call to update
    sendUpdateRequest();
}

void InputListField::setIndex(int index)
{
    qDebug() << "InputListField: Calling Set Index, old: " << this->getData()->getIndex() << ", new: " << index;
    this->data->setIndex(index);
    // call to update
    sendUpdateRequest();
}

void InputListField::sendRemoveRequest() {
    emit removeRequested(this);
}

void InputListField::sendUpdateRequest() {
    emit updateRequested(data->getIndex());
}

void InputListField::updateDataAndUI(int index, list<int> indices, list<string> options)
{
    qDebug() << "InputListField: trying to update. index:" << data->getIndex()<<  ", target index: " << index;
    if (data->getIndex() == index)
    {
        qDebug() << "InputListField: Index matched, updating with " << options;

        // temporarily disconnect
        disconnect(ui->index, &QComboBox::currentIndexChanged, this, &InputListField::setIndex);

        // clear the index options
        ui->index->clear();

        // add the index options
        for(int i : indices)
        {
            ui->index->addItem(QString::fromStdString(std::to_string(i)));
        }

        // select the right index
        ui->index->setCurrentIndex(index);

        // update the data
        data->setTextFromList(options);

        // clear the options
        getListWidget()->clear();

        // add the options
        list<string> dataOptions = data->toList();
        qDebug() << "ListField: Updating UI with: " << dataOptions;
        for(string s : dataOptions)
        {
            getListWidget()->addItem(QString::fromStdString(s));
        }
        // reconnect
        connect(ui->index, &QComboBox::currentIndexChanged, this, &InputListField::setIndex);
    }
}
