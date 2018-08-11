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

Page {
	id: page
	padding: 20
	objectName: "Compile"

	background: Item { }

	Flickable {
		id: flick
		interactive: false
		anchors.fill: parent
		contentWidth: width
		contentHeight: label.height
		boundsBehavior: Flickable.StopAtBounds


		Label {
			id: label
			width: parent.width
			text: ProjectCompiler.output
			wrapMode: Text.WrapAtWordBoundaryOrAnywhere

			onTextChanged: if (largeContent) flick.flick(0, -1000)
			property bool largeContent: label.implicitHeight > page.contentItem.height
		}
	}

	contentItem.enabled: !busy.running

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
		target: ProjectCompiler

		onStateChanged: {
			if (visible && state === 3)
				MainManager.safePrepare()
			else if (visible && state === 4)
				stackView.pop(baseItem)
		}
	}

	Connections {
		target: MainManager
		onPreparingChanged: if (!preparing) stackView.push(preparationPage)
	}
}
