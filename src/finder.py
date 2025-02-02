import sys

from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton
from PyQt5.QtGui import QColor, QPalette
from PyQt5.QtCore import Qt

found = [0,0,0,0,0,0,0,0]

class LEDMatrix(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        grid = QGridLayout()
        self.setLayout(grid)

        for i in range(8):
            for j in range(8):
                button = QPushButton(self)
                button.setFixedSize(50, 50)
                button.setStyleSheet("border-radius: 5px; background-color: white;")
                button.clicked.connect(self.changeColor)
                grid.addWidget(button, i, j)
        
        label = QPushButton(str(found), self)
        label.setFixedSize(400, 50)
        label.setStyleSheet("border: none; background-color: none; font-size: 20px;")
        label.clicked.connect(self.copyToClipboard)
        grid.addWidget(label, 8, 0, 1, 8)


        self.setWindowTitle('LED Matrix')
        self.show()



    def changeColor(self):
        button = self.sender()
        index = self.layout().indexOf(button)
        row, col, _, _ = self.layout().getItemPosition(index)

        if button.styleSheet() == "border-radius: 5px; background-color: red;":
            button.setStyleSheet("border-radius: 5px; background-color: white;")

            found[col] = found[col] - 2**row
            self.updateLabel()
        else:
            button.setStyleSheet("border-radius: 5px; background-color: red;")
            
            found[col] = found[col] + 2**row
            self.updateLabel()

    def updateLabel(self):
        self.layout().itemAt(64).widget().setText(str(found))

    def copyToClipboard(self):
        clipboard = QApplication.clipboard()
        cpp_list = "{" + ", ".join(map(str, found)) + "}"
        clipboard.setText(cpp_list)
        print("Copied to clipboard:", cpp_list)


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = LEDMatrix()
    sys.exit(app.exec_())