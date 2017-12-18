#include "stdafx.h"
#include "structs.h"
#include "scan.h"
#include "ticket.h"
#include "user.h"
#include "stock.h"

ticket *pTicketFront = NULL;
ticket *pTicketRear = NULL;
ticket *pTicketTemp = NULL;
const char *pfTicket = "ticket.dat";

ticket *FindTicket(short tid)
{
	ticket* temp;
	temp = pTicketFront;
	while (temp != NULL && temp->tid != tid)
		temp = temp->next;
	return temp;
}

void LoadTicketFromFile()
{
	return;
}

bool SaveTicketToFile()
{
	return false;
}

bool AddTicket()
{
	do {
		_alloc(pTicketTemp, ticket);

		// ȷ��СƱ���
		bool bFlag = true;
		do {
			ScanShort("��������ţ�", &pTicketTemp->tid, false);
			bFlag = FindTicket(pTicketTemp->tid) != NULL;
			if (bFlag) printf("СƱ%04d�Ѵ��ڣ�\n", pTicketTemp->tid);
			if (bFlag && !ScanBoolean("�Ƿ�������룿(y/n)��"))
			{
				_free(pTicketTemp, ticket);
				pTicketTemp = NULL;
				bFlag = false;
			}
		} while (bFlag);
		
		if (pTicketTemp == NULL) continue;

		// ȷ�������������ܽ��
		printf("���²�����������0��");
		double c = 0;
		int d = 0, sum = 0;
		char msg[38];

		for (int i = 0; i < 5; i++)
		{
			sprintf(msg, "������%s����������", warehouse[i].fruitName);
			if (warehouse[i].isSingled)
			{
				do { ScanInt(msg, &d); } while (d < 0 && printf("�����������Ϸ���\n"));
				pTicketTemp->amount[i] = d;
				pTicketTemp->credit[i] = d * warehouse[i].singlePrice;
			}
			else
			{
				do { ScanDouble(msg, &c); } while (c < 0 && printf("�����������Ϸ���\n"));
				pTicketTemp->amount[i] = cent(c);
				pTicketTemp->credit[i] = cent(c * warehouse[i].singlePrice);
			}
			sum += pTicketTemp->credit[i];
		}

		// ȷ��֧����ʽ
		bFlag = true;
		do {

			// ��Ա�� or �ֽ�
			do {
				ScanShort("�������Ա���ţ��ֽ�Ϊ-1����", &pTicketTemp->vipCard, true);
			} while (GetCardById(pTicketTemp->vipCard) == NULL && printf("û���ҵ��û�Ա��\n"));

			if (pTicketTemp->vipCard == -1)
			{
				// ���ֽ�
				bool bFlag = true;
				do {
					ScanInt("�����������ֽ�������", &pTicketTemp->given);
					bFlag = pTicketTemp->given < sum;
					if (bFlag) printf("���ܵ���Ǯ��\n");
					if (bFlag && !ScanBoolean("�Ƿ���������ֽ�������(y/n)��"))
					{
						_free(pTicketTemp, ticket);
						pTicketTemp = NULL;
						bFlag = false;
					}
				} while (bFlag);
				if (pTicketTemp == NULL) break;

				pTicketTemp->left = pTicketTemp->given - sum;
			}
			else
			{
				// �ջ�Ա��
				bool bFlag = false;
				while (pUserTemp->balance < sum)
				{
					if (ScanBoolean("���㣬�Ƿ����̳�ֵ��(y/n)��"))
					{
						ChargeInConsole(pTicketTemp->vipCard);
					}
					else
					{
						if (ScanBoolean("�Ƿ������������ʹ���ֽ���(y/n)��"))
						{
							bFlag = true;
						}
						else
						{
							printf("������ֵ������ʧ�ܣ��˳���. . . \n");
							_free(pTicketTemp, ticket);
							pTicketTemp = NULL;
						}
						break;
					}
				}
				if (bFlag) continue;
				if (pTicketTemp == NULL) break;
			}

		} while (bFlag);

		if (pTicketTemp == NULL) continue;
		
		ChargeToCard(pTicketTemp->vipCard, sum, false);
		pUserTemp = NULL;

		if (pTicketRear == NULL)
		{
			pTicketFront = pTicketTemp;
			pTicketRear = pTicketTemp;
		}
		else
		{
			pTicketRear->next = pTicketTemp;
			pTicketRear = pTicketTemp;
		}

		pTicketTemp = NULL;

	} while (ScanBoolean("�Ƿ�����½�������(y/n)��"));
	
	return false;
}

