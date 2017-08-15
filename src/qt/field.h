#ifndef FIELD_H
#define FIELD_H

#include <QLabel>

class Field : public QLabel {
	Q_OBJECT

public:
	Field(unsigned c, QWidget* parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
	~Field();
	int get_coord();
	void set_coord(int c);

signals: 
	void clicked();

protected:
	void mousePressEvent(QMouseEvent* event);

private:
	int coord;
};

#endif
