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

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0

Page {
	id: page
	clip: true
	padding: 15
	rightPadding: 5
	objectName: "PathSelection"

	Settings {
		property alias qtdir: qtdir.content
		property alias outdir: outdir.content
		property alias execpath: execpath.content
		property alias projectdir: projectdir.content
		property alias compile: compileCheck.checked
	}

	contentItem: ColumnLayout {
		spacing: 15
		enabled: !busy.running

		PathChooser {
			id: qtdir
			title: "Qt Build Directory"
			onInfoClicked: infoDialog.openPopup(0)

			checkFunction: function(text, wlabel) {
				var x = defaultCheckFunction(text, wlabel)

				if (x) {
					x = MainManager.checkQtBuildPath(text)
					if (!x) wlabel.text = "This doesn't seem to be a Qt build directory"
				}

				return x
			}
		}

		PathChooser {
			id: execpath
			isdir: false
			title: "Executable File Path"
			visible: !compileCheck.checked
			onInfoClicked: infoDialog.openPopup(1)
		}

		PathChooser {
			id: projectdir
			title: "Project Directory"
			onInfoClicked: infoDialog.openPopup(2)

			checkFunction: function(text, wlabel) {
				var x = defaultCheckFunction(text, wlabel)

				if (x) {
					x = MainManager.checkProjectDirectory(text)
					if (!x) wlabel.text = "This doesn't seem to be a Qt project directory"
				}

				return x
			}
		}

		PathChooser {
			id: outdir
			title: "Final Output Directory"
			onInfoClicked: infoDialog.openPopup(3)
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}

		RowLayout {
			CheckBox {
				id: compileCheck
				Layout.fillWidth: true
				text: "Compile the project from source"

				onCheckedChanged: MainManager.compileProject = checked
			}

			Button {
				flat: true
				text: "Next"
				font.bold: true
				highlighted: true
				Layout.rightMargin: 10

				enabled: qtdir.confirmed && (compileCheck.checked || execpath.confirmed)
						 && projectdir.confirmed && outdir.confirmed

				onClicked: {
					MainManager.setPaths(qtdir.content, execpath.content,
										 projectdir.content, outdir.content)

					if (compileCheck.checked) {
						ProjectCompiler.compile()
						stackView.push(compilingPage)
					}
					else
						MainManager.safePrepare()
				}
			}
		}
	}

	ColumnLayout {
		parent: page
		anchors.centerIn: parent

		BusyIndicator {
			id: busy
			running: MainManager.preparing
			Layout.alignment: Qt.AlignHCenter
		}

		Label {
			text: MainManager.prepareStatus
			Layout.alignment: Qt.AlignHCenter
		}
	}

	Connections {
		target: MainManager
		onPreparingChanged: if (!preparing) stackView.push(preparationPage)
	}
}
