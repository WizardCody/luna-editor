/********************************************************************************
** Form generated from reading UI file 'OptionsWindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef OPTIONSWINDOW_UI_H
#define OPTIONSWINDOW_UI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OptionsWindow
{
public:
    QGridLayout *mOptionsLayout;
    QFrame *mButtonFrame;
    QHBoxLayout *mButtonFrameLayout;
    QSpacerItem *mHorizontalSpacer;
    QPushButton *mAcceptButton;
    QPushButton *mRejectButton;
    QPushButton *mApplyButton;
    QTabWidget *mTabWidget;
    QWidget *mTab01;
    QGridLayout *mTab01Layout;
    QGroupBox *mSourceGroup;
    QGridLayout *mSourceGroupLayout;
    QLineEdit *mSourceLineEdit;
    QToolButton *mSourceButton1;
    QToolButton *mSourceButton2;
    QToolButton *mSourceButton3;
    QGroupBox *mOptionsGroup;
    QGridLayout *mOptionsGroupLayout;
    QLabel *mMaxVisibleLabel;
    QSpinBox *mMaxVisibleBox;
    QLabel *mMinCharLabel;
    QSpinBox *mMinCharBox;
    QLabel *mTypingLabel;
    QLabel *mSortingLabel;
    QComboBox *mTypingComboBox;
    QComboBox *mSortingComboBox;
    QWidget *mTab03;
    QGridLayout *gridLayout;
    QSpacerItem *mVerticalSpacer2;
    QGroupBox *mCodeGroup;
    QGridLayout *mCodeGroupLayout;
    QLabel *mTabSizeLabel;
    QSpinBox *mTabSizeBox;
    QLabel *mGuideLineLabel;
    QSpinBox *mGuideLineBox;
    QWidget *mTab02;
    QGridLayout *mTab02Layout;
    QGroupBox *mApplicationGroup;
    QGridLayout *mApplicationLayout;
    QLabel *mInstanceLabel;
    QComboBox *mInstanceComboBox;
    QLabel *mLanguageLabel;
    QComboBox *mLanguageComboBox;
    QSpacerItem *mVerticalSpacer;

    void setupUi(QDialog *OptionsWindow)
    {
        if (OptionsWindow->objectName().isEmpty())
            OptionsWindow->setObjectName(QString::fromUtf8("OptionsWindow"));
        OptionsWindow->resize(450, 329);
        OptionsWindow->setMinimumSize(QSize(0, 329));
        OptionsWindow->setMaximumSize(QSize(1000, 329));
        mOptionsLayout = new QGridLayout(OptionsWindow);
        mOptionsLayout->setObjectName(QString::fromUtf8("mOptionsLayout"));
        mButtonFrame = new QFrame(OptionsWindow);
        mButtonFrame->setObjectName(QString::fromUtf8("mButtonFrame"));
        mButtonFrame->setFrameShape(QFrame::StyledPanel);
        mButtonFrame->setFrameShadow(QFrame::Raised);
        mButtonFrameLayout = new QHBoxLayout(mButtonFrame);
        mButtonFrameLayout->setSpacing(0);
        mButtonFrameLayout->setContentsMargins(0, 0, 0, 0);
        mButtonFrameLayout->setObjectName(QString::fromUtf8("mButtonFrameLayout"));
        mHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        mButtonFrameLayout->addItem(mHorizontalSpacer);

        mAcceptButton = new QPushButton(mButtonFrame);
        mAcceptButton->setObjectName(QString::fromUtf8("mAcceptButton"));

        mButtonFrameLayout->addWidget(mAcceptButton);

        mRejectButton = new QPushButton(mButtonFrame);
        mRejectButton->setObjectName(QString::fromUtf8("mRejectButton"));

        mButtonFrameLayout->addWidget(mRejectButton);

        mApplyButton = new QPushButton(mButtonFrame);
        mApplyButton->setObjectName(QString::fromUtf8("mApplyButton"));

        mButtonFrameLayout->addWidget(mApplyButton);


        mOptionsLayout->addWidget(mButtonFrame, 2, 0, 1, 1);

        mTabWidget = new QTabWidget(OptionsWindow);
        mTabWidget->setObjectName(QString::fromUtf8("mTabWidget"));
        mTab01 = new QWidget();
        mTab01->setObjectName(QString::fromUtf8("mTab01"));
        mTab01Layout = new QGridLayout(mTab01);
        mTab01Layout->setObjectName(QString::fromUtf8("mTab01Layout"));
        mSourceGroup = new QGroupBox(mTab01);
        mSourceGroup->setObjectName(QString::fromUtf8("mSourceGroup"));
        mSourceGroupLayout = new QGridLayout(mSourceGroup);
        mSourceGroupLayout->setObjectName(QString::fromUtf8("mSourceGroupLayout"));
        mSourceLineEdit = new QLineEdit(mSourceGroup);
        mSourceLineEdit->setObjectName(QString::fromUtf8("mSourceLineEdit"));

        mSourceGroupLayout->addWidget(mSourceLineEdit, 0, 0, 1, 1);

        mSourceButton1 = new QToolButton(mSourceGroup);
        mSourceButton1->setObjectName(QString::fromUtf8("mSourceButton1"));

        mSourceGroupLayout->addWidget(mSourceButton1, 0, 1, 1, 1);

        mSourceButton2 = new QToolButton(mSourceGroup);
        mSourceButton2->setObjectName(QString::fromUtf8("mSourceButton2"));

        mSourceGroupLayout->addWidget(mSourceButton2, 0, 2, 1, 1);

        mSourceButton3 = new QToolButton(mSourceGroup);
        mSourceButton3->setObjectName(QString::fromUtf8("mSourceButton3"));

        mSourceGroupLayout->addWidget(mSourceButton3, 0, 3, 1, 1);


        mTab01Layout->addWidget(mSourceGroup, 0, 0, 1, 1);

        mOptionsGroup = new QGroupBox(mTab01);
        mOptionsGroup->setObjectName(QString::fromUtf8("mOptionsGroup"));
        mOptionsGroupLayout = new QGridLayout(mOptionsGroup);
        mOptionsGroupLayout->setObjectName(QString::fromUtf8("mOptionsGroupLayout"));
        mMaxVisibleLabel = new QLabel(mOptionsGroup);
        mMaxVisibleLabel->setObjectName(QString::fromUtf8("mMaxVisibleLabel"));

        mOptionsGroupLayout->addWidget(mMaxVisibleLabel, 0, 0, 1, 1);

        mMaxVisibleBox = new QSpinBox(mOptionsGroup);
        mMaxVisibleBox->setObjectName(QString::fromUtf8("mMaxVisibleBox"));

        mOptionsGroupLayout->addWidget(mMaxVisibleBox, 0, 1, 1, 1);

        mMinCharLabel = new QLabel(mOptionsGroup);
        mMinCharLabel->setObjectName(QString::fromUtf8("mMinCharLabel"));

        mOptionsGroupLayout->addWidget(mMinCharLabel, 1, 0, 1, 1);

        mMinCharBox = new QSpinBox(mOptionsGroup);
        mMinCharBox->setObjectName(QString::fromUtf8("mMinCharBox"));

        mOptionsGroupLayout->addWidget(mMinCharBox, 1, 1, 1, 1);

        mTypingLabel = new QLabel(mOptionsGroup);
        mTypingLabel->setObjectName(QString::fromUtf8("mTypingLabel"));

        mOptionsGroupLayout->addWidget(mTypingLabel, 2, 0, 1, 1);

        mSortingLabel = new QLabel(mOptionsGroup);
        mSortingLabel->setObjectName(QString::fromUtf8("mSortingLabel"));

        mOptionsGroupLayout->addWidget(mSortingLabel, 3, 0, 1, 1);

        mTypingComboBox = new QComboBox(mOptionsGroup);
        mTypingComboBox->setObjectName(QString::fromUtf8("mTypingComboBox"));

        mOptionsGroupLayout->addWidget(mTypingComboBox, 2, 1, 1, 1);

        mSortingComboBox = new QComboBox(mOptionsGroup);
        mSortingComboBox->setObjectName(QString::fromUtf8("mSortingComboBox"));

        mOptionsGroupLayout->addWidget(mSortingComboBox, 3, 1, 1, 1);


        mTab01Layout->addWidget(mOptionsGroup, 1, 0, 1, 1);

        mTabWidget->addTab(mTab01, QString());
        mTab03 = new QWidget();
        mTab03->setObjectName(QString::fromUtf8("mTab03"));
        gridLayout = new QGridLayout(mTab03);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mVerticalSpacer2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(mVerticalSpacer2, 1, 0, 1, 1);

        mCodeGroup = new QGroupBox(mTab03);
        mCodeGroup->setObjectName(QString::fromUtf8("mCodeGroup"));
        mCodeGroupLayout = new QGridLayout(mCodeGroup);
        mCodeGroupLayout->setObjectName(QString::fromUtf8("mCodeGroupLayout"));
        mTabSizeLabel = new QLabel(mCodeGroup);
        mTabSizeLabel->setObjectName(QString::fromUtf8("mTabSizeLabel"));

        mCodeGroupLayout->addWidget(mTabSizeLabel, 0, 0, 1, 1);

        mTabSizeBox = new QSpinBox(mCodeGroup);
        mTabSizeBox->setObjectName(QString::fromUtf8("mTabSizeBox"));
        mTabSizeBox->setMinimum(1);
        mTabSizeBox->setMaximum(100);
        mTabSizeBox->setSingleStep(1);
        mTabSizeBox->setValue(5);

        mCodeGroupLayout->addWidget(mTabSizeBox, 0, 1, 1, 1);

        mGuideLineLabel = new QLabel(mCodeGroup);
        mGuideLineLabel->setObjectName(QString::fromUtf8("mGuideLineLabel"));

        mCodeGroupLayout->addWidget(mGuideLineLabel, 1, 0, 1, 1);

        mGuideLineBox = new QSpinBox(mCodeGroup);
        mGuideLineBox->setObjectName(QString::fromUtf8("mGuideLineBox"));
        mGuideLineBox->setMinimum(0);
        mGuideLineBox->setMaximum(1000);
        mGuideLineBox->setValue(100);

        mCodeGroupLayout->addWidget(mGuideLineBox, 1, 1, 1, 1);


        gridLayout->addWidget(mCodeGroup, 0, 0, 1, 1);

        mTabWidget->addTab(mTab03, QString());
        mTab02 = new QWidget();
        mTab02->setObjectName(QString::fromUtf8("mTab02"));
        mTab02Layout = new QGridLayout(mTab02);
        mTab02Layout->setObjectName(QString::fromUtf8("mTab02Layout"));
        mApplicationGroup = new QGroupBox(mTab02);
        mApplicationGroup->setObjectName(QString::fromUtf8("mApplicationGroup"));
        mApplicationLayout = new QGridLayout(mApplicationGroup);
        mApplicationLayout->setObjectName(QString::fromUtf8("mApplicationLayout"));
        mInstanceLabel = new QLabel(mApplicationGroup);
        mInstanceLabel->setObjectName(QString::fromUtf8("mInstanceLabel"));

        mApplicationLayout->addWidget(mInstanceLabel, 0, 0, 1, 1);

        mInstanceComboBox = new QComboBox(mApplicationGroup);
        mInstanceComboBox->setObjectName(QString::fromUtf8("mInstanceComboBox"));

        mApplicationLayout->addWidget(mInstanceComboBox, 0, 1, 1, 1);

        mLanguageLabel = new QLabel(mApplicationGroup);
        mLanguageLabel->setObjectName(QString::fromUtf8("mLanguageLabel"));

        mApplicationLayout->addWidget(mLanguageLabel, 1, 0, 1, 1);

        mLanguageComboBox = new QComboBox(mApplicationGroup);
        mLanguageComboBox->setObjectName(QString::fromUtf8("mLanguageComboBox"));

        mApplicationLayout->addWidget(mLanguageComboBox, 1, 1, 1, 1);


        mTab02Layout->addWidget(mApplicationGroup, 0, 0, 1, 1);

        mVerticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        mTab02Layout->addItem(mVerticalSpacer, 1, 0, 1, 1);

        mTabWidget->addTab(mTab02, QString());

        mOptionsLayout->addWidget(mTabWidget, 0, 0, 1, 1);


        retranslateUi(OptionsWindow);

        mTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OptionsWindow);
    } // setupUi

    void retranslateUi(QDialog *OptionsWindow)
    {
        OptionsWindow->setWindowTitle(QApplication::translate("OptionsWindow", "Configuration", 0, QApplication::UnicodeUTF8));
        mAcceptButton->setText(QApplication::translate("OptionsWindow", "OK", 0, QApplication::UnicodeUTF8));
        mRejectButton->setText(QApplication::translate("OptionsWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        mApplyButton->setText(QApplication::translate("OptionsWindow", "Apply", 0, QApplication::UnicodeUTF8));
        mSourceGroup->setTitle(QApplication::translate("OptionsWindow", "Source", 0, QApplication::UnicodeUTF8));
        mSourceButton1->setText(QApplication::translate("OptionsWindow", "...", 0, QApplication::UnicodeUTF8));
        mSourceButton2->setText(QApplication::translate("OptionsWindow", "parse", 0, QApplication::UnicodeUTF8));
        mSourceButton3->setText(QApplication::translate("OptionsWindow", "clean", 0, QApplication::UnicodeUTF8));
        mOptionsGroup->setTitle(QApplication::translate("OptionsWindow", "Options", 0, QApplication::UnicodeUTF8));
        mMaxVisibleLabel->setText(QApplication::translate("OptionsWindow", "Max visible items", 0, QApplication::UnicodeUTF8));
        mMinCharLabel->setText(QApplication::translate("OptionsWindow", "Min character number", 0, QApplication::UnicodeUTF8));
        mTypingLabel->setText(QApplication::translate("OptionsWindow", "Typing sensitivity", 0, QApplication::UnicodeUTF8));
        mSortingLabel->setText(QApplication::translate("OptionsWindow", "Sorting sensitivity", 0, QApplication::UnicodeUTF8));
        mTypingComboBox->clear();
        mTypingComboBox->insertItems(0, QStringList()
         << QApplication::translate("OptionsWindow", "case-sensitive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OptionsWindow", "case-insensitive", 0, QApplication::UnicodeUTF8)
        );
        mSortingComboBox->clear();
        mSortingComboBox->insertItems(0, QStringList()
         << QApplication::translate("OptionsWindow", "case-sensitive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OptionsWindow", "case-insensitive", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OptionsWindow", "unsorted", 0, QApplication::UnicodeUTF8)
        );
        mTabWidget->setTabText(mTabWidget->indexOf(mTab01), QApplication::translate("OptionsWindow", "Auto-Completer", 0, QApplication::UnicodeUTF8));
        mCodeGroup->setTitle(QApplication::translate("OptionsWindow", "Code", 0, QApplication::UnicodeUTF8));
        mTabSizeLabel->setText(QApplication::translate("OptionsWindow", "Tab Width", 0, QApplication::UnicodeUTF8));
        mGuideLineLabel->setText(QApplication::translate("OptionsWindow", "Guide Line", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(mTab03), QApplication::translate("OptionsWindow", "Field", 0, QApplication::UnicodeUTF8));
        mApplicationGroup->setTitle(QApplication::translate("OptionsWindow", "Application", 0, QApplication::UnicodeUTF8));
        mInstanceLabel->setText(QApplication::translate("OptionsWindow", "Instance", 0, QApplication::UnicodeUTF8));
        mInstanceComboBox->clear();
        mInstanceComboBox->insertItems(0, QStringList()
         << QApplication::translate("OptionsWindow", "single", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("OptionsWindow", "multiple", 0, QApplication::UnicodeUTF8)
        );
        mLanguageLabel->setText(QApplication::translate("OptionsWindow", "Language", 0, QApplication::UnicodeUTF8));
        mTabWidget->setTabText(mTabWidget->indexOf(mTab02), QApplication::translate("OptionsWindow", "Other", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class OptionsWindow: public Ui_OptionsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // OPTIONSWINDOW_UI_H
