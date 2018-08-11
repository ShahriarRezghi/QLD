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

#ifndef QMLMANAGER_H
#define QMLMANAGER_H

#include "baseclass.h"

class QmlManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList foundImports READ foundImports WRITE setFoundImports
				   NOTIFY foundImportsChanged)

	Q_PROPERTY(QStringList notFoundImports READ notFoundImports WRITE
				   setNotFoundImports NOTIFY notFoundImportsChanged)

	QStringList m_foundImports;
	QStringList m_notFoundImports;

	QStringList m_secondVersionImports;

public:  // TODO remove
	void extractImportsFromDir(const QString &dirpath);
	QStringList extractImportsFromFile(const QString &filepath);

	QStringList getAllQtQmlImports();
	void removeInnerImports();
	void divideFoundAndNotFound();

public:
	explicit QmlManager(QObject *parent = nullptr);

	QStringList foundImports() const;
	QStringList notFoundImports() const;

	void start();
	QStringList getAllSoFiles();

public slots:
	void setFoundImports(const QStringList &foundImports);
	void setNotFoundImports(const QStringList &notFoundImports);

signals:
	void foundImportsChanged(QStringList foundImports);
	void notFoundImportsChanged(QStringList notFoundImports);
};

#endif  // QMLMANAGER_H
