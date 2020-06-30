/*******************************************************************************************
**
** Project: Luna Editor
** File: MainWindow.cpp
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

#include "MainWindow.h"

#include <QtGui/QApplication>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>
#include <QtGui/QMenuBar>
#include <QtGui/QCompleter>
#include <QtGui/QTabBar>
#include <QtGui/QFontDialog>
#include <QtCore/QUrl>
#include <QtCore/QMutex>
#include <QtCore/QSignalMapper>

#include "OptionsWindow.h"
#include "FinderWindow.h"

#include "CodeEdit.h"
#include "XmlReader.h"
#include "MdiSubWindow.h"
#include "StatusBar.h"
#include "MdiArea.h"
#include "ExporterHtml.h"
#include "Global.h"

/*======================================== PUBLIC ========================================*/

MainWindow *MainWindow::mInstance = 0;

MainWindow::MainWindow(QWidget *pParent)
    : QMainWindow(pParent)
{
    resize(640, 640);

    setStatusBar(mStatusBar = new StatusBar(this));

    SetupEditor();
    SetupFileMenu();
    SetupEditMenu();
    SetupViewMenu();
    SetupHelpMenu();

    QDir::setCurrent(QApplication::applicationDirPath());

    mXmlReader = new XmlReader(this);
    mXmlReader->LoadFile("Data/functions.xml");

    mCacheFile = new QFile("Data/cache");
    LoadState(mCacheFile);

    mOptionsWindow = new OptionsWindow(this);
    mOptionsWindow->setObjectName(QString::fromUtf8("mOptionsWindow"));

    mFinderWindow = new FinderWindow(this);
    mFinderWindow->setObjectName(QString::fromUtf8("mFinderWindow"));

    setCentralWidget(mMdiArea);
    setWindowIcon(QIcon(":/resources/icon.png"));
    setAcceptDrops(true);
}

MainWindow *MainWindow::Instance()
{
    static QMutex tMutex;
    if (!mInstance) {
        tMutex.lock();
        if (!mInstance)
            mInstance = new MainWindow;
        tMutex.unlock();
    }
    return mInstance;
}

void MainWindow::Drop()
{
    static QMutex tMutex;
    tMutex.lock();
    delete mInstance;
    mInstance = 0;
    tMutex.unlock();
}

CodeEdit *MainWindow::GetActiveDocument() const
{
    if (MdiSubWindow *rActiveSubWindow = qobject_cast<MdiSubWindow *>
                                         (mMdiArea->activeSubWindow()))
        return qobject_cast<CodeEdit *>(rActiveSubWindow->widget());
    return 0;
}

CodeEdit *MainWindow::GetCurrentDocument() const
{
    if (MdiSubWindow *rCurrentSubWindow = qobject_cast<MdiSubWindow *>
                                          (mMdiArea->currentSubWindow()))
        return qobject_cast<CodeEdit *>(rCurrentSubWindow->widget());
    return 0;
}

CodeEdit *MainWindow::FindDocument(const QString &pFileName)
{
    QString tFilePath = GetCanonicalFile(pFileName);
    foreach(QMdiSubWindow *rWindow, mMdiArea->subWindowList()) {
        CodeEdit *rDocument = qobject_cast<CodeEdit *>(rWindow->widget());
        if (rDocument->GetFilePath() == tFilePath)
            return rDocument;
    }
    return 0;
}

MdiSubWindow *MainWindow::FindDocumentWindow(const QString &pFileName)
{
    QString tFilePath = GetCanonicalFile(pFileName);
    foreach(QMdiSubWindow *rWindow, mMdiArea->subWindowList()) {
        CodeEdit *rDocument = qobject_cast<CodeEdit *>(rWindow->widget());
        if (rDocument->GetFilePath() == tFilePath)
            return qobject_cast<MdiSubWindow *>(rWindow);
    }
    return 0;
}

QList<CodeEdit *> MainWindow::GetDocumentList() const
{
    QList<CodeEdit *> rList;

    foreach(QMdiSubWindow *rWindow, mMdiArea->subWindowList()) {
        rList.append(qobject_cast<CodeEdit *>(rWindow->widget()));
    }

    return rList;
}

void MainWindow::SetDocFont(const QFont &pFont)
{
    mCodeFont = pFont;

    if (!mCodeFont.fixedPitch())
        mCodeFont.setFixedPitch(true);

    foreach(CodeEdit *rDoc, GetDocumentList()) {
        rDoc->setFont(mCodeFont);
        rDoc->updateFont();
    }
}

