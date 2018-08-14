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

	property string title
	property string content

	function openPopup(i) {
		if (i === 0) {
			title = "Qt Build Directory"
			content = "This is the directory that contains a build of the Qt library. in this directory there are some directories like bin and lib and qml and the bin directory contains qmake executable.\nexample: /home/shahriar/Qt5.11.1/5.11.1/gcc_64";
		}
		else if (i === 1) {
			title = "Executable File Path"
			content = "This is the path of the project's executable file.\nexample: /home/shahriar/QtProjects/build-QLD-Desktop_Qt_5_11_1_GCC_64bit-Release/QLD"
		}
		else if (i === 2) {
			title = "Project Directory"
			content = "This is the directory that contains the project files and the .pro file of the project.\nexample: /home/shahriar/QtProjects/QLD"
		}
		else if (i === 3) {
			title = "Final Output Directory"
			content = "This is the directory that you want the output libraries and executables and qml modules and the script file to be placed.\nexample: /home/shahriar/QLD-Release"
		}

		open()
	}

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

		Label {
			text: content
			Layout.fillWidth: true
			wrapMode: Text.WrapAtWordBoundaryOrAnywhere
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
