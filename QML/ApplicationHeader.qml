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

import QtQuick 2.0
import QtQuick.Controls 2.0

TopBar {
	text: {
		if (stackView.currentPage === pathSelectionPage)
			return "Select Paths"
		else if (stackView.currentPage === compilingPage)
			return "Compiling"
		else if (stackView.currentPage === preparationPage)
			return "Preparation"
		else if (stackView.currentPage === resultPage)
			return "Results"
	}

	ToolButton {
		text: "➔"
		rotation: 180
		font.pointSize: largeFont

		anchors.right: menuButton.left
		anchors.verticalCenter: parent.verticalCenter

		onClicked: stackView.pop(baseItem)
		visible: stackView.currentPage !== pathSelectionPage
	}

	ToolButton {
		id: menuButton
		text: "\u2630"
		font.pointSize: largeFont

		anchors.right: parent.right
		anchors.verticalCenter: parent.verticalCenter

		onClicked: menu.open()
	}

	Menu {
		id: menu
		y: parent.height
		x: parent.width - width

		MenuItem {
			text: "Settings"
			onClicked: settingsDialog.open()
		}

		MenuItem {
			text: "About"
			onClicked: aboutDialog.open()
		}

		MenuItem {
			text: "Exit"
			onClicked: Qt.quit()
		}
	}
}