/*===================================== PUBLIC SLOTS =====================================*/

void MainWindow::NewDocument()
{
    MdiSubWindow *rDoc = CreateDocument();
    rDoc->GetEditor()->NewFile();
    rDoc->show();
    mStatusBar->showMessage(tr("New file."), 4000);
}

void MainWindow::ResetDocument()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->NewFile(); // !!
}

bool MainWindow::OpenDocument(const QString &pPath)
{
    QString tFileName = pPath;
    if (tFileName.isEmpty()) {
        tFileName = CodeEdit::GetLoadDialog(this);
        if (tFileName.isEmpty())
            return false;
    }

    MdiSubWindow *rExisting = FindDocumentWindow(tFileName);
    if (rExisting) {
        mMdiArea->setActiveSubWindow(rExisting);
        return false;
    }

    MdiSubWindow *rDoc = CreateDocument();
    if (rDoc->GetEditor()->LoadFile(tFileName)) {
        mStatusBar->showMessage(tr("File was opened successfully."), 4000);
        rDoc->show();
        return true;
    } else {
        mStatusBar->showMessage(tr("Cannot open file."), 4000);
        rDoc->close();
    }

    return false;
}

int MainWindow::OpenDocuments(const QStringList &pList)
{
    int tSuccess = 0;
    foreach(QString rPath, pList) {
        if (OpenDocument(rPath))
            tSuccess++;
    }
    return tSuccess;
}

bool MainWindow::SaveDocument()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return false;

    if (rDoc->ResaveFile()) {
        mStatusBar->showMessage(tr("File was saved successfully."), 4000);
        UpdateUi();
        return true;
    } else {
        mStatusBar->showMessage(tr("Cannot resave file."), 4000);
    }

    return false;
}

bool MainWindow::SaveAsDocument(const QString &pPath)
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return false;

    if (rDoc->SaveFile(pPath)) {
        mStatusBar->showMessage(tr("File was saved successfully."), 4000);
        UpdateUi();
        return true;
    } else {
        mStatusBar->showMessage(tr("Cannot resave file."), 4000);
    }

    return false;
}

void MainWindow::CloseDocument(const QString &pDoc)
{
    if (!pDoc.isEmpty()) {
        MdiSubWindow *rWindow = FindDocumentWindow(pDoc);
        if (rWindow)
            rWindow->close();
    } else {
        mMdiArea->closeActiveSubWindow();
    }

    if (mMdiArea->subWindowList().count() <= 0)
        NewDocument();
}

void MainWindow::CloseAll()
{
    mMdiArea->closeAllSubWindows();

    if (mMdiArea->subWindowList().count() <= 0)
        NewDocument();
}

void MainWindow::CloseAllOthers(const QString &pDoc)
{
    MdiSubWindow *rWindow;
    if (!pDoc.isEmpty()) {
        rWindow = FindDocumentWindow(pDoc);
    } else {
        rWindow = qobject_cast<MdiSubWindow *>(mMdiArea->currentSubWindow());
    }

    if (!rWindow) return;

    foreach(QMdiSubWindow *rSubWindow, mMdiArea->subWindowList()) {
        if (rSubWindow != rWindow)
            rSubWindow->close();
    }
}

bool MainWindow::ReplaceDocument(const QString &pDoc, const QString &pPath)
{
    QString tFileName = pPath;
    if (tFileName.isEmpty()) {
        tFileName = CodeEdit::GetLoadDialog(this);
        if (tFileName.isEmpty())
            return false;
    }

    MdiSubWindow *rExisting = FindDocumentWindow(tFileName);
    if (rExisting) {
        mMdiArea->setActiveSubWindow(rExisting);
        return false;
    }

    CodeEdit *rDoc;
    if (pDoc.isEmpty()) {
        rDoc = GetCurrentDocument();
    } else {
        rDoc = FindDocument(pDoc);
    }

    if (rDoc && rDoc->LoadFile(tFileName)) {
        mStatusBar->showMessage(tr("File was replaced successfully."), 4000);
        UpdateUi();
        return true;
    } else {
        mStatusBar->showMessage(tr("Cannot replace file."), 4000);
    }

    return false;
}

void MainWindow::Cut()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->cut();
}

void MainWindow::Copy()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->copy();
}

void MainWindow::Paste()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->paste();
}

void MainWindow::Delete()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->textCursor().removeSelectedText();
}

