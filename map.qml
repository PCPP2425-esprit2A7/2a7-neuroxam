import QtQuick 2.15
import QtQuick.Window 2.15
import QtLocation 5.15
import QtPositioning 5.15

Rectangle {
    id: root
    width: parent ? parent.width : 800
    height: parent ? parent.height : 600
    color: "lightgray"

    signal mapClicked(double latitude, double longitude)

    Plugin {
        id: mapPlugin
        name: "osm"
        PluginParameter {
            name: "osm.mapping.custom.host"
            value: "https://tile.openstreetmap.org/"
        }
        PluginParameter {
            name: "osm.mapping.providersrepository.disabled"
            value: "true"
        }
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(46.2276, 2.2137) // Start in France
        zoomLevel: 6
        focus: true
        MouseArea {
            id: panArea
            anchors.fill: parent
            property point lastMousePos
            acceptedButtons: Qt.LeftButton

            onPressed: lastMousePos = Qt.point(mouse.x, mouse.y)

            onPositionChanged: {
                if (pressedButtons & Qt.LeftButton) {
                    var dx = mouse.x - lastMousePos.x
                    var dy = mouse.y - lastMousePos.y
                    lastMousePos = Qt.point(mouse.x, mouse.y)

                    // Calculate new center
                    var centerPixel = Qt.point(width/2 - dx, height/2 - dy)
                    map.center = map.toCoordinate(centerPixel)
                }
            }
        }
        // Only one MouseArea for right-click
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            onClicked: function(mouse) {
                var clickedCoordinate = map.toCoordinate(Qt.point(mouse.x, mouse.y));
                root.mapClicked(clickedCoordinate.latitude, clickedCoordinate.longitude);
                markersModel.append({
                    lat: clickedCoordinate.latitude,
                    lon: clickedCoordinate.longitude,
                    title: "New Centre"
                });
            }
        }

        // Mouse wheel zoom
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.NoButton
            onWheel: {
                var zoomBefore = map.zoomLevel
                var newZoom = wheel.angleDelta.y > 0 ?
                    Math.min(zoomBefore + 0.5, map.maximumZoomLevel) :
                    Math.max(zoomBefore - 0.5, map.minimumZoomLevel)

                map.zoomLevel = newZoom
            }
        }

        MapItemView {
            model: ListModel {
                id: markersModel
            }

            delegate: MapQuickItem {
                coordinate: QtPositioning.coordinate(lat, lon)
                anchorPoint.x: image.width/2
                anchorPoint.y: image.height

                sourceItem: Rectangle {
                    id: image
                    width: 20
                    height: 20
                    radius: 10
                    color: "red"
                    border.width: 2
                    border.color: "white"
                    Text {
                        text: title
                        anchors.top: parent.bottom
                        anchors.horizontalCenter: parent.horizontalCenter
                        font.pixelSize: 12
                    }
                }
            }
        }
    }

    // Navigation Controls
    Column {
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.margins: 10
        spacing: 5


        // Zoom Controls
        Rectangle {
            width: 40
            height: 40
            color: "white"
            radius: 5
            border.width: 1
            Text {
                text: "+"
                anchors.centerIn: parent
                font.pixelSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: map.zoomLevel = Math.min(map.zoomLevel + 1, 20)
            }
        }

        Rectangle {
            width: 40
            height: 40
            color: "white"
            radius: 5
            border.width: 1
            Text {
                text: "-"
                anchors.centerIn: parent
                font.pixelSize: 20
            }
            MouseArea {
                anchors.fill: parent
                onClicked: map.zoomLevel = Math.max(map.zoomLevel - 1, 1)
            }
        }
    }

    // Status Display
    Text {
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.margins: 10
        text: "Lat: " + map.center.latitude.toFixed(4) +
              " | Lon: " + map.center.longitude.toFixed(4) +
              " | Zoom: " + map.zoomLevel.toFixed(1)
        font.pixelSize: 12
        color: "black"
        style: Text.Outline
        styleColor: "white"
    }

    // Add this function to the root item
    function addMarkers(newMarkers) {
        for (var i = 0; i < newMarkers.length; i++) {
            markersModel.append(newMarkers[i]);
        }
    }
}
