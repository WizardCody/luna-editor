/*******************************************************************************************
**
** Project: Luna Editor
** File: CodeEdit.h
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

#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QtGui/QPlainTextEdit>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QCompleter;
QT_END_NAMESPACE

class LineNumberArea;
class CodeParser;
class CodeHighlighter;
class XmlReader;
class StatusBar;

class CodeEdit : public QPlainTextEdit
{
    Q_OBJECT

    friend class LineNumberArea;

    public:
        CodeEdit(QWidget *pParent = 0);

        void SetModelFromFile(const QString &pFileName);
        void SetModelFromReader(XmlReader *pReader);

        void SetLineNumberVisibility(bool pBool);
        void SetGuideLineVisibility(bool pBool);
        void SetWordWrap(bool pBool);
        void SetTabStopWidth(unsigned int pWidth);
        void SetGuideLineWidth(unsigned int pWidth);
        void updateFont();

        void SetMinChar(unsigned int pNum) { mMinChar = pNum; }
        int GetMinChar() const { return mMinChar; }

        void SetStatusBar(StatusBar *pStatusBar);
        StatusBar *GetStatusBar() const { return rStatusBar; }

        void SetCompleter(QCompleter *pCompleter);
        QCompleter *GetCompleter() const { return mCompleter; }

        CodeParser *GetParser() const { return mParser; }
        LineNumberArea *GetLineNumberArea() const { return mLineNumberArea; }
        CodeHighlighter *GetHighlighter() const { return mHighlighter; }

        bool IsModified() const { return document()->isModified(); }
        bool IsUntitled() const { return mIsUntitled; }
        QString GetFilePath() const { return mFilePath; }

        static QString GetLoadDialog(QWidget *pParent = 0);
        static QString GetSaveDialog(QWidget *pParent = 0);

    public slots:
        void NewFile();
        bool LoadFile(const QString &pFilePath = QString());
        bool ReloadFile();
        bool SaveFile(const QString &pFilePath = QString());
        bool ResaveFile();

        void UpdateCursorPosition();

    protected:
        void closeEvent(QCloseEvent *pEvent);
        void resizeEvent(QResizeEvent *pEvent);
        void keyReleaseEvent(QKeyEvent *pEvent);
        void keyPressEvent(QKeyEvent *pEvent);
        void focusInEvent(QFocusEvent *pEvent);
        void contextMenuEvent(QContextMenuEvent *pEvent);
        void paintEvent(QPaintEvent *pEvent);

    private slots:
        void InsertCompletion(const QString &pCompletion);
        void UpdateLineNumberAreaWidth(int pNewBlockCount);
        void UpdateLineNumberArea(const QRect &pRect, int pDy);
        void HighlightCurrentLine();
        void HighlightSelection();
        void DocumentWasModified(bool pMod);

    private:
        QString TextUnderCursor() const;
        void SetFilePath(const QString &pFilePath);
        bool MaybeSave();

        QString mFilePath;

        QCompleter *mCompleter;
        CodeParser *mParser;
        LineNumberArea *mLineNumberArea;
        CodeHighlighter *mHighlighter;
        StatusBar *rStatusBar;

        int mMinChar;
        int mFontWidth;
        int mTabStopWidth;
        int mGuideLineWidth, mGuideLineWidthReal;
        bool mIsUntitled;
        bool mIsGuideLine;

        QList<QTextEdit::ExtraSelection> mExtraCurrentLine;
        QList<QTextEdit::ExtraSelection> mExtraSelection;
};

#endif // CODEEDIT_H

/*========================================================================================*/
