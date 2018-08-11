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

Popup {
	id: item
	modal: true
	padding: 12
	width: parent.width-60
	height: parent.height/2

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property var colors: [
		Material.color(Material.Blue), Material.color(Material.Teal), Material.color(Material.Green),
		Material.color(Material.Lime), Material.color(Material.Yellow), Material.color(Material.Amber), Material.color(Material.Orange),
		Material.color(Material.Red), Material.color(Material.Purple)
	]

	contentItem: ColumnLayout {
		spacing: 10

		Label {
			text: "Settings"
			Layout.topMargin: 10
			Layout.bottomMargin: 10
			font.pointSize: largeFont
			color: Material.accent
			Layout.fillWidth: true
			horizontalAlignment: Text.AlignHCenter
		}

		Switch {
			text: "Dark Theme"
			Layout.fillWidth: true
			checked: window.darkTheme
			onCheckedChanged: window.darkTheme = checked
		}

		Label {
			text: "Theme Color"
			Layout.topMargin: 10
			Layout.bottomMargin: 5
			Layout.fillWidth: true
		}

		Row {
			spacing: 5
			Layout.alignment: Qt.AlignHCenter

			Repeater {
				model: colors

				delegate: AbstractButton {
					width: 40
					height: 40

					contentItem: Rectangle {
						color: modelData
						border.width: 1
						border.color: "grey"
					}

					onClicked: window.primary = modelData
				}
			}
		}

		Item {
			Layout.fillWidth: true
			Layout.fillHeight: true
		}
	}
}
