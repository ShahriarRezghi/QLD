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

#include "pluginmanager.h"

void PluginManager::setNeededPlugins(const QStringList &neededPlugins)
{
	if (m_neededPlugins == neededPlugins) return;

	m_neededPlugins = neededPlugins;
	emit neededPluginsChanged(m_neededPlugins);
}

void PluginManager::start()
{
	m_neededPlugins.clear();

	m_neededPlugins << "xcbglintegrations"
					<< "platforms"
					<< "imageformats"
					<< "iconengines";

	m_neededPlugins << findPluginsFromModules();

	emit neededPluginsChanged(m_neededPlugins);
}

QStringList PluginManager::getAllSoFiles()
{
	QStringList sofiles;

	for (const QString &plugindir : m_neededPlugins)
		sofiles << findFilesInsideDir("*.so",
									  m_qtdir + "/plugins/" + plugindir);

	return sofiles;
}

QStringList PluginManager::findPluginsFromModules()
{
	QStringList plugins;

	QStringList modules = extractModules();

	if (modules.contains("sql")) plugins << "sqldrivers";
	if (modules.contains("gamepad")) plugins << "gamepads";
	if (modules.contains("printsupport")) plugins << "printsupport";

	if (modules.contains("sensors"))
		plugins << "sensors"
				<< "sensorgestures";

	if (modules.contains("positioning"))
		plugins << "geoservices"
				<< "position"
				<< "geometryloaders";

	if (modules.contains("multimedia"))
		plugins << "audio"
				<< "mediaservice"
				<< "playlistformats";

	return plugins;
}

QStringList PluginManager::extractModules()
{
	QStringList proandprifiles = findFilesInsideDir("*.pro", m_projectdir);
	proandprifiles << findFilesInsideDir("*.pri", m_projectdir);

	QStringList modules;
	for (const QString &file : proandprifiles)
		modules << extractMudoulesFromFile(file);

	modules.removeDuplicates();
	return modules;
}

QStringList PluginManager::extractMudoulesFromFile(const QString &filepath)
{
	QStringList modules;
	QFile F(filepath);
	if (!F.open(QIODevice::ReadOnly)) return QStringList();

	QString temp;
	QTextStream S(&F);

	while (S.readLineInto(&temp))
	{
		temp = temp.simplified();
		if (temp.startsWith("#")) continue;
		if (!temp.startsWith("QT")) continue;

		QStringList list = temp.split("+=", QString::SkipEmptyParts);
		if (list.count() != 2) list = temp.split("=", QString::SkipEmptyParts);
		if (list.count() != 2) continue;

		modules << list[1].split(" ", QString::SkipEmptyParts);
	}

	return modules;
}

PluginManager::PluginManager(QObject *parent) : BaseClass(parent) {}
QStringList PluginManager::neededPlugins() const { return m_neededPlugins; }
