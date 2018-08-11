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

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <CPP/cppmanager.h>
#include <CPP/mainmanager.h>
#include <CPP/outputmanager.h>
#include <CPP/pluginmanager.h>
#include <CPP/projectcompiler.h>
#include <CPP/qmlmanager.h>

int main(int argc, char *argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);

	CppManager C;
	QmlManager Q;
	PluginManager P;
	OutputManager O;
	ProjectCompiler PC;
	MainManager M(&C, &Q, &O, &P, &PC);

	QQmlApplicationEngine engine;

	auto *R = engine.rootContext();
	R->setContextProperty("CppManager", &C);
	R->setContextProperty("QmlManager", &Q);
	R->setContextProperty("PluginManager", &P);
	R->setContextProperty("MainManager", &M);
	R->setContextProperty("OutputManager", &O);
	R->setContextProperty("ProjectCompiler", &PC);

	engine.load(QUrl(QLatin1String("qrc:/QML/main.qml")));
	if (engine.rootObjects().isEmpty()) return -1;

	return app.exec();
}