void OutputTicket(ticket* ticket, bool isFull) 
{
	if (isFull)
	{
		printf("==============================================\n");
		printf("|                ˮ������Ʊ��                |\n");
	}
	printf("==============================================\n");
	printf("|                                            |\n");
	printf("|  �����ˣ�%10s  �����%04d          |\n", "", 0);
	printf("|  ���ʽ��%6s    Ʊ�ݱ�ţ�%04d        |\n", "��Ա��", 0);
	int calc = int(ticket->time - pTime);
	printf("|  ����ʱ�䣺%04d��%-2d��%-2d�� %-2d:%02d            |\n", 
		pCurrentDate->tm_year + 1900, pCurrentDate->tm_mon + 1, pCurrentDate->tm_mday, calc / 3600, calc / 60 % 60);
	printf("|--------------------------------------------|\n");
	printf("|  # ��Ʒ��           ����    ����     ���  |\n");
	int sum = 0;
	double count = 0, credit = 0;
	for (int i = 0; i < 5; i++)
	{
		if (pTicketTemp->amount[i] == 0) continue;
		sum += pTicketTemp->credit[i];
		credit = dollar(pTicketTemp->credit[i]);
		count = dollar(pTicketTemp->amount[i] * (warehouse[i].isSingled ? 100 : 1));
		printf("|  %d %12s  %-7.2lf %-7.2lf %-8.2lf  |\n",
			i+1, warehouse[i].fruitName, credit / count, count, credit);
	}
	printf("|--------------------------------------------|\n");
	printf("|  �ϼ�                            %-8.2lf  |\n", dollar(sum));
	printf("|                                            |\n");
	printf("|  �տ%8.2lf      ���㣺%8.2lf        |\n", dollar(pTicketTemp->given), dollar(pTicketTemp->left));
	printf("|                                            |\n");
	if (isFull)
	{
		printf("|  1���˻�����  3�����ʳ�ŵ   109��ȫԺ����  |\n");
		printf("|                                            |\n");
		printf("==============================================\n");
	}

}

void OutputAllTickets()
{
	printf("==============================================\n");
	printf("|                ˮ������Ʊ��                |\n");
	pTicketTemp = pTicketFront->next;
	while (pTicketTemp != NULL)
	{
		OutputTicket(pTicketTemp, false);
		pTicketTemp = pTicketTemp->next;
	}
	printf("==============================================\n");
}

bool ModifyTicket(short tid)
{
	if (ScanBoolean("�Ƿ�ͬʱ�䶯�����ȵĸĶ���(y/n)��"))
	{
		// TODO
	}
	else
	{
		// TODO
	}
	return false; 
}

bool DeleteTicket(short tid)
{
	if (ScanBoolean("�Ƿ��������ȵĸĶ���(y/n)��"))
	{
		// TODO
	}
	else
	{
		// TODO
	}
	return false; 
}

void _ticket_test()
{
	clear();
	char op;
	while (true)
	{
		printf("==================\n");
		printf("|    СƱϵͳ\n");
		printf("==================\n");
		printf("|\n");
		printf("|   1.���һ��СƱ\n");
		printf("|   2.���һ��СƱ����Ϣ\n");
		printf("|   3.���պ������СƱ\n");
		printf("|   4.�޸�СƱ����\n");
		printf("|   5.ɾ��СƱ\n");
		printf("|   6.��ѯ������Ϣ\n");
		printf("|   7.��ѯĳ��ʱ���ڹ�����Ϣ\n");
		printf("|   8.�˳�\n");
		printf("|\n");
		printf("==================\n");
		op = ScanOption("��ѡ����룺", '1', '8');
		printf("\n");
		switch (op)
		{
		case '1':
			AddTicket();
			sleep(500);
			break;
		case '2':
			short tid;
			ScanShort("�����빺�ﵥ�ţ�", &tid, false);
			pTicketTemp = FindTicket(tid);
			if (pTicketTemp == NULL)
			{
				printf("û���ҵ��ù����¼��\n");
			}
			else
			{
				OutputTicket(pTicketTemp, true);
				pTicketTemp = NULL;
			}
			pause();
			break;
		case '3':
			pause();
			break;
		case '4':
			sleep(500);
			break;
		case '5':
			sleep(500);
			break;
		case '6':
			sleep(500);
			break;
		case '7':
			sleep(500);
			break;
		case '8':
			if (ScanBoolean("ȷ���˳���(y/n)��"))
				op = -52;
			break;
		default:
			break;
		}
		
		if (op == -52)
		{
			SaveTicketToFile();
			SaveUserToFile();
			SaveStockToFile();
			LoadStockFromFile();
			LoadUserFromFile();
			LoadTicketFromFile();
			sleep(500);
			clear();
			break;
		}
		clear();
	}
}