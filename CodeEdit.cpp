/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeEdit.cpp
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

#include "CodeEdit.h"

#include <QtGui/QApplication>
#include <QtGui/QCompleter>
#include <QtGui/QScrollBar>
#include <QtGui/QPainter>
#include <QtGui/QStandardItemModel>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QMenu>
#include <QtCore/QUrl>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>

#include "CodeParser.h"
#include "LineNumberArea.h"
#include "CodeHighlighter.h"
#include "XmlReader.h"
#include "CompleterView.h"
#include "StatusBar.h"

/*======================================== PUBLIC ========================================*/

CodeEdit::CodeEdit(QWidget *pParent)
    : QPlainTextEdit(pParent)
{
    mHighlighter = new CodeHighlighter(document());
    mLineNumberArea = new LineNumberArea(this);
    mParser = new CodeParser(this);

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(UpdateLineNumberAreaWidth(int)));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(UpdateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(UpdateCursorPosition()));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(HighlightCurrentLine()));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(HighlightSelection()));
    connect(this, SIGNAL(modificationChanged(bool)), this, SLOT(DocumentWasModified(bool)));

    UpdateLineNumberAreaWidth(0);
    HighlightCurrentLine();
    mMinChar = 1;
    mFontWidth = 1;

    QPalette tPalette = palette();
    tPalette.setColor(QPalette::Inactive, QPalette::Highlight,
                      tPalette.color(QPalette::Active, QPalette::Highlight));
    tPalette.setColor(QPalette::Inactive, QPalette::HighlightedText,
                      tPalette.color(QPalette::Active, QPalette::HighlightedText));
    setPalette(tPalette);

    SetCompleter(new QCompleter(this));
    mCompleter->setPopup(new CompleterView(this));
    mCompleter->setModelSorting(QCompleter::CaseSensitivelySortedModel);
    mCompleter->setCaseSensitivity(Qt::CaseSensitive);
    mCompleter->setWrapAround(false);
}

void CodeEdit::SetModelFromFile(const QString &pFileName)
{
    XmlReader tReader;
    if (tReader.LoadFile(pFileName)) {
        mCompleter->setModel(tReader.GetModel(mCompleter));
    } else if (!mCompleter->model()) {
        mCompleter->setModel(new QStandardItemModel(mCompleter));
    }

    mParser->SetModel(mCompleter->model());
    mParser->ParseText(toPlainText());
}

void CodeEdit::SetModelFromReader(XmlReader *pReader)
{
    if (pReader->IsLoaded()) {
        mCompleter->setModel(pReader->GetModel(mCompleter));
    } else if (!mCompleter->model()) {
        mCompleter->setModel(new QStandardItemModel(mCompleter));
    }

    mParser->SetModel(mCompleter->model());
    mParser->ParseText(toPlainText());
}

void CodeEdit::SetLineNumberVisibility(bool pBool)
{
    mLineNumberArea->setVisible(pBool);
    UpdateLineNumberAreaWidth(0);
}

void CodeEdit::SetGuideLineVisibility(bool pBool)
{
    mIsGuideLine = pBool;
    viewport()->update();
}

void CodeEdit::SetWordWrap(bool pBool)
{
    LineWrapMode tMode;
    if (pBool) {
        tMode = WidgetWidth;
    } else {
        tMode = NoWrap;
    }

    setLineWrapMode(tMode);
}

void CodeEdit::SetTabStopWidth(unsigned int pWidth)
{
    mTabStopWidth = pWidth;
    setTabStopWidth(mTabStopWidth * mFontWidth);
}

void CodeEdit::SetGuideLineWidth(unsigned int pWidth)
{
    mGuideLineWidth = pWidth;
    mGuideLineWidthReal = mGuideLineWidth * mFontWidth;
    viewport()->update();
}

void CodeEdit::updateFont()
{
    mFontWidth = QFontMetrics(font()).width("x");

    SetTabStopWidth(mTabStopWidth);
    SetGuideLineWidth(mGuideLineWidth);
}

void CodeEdit::SetStatusBar(StatusBar *pStatusBar)
{
    rStatusBar = pStatusBar;
    UpdateCursorPosition();
}

void CodeEdit::SetCompleter(QCompleter *pCompleter)
{
    if (mCompleter)
        QObject::disconnect(mCompleter, 0, this, 0);

    mCompleter = pCompleter;
    if (!mCompleter)
        return;

    mCompleter->setWidget(this);
    QObject::connect(mCompleter, SIGNAL(activated(QString)),
                     this, SLOT(InsertCompletion(QString)));
}

QString CodeEdit::GetLoadDialog(QWidget *pParent)
{
    return QFileDialog::getOpenFileName(pParent, tr("Open Script"),
                                        QDir::currentPath(),
                                        "Lua script files (*.lua *.luna)");
}