void MainWindow::Undo()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->undo();
}

void MainWindow::Redo()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->redo();
}

void MainWindow::SelectAll()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;
    rDoc->selectAll();
}

void MainWindow::Find()
{
    if (mFinderWindow)
        mFinderWindow->show();
}

void MainWindow::Options()
{
    if (mOptionsWindow)
        mOptionsWindow->exec();
}

void MainWindow::ExportToHTML()
{
    ExporterHtml tExporter(this);
    tExporter.ExportFromXml(mXmlReader);
}

void MainWindow::LineNumber(bool pChecked)
{
    foreach(CodeEdit *rDoc, GetDocumentList()) {
        rDoc->SetLineNumberVisibility(pChecked);
    }
    mIsLineNum = pChecked;
}

void MainWindow::GuideLine(bool pChecked)
{
    foreach(CodeEdit *rDoc, GetDocumentList()) {
        rDoc->SetGuideLineVisibility(pChecked);
    }
    mIsGuideLine = pChecked;
}

void MainWindow::WordWrap(bool pChecked)
{
    foreach(CodeEdit *rDoc, GetDocumentList()) {
        rDoc->SetWordWrap(pChecked);
    }
    mIsWordWrap = pChecked;
}

void MainWindow::Font()
{
    CodeEdit *rDoc = GetCurrentDocument();
    if (!rDoc) return;

    bool tIsSet;
    QFont tFont = QFontDialog::getFont(&tIsSet, rDoc->font(), this);
    if (tIsSet) {
        SetDocFont(tFont);
        mStatusBar->showMessage(tr("Font has been changed."), 4000);
    }
}

void MainWindow::About()
{
    QMessageBox::about(this, tr("About %1").arg(APP_PRODUCTNAME),
                       tr("<p>The <b>%1</b>, version <b>%2</b>" \
                          "<br><br><b>author:</b> %3" \
                          "<br><b>website:</b> <a href=\"%4\">sourceforge.net</a></p>")
                       .arg(APP_PRODUCTNAME).arg(APP_FILEVER)
                       .arg(APP_COPYRIGHT).arg(APP_PRODUCTURL));
}

void MainWindow::SetActiveSubWindow(QWidget *pWindow)
{
    if (!pWindow)
        return;
    mMdiArea->setActiveSubWindow(qobject_cast<MdiSubWindow *>(pWindow));
}

/*===================================== PRIVATE SLOTS ====================================*/

void MainWindow::UpdateUi()
{
    CodeEdit *rDoc = GetCurrentDocument();
    bool tHasDocument = (rDoc != 0);

    QString tWindowTitle = APP_PRODUCTNAME;
    if (tHasDocument && !rDoc->IsUntitled())
        tWindowTitle.append(QString(" ( %1 )").arg(rDoc->GetFilePath()));
    tWindowTitle.append(" [*]");
    setWindowTitle(tWindowTitle);

    setWindowModified(tHasDocument && rDoc->IsModified());

    if (tHasDocument)
        rDoc->UpdateCursorPosition();
}

void MainWindow::DocumentWasModified(bool pMod)
{
    setWindowModified(pMod);
}

void MainWindow::UpdateViewMenu()
{
    mViewMenu->clear();
    mViewMenu->addAction(mStatusBar->GetToggleAction());
    mActionLineNumber = mViewMenu->addAction(tr("&Line Number"), this, SLOT(LineNumber(bool)));
    mActionLineNumber->setCheckable(true);
    mActionLineNumber->setChecked(mIsLineNum);
    mActionGuideLine = mViewMenu->addAction(tr("&Guide Line"), this, SLOT(GuideLine(bool)));
    mActionGuideLine->setCheckable(true);
    mActionGuideLine->setChecked(mIsGuideLine);
    mViewMenu->addSeparator();
    mActionWordWrap = mViewMenu->addAction(tr("&Word Wrap"), this, SLOT(WordWrap(bool)));
    mActionWordWrap->setCheckable(true);
    mActionWordWrap->setChecked(mIsWordWrap);
    mActionFont = mViewMenu->addAction(tr("&Font"), this, SLOT(Font()));

    QList<QMdiSubWindow *> rWindows = mMdiArea->subWindowList();
    mViewMenu->addSeparator()->setVisible(!rWindows.isEmpty());

    for (int i = 0; i < rWindows.size(); ++i) {
        CodeEdit *rDoc = qobject_cast<CodeEdit *>(rWindows.at(i)->widget());

        QAction *rAction = mViewMenu->addAction(QFileInfo(rDoc->GetFilePath()).fileName());
        rAction->setCheckable(true);
        rAction->setChecked(rDoc == GetActiveDocument());
        connect(rAction, SIGNAL(triggered()), mWindowMapper, SLOT(map()));
        mWindowMapper->setMapping(rAction, rWindows.at(i));
    }
}

