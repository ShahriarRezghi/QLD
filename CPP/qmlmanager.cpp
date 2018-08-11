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

#include "qmlmanager.h"

void QmlManager::extractImportsFromDir(const QString &dirpath)
{
	for (const QString &filepath : findFilesInsideDir("*.qml", dirpath))
		for (QString &import : extractImportsFromFile(filepath))
		{
			QStringList list = import.split("#");
			import = list[1];

			if (list[0] == "2" &&
				m_secondVersionImports.contains(import.split("/").last()))
				import += ".2";

			if (!m_foundImports.contains(import))
			{
				m_foundImports << import;
				extractImportsFromDir(m_qtdir + "/qml/" + import);
			}
		}
}

QStringList QmlManager::extractImportsFromFile(const QString &filepath)
{
	QStringList imports;
	QFile F(filepath);
	if (!F.open(QIODevice::ReadOnly)) return QStringList();

	QString content = F.readAll();
	content.remove(QRegExp("\\{(.*)\\}"));
	content.remove(QRegExp("/\\*(.*)\\*/"));

	for (const QString &line : content.split("\n"))
		for (QString &word : line.split(";", QString::SkipEmptyParts))
		{
			word = word.simplified();
			if (word.startsWith("//")) continue;
			if (!word.startsWith("import")) continue;

			QStringList list = word.split(" ", QString::SkipEmptyParts);
			if (list.count() != 3)
			{
				if (list.count() == 5)
				{
					if (list[3] != "as") continue;
				}
				else
					continue;
			}

			imports << (list[2][0] + "#" + list[1].replace(".", "/"));
		}

	return imports;
}

QStringList QmlManager::getAllQtQmlImports()
{
	QStringList dirs;

	QString dir = m_qtdir + "/qml";

	QDir qdir(dir);
	qdir.setFilter(QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

	QDirIterator it(qdir, QDirIterator::Subdirectories);
	while (it.hasNext()) dirs << it.next().remove(0, dir.count() + 1);

	return dirs;
}

void QmlManager::removeInnerImports()
{
	for (const QString &import : m_foundImports)
	{
		bool contains = false;

		for (const QString &S : m_foundImports)
			if (import.startsWith(S + "/")) contains = true;

		if (contains) m_foundImports.removeOne(import);
	}
}

void QmlManager::divideFoundAndNotFound()
{
	QStringList dirs = getAllQtQmlImports();

	for (const QString &S : m_foundImports)
		if (!dirs.contains(S))
		{
			m_notFoundImports << S;
			m_foundImports.removeOne(S);
		}
}

QmlManager::QmlManager(QObject *parent) : BaseClass(parent)
{
	m_secondVersionImports << "QtQuick"
						   << "Models"
						   << "Window"
						   << "Controls"
						   << "Particles"
						   << "Templates";
}

QStringList QmlManager::getAllSoFiles()
{
	QStringList sofiles;

	for (const QString &dirpath : m_foundImports)
		sofiles << findFilesInsideDir("*.so", m_qtdir + "/qml/" + dirpath);

	return sofiles;
}

void QmlManager::start()
{
	m_foundImports.clear();
	m_notFoundImports.clear();

	extractImportsFromDir(m_projectdir);
	removeInnerImports();
	divideFoundAndNotFound();

	emit foundImportsChanged(m_foundImports);
	emit notFoundImportsChanged(m_notFoundImports);
}

void QmlManager::setFoundImports(const QStringList &foundImports)
{
	if (m_foundImports == foundImports) return;

	m_foundImports = foundImports;
	emit foundImportsChanged(m_foundImports);
}

void QmlManager::setNotFoundImports(const QStringList &nonFoundImports)
{
	if (m_notFoundImports == nonFoundImports) return;

	m_notFoundImports = nonFoundImports;
	emit notFoundImportsChanged(m_notFoundImports);
}

QStringList QmlManager::foundImports() const { return m_foundImports; }
QStringList QmlManager::notFoundImports() const { return m_notFoundImports; }
