#include <QApplication>
#include "UI/cryptochat_ui.hpp"

int main(int argc, char* argv[]) 
{
	QApplication app(argc, argv);

	CryptoChat c;
	c.show();
	c.setGeometry(300, 300, 600, 600);

	app.exec();
}