/*======================================= PROTECTED ======================================*/

void MainWindow::changeEvent(QEvent *pEvent)
{
    if (pEvent->type() == QEvent::LanguageChange) {
        // translate
    }
    QMainWindow::changeEvent(pEvent);
}

void MainWindow::closeEvent(QCloseEvent *pEvent)
{
    mMdiArea->closeAllSubWindows();
    if (mMdiArea->currentSubWindow()) {
        pEvent->ignore();
    } else {
        SaveState(mCacheFile);
        pEvent->accept();
    }
}


void MainWindow::dragEnterEvent(QDragEnterEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *pEvent)
{
    pEvent->acceptProposedAction();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *pEvent)
{
    pEvent->accept();
}

void MainWindow::dropEvent(QDropEvent *pEvent)
{
    const QMimeData *tMimeData = pEvent->mimeData();
    if (tMimeData->hasUrls()) {
        QList<QUrl> tUrlList = tMimeData->urls();
        foreach(QUrl rUrl, tUrlList) {
            QString tFile = QFileInfo(rUrl.toLocalFile()).canonicalFilePath();
            if (OpenDocument(tFile))
                pEvent->acceptProposedAction();
        }
    }
}

/*======================================== PRIVATE =======================================*/

void MainWindow::SetupEditor()
{
    mMdiArea = new MdiArea(this);
    mMdiArea->setObjectName(QString::fromUtf8("mMdiArea"));
    mMdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mMdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mMdiArea->setViewMode(QMdiArea::TabbedView);
    mMdiArea->setDocumentMode(true);
    mMdiArea->setTabsMovable(true);
    mMdiArea->setAcceptDrops(true);

    connect(mMdiArea, SIGNAL(subWindowActivated(QMdiSubWindow *)),
            this, SLOT(UpdateUi()));

    QList<QTabBar *> tTabBarList = mMdiArea->findChildren<QTabBar *>();
    mMdiTabBar = tTabBarList.at(0);
    if (mMdiTabBar)
        mMdiTabBar->setExpanding(false);

    mCodeFont.setFamily("Courier");
    mCodeFont.setFixedPitch(true);
    mCodeFont.setPointSize(10);

    mIsLineNum = true;
    mIsGuideLine = true;
}

void MainWindow::SetupFileMenu()
{
    QMenu *rFileMenu = new QMenu(tr("&File"), this);
    menuBar()->addMenu(rFileMenu);

    mActionNew = rFileMenu->addAction(tr("&New"), this,
                                      SLOT(NewDocument()), QKeySequence::New);
    rFileMenu->addSeparator();

    mActionOpen = rFileMenu->addAction(tr("&Open..."), this,
                                       SLOT(OpenDocument()), QKeySequence::Open);
    mActionSave = rFileMenu->addAction(tr("&Save"), this,
                                       SLOT(SaveDocument()), QKeySequence::Save);
    mActionSaveAs = rFileMenu->addAction(tr("&Save As..."), this,
                                         SLOT(SaveAsDocument()), QKeySequence::SaveAs);

    QMenu *rExportMenu = new QMenu(tr("&Export..."), this);
    rFileMenu->addMenu(rExportMenu);
    mActionExport = rExportMenu->addAction(tr("source to HTML"), this,
                                           SLOT(ExportToHTML()));
    rFileMenu->addSeparator();

    mActionClose = rFileMenu->addAction(tr("&Close"), this,
                                        SLOT(CloseDocument()), QKeySequence::Close);
    mActionCloseAll = rFileMenu->addAction(tr("&Close All"), this,
                                           SLOT(CloseAll()));
    rFileMenu->addSeparator();
    mActionExit = rFileMenu->addAction(tr("&Exit"), this,
                                       SLOT(close()), QKeySequence::Quit);
}

