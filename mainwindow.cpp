#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent) {
    password_label = new QLabel(tr("Password Length: "));
    password_length = new QSpinBox();

    numbers_label = new QLabel(tr("Include Numbers: "));
    numbers_enabled = new QCheckBox();

    symbols_label = new QLabel(tr("Include Symbols: "));
    symbols_enabled = new QCheckBox();

    upper_label = new QLabel(tr("Include Uppercase: "));
    upper_enabled = new QCheckBox();

    lower_label = new QLabel(tr("Include Lowercase: "));
    lower_enabled = new QCheckBox();

    begin_with_label = new QLabel(tr("Begin With: "));
    begin_with_text = new QLineEdit();

    quantity_label = new QLabel(tr("Quantity: "));
    quantity = new QSpinBox();

    generate_button = new QPushButton(tr("Generate Passwords"));

    password_list = new QListWidget();
    copy_button = new QPushButton(tr("Copy to Clipboard"));
    save_button = new QPushButton(tr("Save as"));

    QGridLayout* mainLayout = new QGridLayout;

    mainLayout->addWidget(password_label, 0, 0);
    mainLayout->addWidget(password_length, 0, 1);

    mainLayout->addWidget(numbers_label, 1, 0);
    mainLayout->addWidget(numbers_enabled, 1, 1);

    mainLayout->addWidget(symbols_label, 2, 0);
    mainLayout->addWidget(symbols_enabled, 2, 1);

    mainLayout->addWidget(upper_label, 3, 0);
    mainLayout->addWidget(upper_enabled, 3, 1);

    mainLayout->addWidget(lower_label, 4, 0);
    mainLayout->addWidget(lower_enabled, 4, 1);

    mainLayout->addWidget(begin_with_label, 5, 0);
    mainLayout->addWidget(begin_with_text, 5, 1);

    mainLayout->addWidget(quantity_label, 6, 0);
    mainLayout->addWidget(quantity, 6, 1);

    mainLayout->addWidget(generate_button, 7, 0, 1, 2);

    mainLayout->addWidget(copy_button, 0, 2);
    mainLayout->addWidget(save_button, 0, 3);
    mainLayout->addWidget(password_list, 1, 2, 7, 2);
    setLayout(mainLayout);


    password_length->setMinimum(1);
    password_length->setMaximum(999999);
    quantity->setMinimum(1);
    quantity->setMaximum(999999);

    connect(generate_button, SIGNAL(released()), this, SLOT(generatePasswords()));
    connect(copy_button, SIGNAL(released()), this, SLOT(copyToClipboard()));
    connect(save_button, SIGNAL(released()), this, SLOT(savePasswords()));
}

MainWindow::~MainWindow() {
    delete password_length;
}

void MainWindow::generatePasswords() {
    // clear out old passwords if they exist
    password_list->clear();

    int length = password_length->value();
    bool num = numbers_enabled->isChecked();
    bool symbol = symbols_enabled->isChecked();
    bool upper = upper_enabled->isChecked();
    bool lower = lower_enabled->isChecked();
    std::string begin = begin_with_text->text().toStdString();

    int quant = quantity->value();
    for (int i = 0; i < quant; i++) {
        std::string password = generator(length, num, symbol, upper, lower, begin);
        QString q_password = QString::fromStdString(password);
        password_list->addItem(q_password);
    }
}

void MainWindow::copyToClipboard() {
    QStringList passes;
    for (int i = 0; i < password_list->count(); i++) {
        QListWidgetItem* password = password_list->item(i);
        passes << password->text() << "\n";
    }
    QApplication::clipboard()->setText(passes.join(""));
}

void MainWindow::savePasswords() {
    QStringList passes;
    for (int i = 0; i < password_list->count(); i++) {
        passes << password_list->item(i)->text() << "\n";
    }

    QString defaultFilter("Text Files(*.txt)");
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Generated Passwords"), "", tr("Text Files(*.txt);;All Files(*.*)"), &defaultFilter);

    if (fileName.isEmpty()) {
        return;
    } else {
        QFile password_file(fileName);
        if (!password_file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"), password_file.errorString());
            return;
        }
        QTextStream out(&password_file);
        QString q_passes = passes.join("");
        // const char* raw_passes = q_passes.toStdString().c_str();

        out << q_passes;
    }
}