QString CodeEdit::GetSaveDialog(QWidget *pParent)
{
    return QFileDialog::getSaveFileName(pParent, tr("Save Script"),
                                        QDir::currentPath(),
                                        "Lua script file (*.lua);;" \
                                        "Luna script file (*.luna)");
}

/*===================================== PUBLIC SLOTS =====================================*/

void CodeEdit::NewFile()
{
    static int sFileNumber = 1;

    mIsUntitled = true;
    mFilePath = tr("Script%1").arg(sFileNumber++);
    setWindowTitle(mFilePath + "[*]");

    // reset stuff
    // ...
}

bool CodeEdit::LoadFile(const QString &pFilePath)
{
    QString tFileName = pFilePath;
    if (tFileName.isEmpty()) {
        tFileName = GetLoadDialog(this);
        if (tFileName.isEmpty())
            return false;
    }

    if (QFileInfo(tFileName).isFile() && MaybeSave()) {
        QFile tFile(tFileName);
        if (!tFile.open(QFile::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this, tr("Warning"),
                                 tr("Cannot open file \"%1\"\n%2.")
                                 .arg(tFileName).arg(tFile.errorString()));
            return false;
        }

        QApplication::setOverrideCursor(Qt::WaitCursor);

        QTextStream tStream(&tFile);
        setPlainText(tStream.readAll());

        QApplication::restoreOverrideCursor();

        SetFilePath(tFileName);
        tFile.close();

        return true;
    }

    return false;
}

bool CodeEdit::ReloadFile()
{
    if (IsUntitled()) {
        return LoadFile(QString());
    } else {
        return LoadFile(GetFilePath());
    }

    return false;
}

bool CodeEdit::SaveFile(const QString &pFilePath)
{
    QString tFileName = pFilePath;
    if (tFileName.isEmpty()) {
        tFileName = GetSaveDialog(this);
        if (tFileName.isEmpty())
            return false;
    }

    QFile tFile(tFileName);
    if (!tFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Warning"),
                             tr("Cannot save file \"%1\"\n%2.")
                             .arg(tFileName).arg(tFile.errorString()));
        return false;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);

    QTextStream tStream(&tFile);
    tStream.setCodec("UTF-8");

    if (rStatusBar->GetFormat() == "UTF-8 BOM")
        tStream.setGenerateByteOrderMark(true);

    tStream << toPlainText();

    QApplication::restoreOverrideCursor();

    SetFilePath(tFileName);
    tFile.close();

    return true;
}

bool CodeEdit::ResaveFile()
{
    if (IsUntitled()) {
        return SaveFile(QString());
    } else {
        return SaveFile(GetFilePath());
    }

    return false;
}

/*======================================= PROTECTED ======================================*/

void CodeEdit::closeEvent(QCloseEvent *pEvent)
{
    if (MaybeSave()) {
        pEvent->accept();
    } else {
        pEvent->ignore();
    }
}

void CodeEdit::resizeEvent(QResizeEvent *pEvent)
{
    QPlainTextEdit::resizeEvent(pEvent);

    QRect tContentsRect = contentsRect();
    mLineNumberArea->setGeometry(QRect(tContentsRect.left(), tContentsRect.top(),
                                       mLineNumberArea->GetAreaWidth(),
                                       tContentsRect.height()));
}

void CodeEdit::keyReleaseEvent(QKeyEvent *pEvent)
{
    mParser->ParseText(toPlainText());
}

