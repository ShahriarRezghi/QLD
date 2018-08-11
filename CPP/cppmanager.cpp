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

#include "cppmanager.h"

void CppManager::setQtLibraries(const QStringList &qtLibraries)
{
	if (m_qtLibraries == qtLibraries) return;

	m_qtLibraries = qtLibraries;
	emit qtLibrariesChanged(m_qtLibraries);
}

void CppManager::setCppLibraries(const QStringList &cppLibraries)
{
	if (m_cppLibraries == cppLibraries) return;

	m_cppLibraries = cppLibraries;
	emit cppLibrariesChanged(m_cppLibraries);
}

void CppManager::setNotFoundLibs(const QStringList &notFoundLibs)
{
	if (m_notFoundLibs == notFoundLibs) return;

	m_notFoundLibs = notFoundLibs;
	emit notFoundLibsChanged(m_notFoundLibs);
}

void CppManager::extractAllLibs(const QStringList &execfiles)
{
	for (const QString &execfile : execfiles)
		for (const QString &lib : extractLibsFromExecutable(execfile))
			if (!m_cppLibraries.contains(lib))
			{
				m_cppLibraries << lib;
				extractAllLibs(QStringList(lib));
			}
}

QStringList CppManager::extractLibsFromExecutable(const QString &execpath)
{
	QProcess P;
	P.start("ldd " + execpath, QProcess::ReadOnly);

	if (!P.waitForStarted()) return QStringList();
	if (!P.waitForFinished()) return QStringList();

	auto data = QString(P.readAll());
	QStringList libs;

	for (QString &line : data.split("\n", QString::SkipEmptyParts))
	{
		line = line.simplified();
		auto innerlist = line.split(" ");

		if (innerlist.count() < 3) continue;
		line = innerlist[2];

		if (!line.startsWith("/"))
			m_notFoundLibs << innerlist[0];
		else
			libs << line;
	}

	return libs;
}

void CppManager::divideLibraries()
{
	QFileInfo libInfo;

	for (QString lib : m_cppLibraries)
	{
		//		QString name;
		libInfo.setFile(lib);
		QString name = libInfo.fileName();

		if (!name.isEmpty() &&
			(name.startsWith("libQt") || lib.startsWith(m_qtdir)))
		{
			m_qtLibraries << name;
			m_cppLibraries.removeOne(lib);
		}
	}
}

void CppManager::start(const QStringList &executables)
{
	m_qtLibraries.clear();
	m_cppLibraries.clear();
	m_notFoundLibs.clear();

	extractAllLibs(executables);
	divideLibraries();

	m_notFoundLibs.removeDuplicates();

	emit qtLibrariesChanged(m_qtLibraries);
	emit cppLibrariesChanged(m_cppLibraries);
	emit notFoundLibsChanged(m_notFoundLibs);
}

QStringList CppManager::getQtLibrariesFullPaths()
{
	QStringList paths;

	auto dir = m_qtdir + "/lib";
	for (const QString &qtlib : m_qtLibraries) paths << dir + "/" + qtlib;

	return paths;
}

CppManager::CppManager(QObject *parent) : BaseClass(parent) {}
QStringList CppManager::qtLibraries() const { return m_qtLibraries; }
QStringList CppManager::cppLibraries() const { return m_cppLibraries; }
QStringList CppManager::notFoundLibs() const { return m_notFoundLibs; }
