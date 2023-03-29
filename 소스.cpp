#include<iostream>
#include<cstring>
using namespace std;

class Account
{
	int ID;			//����ID
	char* Name;		//�̸�
	int Money;		//�ܾ�
	int Interest;	//������
	int BoSin;		//��������. 1->���뿹�ݰ���. 2->�ſ�ŷڰ���.
	int Trust;		//�ſ���. 0->���뿹�ݰ���. 1->A. 2->B. 3->C.
public:
	Account(int id, const char* name, int money, int inter, int bosin, int trust) :ID(id), Money(money), Interest(inter), BoSin(bosin), Trust(trust)
	{
		Name = new char[strlen(name)+1];
		strcpy(Name, name);
	}
	int GetID() { return ID; }
	int GetMoney() { return Money; }
	void ChangeMoney(int money) { Money = money; }	//�ܾ� �缳��
	int GetTrust() { return Trust; }
	int GetInter() { return Interest; }
	void Show()	//ShowAll���� ������ Ŭ������ �����ش�.
	{
		cout << "����ID: " << ID << endl;
		cout << "�� ��: " << Name << endl;
		cout << "�� ��: " << Money << endl;
		cout << "������: " << Interest << endl;
		if (BoSin == 1) { cout << "��������: ���뿹�ݰ���" << endl << endl; }
		else 
		{ 
			cout << "��������: �ſ�ŷڰ���" << endl;
			if (Trust == 1) { cout << "�ſ���: A" << endl << endl; }
			else if (Trust == 2) { cout << "�ſ���: B" << endl << endl; }
			else { cout << "�ſ���: C" << endl << endl; }
		}
	}
	~Account() { delete[]Name; }	//������ ����
};

class AccountHandler
{
	Account* Acc[100]{};
	int AccNum = 0;
public:
	void Make()
	{
		if (AccNum == 100)	//Ŭ���� ������ 100�� ����
		{
			cout << "������ ���� �ʹ� �����ϴ�." << endl << endl;
			exit(0);
		}

		int BoSin;
		int ID;
		char Name[50];
		int Money;
		int Interest;
		int Trust;

		cout << "[������������]" << endl;
		cout << "1.���뿹�ݰ��� 2.�ſ�ŷڰ���" << endl;
		cout << "����: "; cin >> BoSin;
		if (BoSin == 1) { cout << "[���뿹�ݰ��� ����]" << endl; }
		else { cout << "[�ſ�ŷڰ��� ����]" << endl; }
		cout << "����ID: "; cin >> ID;
		for(int i=0;i<AccNum;i++)
		{
			if (Acc[i]->GetID() == ID)
			{
				cout << "������ ID�� �ֽ��ϴ�. ���������� ó������ �ٽ� ���ּ���." << endl << endl;
				break;
			}
		}
		cout << "�� ��: "; cin >> Name;	//�̸� �Է��� ���ؼ��� �����͸� �����ؾ� �Ѵ�.
		cout << "�� ��: "; cin >> Money;
		cout << "������: "; cin >> Interest;
		if (BoSin == 2)
		{
			cout << "�ſ���(1toA, 2toB, 3toC): "; cin >> Trust;
		}
		else { Trust = 0; }	//���뿹�ݰ��´� Trust=0
		cout << endl;

		Acc[AccNum] = new Account(ID, Name, Money, Interest, BoSin, Trust);
		AccNum++;
	}
	void Put()
	{
		int ID;			//�Ա��Ϸ��� ����
		double Money;	//�Ա��Ϸ��� �ݾ�
		double plusInt;	//�߰� ����
		double Int;		//�� ����

		cout << "����ID: "; cin >> ID;
		cout << "�Աݾ�: "; cin >> Money;
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
		int ID;		//����Ϸ��� ����
		int Money;	//����Ϸ��� �ݾ�

		cout << "����ID: "; cin >> ID;
		cout << "��ݾ�: "; cin >> Money;

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
			Acc[i] = NULL;	//������ Ŭ���� �ʱ�ȭ
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
		cout << "1. ���°���" << endl;
		cout << "2. �� ��" << endl;
		cout << "3. �� ��" << endl;
		cout << "4. �������� ��ü ���" << endl;
		cout << "5. ���α׷� ����" << endl;
		cout << "����: "; cin >> choice;
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