/*******************************************************************************************
**
** Project: Luna Editor
** File: ExporterHtml.cpp
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

#include "ExporterHtml.h"

#include <QtGui/QApplication>
#include <QtGui/QProgressDialog>
#include <QtGui/QStandardItemModel>
#include <QtGui/QFileDialog>
#include <QtCore/QFile>
#include <QtCore/QDebug>

#include "XmlReader.h"

/*======================================== PUBLIC ========================================*/

ExporterHtml::ExporterHtml(QWidget *pParent) :
    QObject(pParent),
    rParentWidget(pParent)
{
}

QString ExporterHtml::GetFileDialog(QWidget *pParent)
{
    return QFileDialog::getSaveFileName(pParent, tr("Export to..."),
                                        QApplication::applicationDirPath(),
                                        "html file (*.html)");
}

void ExporterHtml::ExportFromXml(XmlReader *pReader)
{
    QString tMainFilePath = GetFileDialog(rParentWidget);
    if (tMainFilePath.isEmpty())
        return;

    QProgressDialog tProgress(rParentWidget);
    tProgress.setCancelButtonText("Abort");
    tProgress.setMinimumSize(tProgress.size());
    tProgress.setMaximumSize(tProgress.size());
    tProgress.setWindowFlags(rParentWidget->windowFlags());
    tProgress.setWindowModality(Qt::WindowModal);
    tProgress.setMinimumDuration(0);

    tProgress.setLabelText("Processing...");
    tProgress.show();

    QFileInfo tMainFileInfo(tMainFilePath);
    QDir tMainFileDir = tMainFileInfo.absoluteDir();
    QString tFolderName = tMainFileInfo.baseName()+"_src";
    QDir tSrcDir = tMainFileDir.path()+'/'+tFolderName;
    if (!tMainFileDir.mkdir(tFolderName)) {
        qDebug() << "cannot make" << tSrcDir.path();
        if (!tSrcDir.exists())
            return;
    }

    QFile tTemplateFuncFile("Data/Templates/html/function.html");
    if (!tTemplateFuncFile.open(QIODevice::ReadOnly)) {
        qDebug() << "cannot open template file";
        return;
    }

    QTextStream tTemplateFuncStream(&tTemplateFuncFile);
    QString tFuncData = tTemplateFuncStream.readAll();

    QStandardItemModel *tModel = qobject_cast<QStandardItemModel *>
                                 (pReader->GetModel(parent()));

    QString tFuncListTAG;
    tProgress.setMaximum(tModel->rowCount());
    for (int i = 0; i < tModel->rowCount(); i++) {
        QString tFuncName = tModel->item(i)->text();
        QString tFuncFileName = tFuncName+".html";
        QFile tFuncFile(tSrcDir.path()+'/'+tFuncFileName);
        tFuncFile.open(QIODevice::WriteOnly);
        QTextStream tStream(&tFuncFile);
        QString finalData = tFuncData;
        finalData.replace("[LUNAEDITOR_TAGS:FUNC_NAME]", tFuncName);
        QString tFuncTip = tModel->item(i)->toolTip();
        tFuncTip.replace("\n", "<br>");
        tFuncTip.replace("\r", "<br>");
        finalData.replace("[LUNAEDITOR_TAGS:FUNC_DESC]", tFuncTip);
        tStream << finalData;
        tFuncListTAG += "<a href=\""+tFolderName+'/'
                        +tFuncFileName+"\">"
                        +tFuncName+"</a><br>";
        tProgress.setValue(i+1);
    }

    tProgress.setLabelText("Exporting...");
    tProgress.setValue(0);
    tProgress.setMaximum(1);

    QFile tTemplateFile("Data/Templates/html/index.html");
    if (!tTemplateFile.open(QIODevice::ReadOnly)) {
        qDebug() << "cannot open template file";
        return;
    }

    QTextStream tTemplateStream(&tTemplateFile);
    QString tData = tTemplateStream.readAll();
    tData.replace("[LUNAEDITOR_TAGS:FUNC_LIST]", tFuncListTAG);

    QFile tMainFile(tMainFilePath);
    if (!tMainFile.open(QIODevice::WriteOnly)) {
        qDebug() << "cannot open" << tMainFile.fileName();
        return;
    }
    QTextStream tMainStream(&tMainFile);
    tMainStream << tData;

    tProgress.setValue(1);
}

/*===================================== PUBLIC SLOTS =====================================*/

/*===================================== PRIVATE SLOTS ====================================*/

/*======================================= PROTECTED ======================================*/

/*======================================== PRIVATE =======================================*/

/*========================================================================================*/
