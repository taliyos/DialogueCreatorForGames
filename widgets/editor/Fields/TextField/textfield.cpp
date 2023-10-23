#include "textfield.h"
#include "ui_textfield.h"
#include <QWebEngineView>
TextField::TextField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextField)
{
    ui->setupUi(this);
    connect(ui->preview, &QPushButton::clicked, this, &TextField::exportToBrowser);
}

QString TextField::generateHtml(const QString& content) {
    QString base64Image;

    QString fullHtml;
    fullHtml += "<!DOCTYPE html>";
    fullHtml += "<html><head><title>Dialogue Preview</title>";
    fullHtml += R"(<script src="https://code.jquery.com/jquery-3.6.0.min.js"></script>)";
    fullHtml += R"(
    <script>
//    $(document).ready(function() {
//        $('.dialogue-box').hide().fadeIn(1000);
//        $('.dialogue-box').click(function() {
//            $(this).fadeOut(1000);
//        });
//    });
    </script>
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


void TextField::exportToBrowser() {
    QString content = ui->textField->text();
    emit previewRequested(content);
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
