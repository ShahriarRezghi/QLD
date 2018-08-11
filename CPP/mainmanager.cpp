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

#include "mainmanager.h"

#include <QDesktopServices>
#include <QProcess>
#include <QtConcurrent/QtConcurrent>

QStringList MainManager::getAllExecutables()
{
	QStringList list = m_qml->getAllSoFiles();
	list << m_plg->getAllSoFiles();
	list << m_executablepath;

	return list;
}

bool MainManager::cleanup()
{
	QString program = "make";
	QStringList args;
	args << "clean";

	QProcess P;
	P.setWorkingDirectory(m_projectdir);
	P.start(program, args);

	P.waitForFinished();

	bool x1 = P.exitCode();
	bool x2 = QFile(m_projectdir + "/Makefile").remove();
	bool x3 = QFile(m_executablepath).remove();

	return x1 && x2 && x3;
}

bool MainManager::compress()
{
	QString name;
	auto list = QDir(m_projectdir).entryList(QStringList() << "*.pro");

	if (list.size() == 1)
	{
		name = list.first();
		name.remove(name.size() - 4, 4);
	}
	else
		name = QFileInfo(m_executablepath).baseName();

	name += ".tar.xz";
	auto wd = QFileInfo(m_outputdir).dir().path();

	QString program = "tar";
	QStringList args;
	args << "-cJf";
	args << name;
	args << QDir(m_outputdir).dirName();

	QProcess P;
	P.setWorkingDirectory(wd);
	P.start(program, args);

	P.waitForFinished(-1);
	auto ec = P.exitCode();

	return ec;
}

MainManager::MainManager(CppManager *cpp, QmlManager *qml, OutputManager *out,
						 PluginManager *plg, ProjectCompiler *prj,
						 QObject *parent)
	: BaseClass(parent)
{
	m_cpp = cpp;
	m_qml = qml;
	m_out = out;
	m_plg = plg;
	m_prj = prj;

	m_preparing = false;
	m_processing = false;
}

void MainManager::prepare()
{
	setPreparing(true);

	setPrepareStatus("Gathering Info About QML");
	m_qml->start();

	setPrepareStatus("Gathering Info About Plugins");
	m_plg->start();

	setPrepareStatus("Gathering Info About C++");
	m_cpp->start(getAllExecutables());

	setPrepareStatus("");
	setPreparing(false);
}

void MainManager::start()
{
	setProcessing(true);

	setProcessingStatus("Copying Files");
	m_out->copyAll(m_cpp->getQtLibrariesFullPaths(), m_cpp->cppLibraries(),
				   m_qml->foundImports(), m_plg->neededPlugins(),
				   m_eraseOutput);

	if (m_compileProject)
	{
		setProcessingStatus("Cleaning Up");
		cleanup();
	}

	if (m_compressOutput)
	{
		setProcessingStatus("Compressing");
		compress();
	}

	setProcessingStatus("");
	setProcessing(false);
}

void MainManager::startStatic(MainManager *main) { main->start(); }

void MainManager::prepareStatic(MainManager *main) { main->prepare(); }

bool MainManager::hasPrems(const QString &path)
{
	QFileInfo info(path);
	return (info.isReadable() && info.isWritable());
}

QString MainManager::stringFromUrl(QString url)
{
	return url.remove("file://");
}

bool MainManager::pathExists(bool isdir, const QString &path)
{
	if (isdir) return QDir(path).exists();
	return QFile(path).exists();
}

bool MainManager::checkQtBuildPath(QString path)
{
	if (!path.endsWith('/')) path += '/';

	bool x = pathExists(true, path + "qml");
	if (x) x = pathExists(true, path + "bin");
	if (x) x = pathExists(true, path + "lib");
	if (x) x = pathExists(true, path + "plugins");

	return x;
}

bool MainManager::checkProjectDirectory(QString path)
{
	auto list = QDir(path).entryList(QStringList() << "*.pro");
	return list.size() == 1;
}

void MainManager::showDirectory(const QString &directory)
{
	QDesktopServices::openUrl("file://" + directory);
}

void MainManager::setPreparing(bool preparing)
{
	if (m_preparing == preparing) return;

	m_preparing = preparing;
	emit preparingChanged(m_preparing);
}

void MainManager::setProcessing(bool processing)
{
	if (m_processing == processing) return;

	m_processing = processing;
	emit processingChanged(m_processing);
}

void MainManager::setPrepareStatus(QString prepareStatus)
{
	if (m_prepareStatus == prepareStatus) return;

	m_prepareStatus = prepareStatus;
	emit prepareStatusChanged(m_prepareStatus);
}

void MainManager::setProcessingStatus(QString processingStatus)
{
	if (m_processingStatus == processingStatus) return;

	m_processingStatus = processingStatus;
	emit processingStatusChanged(m_processingStatus);
}

bool MainManager::preparing() const { return m_preparing; }

bool MainManager::processing() const { return m_processing; }

QString MainManager::prepareStatus() const { return m_prepareStatus; }

QString MainManager::processingStatus() const { return m_processingStatus; }

void MainManager::setPaths(const QString &qtdir, const QString &execpath,
						   const QString &projectdir, const QString &outdir)
{
	QStringList list;
	list << qtdir << execpath << projectdir << outdir;

	for (QString &S : list)
		if (S.count() && S[S.count() - 1] == "/") S.remove(S.count() - 1, 1);

	setQtdir(list[0]);
	setExecutablepath(list[1]);
	setProjectdir(list[2]);
	setOutputdir(list[3]);
}

void MainManager::safeStart()
{
	QtConcurrent::run(&MainManager::startStatic, this);
}

void MainManager::safePrepare()
{
	QtConcurrent::run(&MainManager::prepareStatic, this);
}
