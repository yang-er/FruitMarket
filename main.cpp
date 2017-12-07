#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

struct stock warehouse[5];
extern void _stock_test();
int main()
{
	time_t p;
	struct tm*cur;
	time(&p);
	cur = localtime(&p);
	printf("The current date/time is: %s", asctime(cur));
	LoadStockFromFile();
	_stock_test();
#ifdef DEBUG
	system("pause");
#endif
    return 0;
}
