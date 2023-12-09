#include <QWidget>
#include <algorithm>

#include "fielddata.h"
#include "../ConnectionData/connectionData.h"
#include "widgets/editor/Fields/CharacterField/characterfield.h"
#include "widgets/editor/Fields/TextField/textfield.h"


/// <summary>A class that holds the raw data for text fields.</summary>
FieldData::FieldData(QWidget* ui, ConnectionData* fromConnection, ConnectionData* toConnection)
{
    this->ui = ui;
    this->fromConnection = fromConnection;
    this->toConnection = toConnection;

    this->text = string("");
    this->textToEffects = map<pair<int, int>, list<int>>();
    this->fieldEffects = list<int>();
}

FieldData::~FieldData() {
    // Delete the UI Widget before removing the data
    if (ui != nullptr) {
        delete ui;
    }
}

void FieldData::setFieldType(FieldTypes type) {
    qInfo("set field type to: " + type);
    fieldType = type;
}

FieldTypes FieldData::getFieldType() const { return fieldType; }

QString FieldData::generateHtml(const QString& content, const QString& content2, FieldData* data) {
    QString newContent = content;
    // 1 = wobble
    if (data->hasFieldEffect(1))
        newContent = "<effect type=\"wobble\">" + content + "</effect>";
    // 2 = enlarge
    else if (data->hasFieldEffect(2))
        newContent = "<effect type=\"enlarge\">" + content + "</effect>";
    // 3 = speedUp
    else if (data->hasFieldEffect(3))
        newContent = "<effect type=\"speedUp\">" + content + "</effect>";
    // 4 = bold
    else if (data->hasFieldEffect(4))
        newContent = "<effect type=\"bold\">" + content + "</effect>";
    // 5 = typed
    else if (data->hasFieldEffect(5))
        newContent = "<effect type=\"typed\">" + content + "</effect>";

    if (newContent == content)
    {
        const map<pair<int,int>, list<int>> textEffects = data->getTextEffects();
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


void FieldData::setText(string newText)
{
    text = newText;
}
const string FieldData::getText()
{
    return text;
}
const map<pair<int, int>, list<int>> FieldData::getTextEffects()
{
    return this->textToEffects;
}
const list<int> FieldData::getFieldEffects()
{
    return this->fieldEffects;
}
bool FieldData::hasFieldEffect(int tag)
{
    return find(fieldEffects.begin(), fieldEffects.end(), tag) != fieldEffects.end();
}
void FieldData::applyFieldEffect(int tag)
{
    fieldEffects.push_back(tag);
}
void FieldData::removeFieldEffect(int tag)
{
    fieldEffects.remove(tag);
}
void FieldData::addOrRemoveFieldEffect(int tag)
{
    if (hasFieldEffect(tag))
        removeFieldEffect(tag);
    else
    {
        // Since only one field effect can be active, remove the previous effects here
        fieldEffects = list<int>();
        applyFieldEffect(tag);
    }
}

// TODO: FINISH THIS ****
/// <summary>
/// Looks to see if a given range between index1 and index2 has a text effect with a given tag
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     none
/// returns:
///     if the given range has the text effect applied somewhere within
/// </summary>
bool FieldData::hasTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    qDebug() << "test";

    // Check to see if the range is valid
    if (index1 >= index2) //|| index1 >= text.length()|| index2 >= text.length())
        return false;
    qDebug() << "test2";
    // Look for a mapping of the text fields that covers this range
    for(map<pair<int,int>,list<int>>::iterator it = textToEffects.begin(); it != textToEffects.end(); it++)
    {
        // Check to see if this range contains the effect
//        if (it->first.first <= index1 && it->first.second <= index2)
//            return find(it->second.begin(), it->second.end(), tag) != it->second.end();

        // Check to see if this range contains ANY effect. If so, return true
        qDebug() << "in loop";
        qDebug() << index1 << index2 << it->first.first << it->first.second;
        if ((index1 >= it->first.first && index1 < it->first.second) || (index2 >= it->first.first && index2 < it->first.second) )
            return true;
    }
    // Return false if it isn't found

    return false;
}

/// <summary>
/// applies a text effect to the given substring in the text.
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::applyTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    textToEffects[key] = {tag};
}

/// <summary>
/// removes a text effect from the given substring in the text
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::removeTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    // remember: map<pair<int, int>, list<int>>*
    pair<int, int> key = pair<int, int>(index1, index2);
    textToEffects.erase(key);
}

/// <summary>
/// applies the given text effect to a substring if it is not applied within.
/// otherwise, removes the effect.
/// arguments:
///     index1 : starting index inclusive
///     index2 : ending index inclusive
///     tag : the tag for the effect
/// modifies:
///     textToEffects
/// returns:
///     none
/// </summary>
void FieldData::addOrRemoveTextEffect(unsigned int index1, unsigned int index2, int tag)
{
    if (hasTextEffect(index1, index2, tag))
        removeTextEffect(index1, index2, tag);
    else
        applyTextEffect(index1, index2, tag);
}

const ConnectionData* FieldData::replaceFromConnection(ConnectionData* connection) {
    fromConnection = connection;
    return nullptr;
}

const ConnectionData* FieldData::replaceToConnection(ConnectionData* connection) {
    ConnectionData* previous = toConnection;
    toConnection = connection;
    return previous;
}

ConnectionData* FieldData::getToConnection() {
    return toConnection;
}

ConnectionData* FieldData::getFromConnection() {
    return fromConnection;
}

QWidget* FieldData::getUi() {
    return ui;
}

void FieldData::removeAll() {
    if (toConnection != nullptr) {
        toConnection->removeAll();
    }

    delete this;
}

const nlohmann::json FieldData::toJson()
{
    if (fieldType == List || fieldType == UserPrompt || fieldType == UserList)
    {
        nlohmann::json j;
        j["type"] = fieldType;
        return j;
    }
    nlohmann::json j;
    j["text"] = this->text;
    j["fieldEffects"] = this->fieldEffects;
    j["textEffects"] = this->textToEffects;
    TextField* field = reinterpret_cast <TextField*>(getUi());
    j["soundFile"] = field->getSoundFile().toStdString();
    CharacterField* characterField = field->getCharacterField();
    j["character"] = "";
    if (characterField)
        j["character"] = characterField->getText().toStdString();
    j["type"] = fieldType;

    return j;
}

void FieldData::fromJson(nlohmann::json j)
{
    this->fieldType = j["type"];
    if (fieldType == List || fieldType == UserPrompt || fieldType == UserList)
        return;
    this->text = j["text"];
    list<int> fieldEffects = j["fieldEffects"];
    this->fieldEffects = fieldEffects;
    this->textToEffects =  j["textEffects"];
    TextField* field = reinterpret_cast <TextField*>(getUi());
    if (QString::fromStdString(j["character"]).isEmpty())
        return;

    CharacterField* characterField = field->getCharacterField();
    if (!characterField)
    {
        field->addCharacterWidget();
        characterField = field->getCharacterField();
    }
    characterField->setText(QString::fromStdString(j["character"]));
}
