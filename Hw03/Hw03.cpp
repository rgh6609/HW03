//인벤토리
#include <clocale>
#include <iostream>
#include <string>

using namespace std;

class Item {
public:
	Item(const string& Getname = "", int price = 0) : name_(Getname), price_(price) {}
	const string& GetName() const { return name_; }
	int GetPrice() const { return price_; }
	void Clear() { name_ = ""; price_ = 0; }
	void PrintInfo() const {
		if (name_ == "") cout << "(비어 있음)" << endl;
		else cout << "아이템: " << name_ << " / 가격: " << price_ << " G" << endl;
	}
private:
	string name_;
	int price_;
};

template<typename T>
class BAG {
public:
	BAG(int capacity = 5) {
		capacity_ = (capacity <= 0) ? 1 : capacity;
		size_ = 0;
		pItems_ = new T[capacity_];
	}
	~BAG() {
		if (pItems_ != nullptr) { delete[] pItems_; pItems_ = nullptr; }
	}

	bool AddItem(const T& item) {
		if (size_ < capacity_) {
			pItems_[size_] = item;
			size_++;
			return true;
		}
		cout << "(경고) 가방에 자리가 없습니다!" << endl;
		return false;
	}

	T RemoveLastItem() {
		if (size_ > 0) {
			size_--;
			T removed = pItems_[size_];
			pItems_[size_].Clear();
			return removed;
		}
		cout << "(경고) 가방에 물건이 없습니다!" << endl;
		return Item("", 0);
	}

	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_; }

	void PrintAllItems() const {
		cout << "\n--- 소지품 목록 (" << size_ << "/" << capacity_ << ") ---" << endl;
		for (int i = 0; i < capacity_; ++i) {
			cout << "[" << i << "] ";
			pItems_[i].PrintInfo();
		}
		cout << "--------------------------------" << endl;
	}

private:
	T* pItems_;
	int capacity_;
	int size_;
};

int main() {
	setlocale(LC_ALL, "KOREAN");

	int myGold = 1000;
	BAG<Item>* ItemBAG = new BAG<Item>(5);

	int menu;
	while (true) {
		cout << "\n[ 현재 소지 골드 : " << myGold << " G ]" << endl;
		ItemBAG->PrintAllItems();
		cout << "=========={ 상점 }===========" << endl;
		cout << "1.빨간포션(100G) 2.파란포션(100G) /n 3.양날검(300G) 4.나무방패(300G) 5.가죽 갑옷(300G)" << endl;
		cout << "6.마지막 아이템 판매 7.게임 종료" << endl;

		cin >> menu;

		if (menu == 1) {
			if (myGold >= 100) {
				if (ItemBAG->AddItem(Item("빨간 포션", 100))) {
					myGold -= 100;
					cout << ">> 빨간 포션을 구매했습니다! (-100G)" << endl;
				}
			}
			else {
				cout << ">> 골드가 부족합니다!" << endl;
			}
		}
		if (menu == 2) {
			if (myGold >= 100) {
				if (ItemBAG->AddItem(Item("파란 포션", 100))) {
					myGold -= 100;
					cout << ">> 파란 포션을 구매했습니다! (-100G)" << endl;
				}
			}
			else {
				cout << ">> 골드가 부족합니다!" << endl;
			}
		}
		if (menu == 3) {
			if (myGold >= 300) {
				if (ItemBAG->AddItem(Item("양날검", 100))) {
					myGold -= 300;
					cout << ">> 양날검 을 구매했습니다! (-300G)" << endl;
				}
			}
			else {
				cout << ">> 골드가 부족합니다!" << endl;
			}
		}
		if (menu == 4) {
			if (myGold >= 300) {
				if (ItemBAG->AddItem(Item("나무 방패", 300))) {
					myGold -= 300;
					cout << ">> 나무 방패 을 구매했습니다! (-300G)" << endl;
				}
			}
			else {
				cout << ">> 골드가 부족합니다!" << endl;
			}
		}
		if (menu == 5) {
			if (myGold >= 300) {
				if (ItemBAG->AddItem(Item("가죽 갑옷", 300))) {
					myGold -= 300;
					cout << ">> 가죽 갑옷 을 구매했습니다! (-300G)" << endl;
				}
			}
			else {
				cout << ">> 골드가 부족합니다!" << endl;
			}
		}
		else if (menu == 6) {
			if (ItemBAG->GetSize() > 0) {
				Item soldItem = ItemBAG->RemoveLastItem();
				myGold += soldItem.GetPrice();
				cout << ">> " << soldItem.GetName() << "을(를) 판매했습니다! (+" << soldItem.GetPrice() << "G)" << endl;
			}
			else {
				cout << ">> 판매할 아이템이 없습니다!" << endl;
			}
		}
		else if (menu == 7) {
			cout << "게임을 종료합니다." << endl;
			break;
		}
	}

	delete ItemBAG;
	return 0;
}