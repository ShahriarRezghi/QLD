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
	objectName: "Preparation"

	property var cpplibs: []

	contentItem: ColumnLayout {
		spacing: 10
		enabled: !busy.running

		Label {
			elide: Text.ElideRight
			Layout.fillWidth: true
			Layout.bottomMargin: 5
			font.pointSize: mediumFont
			text: "Choose Non-Qt Libraries To Copy"
		}

		Flickable {
			id: flick
			Layout.fillWidth: true
			Layout.fillHeight: true
			contentWidth: width
			contentHeight: column.height
			clip: true

			ScrollBar.vertical: ScrollBar { }

			Rectangle {
				parent: flick
				anchors.fill: parent
				color: "transparent"
				border.color: Material.accent
			}

			Column {
				id: column
				width: parent.width

				Repeater {
					model: CppManager.cppLibraries

					delegate: CheckDelegate {
						id: del
						text: modelData
						width: parent.width

						Connections {
							target: checkAll
							onCheckedChanged: del.checked = checkAll.checked
						}

						onCheckedChanged: {
							var place = cpplibs.indexOf(del.text)

							if (checked && place < 0)
								cpplibs.push(del.text)
							else if (place > -1)
								cpplibs.splice(place, 1)
						}
					}
				}
			}
		}

		CheckBox {
			id: checkAll
			Layout.fillWidth: true
			text: "Check All The Above"

			topPadding: 6
			bottomPadding: 6
		}

		CheckBox {
			id: erase
			Layout.fillWidth: true
			text: "Erase Everything In: " + ProjectCompiler.outputdir

			onCheckedChanged: MainManager.eraseOutput = checked

			topPadding: 6
			bottomPadding: 6
		}

		CheckBox {
			id: openOutput
			checked: true
			Layout.fillWidth: true
			text: "Open Output Directory When Done"

			onCheckedChanged: MainManager.openOutput = checked

			topPadding: 6
			bottomPadding: 6
		}

		RowLayout {
			Layout.fillHeight: false

			CheckBox {
				id: comperssBox
				Layout.fillWidth: true
				text: "Compress Output Directory"

				onCheckedChanged: MainManager.compressOutput = checked

				topPadding: 6
				bottomPadding: 6
			}

			Button {
				text: "Start"
				font.bold: true
				flat: true
				highlighted: true

				onClicked: {
					CppManager.cppLibraries = cpplibs
					MainManager.safeStart()
				}
			}
		}
	}

	Settings {
		property alias erase: erase.checked
		property alias compress: comperssBox.checked
		property alias openOutput: openOutput.checked
	}

	ColumnLayout {
		parent: page
		anchors.centerIn: parent

		BusyIndicator {
			id: busy
			running: MainManager.processing
			Layout.alignment: Qt.AlignHCenter
		}

		Label {
			text: MainManager.processingStatus
			Layout.alignment: Qt.AlignHCenter
		}
	}

	Connections {
		target: MainManager

		onProcessingChanged: {
			if (visible && !processing) {
				stackView.push(resultPage)

				if (openOutput.checked)
					MainManager.showDirectory(ProjectCompiler.outputdir)
			}
		}
	}
}
