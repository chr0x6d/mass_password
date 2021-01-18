#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>

#include <QWidget>
#include "generator.h"

class QSpinBox;
class QCheckBox;
class QListWidget;
class QPushButton;
class QLineEdit;
class QLabel;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void generatePasswords();
    void copyToClipboard();
    void savePasswords();

private:
    QLabel* password_label;
    QSpinBox* password_length;

    QLabel* numbers_label;
    QCheckBox* numbers_enabled;

    QLabel* symbols_label;
    QCheckBox* symbols_enabled;

    QLabel* upper_label;
    QCheckBox* upper_enabled;

    QLabel* lower_label;
    QCheckBox* lower_enabled;

    QLabel* begin_with_label;
    QLineEdit* begin_with_text;

    QLabel* quantity_label;
    QSpinBox* quantity;

    QPushButton* generate_button;

    QListWidget* password_list;
    QPushButton* copy_button;
    QPushButton* save_button;
};


#endif
