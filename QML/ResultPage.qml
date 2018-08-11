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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0

Page {
	clip: true
	objectName: "Result"

	header: ColumnLayout {
		spacing: 0

		TabBar {
			id: tabBar
			Layout.fillWidth: true

			TabButton {
				width: implicitWidth
				text: "Copied Paths"
			}

			TabButton {
				width: implicitWidth
				text: "Qt Libraries"
			}

			TabButton {
				width: implicitWidth
				text: "Non-Qt Libraries"
			}

			TabButton {
				width: implicitWidth
				text: "Unknown Libraries"
			}

			TabButton {
				width: implicitWidth
				text: "Qml Imports"
			}

			TabButton {
				width: implicitWidth
				text: "Failed Qml Imports"
			}
		}

		Rectangle {
			height: 1
			Layout.fillWidth: true
			color: Material.accent
		}
	}

	ListView {
		id: listview
		clip: true
		anchors.fill: parent
		ScrollBar.vertical: ScrollBar {}

		model: {
			var i = tabBar.currentIndex

			if (i == 0)
				return OutputManager.pathsToCopy
			else if (i == 1)
				return CppManager.qtLibraries
			else if (i == 2)
				return CppManager.cppLibraries
			else if (i == 3)
				return CppManager.notFoundLibs
			else if (i == 4)
				return QmlManager.foundImports
			else if (i == 5)
				return QmlManager.notFoundImports
		}

		Label {
			text: "Nothing Here"
			visible: !parent.count
			anchors.centerIn: parent
		}

		delegate: Label {
			id: label
			padding: 10
			width: parent.width
			elide: Text.ElideRight

			text: (tabBar.currentIndex == 0 ? (OutputManager.copySuccess[index]
											   ? "✔   ":"🞪   "):"") + modelData
		}
	}
}
