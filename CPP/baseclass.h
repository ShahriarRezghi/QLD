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

#ifndef BASECLASS_H
#define BASECLASS_H

#include <QDebug>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QProcess>
#include <QTextStream>

class BaseClass : public QObject
{
	// This class is the base of the main c++ classes that are used in this
	// project. This class allows the derived classes access to the directories
	// That we are working here and some tool functions.

	Q_OBJECT

	Q_PROPERTY(QString qtdir READ qtdir WRITE setQtdir NOTIFY qtdirChanged)
	Q_PROPERTY(QString outputdir READ outputdir WRITE setOutputdir NOTIFY
				   outputdirChanged)
	Q_PROPERTY(QString projectdir READ projectdir WRITE setProjectdir NOTIFY
				   projectdirChanged)
	Q_PROPERTY(QString executablepath READ executablepath WRITE
				   setExecutablepath NOTIFY executablepathChanged)

	Q_PROPERTY(bool compileProject READ compileProject WRITE setCompileProject
				   NOTIFY compileProjectChanged)
	Q_PROPERTY(bool eraseOutput READ eraseOutput WRITE setEraseOutput NOTIFY
				   eraseOutputChanged)
	Q_PROPERTY(bool openOutput READ openOutput WRITE setOpenOutput NOTIFY
				   openOutputChanged)
	Q_PROPERTY(bool compressOutput READ compressOutput WRITE setCompressOutput
				   NOTIFY compressOutputChanged)

protected:
	static bool m_openOutput;
	static bool m_eraseOutput;
	static bool m_compressOutput;
	static bool m_compileProject;

	static QString m_qtdir;
	static QString m_outputdir;
	static QString m_projectdir;
	static QString m_executablepath;

	QStringList findFilesInsideDir(const QString &name, const QString &dirpath);

public:
	explicit BaseClass(QObject *parent = nullptr);

	QString qtdir() const;
	QString outputdir() const;
	QString projectdir() const;
	QString executablepath() const;

	bool openOutput() const;
	bool eraseOutput() const;
	bool compileProject() const;
	bool compressOutput() const;

public slots:
	void setQtdir(const QString &qtdir);
	void setOutputdir(const QString &outputdir);
	void setProjectdir(const QString &projectdir);
	void setExecutablepath(const QString &executablepath);

	void setOpenOutput(bool openOutput);
	void setEraseOutput(bool eraseOutput);
	void setCompileProject(bool compileProject);
	void setCompressOutput(bool compressOutput);

signals:
	void qtdirChanged(QString qtdir);
	void outputdirChanged(QString outputdir);
	void projectdirChanged(QString projectdir);
	void executablepathChanged(QString executablepath);

	void openOutputChanged(bool openOutput);
	void eraseOutputChanged(bool eraseOutput);
	void compileProjectChanged(bool compileProject);
	void compressOutputChanged(bool compressOutput);
};

#endif  // BASECLASS_H
