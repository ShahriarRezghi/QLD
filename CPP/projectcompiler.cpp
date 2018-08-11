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

#include "projectcompiler.h"

ProjectCompiler::ProjectCompiler(QObject *parent) : BaseClass(parent)
{
	setState(BaseState);

	connect(&m_process, &QProcess::readyRead, this,
			&ProjectCompiler::readOutput);

	connect(&m_process, &QProcess::errorOccurred, this,
			&ProjectCompiler::handleError);

	connect(&m_process,
			QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this,
			&ProjectCompiler::compileFinished);
}

QString ProjectCompiler::findProFile()
{
	QStringList ft;
	ft << "*.pro";
	auto pros = QDir(m_projectdir).entryList(ft);

	return (pros.size() != 1) ? "" : pros.front();
}

void ProjectCompiler::compileFinished(int exitCode)
{
	if (m_state == QmakeState)
	{
		m_process.start("make");
		setState(MakeState);
	}
	else if (m_state == MakeState)
		setState(exitCode == 0 ? FinishedState : FailedState);
}

void ProjectCompiler::handleError(QProcess::ProcessError E)
{
	qDebug() << m_process.errorString();
}

void ProjectCompiler::compile()
{
	setOutput("");
	setState(QmakeState);

	m_process.setWorkingDirectory(m_projectdir);
	auto proFilePath = m_projectdir + "/" + findProFile();

	auto ep = proFilePath;
	ep.remove(ep.size() - 4, 4);
	setExecutablepath(ep);

	auto program = m_qtdir + "/bin/qmake";
	QStringList args;
	args << proFilePath;

	m_process.start(program, args);
}

void ProjectCompiler::setState(int state)
{
	if (m_state == state) return;

	m_state = state;
	emit stateChanged(m_state);
}

void ProjectCompiler::setOutput(QString output)
{
	if (m_output == output) return;

	m_output = output;
	emit outputChanged();
}

int ProjectCompiler::state() const { return m_state; }

QString ProjectCompiler::output() const { return m_output; }

void ProjectCompiler::readOutput()
{
	auto data = m_process.readAll();
	m_output += data;
	emit outputChanged();
}
