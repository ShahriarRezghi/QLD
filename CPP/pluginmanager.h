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

#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include "baseclass.h"

class PluginManager : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(QStringList neededPlugins READ neededPlugins WRITE
				   setNeededPlugins NOTIFY neededPluginsChanged)

	QStringList m_neededPlugins;

	QStringList extractModules();
	QStringList findPluginsFromModules();
	QStringList extractMudoulesFromFile(const QString &filepath);

public:
	explicit PluginManager(QObject *parent = nullptr);

	QStringList neededPlugins() const;

	void start();
	QStringList getAllSoFiles();

public slots:
	void setNeededPlugins(const QStringList &neededPlugins);

signals:
	void neededPluginsChanged(QStringList neededPlugins);
};

#endif  // PLUGINMANAGER_H
