#include <QWidget>

#include "../crypto.hpp"

class QComboBox;
class QGridLayout;
class QTextEdit;
class QPushButton;

class CryptoChat : public QWidget {
	Q_OBJECT
public:
	CryptoChat(QWidget *parent=0);
public slots:
	void switch_enc_dec(int);
	void encrypt();
	void decrypt();
private:
	Crypto cryp;
	QGridLayout *main_layout;
	QComboBox *cmb_enc_dec;
	QTextEdit *in_text_edit;
	QTextEdit *out_text_edit;
	QPushButton *btn_enc_dec;
};