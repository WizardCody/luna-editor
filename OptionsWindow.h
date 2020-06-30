/*******************************************************************************************
**
** Project: Luna Editor
** File: OptionsWindow.h
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

#ifndef OPTIONSWINDOW_H
#define OPTIONSWINDOW_H

#include "generated/OptionsWindow_ui.h"

/*======================================== CLASSES =======================================*/

QT_BEGIN_NAMESPACE
class QSettings;
QT_END_NAMESPACE

class MainWindow;
class CodeEdit;
class SourceParser;

class OptionsWindow : public QDialog
{
    Q_OBJECT

    public:
        explicit OptionsWindow(MainWindow *pParent);

        void SetSettings(QSettings *pSettings);
        QSettings *GetSettings() const { return rSettings; }
        void SaveSettings(QSettings *pDevice);
        void LoadSettings(QSettings *pDevice);

        void ApplyCurrent();
        void ApplyAll();
        void ApplyTo(CodeEdit *pDoc);

        QString GetSource() const;
        SourceParser *GetSourceParser() const { return mSourceParser; }

    public slots:
        void accept();
        void reject();
        void apply();

        void SourceDir();
        void SourceParse();
        void SourceClean();

    protected:
        void changeEvent(QEvent *pEvent);

    private:
        Ui_OptionsWindow ui;

        MainWindow *rMainWindow;
        SourceParser *mSourceParser;

        QSettings *rSettings;
};

#endif // OPTIONSWINDOW_H

/*========================================================================================*/