void CodeEdit::keyPressEvent(QKeyEvent *pEvent)
{
    if (mCompleter && mCompleter->popup()->isVisible()) {
        //-- The following keys are forwarded by the completer to the widget
        switch (pEvent->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
            pEvent->ignore();
            return; //-- let the completer do default behavior
        default:
            break;
        }
    }

    /**
        The following features are a little buggy. They may appear in the next
        version or not.
        CTRL + Q    : comment out
        CTRL + W    : uncomment
        TAB         : increase line indent
        SHIFT + TAB : decrease line indent
    */
    /*
    bool tIsCom = ((pEvent->modifiers() & Qt::ControlModifier) &&
                    pEvent->key() == Qt::Key_Q);
    if(tIsCom){
        QTextCursor tCursor = textCursor();
        tCursor.beginEditBlock();

        tCursor.setPosition(textCursor().selectionEnd());
        int tBlockEnd = tCursor.blockNumber();
        tCursor.setPosition(textCursor().selectionStart());
        int tBlockStart = tCursor.blockNumber();

        int tBlocks = tBlockEnd - tBlockStart;
        while(tBlockStart <= tBlockEnd){
            tCursor.insertText("--~");
            tCursor.movePosition(QTextCursor::NextBlock);
            tBlockStart++;
        }
        if(tBlocks > 0){
            moveCursor(QTextCursor::QTextCursor::StartOfBlock,
                       QTextCursor::KeepAnchor);
        }

        tCursor.endEditBlock();
        return;
    }
    */

    /*
    bool tIsUnCom = ((pEvent->modifiers() & Qt::ControlModifier) &&
                    pEvent->key() == Qt::Key_W);
    if(tIsUnCom){
        QTextCursor tCursor = textCursor();
        tCursor.beginEditBlock();

        tCursor.setPosition(textCursor().selectionEnd());
        int tBlockEnd = tCursor.blockNumber();
        tCursor.setPosition(textCursor().selectionStart());
        int tBlockStart = tCursor.blockNumber();

        if(tCursor.selectedText().contains("--~")){
            // ...
        }

        tCursor.endEditBlock();
        return;
    }
    */

    /*
    bool tIsTab = (pEvent->key() == Qt::Key_Tab); //-- TAB
    if(tIsTab){
        QTextCursor tCursor = textCursor();
        tCursor.beginEditBlock();

        tCursor.setPosition(textCursor().selectionEnd());
        int tBlockEnd = tCursor.blockNumber();
        tCursor.setPosition(textCursor().selectionStart());
        int tBlockStart = tCursor.blockNumber();

        int tBlocks = tBlockEnd - tBlockStart;
        while(tBlockStart <= tBlockEnd){
            tCursor.insertText("\t");
            tCursor.movePosition(QTextCursor::NextBlock);
            tBlockStart++;
        }
        if(tBlocks > 0){
            moveCursor(QTextCursor::QTextCursor::StartOfBlock,
                       QTextCursor::KeepAnchor);
        }

        tCursor.endEditBlock();
        return;
    }

    bool tIsBackTab = (pEvent->key() == Qt::Key_Backtab); //-- SHIFT+TAB
    if(tIsBackTab){
        QTextCursor tCursor = textCursor();
        tCursor.beginEditBlock();

        tCursor.setPosition(textCursor().selectionEnd());
        int tBlockEnd = tCursor.blockNumber();
        tCursor.setPosition(textCursor().selectionStart());
        int tBlockStart = tCursor.blockNumber();

        int tBlocks = tBlockEnd - tBlockStart;
        while(tBlockStart <= tBlockEnd){
            tCursor.deleteChar();
            tCursor.movePosition(QTextCursor::NextBlock);
            tBlockStart++;
        }


        // Theres a bug with QTextCursor::NextBlock and deleteChar() function.
        // Below is a workaround for it.
        tCursor.movePosition(QTextCursor::EndOfBlock);
        tCursor.insertText(" ");
        tCursor.deletePreviousChar();

        tCursor.endEditBlock();
        return;
    }
    */

    bool tIsLineFeed = ((pEvent->modifiers() & Qt::ShiftModifier) &&
                        pEvent->key() == Qt::Key_Return); //-- SHIFT+ENTER
    if (tIsLineFeed) { //-- Turn line feed (\n) into carriage return (\r)
        textCursor().insertText("\r");
        return;
    }

    bool tIsShortcut = ((pEvent->modifiers() & Qt::ControlModifier) &&
                        pEvent->key() == Qt::Key_Space); //-- CTRL+SPACE
    if (!mCompleter || !tIsShortcut) //-- do not process the shortcut when we have a completer
        QPlainTextEdit::keyPressEvent(pEvent);

    const bool tCtrlOrShift = pEvent->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
    if (!mCompleter || (tCtrlOrShift && pEvent->text().isEmpty()))
        return;

    static QString tEow("~!@#$%^&*()+{}|:\"<>?,./;'[]\\-="); //-- end of word
    bool tHasModifier = (pEvent->modifiers() != Qt::NoModifier) && !tCtrlOrShift;
    QString tCompletionPrefix = TextUnderCursor();

    if (!tIsShortcut && (tHasModifier || pEvent->text().isEmpty() ||
                         tCompletionPrefix.length() < mMinChar || //-- number of characters
                         tEow.contains(pEvent->text().right(1)))) {
        mCompleter->popup()->hide();
        return;
    }

    if (tCompletionPrefix != mCompleter->completionPrefix()) {
        mCompleter->setCompletionPrefix(tCompletionPrefix);
        mCompleter->popup()->setCurrentIndex(mCompleter->completionModel()->index(0, 0));
    }

    QRect tCursorRect = cursorRect();
    tCursorRect.setWidth(mCompleter->popup()->sizeHintForColumn(0)
                         + mCompleter->popup()->verticalScrollBar()->sizeHint().width());
    mCompleter->complete(tCursorRect); //-- popup it up!
}

