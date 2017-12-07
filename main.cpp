#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

struct stock warehouse[5];

int main()
{
	time_t p;
	struct tm*cur;
	time(&p);
	cur = localtime(&p);
	printf("The current date/time is: %s", asctime(cur));
	LoadStockFromFile(warehouse);
	OutputStock(warehouse);
#ifdef DEBUG
	system("pause");
#endif
    return 0;
}
