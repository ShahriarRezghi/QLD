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
import QtQuick.Dialogs 1.2

ColumnLayout {
	id: root
	spacing: 0
	Layout.fillHeight: false

	property string title
	property bool isdir: true
	property bool confirmed: false
	property alias content: field.text

	signal infoClicked()

	property var checkFunction: defaultCheckFunction
	property var defaultCheckFunction: function(text, wlabel) {
		if (!MainManager.pathExists(isdir, text))
		{
			wlabel.text = "This Path doesn't exist"
			return false
		}
		else if (!MainManager.hasPrems(text))
		{
			wlabel.text = "This Program doesn't have permission to access this path"
			return false
		}
		else
		{
			wlabel.text = "This path is OK"
			return true
		}
	}

	Label {
		text: title
		font.bold: true
		elide: Text.ElideRight
		Layout.fillWidth: true
		font.pointSize: mediumFont
	}

	RowLayout {
		Layout.fillHeight: false

		TextField {
			id: field
			Layout.rightMargin: 5
			Layout.fillWidth: true
			placeholderText: "Enter path or browse"

			onTextChanged: confirmed = checkFunction(text, wlabel)
		}

		Button {
			text: "Browse"
			flat: true
			onClicked: fd.open()
		}

		ToolButton {
			text: "ⓘ"
			font.pointSize: largeFont
			flat: true
			onClicked: infoClicked()
		}
	}

	Label {
		id: wlabel
		elide: Text.ElideRight
		Layout.fillWidth: true
	}

	Item {
		height: 15
		opacity: .5
		Layout.fillWidth: true
	}

	FileDialog {
		id: fd
		selectFolder: isdir
		selectMultiple: false

		onAccepted: field.text = MainManager.stringFromUrl(isdir ? folder:fileUrl)
	}
}
