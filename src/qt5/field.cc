#include "field.h"

Field::Field(unsigned c, QWidget* parent, Qt::WindowFlags f) : QLabel(parent, f), coord(c) {}

void Field::mousePressEvent(QMouseEvent* event) {
	event->accept();
	emit clicked();
}

int Field::get_coord() 
{
	return coord;
}

void Field::set_coord(int c)
{
	coord = c;
}

Field::~Field() {}
