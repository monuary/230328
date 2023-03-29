#include<iostream>
#include<cstring>
using namespace std;

class Account
{
	int ID;			//계좌ID
	char* Name;		//이름
	int Money;		//잔액
	int Interest;	//이자율
	int BoSin;		//계좌종류. 1->보통예금계좌. 2->신용신뢰계좌.
	int Trust;		//신용등급. 0->보통예금계좌. 1->A. 2->B. 3->C.
public:
	Account(int id, const char* name, int money, int inter, int bosin, int trust) :ID(id), Money(money), Interest(inter), BoSin(bosin), Trust(trust)
	{
		Name = new char[strlen(name)+1];
		strcpy(Name, name);
	}
	int GetID() { return ID; }
	int GetMoney() { return Money; }
	void ChangeMoney(int money) { Money = money; }	//잔액 재설정
	int GetTrust() { return Trust; }
	int GetInter() { return Interest; }
	void Show()	//ShowAll에서 각각의 클래스를 보여준다.
	{
		cout << "계좌ID: " << ID << endl;
		cout << "이 름: " << Name << endl;
		cout << "잔 액: " << Money << endl;
		cout << "이자율: " << Interest << endl;
		if (BoSin == 1) { cout << "계좌종류: 보통예금계좌" << endl << endl; }
		else 
		{ 
			cout << "계좌종류: 신용신뢰계좌" << endl;
			if (Trust == 1) { cout << "신용등급: A" << endl << endl; }
			else if (Trust == 2) { cout << "신용등급: B" << endl << endl; }
			else { cout << "신용등급: C" << endl << endl; }
		}
	}
	~Account() { delete[]Name; }	//포인터 관리
};

class AccountHandler
{
	Account* Acc[100]{};
	int AccNum = 0;
public:
	void Make()
	{
		if (AccNum == 100)	//클래스 개수는 100개 한정
		{
			cout << "계좌의 수가 너무 많습니다." << endl << endl;
			exit(0);
		}

		int BoSin;
		int ID;
		char Name[50];
		int Money;
		int Interest;
		int Trust;

		cout << "[계좌종류선택]" << endl;
		cout << "1.보통예금계좌 2.신용신뢰계좌" << endl;
		cout << "선택: "; cin >> BoSin;
		if (BoSin == 1) { cout << "[보통예금계좌 개설]" << endl; }
		else { cout << "[신용신뢰계좌 개설]" << endl; }
		cout << "계좌ID: "; cin >> ID;
		for(int i=0;i<AccNum;i++)
		{
			if (Acc[i]->GetID() == ID)
			{
				cout << "동일한 ID가 있습니다. 계정생성을 처음부터 다시 해주세요." << endl << endl;
				break;
			}
		}
		cout << "이 름: "; cin >> Name;	//이름 입력을 위해서는 포인터를 제외해야 한다.
		cout << "잔 액: "; cin >> Money;
		cout << "이자율: "; cin >> Interest;
		if (BoSin == 2)
		{
			cout << "신용등급(1toA, 2toB, 3toC): "; cin >> Trust;
		}
		else { Trust = 0; }	//보통예금계좌는 Trust=0
		cout << endl;

		Acc[AccNum] = new Account(ID, Name, Money, Interest, BoSin, Trust);
		AccNum++;
	}
	void Put()
	{
		int ID;			//입금하려는 계좌
		double Money;	//입금하려는 금액
		double plusInt;	//추가 이자
		double Int;		//총 이자

		cout << "계좌ID: "; cin >> ID;
		cout << "입금액: "; cin >> Money;
		cout << endl;

		for(int i=0;i<AccNum;i++)
		{
			if (Acc[i]->GetID() == ID)
			{
				if (Acc[i]->GetTrust() == 0) { plusInt = 0; }
				else if (Acc[i]->GetTrust() == 1) { plusInt = 7; }
				else if (Acc[i]->GetTrust() == 2) { plusInt = 4; }
				else { plusInt = 2; }
				Int = 1 + (Acc[i]->GetInter() + plusInt)/100;

				Money = (Money + Acc[i]->GetMoney())*Int;
				Acc[i]->ChangeMoney(Money);
			}
		}
	}
	void Pull()
	{
		int ID;		//출금하려는 계좌
		int Money;	//출금하려는 금액

		cout << "계좌ID: "; cin >> ID;
		cout << "출금액: "; cin >> Money;

		Money = Acc[AccNum]->GetMoney() - Money;
		Acc[AccNum]->ChangeMoney(Money);
	}
	void ShowAll()
	{
		for (int i = 0; i < AccNum; i++)
		{
			cout << i+1 << "." << endl;
			Acc[i]->Show();
		}
	}
	~AccountHandler()
	{
		for (int i = 0; i < AccNum; i++)
		{
			Acc[i] = NULL;	//포인터 클래스 초기화
		}
	}
};

int main()
{
	AccountHandler hand;
	int choice;

	while (1)
	{
		cout << "-----Menu-----" << endl;
		cout << "1. 계좌개설" << endl;
		cout << "2. 입 금" << endl;
		cout << "3. 출 금" << endl;
		cout << "4. 계좌정보 전체 출력" << endl;
		cout << "5. 프로그램 종료" << endl;
		cout << "선택: "; cin >> choice;
		cout << endl;
		
		switch (choice)
		{
		case 1:
			hand.Make(); break;
		case 2:
			hand.Put(); break;
		case 3:
			hand.Pull(); break;
		case 4:
			hand.ShowAll(); break;
		case 5:
			return 0;
		default:
			cout << "Illegal selection.." << endl;
		}
	}
	return 0;
}