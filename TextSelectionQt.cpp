#include <QApplication>
#include <QLineEdit>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QWidget>

// Custom single-line QLineEdit where selection is not rotated 90 degrees
class QSingleLineEdit : public QLineEdit
{
public:
	QSingleLineEdit(QWidget* parent = nullptr) : QLineEdit(parent), dragging(false), startPos(0)
	{
	}

protected:
	void mousePressEvent(QMouseEvent* event) override
	{
		if (event->button() == Qt::LeftButton)
		{
			dragging = true;
			startPos = cursorPositionAt(event->pos());
			setCursorPosition(startPos);
		}
		QLineEdit::mousePressEvent(event);
	}

	void mouseMoveEvent(QMouseEvent* event) override
	{
		if (dragging)
		{
			int newPos = cursorPositionAt(event->pos());
			setSelection(startPos, newPos - startPos);
			return;
		}

		QLineEdit::mouseMoveEvent(event);
	}

	void mouseReleaseEvent(QMouseEvent* event) override
	{
		dragging = false;
		QLineEdit::mouseReleaseEvent(event);
	}

private:
	bool dragging;
	int startPos;
};

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	QWidget window;
	window.setWindowTitle("Qt Text Selection Example");
	QVBoxLayout* layout = new QVBoxLayout(&window);

	QLabel* topLabel = new QLabel();
	topLabel->setText("Try selecting parts of the text using the mouse, and see which one of these two input fields you find more intuitive to use.\n");
	topLabel->setWordWrap(true);
	layout->addWidget(topLabel);

	QLabel* labelA = new QLabel();
	labelA->setText("A: JoaCHIP style:");
	layout->addWidget(labelA);

	// Horizontal mouse movement to do horizontal selection
	QSingleLineEdit* customEdit = new QSingleLineEdit();
	customEdit->setText("Use the mouse to select parts of this text");
	layout->addWidget(customEdit);

	QLabel* labelB = new QLabel();
	labelB->setText("B: Default Qt style:");
	layout->addWidget(labelB);

	// Vertical mouse movement to do horizontal selection (Qt default)
	QLineEdit* normalEdit = new QLineEdit();
	normalEdit->setText("Use the mouse to select parts of this text");
	layout->addWidget(normalEdit);

	window.resize(400, 200);
	window.show();

	return app.exec();
}
