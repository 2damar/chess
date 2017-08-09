#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "chess_board.h"

class MainWindow : public QMainWindow {

	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent* event);

};

#endif
