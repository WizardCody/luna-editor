/*******************************************************************************************
**
** Project: Luna Editor
** File: MainWindow.h
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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QSignalMapper;
class QIODevice;
class QFile;
QT_END_NAMESPACE

class OptionsWindow;
class FinderWindow;
class MdiSubWindow;
class MdiArea;
class CodeEdit;
class XmlReader;
class StatusBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *pParent = 0);
        static MainWindow *Instance();
        static void Drop();

        CodeEdit *GetActiveDocument() const;
        CodeEdit *GetCurrentDocument() const;
        CodeEdit *FindDocument(const QString &pDoc);
        MdiSubWindow *FindDocumentWindow(const QString &pDoc);
        QList<CodeEdit *> GetDocumentList() const;

        StatusBar *GetStatusBar() const { return mStatusBar; }
        XmlReader *GetXmlReader() const { return mXmlReader; }
        void SetDocFont(const QFont &pFont);
        QFont GetDocFont() const { return mCodeFont; }

        OptionsWindow *GetOptionsWindow() const { return mOptionsWindow; }
        FinderWindow *GetFinderWindow() const { return mFinderWindow; }

    public slots:
        void NewDocument();
        void ResetDocument();
        bool OpenDocument(const QString &pPath = QString());
        int  OpenDocuments(const QStringList &pList);
        bool SaveDocument();
        bool SaveAsDocument(const QString &pPath = QString());
        void CloseDocument(const QString &pDoc = QString());
        void CloseAll();
        void CloseAllOthers(const QString &pDoc = QString());
        bool ReplaceDocument(const QString &pDoc, const QString &pPath = QString());

        void Cut();
        void Copy();
        void Paste();
        void Delete();
        void Undo();
        void Redo();
        void SelectAll();
        void Find();
        void Options();

        void ExportToHTML();

        void LineNumber(bool pChecked);
        void GuideLine(bool pChecked);
        void WordWrap(bool pChecked);
        void Font();

        void About();

        void SetActiveSubWindow(QWidget *pWindow);

    private slots:
        void UpdateUi();

        void DocumentWasModified(bool pMod);
        void UpdateViewMenu();

    protected:
        void changeEvent(QEvent *pEvent);
        void closeEvent(QCloseEvent *pEvent);
        void dragEnterEvent(QDragEnterEvent *pEvent);
        void dragMoveEvent(QDragMoveEvent *pEvent);
        void dragLeaveEvent(QDragLeaveEvent *pEvent);
        void dropEvent(QDropEvent *pEvent);

    private:
        MainWindow(const MainWindow &); // hide copy constructor
        MainWindow &operator=(const MainWindow &); // hide assign op

        static MainWindow *mInstance;

        void SetupEditor();
        void SetupFileMenu();
        void SetupEditMenu();

        QMenu *mViewMenu;
        void SetupViewMenu();
        void SetupHelpMenu();

        QFile *mCacheFile;
        void LoadState(QIODevice *pDevice);
        void SaveState(QIODevice *pDevice);

        MdiSubWindow *CreateDocument();
        QString GetCanonicalFile(const QString &pPath);

        MdiArea *mMdiArea;
        QTabBar *mMdiTabBar;
        StatusBar *mStatusBar;
        bool mIsLineNum;
        bool mIsGuideLine;
        bool mIsWordWrap;
        QFont mCodeFont;

        QSignalMapper *mWindowMapper;

        QAction *mActionNew;
        QAction *mActionOpen;
        QAction *mActionSave;
        QAction *mActionSaveAs;
        QAction *mActionExport;
        QAction *mActionClose;
        QAction *mActionCloseAll;
        QAction *mActionExit;
        QAction *mActionCut;
        QAction *mActionCopy;
        QAction *mActionPaste;
        QAction *mActionDelete;
        QAction *mActionUndo;
        QAction *mActionRedo;
        QAction *mActionSelectAll;
        QAction *mActionFind;
        QAction *mActionOptions;
        QAction *mActionStatus;
        QAction *mActionLineNumber;
        QAction *mActionGuideLine;
        QAction *mActionWordWrap;
        QAction *mActionFont;
        QAction *mActionAbout;

        OptionsWindow *mOptionsWindow;
        FinderWindow *mFinderWindow;

        XmlReader *mXmlReader;
};

#endif // MAINWINDOW_H

/*========================================================================================*/