void CodeEdit::focusInEvent(QFocusEvent *pEvent)
{
    QPlainTextEdit::focusInEvent(pEvent);
}

void CodeEdit::contextMenuEvent(QContextMenuEvent *pEvent)
{
    QMenu *rMenu = createStandardContextMenu();

    //-- Custom context menu
    rMenu->exec(pEvent->globalPos());
    delete rMenu;
}

void CodeEdit::paintEvent(QPaintEvent *pEvent)
{
    QPlainTextEdit::paintEvent(pEvent);

    QPainter tPainter(viewport());
    if (mIsGuideLine) {
        tPainter.drawLine(mGuideLineWidthReal, 0,
                          mGuideLineWidthReal, viewport()->height());
    }
}

/*===================================== PRIVATE SLOTS ====================================*/

void CodeEdit::InsertCompletion(const QString &pCompletion)
{
    if (mCompleter->widget() != this)
        return;
    QTextCursor tCursor = textCursor();
    int tExtra = pCompletion.length() - mCompleter->completionPrefix().length();
    tCursor.movePosition(QTextCursor::EndOfWord);
    tCursor.insertText(pCompletion.right(tExtra));
    setTextCursor(tCursor);
}

void CodeEdit::UpdateLineNumberAreaWidth(int pNewBlockCount)
{
    if (!mLineNumberArea->isHidden()) {
        setViewportMargins(mLineNumberArea->GetAreaWidth(), 0, 0, 0);
    } else {
        setViewportMargins(0, 0, 0, 0);
    }
}

void CodeEdit::UpdateLineNumberArea(const QRect &pRect, int pDy)
{
    if (pDy) {
        mLineNumberArea->scroll(0, pDy);
    } else {
        mLineNumberArea->update(0, pRect.y(), mLineNumberArea->width(), pRect.height());
    }

    if (pRect.contains(viewport()->rect()))
        UpdateLineNumberAreaWidth(0);
}

void CodeEdit::UpdateCursorPosition()
{
    if (rStatusBar) {
        rStatusBar->SetCursorPosition(textCursor().blockNumber() + 1,
                                      textCursor().columnNumber() + 1);
    }
}

void CodeEdit::HighlightCurrentLine()
{
    mExtraCurrentLine.clear();

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection tLineSelection;
        QColor tLineColor = QColor(Qt::gray).lighter(150);

        tLineSelection.format.setBackground(tLineColor);
        tLineSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
        tLineSelection.cursor = textCursor();
        tLineSelection.cursor.clearSelection();
        mExtraCurrentLine.append(tLineSelection);
    }

    setExtraSelections(mExtraCurrentLine + mExtraSelection);
}

void CodeEdit::HighlightSelection()
{
    mExtraSelection.clear();

    if (textCursor().hasSelection()) {
        QTextCursor tTextCursor(document());
        QString tSelectText = textCursor().selectedText();
        QColor tSelectColor = QColor(255,165,0).lighter(150);
        if (!tSelectText.simplified().isEmpty()) {
            while (!tTextCursor.isNull()) {
                tTextCursor = document()->find(tSelectText, tTextCursor.position(),
                                               QTextDocument::FindCaseSensitively |
                                               QTextDocument::FindWholeWords);
                QTextEdit::ExtraSelection tTextSelection;
                tTextSelection.format.setBackground(tSelectColor);
                tTextSelection.cursor = tTextCursor;
                mExtraSelection.append(tTextSelection);
            }
        }
    }

    setExtraSelections(mExtraCurrentLine + mExtraSelection);
}

void CodeEdit::DocumentWasModified(bool pMod)
{
    setWindowModified(pMod);
}

/*======================================== PRIVATE =======================================*/

QString CodeEdit::TextUnderCursor() const
{
    QTextCursor tCursor = textCursor();
    tCursor.select(QTextCursor::WordUnderCursor);
    return tCursor.selectedText();
}

void CodeEdit::SetFilePath(const QString &pFilePath)
{
    QFileInfo tFileInfo(pFilePath);
    mIsUntitled = false;
    mFilePath = tFileInfo.canonicalFilePath();
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(tFileInfo.fileName() + "[*]");
}

bool CodeEdit::MaybeSave()
{
    if (document()->isModified()) {
        QMessageBox::StandardButton tRet;
        tRet = QMessageBox::warning(this, tr("information"),
                                    tr("\"%1\" has been modified.\n"
                                       "Do you want to save your changes?").
                                    arg(GetFilePath()),
                                    QMessageBox::Save | QMessageBox::Discard
                                    | QMessageBox::Cancel);
        if (tRet == QMessageBox::Save) {
            ResaveFile();
        } else if (tRet == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

/*========================================================================================*/