void MainWindow::SetupEditMenu()
{
    QMenu *rEditMenu = new QMenu(tr("&Edit"), this);
    menuBar()->addMenu(rEditMenu);

    mActionCut = rEditMenu->addAction(tr("&Cut"), this,
                                      SLOT(Cut()), QKeySequence::Cut);
    mActionCopy = rEditMenu->addAction(tr("&Copy"), this,
                                       SLOT(Copy()), QKeySequence::Copy);
    mActionPaste = rEditMenu->addAction(tr("&Paste"), this,
                                        SLOT(Paste()), QKeySequence::Paste);
    mActionDelete = rEditMenu->addAction(tr("&Delete"), this,
                                         SLOT(Delete()), QKeySequence::Delete);
    rEditMenu->addSeparator();
    mActionUndo = rEditMenu->addAction(tr("&Undo"), this,
                                       SLOT(Undo()), QKeySequence::Undo);
    mActionRedo = rEditMenu->addAction(tr("&Redo"), this,
                                       SLOT(Redo()), QKeySequence::Redo);
    rEditMenu->addSeparator();
    mActionSelectAll = rEditMenu->addAction(tr("&Select All"), this,
                                            SLOT(SelectAll()), QKeySequence::SelectAll);
    mActionFind = rEditMenu->addAction(tr("&Find"), this,
                                       SLOT(Find()), QKeySequence::Find);
    rEditMenu->addSeparator();
    mActionOptions = rEditMenu->addAction(tr("&Options"), this,
                                          SLOT(Options()), QKeySequence::Preferences);
}

void MainWindow::SetupViewMenu()
{
    mViewMenu = new QMenu(tr("&View"), this);
    menuBar()->addMenu(mViewMenu);

    mWindowMapper = new QSignalMapper(this);
    connect(mWindowMapper, SIGNAL(mapped(QWidget *)),
            this, SLOT(SetActiveSubWindow(QWidget *)));

    connect(mViewMenu, SIGNAL(aboutToShow()), this, SLOT(UpdateViewMenu()));
    UpdateViewMenu();
}

void MainWindow::SetupHelpMenu()
{
    QMenu *rHelpMenu = new QMenu(tr("&Help"), this);
    menuBar()->addMenu(rHelpMenu);

    mActionAbout = rHelpMenu->addAction(tr("&About"), this, SLOT(About()));
}

void MainWindow::LoadState(QIODevice *pDevice)
{
    if (!pDevice->open(QIODevice::ReadOnly))
        return;

    QDataStream tData(pDevice);
    QByteArray tGeometry, tState;
    bool tStatusBar;
    bool tLineNumber;
    bool tGuideLine;
    bool tWordWrap;
    QString tFontStr;
    tData >> tGeometry >> tState >> tStatusBar
          >> tLineNumber >> tGuideLine >> tWordWrap >> tFontStr;
    pDevice->close();

    restoreGeometry(tGeometry);
    restoreState(tState);
    mStatusBar->setVisible(tStatusBar);
    LineNumber(tLineNumber);
    GuideLine(tGuideLine);
    WordWrap(tWordWrap);
    mCodeFont.fromString(tFontStr);
}

void MainWindow::SaveState(QIODevice *pDevice)
{
    if (!pDevice->open(QIODevice::WriteOnly))
        return;

    QDataStream tData(pDevice);
    tData << saveGeometry() << saveState() << mStatusBar->isVisible()
          << mIsLineNum << mIsGuideLine << mIsWordWrap << mCodeFont.toString();

    pDevice->close();
}

MdiSubWindow *MainWindow::CreateDocument()
{
    MdiSubWindow *rDocWindow = new MdiSubWindow(mMdiArea);

    CodeEdit *rDocument = new CodeEdit(rDocWindow);
    rDocument->SetModelFromReader(mXmlReader);
    rDocument->SetLineNumberVisibility(mIsLineNum);
    rDocument->SetGuideLineVisibility(mIsGuideLine);
    rDocument->SetWordWrap(mIsWordWrap);
    rDocument->setFont(mCodeFont);
    rDocument->SetStatusBar(mStatusBar);
    rDocument->setWindowTitle("[*]");

    GetOptionsWindow()->ApplyTo(rDocument);
    rDocWindow->SetEditor(rDocument);

    connect(rDocument, SIGNAL(modificationChanged(bool)),
            this, SLOT(DocumentWasModified(bool)));

    return rDocWindow;
}

QString MainWindow::GetCanonicalFile(const QString &pPath)
{
    QString rPath = pPath;
    if (QFileInfo(rPath).isFile())
        rPath = QFileInfo(rPath).canonicalFilePath();
    return rPath;
}

/*========================================================================================*/
