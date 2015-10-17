#include "cryptochat_ui.hpp"
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <iostream>

#include <QComboBox>
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QTextEdit>

using namespace std;

CryptoChat::CryptoChat(QWidget *parent) : QWidget(parent) {

	main_layout = new QGridLayout;

	cmb_enc_dec = new QComboBox;
	cmb_enc_dec->addItem("Encrypt");
	cmb_enc_dec->addItem("Decrypt");
	main_layout->addWidget(cmb_enc_dec, 0, 0);

	in_text_edit = new QTextEdit;
	main_layout->addWidget(in_text_edit, 1, 0);

	out_text_edit = new QTextEdit;
	main_layout->addWidget(out_text_edit, 2, 0);

	btn_enc_dec = new QPushButton("Enc/Dec", this);
	main_layout->addWidget(btn_enc_dec, 3, 0);

	setLayout(main_layout);

	connect(cmb_enc_dec, SIGNAL(currentIndexChanged(int)), this, SLOT(switch_enc_dec(int)));
	connect(btn_enc_dec, SIGNAL(clicked()), this, SLOT(encrypt()));
}

void CryptoChat::switch_enc_dec(int index) {
	if(index==0) {
		disconnect(btn_enc_dec, SIGNAL(clicked()), this, SLOT(decrypt()));
		connect(btn_enc_dec, SIGNAL(clicked()), this, SLOT(encrypt()));
	}
	else {
		disconnect(btn_enc_dec, SIGNAL(clicked()), this, SLOT(encrypt()));
		connect(btn_enc_dec, SIGNAL(clicked()), this, SLOT(decrypt()));
	}
}

void CryptoChat::encrypt() {
	cout << "ENCRYPT" << endl;
	string msg = in_text_edit->toPlainText().toStdString();
	out_text_edit->setText(QString::fromStdString(cryp.aes_encrypt(msg)));
}

void CryptoChat::decrypt() {
	cout << "DECRYPT" << endl;
	string msg = in_text_edit->toPlainText().toStdString();
	out_text_edit->setText(QString::fromStdString(cryp.aes_decrypt(msg)));
}