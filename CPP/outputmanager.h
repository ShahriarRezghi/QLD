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

#ifndef OUTPUTMANAGER_H
#define OUTPUTMANAGER_H

#include "baseclass.h"

class OutputManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList pathsToCopy READ pathsToCopy WRITE setPathsToCopy
				   NOTIFY pathsToCopyChanged)

	Q_PROPERTY(QList<bool> copySuccess READ copySuccess WRITE setCopySuccess
				   NOTIFY copySuccessChanged)

	QStringList m_pathsToCopy;
	QList<bool> m_copySuccess;

	bool copyDir(const QString &source, const QString &destin);
	bool copyFile(const QString &source, const QString &destin);

	void copyCpp(const QStringList &libs);
	void copyQml(const QStringList &dirs);
	void copyPlugins(const QStringList &plugins);

	void createDirectories();
	void createRunFile();
	void copyExec();

public:
	explicit OutputManager(QObject *parent = nullptr);

	QStringList pathsToCopy() const;
	QList<bool> copySuccess() const;

	void copyAll(const QStringList &qtlibs, const QStringList &libs,
				 const QStringList &dirs, const QStringList &plugins,
				 bool erase);

public slots:
	void setPathsToCopy(const QStringList &pathsToCopy);
	void setCopySuccess(const QList<bool> &copySuccess);

signals:
	void pathsToCopyChanged(QStringList pathsToCopy);
	void copySuccessChanged(QList<bool> copySuccess);
};

#endif  // OUTPUTMANAGER_H
