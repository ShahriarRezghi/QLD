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

#ifndef CPPMANAGER_H
#define CPPMANAGER_H

#include "baseclass.h"

class CppManager : public BaseClass
{
	// This class tries to figure out which libraries this project depends
	// on. The libraries devides into three catagoreies:
	// 1. qt libraries
	// 2. libraries that are non-qt and existant
	// 3. libraries that are not found

	Q_OBJECT
	Q_PROPERTY(QStringList qtLibraries READ qtLibraries WRITE setQtLibraries
				   NOTIFY qtLibrariesChanged)

	Q_PROPERTY(QStringList cppLibraries READ cppLibraries WRITE setCppLibraries
				   NOTIFY cppLibrariesChanged)

	Q_PROPERTY(QStringList notFoundLibs READ notFoundLibs WRITE setNotFoundLibs
				   NOTIFY notFoundLibsChanged)

	QStringList m_qtLibraries;
	QStringList m_cppLibraries;
	QStringList m_notFoundLibs;

	void extractAllLibs(const QStringList &execfiles);
	QStringList extractLibsFromExecutable(const QString &execpath);

	void divideLibraries();

public:
	explicit CppManager(QObject *parent = nullptr);

	QStringList qtLibraries() const;
	QStringList cppLibraries() const;
	QStringList notFoundLibs() const;

	QStringList getQtLibrariesFullPaths();

	void start(const QStringList &executables);

public slots:
	void setQtLibraries(const QStringList &qtLibraries);
	void setCppLibraries(const QStringList &cppLibraries);
	void setNotFoundLibs(const QStringList &notFoundLibs);

signals:
	void qtLibrariesChanged(QStringList qtLibraries);
	void cppLibrariesChanged(QStringList cppLibraries);
	void notFoundLibsChanged(QStringList notFoundLibs);
};

#endif  // CPPMANAGER_H
