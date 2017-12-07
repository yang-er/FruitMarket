#include "stdafx.h"
#include "user.h"
#include "ticket.h"
#include "stock.h"
#include "scan.h"

int main()
{
	time_t p;
	struct tm*cur;
	time(&p);
	cur = localtime(&p);
	printf("The current date/time is: %s", asctime(cur));
	int i;
	while (1)
	{
		printf("1.output a line; \n");
		printf("2.exit; \n");
		ScanInt("Please choose your option: ", &i);
		if (i == 2)
		{
			if (ScanBoolean("Are you ready for it(y/n): "))
				break;
		}
		else
			printf("hahahahhahahah\n");
	}
#ifdef DEBUG
	system("pause");
#endif
    return 0;
}
