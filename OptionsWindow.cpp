/*******************************************************************************************
**
** Project: Luna Editor
** File: OptionsWindow.cpp
**
** Copyright (C) 2014 techvoid.
** All rights reserved.
** http://sourceforge.net/projects/lunaeditor/
**
** This program is free software: you can redistribute it and/or modify it under the terms
** of the GNU General Public License as published by the Free Software Foundation, either
** version 3 of the License, or (at your option) any later version.
**
** This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
** without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
** See the GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along with this
** program. If not, see <http://www.gnu.org/licenses/>.
**
*******************************************************************************************/

/*======================================== HEADERS =======================================*/

#include "OptionsWindow.h"

#include <QtCore/QFile>
#include <QtCore/QSettings>
#include <QtGui/QCompleter>
#include <QtGui/QFileDialog>

#include "MainWindow.h"
#include "CodeEdit.h"
#include "SourceParser.h"
#include "XmlReader.h"

/*======================================== PUBLIC ========================================*/

OptionsWindow::OptionsWindow(MainWindow *pParent) :
    QDialog(pParent),
    rMainWindow(pParent)
{
    ui.setupUi(this);

    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QObject::connect(ui.mSourceButton1, SIGNAL(clicked()), this, SLOT(SourceDir()));
    QObject::connect(ui.mSourceButton2, SIGNAL(clicked()), this, SLOT(SourceParse()));
    QObject::connect(ui.mSourceButton3, SIGNAL(clicked()), this, SLOT(SourceClean()));
    QObject::connect(ui.mAcceptButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(ui.mRejectButton, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(ui.mApplyButton, SIGNAL(clicked()), this, SLOT(apply()));

    mSourceParser = new SourceParser(this);
    mSourceParser->SetXmlReader(rMainWindow->GetXmlReader());
}

void OptionsWindow::SetSettings(QSettings *pSettings)
{
    rSettings = pSettings;
    LoadSettings(pSettings);
    ApplyAll();
}

QString OptionsWindow::GetSource() const
{
    return ui.mSourceLineEdit->text();
}

void OptionsWindow::ApplyCurrent()
{
    ApplyTo(rMainWindow->GetCurrentDocument());
}

void OptionsWindow::ApplyAll()
{
    foreach(CodeEdit *rDoc, rMainWindow->GetDocumentList()) {
        ApplyTo(rDoc);
    }
}

void OptionsWindow::ApplyTo(CodeEdit *pDoc)
{
    QCompleter *rComp = pDoc->GetCompleter();
    rComp->setMaxVisibleItems(ui.mMaxVisibleBox->value());
    pDoc->SetMinChar(ui.mMinCharBox->value());

    int tTypingIndex = ui.mTypingComboBox->currentIndex();
    if (tTypingIndex == 0) {
        rComp->setCaseSensitivity(Qt::CaseSensitive);
    } else {
        rComp->setCaseSensitivity(Qt::CaseInsensitive);
    }

    int tSortingIndex = ui.mSortingComboBox->currentIndex();
    if (tSortingIndex == 0) {
        rComp->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    } else if (tSortingIndex == 1) {
        rComp->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    } else {
        rComp->setModelSorting(QCompleter::UnsortedModel);
    }

    pDoc->SetTabStopWidth(ui.mTabSizeBox->value());
    pDoc->SetGuideLineWidth(ui.mGuideLineBox->value());
    pDoc->updateFont();
}

/*===================================== PUBLIC SLOTS =====================================*/

void OptionsWindow::accept()
{
    QDialog::accept();
    SaveSettings(rSettings);
    ApplyAll();
}

void OptionsWindow::reject()
{
    QDialog::reject();
    LoadSettings(rSettings);
    ApplyAll();
}

void OptionsWindow::apply()
{
    SaveSettings(rSettings);
    ApplyAll();
}

void OptionsWindow::SourceDir()
{
    QString tPath = GetSource();
    if (tPath.isEmpty())
        tPath = QDir::currentPath();

    QString rDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                   tPath, QFileDialog::ShowDirsOnly
                   | QFileDialog::DontResolveSymlinks);
    if (!rDir.isEmpty())
        ui.mSourceLineEdit->setText(rDir);
}

void OptionsWindow::SourceParse()
{
    mSourceParser->SetEditorList(rMainWindow->GetDocumentList());

    mSourceParser->ParseDir(GetSource());
}

void OptionsWindow::SourceClean()
{
    mSourceParser->SetEditorList(rMainWindow->GetDocumentList());

    mSourceParser->CleanXml();
}

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

void OptionsWindow::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange) {
        // translate
    }
    QDialog::changeEvent(pEvent);
}

/*======================================== PRIVATE =======================================*/

void OptionsWindow::SaveSettings(QSettings *pDevice)
{
    pDevice->sync();
    pDevice->setValue("source", ui.mSourceLineEdit->text());
    pDevice->setValue("maxVisibleItems", ui.mMaxVisibleBox->value());
    pDevice->setValue("minCharNumber", ui.mMinCharBox->value());
    pDevice->setValue("typingSensitivity", ui.mTypingComboBox->currentIndex());
    pDevice->setValue("sortingSensitivity", ui.mSortingComboBox->currentIndex());
    pDevice->setValue("instanceType", ui.mInstanceComboBox->currentIndex());
    pDevice->setValue("language", ui.mLanguageComboBox->currentIndex());
    pDevice->setValue("tabWidth", ui.mTabSizeBox->value());
    pDevice->setValue("guideLine", ui.mGuideLineBox->value());
}

void OptionsWindow::LoadSettings(QSettings *pDevice)
{
    if (!QFile(pDevice->fileName()).exists())
        QFile(pDevice->fileName()).open(QIODevice::ReadWrite);

    pDevice->sync();
    ui.mSourceLineEdit->setText(pDevice->value("source").toString());
    ui.mMaxVisibleBox->setValue(pDevice->value("maxVisibleItems", 7).toInt());
    ui.mMinCharBox->setValue(pDevice->value("minCharNumber", 1).toInt());
    ui.mTypingComboBox->setCurrentIndex(pDevice->value("typingSensitivity", 0).toInt());
    ui.mSortingComboBox->setCurrentIndex(pDevice->value("sortingSensitivity", 0).toInt());
    ui.mInstanceComboBox->setCurrentIndex(pDevice->value("instanceType", 0).toInt());
    ui.mTabSizeBox->setValue(pDevice->value("tabWidth", 5).toInt());
    ui.mGuideLineBox->setValue(pDevice->value("guideLine", 75).toInt());

    ui.mLanguageComboBox->clear();
    QFileInfoList tLanguages = QDir("Data/Languages")
                               .entryInfoList(QStringList("*.qm"), QDir::Files);
    foreach(QFileInfo tLanguage, tLanguages) {
        ui.mLanguageComboBox->addItem(tLanguage.baseName());
    }
}

/*========================================================================================*/
