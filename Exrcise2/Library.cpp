﻿#include "Library.h"
#include"VietnamBook.h"
#include"EnglishBook.h"

#include<iostream>
using namespace std;


void Library::update_menu(int i)
{
	int choose = 0;
	string _dummy = "";

	system("cls");

	while (1) {
		system("cls");

		cout <<"\t\t\t\t_____________________________________________________________" << endl
			<< "\t\t\t\t|                     U P D A T E _ B O O K                 |" << endl
			<< "\t\t\t\t|-----------------------------------------------------------|" << endl
			<< "\t\t\t\t|1.  Change ID                                              |" << endl
			<< "\t\t\t\t|2.  Change Name                                            |" << endl
			<< "\t\t\t\t|3.  Change Author                                          |" << endl
			<< "\t\t\t\t|4.  Change Publisher                                       |" << endl
			<< "\t\t\t\t|5.  Change Price                                           |" << endl
			<< "\t\t\t\t|0.  No change !                                            |" << endl
			<< "\t\t\t\t|-----------------------------------------------------------|" << endl
			<< "\t\t\t\t|>>  You choose ?                                           |" << endl
			<< "\t\t\t\t|___________________________________________________________|" << endl
			<< "\n\t\t\t\t>> ";

		cout << "\n **UPDATE BOOK \n";
		cout<< "\n+ 1: Change ID \n"
			<< "+ 2: Change Name \n"
			<< "+ 3: Change Author \n"
			<< "+ 4: Change Publisher \n"
			<< "+ 5: Change Price \n"
			<< "+ 0: No change ! \n"
			<< "+ Choose ?  \n\n"
			<< ">> ";

		cin >> choose;
		cin.ignore();

		cout << endl;

		switch (choose)
		{
			case 0: {
				return;
			}
			case 1: {
				cout << ">> New ID: ";
				getline(cin, _dummy);
				cin.ignore(0);
				list_book.at(i)->set_id(_dummy);
				break;
			}
			case 2: {
				cout << ">> New Name: ";
				getline(cin, _dummy);
				cin.ignore(0);
				list_book.at(i)->set_name(_dummy);
				break;
			}
			case 3: {
				cout << ">> New Author: ";
				getline(cin, _dummy);
				cin.ignore(0);
				list_book.at(i)->set_author(_dummy);
				break;
			}
			case 4: {
				cout << ">> New Publisher: ";
				getline(cin, _dummy);
				cin.ignore(0);
				list_book.at(i)->set_publisher(_dummy);
				break;
			}
			case 5: {
				cout << ">> New Price: ";
				int _temp = 0;
				cin >> _temp;
				list_book.at(i)->set_price(_temp);
				break;
			}

			default: break;
		}
	}
}

void Library::load(string file_name_in)
{
	
	// Con trỏ file đọc đối tượng:
	ifstream in_file;

	in_file.open(file_name_in);

	string is_viet_nam_book = "1";
	string _temp = "";

	if (in_file.is_open()) {
		while (!in_file.eof())
		{
			getline(in_file, is_viet_nam_book);

			if (is_viet_nam_book.size()) {
				if (stoi(is_viet_nam_book)) {
					VietnamBook* _dummy = new VietnamBook();

					getline(in_file, _temp);
					_dummy->set_id(_temp);

					getline(in_file, _temp);
					_dummy->set_name(_temp);

					getline(in_file, _temp);
					_dummy->set_author(_temp);

					getline(in_file, _temp);
					_dummy->set_publisher(_temp);

					getline(in_file, _temp);
					_dummy->set_price(stoi(_temp));

					list_book.push_back(_dummy);
				}
				else {
					EnglishBook* _dummy = new EnglishBook();

					getline(in_file, _temp);
					_dummy->set_id(_temp);

					getline(in_file, _temp);
					_dummy->set_name(_temp);

					getline(in_file, _temp);
					_dummy->set_author(_temp);

					getline(in_file, _temp);
					_dummy->set_publisher(_temp);

					getline(in_file, _temp);
					_dummy->set_price(stoi(_temp));

					getline(in_file, _temp);
					_dummy->set_ISBN(_temp);

					list_book.push_back(_dummy);
				}
			}
		}
	}
}

void Library::save(string file_name_out)
{
	// Con trỏ file ghi đối tượng:
	ofstream out_file;
	out_file.open(file_name_out, ios::out);

	bool is_viet_nam_book = true;

	if (out_file.is_open()) {
		for (int i = 0; i < list_book.size(); i++) {
			is_viet_nam_book = list_book.at(i)->get_type(1);
			out_file << is_viet_nam_book << endl;

			if (is_viet_nam_book) {
				VietnamBook* _dummy = (VietnamBook*)list_book.at(i);
				out_file << _dummy->get_id() << endl;
				out_file << _dummy->get_name() << endl;
				out_file << _dummy->get_author() << endl;
				out_file << _dummy->get_publisher() << endl;
				out_file << _dummy->get_price() << endl;
			}
			else {
				EnglishBook* _dummy = (EnglishBook*)list_book.at(i);
				out_file << _dummy->get_id() << endl;
				out_file << _dummy->get_name() << endl;
				out_file << _dummy->get_author() << endl;
				out_file << _dummy->get_publisher() << endl;
				out_file << _dummy->get_price() << endl;
				out_file << _dummy->get_ISBN() << endl;
			}
			
		}
	}

	out_file.close();
}

