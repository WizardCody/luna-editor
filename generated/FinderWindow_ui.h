/********************************************************************************
** Form generated from reading UI file 'FinderWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef FINDERWINDOW_UI_H
#define FINDERWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FinderWindow
{
public:
    QGridLayout *mFinderLayout;
    QGroupBox *mTextGroupBox;
    QFormLayout *mTextGroupLayout;
    QLineEdit *mTextLineEdit;
    QFrame *mTextFrame1;
    QHBoxLayout *mTextFrameLayout1;
    QRadioButton *mTextPrevious;
    QRadioButton *mTextNext;
    QFrame *mTextFrame2;
    QHBoxLayout *mTextFrameLayout2;
    QCheckBox *mTextCaseSensitive;
    QFrame *mButtonFrame;
    QVBoxLayout *mButtonLayout;
    QPushButton *mButtonFind;
    QPushButton *mButtonCancel;

    void setupUi(QDialog *FinderWindow)
    {
        if (FinderWindow->objectName().isEmpty())
            FinderWindow->setObjectName(QString::fromUtf8("FinderWindow"));
        FinderWindow->resize(380, 100);
        FinderWindow->setMinimumSize(QSize(0, 100));
        FinderWindow->setMaximumSize(QSize(1000, 100));
        mFinderLayout = new QGridLayout(FinderWindow);
        mFinderLayout->setObjectName(QString::fromUtf8("mFinderLayout"));
        mTextGroupBox = new QGroupBox(FinderWindow);
        mTextGroupBox->setObjectName(QString::fromUtf8("mTextGroupBox"));
        mTextGroupLayout = new QFormLayout(mTextGroupBox);
        mTextGroupLayout->setObjectName(QString::fromUtf8("mTextGroupLayout"));
        mTextGroupLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        mTextGroupLayout->setContentsMargins(9, -1, -1, -1);
        mTextLineEdit = new QLineEdit(mTextGroupBox);
        mTextLineEdit->setObjectName(QString::fromUtf8("mTextLineEdit"));

        mTextGroupLayout->setWidget(0, QFormLayout::SpanningRole, mTextLineEdit);

        mTextFrame1 = new QFrame(mTextGroupBox);
        mTextFrame1->setObjectName(QString::fromUtf8("mTextFrame1"));
        mTextFrame1->setFrameShape(QFrame::StyledPanel);
        mTextFrame1->setFrameShadow(QFrame::Raised);
        mTextFrameLayout1 = new QHBoxLayout(mTextFrame1);
        mTextFrameLayout1->setSpacing(0);
        mTextFrameLayout1->setContentsMargins(0, 0, 0, 0);
        mTextFrameLayout1->setObjectName(QString::fromUtf8("mTextFrameLayout1"));
        mTextPrevious = new QRadioButton(mTextFrame1);
        mTextPrevious->setObjectName(QString::fromUtf8("mTextPrevious"));

        mTextFrameLayout1->addWidget(mTextPrevious);

        mTextNext = new QRadioButton(mTextFrame1);
        mTextNext->setObjectName(QString::fromUtf8("mTextNext"));

        mTextFrameLayout1->addWidget(mTextNext);


        mTextGroupLayout->setWidget(1, QFormLayout::LabelRole, mTextFrame1);

        mTextFrame2 = new QFrame(mTextGroupBox);
        mTextFrame2->setObjectName(QString::fromUtf8("mTextFrame2"));
        mTextFrame2->setFrameShape(QFrame::StyledPanel);
        mTextFrame2->setFrameShadow(QFrame::Raised);
        mTextFrameLayout2 = new QHBoxLayout(mTextFrame2);
        mTextFrameLayout2->setContentsMargins(0, 0, 0, 0);
        mTextFrameLayout2->setObjectName(QString::fromUtf8("mTextFrameLayout2"));
        mTextCaseSensitive = new QCheckBox(mTextFrame2);
        mTextCaseSensitive->setObjectName(QString::fromUtf8("mTextCaseSensitive"));
        mTextCaseSensitive->setLayoutDirection(Qt::RightToLeft);

        mTextFrameLayout2->addWidget(mTextCaseSensitive);


        mTextGroupLayout->setWidget(1, QFormLayout::FieldRole, mTextFrame2);


        mFinderLayout->addWidget(mTextGroupBox, 0, 5, 1, 1);

        mButtonFrame = new QFrame(FinderWindow);
        mButtonFrame->setObjectName(QString::fromUtf8("mButtonFrame"));
        mButtonFrame->setFrameShape(QFrame::StyledPanel);
        mButtonFrame->setFrameShadow(QFrame::Raised);
        mButtonLayout = new QVBoxLayout(mButtonFrame);
        mButtonLayout->setObjectName(QString::fromUtf8("mButtonLayout"));
        mButtonLayout->setContentsMargins(0, 10, 0, 10);
        mButtonFind = new QPushButton(mButtonFrame);
        mButtonFind->setObjectName(QString::fromUtf8("mButtonFind"));

        mButtonLayout->addWidget(mButtonFind);

        mButtonCancel = new QPushButton(mButtonFrame);
        mButtonCancel->setObjectName(QString::fromUtf8("mButtonCancel"));

        mButtonLayout->addWidget(mButtonCancel);


        mFinderLayout->addWidget(mButtonFrame, 0, 6, 1, 1);


        retranslateUi(FinderWindow);

        QMetaObject::connectSlotsByName(FinderWindow);
    } // setupUi

    void retranslateUi(QDialog *FinderWindow)
    {
        FinderWindow->setWindowTitle(QApplication::translate("FinderWindow", "Finder", 0, QApplication::UnicodeUTF8));
        mTextGroupBox->setTitle(QApplication::translate("FinderWindow", "Text", 0, QApplication::UnicodeUTF8));
        mTextPrevious->setText(QApplication::translate("FinderWindow", "Previous", 0, QApplication::UnicodeUTF8));
        mTextNext->setText(QApplication::translate("FinderWindow", "Next", 0, QApplication::UnicodeUTF8));
        mTextCaseSensitive->setText(QApplication::translate("FinderWindow", "Case Sensitive", 0, QApplication::UnicodeUTF8));
        mButtonFind->setText(QApplication::translate("FinderWindow", "Find", 0, QApplication::UnicodeUTF8));
        mButtonCancel->setText(QApplication::translate("FinderWindow", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FinderWindow: public Ui_FinderWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // FINDERWINDOW_UI_H
