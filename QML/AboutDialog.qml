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
	id: popup
	modal: true
	padding: 12
	width: parent.width-60

	x: (parent.width-width)/2
	y: (parent.height-height)/2

	property string title: "About"
	property string content: "This is an open-source software written with Qt framework that deploys Qt projects on linux operating systems.\n\nThis software is written by Shahriar Rezghi (shahriar25.ss@gmail.com).\n\nCopyright (C) 2018  Shahriar Rezghi\n\nThis program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details."

	contentItem: ColumnLayout {
		Label {
			text: title
			Layout.topMargin: 10
			Layout.bottomMargin: 10
			font.pointSize: largeFont
			color: Material.accent
			Layout.fillWidth: true
			horizontalAlignment: Text.AlignHCenter
		}

		RowLayout {
			id: row
			spacing: 30
			Layout.leftMargin: 10

			Control {
				implicitWidth: 100
				implicitHeight: 100

				contentItem: Image {
					anchors.fill: parent
					source: "qrc:/Images/icon.png"

					sourceSize.width: width
					sourceSize.height: height
				}
			}

			Label {
				text: content
				Layout.fillWidth: true
				wrapMode: Text.WrapAtWordBoundaryOrAnywhere
			}
		}

		Button {
			text: "Close"
			onClicked: popup.close()
			flat: true
			highlighted: true
			Layout.alignment: Qt.AlignRight
		}
	}
}
