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

#ifndef PROJECTCOMPILER_H
#define PROJECTCOMPILER_H

#include "baseclass.h"

#include <QProcess>

enum CompileState
{
	BaseState,      // = 0
	QmakeState,     // = 1
	MakeState,      // = 2
	FinishedState,  // = 3
	FailedState     // = 4
};

class ProjectCompiler : public BaseClass
{
	Q_OBJECT

	Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
	Q_PROPERTY(QString output READ output WRITE setOutput NOTIFY outputChanged)

	int m_state;
	QString m_output;
	QProcess m_process;

	QString findProFile();

private slots:
	void readOutput();
	void compileFinished(int exitCode);
	void handleError(QProcess::ProcessError E);

public:
	explicit ProjectCompiler(QObject *parent = nullptr);

	int state() const;
	QString output() const;

public slots:
	void compile();

	void setState(int state);
	void setOutput(QString output);

signals:
	void outputChanged();
	void stateChanged(int state);
};

#endif  // PROJECTCOMPILER_H
