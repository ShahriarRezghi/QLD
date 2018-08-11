/* Copyright (C) 2018  Shahriar Rezghi
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * You can contact me by email: shahriar25.ss@gmail.com */

#ifndef MAINMANAGER_H
#define MAINMANAGER_H

#include "baseclass.h"
#include "cppmanager.h"
#include "outputmanager.h"
#include "pluginmanager.h"
#include "projectcompiler.h"
#include "qmlmanager.h"

class MainManager : public BaseClass
{
	// This class contains all of the main classes and manages them and
	// interacts with QML

	Q_OBJECT

	Q_PROPERTY(bool preparing READ preparing WRITE setPreparing NOTIFY
				   preparingChanged)
	Q_PROPERTY(bool processing READ processing WRITE setProcessing NOTIFY
				   processingChanged)

	Q_PROPERTY(QString prepareStatus READ prepareStatus WRITE setPrepareStatus
				   NOTIFY prepareStatusChanged)
	Q_PROPERTY(QString processingStatus READ processingStatus WRITE
				   setProcessingStatus NOTIFY processingStatusChanged)

	CppManager *m_cpp;
	QmlManager *m_qml;
	PluginManager *m_plg;
	OutputManager *m_out;
	ProjectCompiler *m_prj;

	bool m_preparing;
	bool m_processing;

	QString m_prepareStatus;
	QString m_processingStatus;

	QStringList getAllExecutables();

	bool cleanup();
	bool compress();

	void prepare();
	void start();

	static void prepareStatic(MainManager *main);
	static void startStatic(MainManager *main);

public:
	explicit MainManager(CppManager *cpp, QmlManager *qml, OutputManager *out,
						 PluginManager *plg, ProjectCompiler *prj,
						 QObject *parent = nullptr);

	bool preparing() const;
	bool processing() const;

	QString prepareStatus() const;
	QString processingStatus() const;

public slots:
	void setPaths(const QString &qtdir, const QString &execpath,
				  const QString &projectdir, const QString &outdir);

	void safePrepare();
	void safeStart();

	bool hasPrems(const QString &path);
	QString stringFromUrl(QString url);
	bool pathExists(bool isdir, const QString &path);

	bool checkQtBuildPath(QString path);
	bool checkProjectDirectory(QString path);

	void showDirectory(const QString &directory);

	void setPreparing(bool preparing);
	void setProcessing(bool processing);

	void setPrepareStatus(QString prepareStatus);
	void setProcessingStatus(QString processingStatus);

signals:
	void preparingChanged(bool preparing);
	void processingChanged(bool processing);

	void prepareStatusChanged(QString prepareStatus);
	void processingStatusChanged(QString processingStatus);
};

#endif  // MAINMANAGER_H
