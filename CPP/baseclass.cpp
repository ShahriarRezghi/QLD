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

#include "baseclass.h"

QString BaseClass::m_qtdir = QString();
QString BaseClass::m_outputdir = QString();
QString BaseClass::m_projectdir = QString();
QString BaseClass::m_executablepath = QString();

bool BaseClass::m_openOutput = false;
bool BaseClass::m_eraseOutput = false;
bool BaseClass::m_compileProject = false;
bool BaseClass::m_compressOutput = false;

BaseClass::BaseClass(QObject *parent) : QObject(parent) {}

QStringList BaseClass::findFilesInsideDir(const QString &name,
										  const QString &dirpath)
{
	QStringList files;

	QDir dir(dirpath);
	dir.setNameFilters(QStringList(name));

	QDirIterator it(dir, QDirIterator::Subdirectories);
	while (it.hasNext()) files << it.next();

	return files;
}

QString BaseClass::qtdir() const { return m_qtdir; }

QString BaseClass::outputdir() const { return m_outputdir; }

QString BaseClass::projectdir() const { return m_projectdir; }

QString BaseClass::executablepath() const { return m_executablepath; }

bool BaseClass::openOutput() const { return m_openOutput; }

bool BaseClass::eraseOutput() const { return m_eraseOutput; }

bool BaseClass::compileProject() const { return m_compileProject; }

bool BaseClass::compressOutput() const { return m_compressOutput; }

void BaseClass::setQtdir(const QString &qtdir)
{
	if (m_qtdir == qtdir) return;

	m_qtdir = qtdir;
	emit qtdirChanged(m_qtdir);
}

void BaseClass::setOutputdir(const QString &outputdir)
{
	if (m_outputdir == outputdir) return;

	m_outputdir = outputdir;
	emit outputdirChanged(m_outputdir);
}

void BaseClass::setProjectdir(const QString &projectdir)
{
	if (m_projectdir == projectdir) return;

	m_projectdir = projectdir;
	emit projectdirChanged(m_projectdir);
}

void BaseClass::setExecutablepath(const QString &executablepath)
{
	if (m_executablepath == executablepath) return;

	m_executablepath = executablepath;
	emit executablepathChanged(m_executablepath);
}

void BaseClass::setCompileProject(bool compileProject)
{
	if (m_compileProject == compileProject) return;

	m_compileProject = compileProject;
	emit compileProjectChanged(m_compileProject);
}

void BaseClass::setCompressOutput(bool compressOutput)
{
	if (m_compressOutput == compressOutput) return;

	m_compressOutput = compressOutput;
	emit compressOutputChanged(m_compressOutput);
}

void BaseClass::setEraseOutput(bool eraseOutput)
{
	if (m_eraseOutput == eraseOutput) return;

	m_eraseOutput = eraseOutput;
	emit eraseOutputChanged(m_eraseOutput);
}

void BaseClass::setOpenOutput(bool openOutput)
{
	if (m_openOutput == openOutput) return;

	m_openOutput = openOutput;
	emit openOutputChanged(m_openOutput);
}
