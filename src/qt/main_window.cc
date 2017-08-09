#include "main_window.h"

MainWindow::MainWindow()
{
	ChessBoard* cb = new ChessBoard();
	cb->set_pieces();
	setCentralWidget(cb);

}

void MainWindow::closeEvent(QCloseEvent* event)
{}
	
