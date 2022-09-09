import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0
import QtQuick.Dialogs
import QtQuick.Layouts
import RECEIVER 1.0

Window {
    width: 1080
    height: 720
    visible: true
    color: "#AABBCC"
    title: qsTr("Hello World")

    ColumnLayout{
        FileDialog{
            id:openImage
            title:"Choose an image..."
            onAccepted: {
                imageOpened.source=selectedFile
                modifyButton.visible=true
            }
        }
        Button{
            text:"Open an image"
            onClicked: {
                openImage.open()
            }
        }
        RowLayout{
            id:imagerow
            visible:true
            Image {
                id: imageOpened
                sourceSize.height:500
                fillMode: Image.PreserveAspectFit
            }
            ColumnLayout{
                Text{
                    id:instructiontext
                    text:"Enter the colors into which to \ndecompose the image :"
                }
                GridLayout{
                    columns:4

                    Text{
                        text:"color1 :"
                    }
                    TextEdit{
                        id:r1
                        bottomPadding: 10
                        rightPadding: 10
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:g1
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:b1
                        text: "0"
                    }
                    Text{
                        text:"color2 :"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:r2
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:g2
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:b2
                        text: "0"
                    }
                    Text{
                        text:"color3 :"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:r3
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:g3
                        text: "0"
                    }
                    TextEdit{
                        bottomPadding: 10
                        rightPadding: 10
                        id:b3
                        text: "0"
                    }
                }
            }
        }
        Button{
            id:modifyButton
            objectName: "modifyButton"
            text:"decompose the image"
            visible: false
            property variant myArray:[128,30,200,50,0,55,234,54,200]
            PaletteReceiver{
                id:paletteReciever
                xx: modifyButton.myArray
                objectName:"PaletteReceiver1"
            }
            onClicked: {
                instructiontext.text = "Now you can modify these colors \nbefore the image is reconstructed"
                myArray=[parseInt(r1.text),parseInt(g1.text),parseInt(b1.text),
                        parseInt(r2.text),parseInt(g2.text),parseInt(b2.text),
                        parseInt(r3.text),parseInt(g3.text),parseInt(b3.text)]
                firstStepButton.xxChanged(myArray)
                imageOpened.source = "image://palette/"+imageOpened.source.toString()
                modifyButton.visible=false
                newpaletteButton.visible=true
            }
        }
        Button{
            id:newpaletteButton
            objectName: "newpaletteButton"
            text:"reconstruct the image"
            visible: false
            property variant myArray:[128,30,200,50,0,55,234,54,200]
            PaletteReceiver{
                id:paletteReciever2
                xx: modifyButton.myArray
                objectName:"PaletteReceiver2"
            }
            onClicked: {
                myArray=[parseInt(r1.text),parseInt(g1.text),parseInt(b1.text),
                        parseInt(r2.text),parseInt(g2.text),parseInt(b2.text),
                        parseInt(r3.text),parseInt(g3.text),parseInt(b3.text)]
                firstStepButton.xxChanged(myArray)
                imageOpened.source = "image://modification/"+
                        imageOpened.source.toString().replace("image://palette/","")
            }
        }
    }
}
