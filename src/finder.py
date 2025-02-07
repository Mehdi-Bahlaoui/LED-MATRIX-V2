import sys
from PyQt5.QtWidgets import QApplication, QWidget, QGridLayout, QPushButton
from PyQt5.QtGui import QColor, QPalette
from PyQt5.QtCore import Qt

found = [0, 0, 0, 0, 0, 0, 0, 0]


class LEDMatrix(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.dragging = False  # Track whether we're in a dragging state
        self.current_color = "red"  # Default color to apply during dragging

    def initUI(self):
        grid = QGridLayout()
        self.setLayout(grid)

        # Create buttons and add them to the grid
        self.buttons = []
        for i in range(8):
            row = []
            for j in range(8):
                button = QPushButton(self)
                button.setFixedSize(50, 50)
                button.setStyleSheet("border-radius: 5px; background-color: white;")
                button.clicked.connect(self.changeColor)
                grid.addWidget(button, i, j)
                row.append(button)
            self.buttons.append(row)

        # Add a label to display the `found` array
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

    def mousePressEvent(self, event):
        # Start dragging when the left mouse button is pressed
        if event.button() == Qt.LeftButton:
            self.dragging = True
            # Check if the press is on a button
            widget = QApplication.widgetAt(event.globalPos())
            if isinstance(widget, QPushButton):
                # Determine the initial color to apply during dragging
                self.current_color = (
                    "red"
                    if widget.styleSheet() == "border-radius: 5px; background-color: white;"
                    else "white"
                )
                self.changeColorForButton(widget)

    def mouseMoveEvent(self, event):
        # If dragging, change the color of the button under the cursor
        if self.dragging:
            widget = QApplication.widgetAt(event.globalPos())
            if isinstance(widget, QPushButton):
                self.changeColorForButton(widget)

    def mouseReleaseEvent(self, event):
        # Stop dragging when the left mouse button is released
        if event.button() == Qt.LeftButton:
            self.dragging = False

    def changeColorForButton(self, button):
        index = self.layout().indexOf(button)
        row, col, _, _ = self.layout().getItemPosition(index)

        # Only change the color if it's not already the desired color
        if button.styleSheet() != f"border-radius: 5px; background-color: {self.current_color};":
            button.setStyleSheet(f"border-radius: 5px; background-color: {self.current_color};")
            if self.current_color == "red":
                found[col] = found[col] + 2**row
            else:
                found[col] = found[col] - 2**row
            self.updateLabel()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = LEDMatrix()
    sys.exit(app.exec_())