void Library::add(Book* _book)
{
	auto it = find(list_book.begin(), list_book.end(), _book);

	// Nếu sách chưa có trong thư viện thì thêm vào
	if (!(it != list_book.end())) {
		this->list_book.push_back(_book);
	}
}

void Library::display()
{
	system("cls");
	cout << "___**DISPLAY**___\n\n";
	for (int i = 0; i < this->list_book.size(); i++) {
		this->list_book.at(i)->display();
		cout << endl;
	}
}

void Library::del_by_book_id(string _id)
{
	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_id()._Equal(_id)) {
			this->list_book.erase(list_book.begin() + i);
			i--;
		}
	}
}

void Library::del_by_book_name(string _name)
{
	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_name()._Equal(_name)) {
			this->list_book.erase(list_book.begin() + i);
			i--;
		}
	}
}

void Library::del_by_book_author(string _author)
{
	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_author()._Equal(_author)) {
			this->list_book.erase(list_book.begin() + i);
			i--;
		}
	}
}

void Library::del_by_book_publisher(string _publiser)
{
	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_publisher()._Equal(_publiser)) {
			this->list_book.erase(list_book.begin() + i);
			i--;
		}
	}
}

void Library::del_by_book_price(double _price)
{
	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_price() == _price) {
			this->list_book.erase(list_book.begin() + i);
			i--;
		}
	}
}

void Library::find_by_book_id(string _id)
{
	vector<int> _dummy = find_by_id(_id);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "\n**TOTAL FOUND " << _dummy.size() << " RESULTS !\n\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*BOOK: " << i + 1 << endl;
		list_book.at(_dummy.at(i))->display();
	}
}

void Library::find_by_book_name(string _name)
{
	vector<int> _dummy = find_by_name(_name);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*BOOK: " << i + 1 << endl;
		list_book.at(_dummy.at(i))->display();
	}
}

void Library::find_by_book_author(string _author)
{
	vector<int> _dummy = find_by_author(_author);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*BOOK: " << i + 1 << endl;
		list_book.at(_dummy.at(i))->display();
	}
}

void Library::find_by_book_publisher(string _publiser)
{
	vector<int> _dummy = find_by_publisher(_publiser);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*BOOK: " << i + 1 << endl;
		list_book.at(_dummy.at(i))->display();
	}
}

void Library::find_by_book_price(double _price)
{
	vector<int> _dummy = find_by_price(_price);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*BOOK: " << i + 1 << endl;
		list_book.at(_dummy.at(i))->display();
	}
}

vector<int> Library::find_by_id(string _id)
{
	vector<int> _dummy;

	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_id()._Equal(_id)) {
			_dummy.push_back(i);
		}
	}

	return vector<int>(_dummy);
}

vector<int> Library::find_by_name(string _name)
{
	vector<int> _dummy;

	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_name()._Equal(_name)) {
			_dummy.push_back(i);
		}
	}

	return vector<int>(_dummy);
}

vector<int> Library::find_by_author(string _author)
{
	vector<int> _dummy;

	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_author()._Equal(_author)) {
			_dummy.push_back(i);
		}
	}

	return vector<int>(_dummy);
}

vector<int> Library::find_by_publisher(string _publiser)
{
	vector<int> _dummy;

	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_publisher()._Equal(_publiser)) {
			_dummy.push_back(i);
		}
	}

	return vector<int>(_dummy);
}

vector<int> Library::find_by_price(double _price)
{
	vector<int> _dummy;

	for (int i = 0; i < this->list_book.size(); i++) {
		if (this->list_book.at(i)->get_price() == _price) {
			_dummy.push_back(i);
		}
	}

	return vector<int>(_dummy);
}

void Library::update_by_book_id(string _id)
{
	vector<int> _dummy = find_by_id(_id);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*UPDATE BOOK " << i + 1 << endl;
		update_menu(_dummy.at(i));
	}
}

void Library::update_by_book_name(string _name)
{
	vector<int> _dummy = find_by_name(_name);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*UPDATE BOOK " << i + 1 << endl;
		update_menu(_dummy.at(i));
	}
}

void Library::update_by_book_author(string _author)
{
	vector<int> _dummy = find_by_author(_author);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*UPDATE BOOK " << i + 1 << endl;
		update_menu(_dummy.at(i));
	}
}

void Library::update_by_book_publisher(string _publiser)
{
	vector<int> _dummy = find_by_publisher(_publiser);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*UPDATE BOOK " << i + 1 << endl;
		update_menu(_dummy.at(i));
	}
}

void Library::update_by_book_price(double _price)
{
	vector<int> _dummy = find_by_price(_price);

	if (_dummy.size() == 0) {
		cout << "NOT FOUND !\n";
		return;
	}

	cout << "**TOTAL FOUND " << _dummy.size() << " RESULTS !\n";

	for (int i = 0; i < _dummy.size(); i++) {
		cout << "*UPDATE BOOK " << i + 1 << endl;
		update_menu(_dummy.at(i));
	}
}
