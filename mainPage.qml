import QtQuick 2.0

Item {
    //anchors.fill:   parent
    /*
    Rectangle{
        id:             titleBar
        anchors.left:   parent.left
        anchors.right:  parent.right
        anchors.top:    parent.top
        //width: 200
        height:         30
        color:          "black"

    }
*/
    Rectangle{
        id:             viewBar
        anchors.left:   parent.left
        anchors.right:  parent.right
        anchors.top:    parent.top
        anchors.bottom: parent.bottom
        color:          "red"
    }

    Rectangle{
        id:             toolBar
        anchors.left:   parent.left
        anchors.right:  parent.right
        anchors.top:    parent.top
        height:         30
        color:          "green"
        opacity:        0.5
    }

}
