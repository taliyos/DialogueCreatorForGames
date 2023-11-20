#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include "data/Fields/MainFields/text/textdata.h"
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QWebEngineView>
#include <QMediaPlayer>
#include <QAudioOutput>

class CharacterField;
namespace Ui {
class TextField;
}

class TextField : public QWidget
{
    Q_OBJECT

public:
    explicit TextField(QWidget *parent = nullptr);
    ~TextField();
    static QString generateHtml(const QString& content, const QString& content2, TextData* textData);
    void exportToBrowser();
    void applyCharacterEffect(int effectNumber);
    void setView(QWebEngineView* v);

    QLineEdit* getTextField();
    CharacterField* getCharacterField();
    QPushButton* getPreview();

    TextData* getData();
    void setData(TextData* data);

    /**
     * Toggles the character field when the button is clicked
     */
    void onCharacterClicked();

    /**
     * Adds a character text field above the TextField
     */
    void addCharacterWidget();

    /**
     * Removes the character text field
     */
    void removeCharacterWidget();

    /**
     * Plays the sound file located at soundFile
     */
    void playSound();

    /**
     * Opens a file dialog where the user can select a sound clip to
     * attach to this text field. Only .mp3 files are supported.
     */
    void setSound();

    /**
     * @return The file path to the sound file.
     */
    QString getSoundFile();

signals:
    void previewRequested(const QString& content,const QString& content2, TextData* textData);
    void removeField(TextField* field);


private:
    Ui::TextField *ui;
    TextData* data = nullptr;
    bool characterFieldAdded = false;
    CharacterField* characterField = nullptr;
    void sendRemove();
    QString soundFile = "";
    QMediaPlayer* player = new QMediaPlayer();
    QAudioOutput* audio = new QAudioOutput();
};

#endif // TEXTFIELD_H
