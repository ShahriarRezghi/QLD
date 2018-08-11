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
import Qt.labs.settings 1.0

ApplicationWindow {
	id: window
	visible: true
	title: qsTr("Qt Linux Deployer")

	width: 600
	height: baseItem.implicitHeight + 30 + header.height

	minimumWidth: 600
	minimumHeight: baseItem.implicitHeight + 30 + header.height

	property real smallFont: window.font.pointSize
	property real mediumFont: window.font.pointSize + 2
	property real largeFont: window.font.pointSize + 4

	property bool darkTheme: true
	property color primary: Material.color(Material.Teal)

	Material.theme: darkTheme ? Material.Dark:Material.Light
	Material.accent: primary
	Material.primary: primary

	header: ApplicationHeader { }

	property var baseItem

	StackView {
		id: stackView
		anchors.fill: parent
		initialItem: pathSelectionPage

		Component.onCompleted: baseItem = currentItem

		property var currentPage: {
			var v = currentItem.objectName

			if (v == "PathSelection") return pathSelectionPage
			else if (v == "Preparation") return preparationPage
			else if (v == "Compile") return compilingPage
			else if (v == "Result") return resultPage
		}

		Component {
			id: pathSelectionPage
			PathSelectionPage { }
		}

		Component {
			id: preparationPage
			PreparationPage { }
		}

		Component {
			id: compilingPage
			CompilingPage { }
		}

		Component {
			id: resultPage
			ResultPage { }
		}
	}

	Settings {
		property alias x: window.x
		property alias y: window.y

		property alias primary: window.primary
		property alias darkTheme: window.darkTheme
	}

	InfoDialog {
		id: infoDialog
	}

	AboutDialog {
		id: aboutDialog
	}

	SettingsDialog {
		id: settingsDialog
	}
}
