#include "stdafx.h"
#include "IOCContainer.h"
#include "BlackJack.cpp"


int main()
{
	srand(time(NULL));
	cout << "Two separete games for two bots\n";

	CleverBot bot1(START_CASH);
	IOCContainer::instanceClass().registerClass(make_shared<BlackJack<CleverBot> >());
	shared_ptr<BlackJack <CleverBot> > gamePtrFirst;
	gamePtrFirst = IOCContainer::instanceClass().resolveClass<BlackJack <CleverBot>>();
	gamePtrFirst->game(&bot1, NUMBER_OF_ROUNDS);
	cout << "CleverBot has: ";
	cout << bot1.getCash() << " money\n";

	SillyBot bot2(START_CASH);
	IOCContainer::instanceClass().registerClass(make_shared<BlackJack<SillyBot> >());
	shared_ptr<BlackJack <SillyBot> > gamePtrSecond;
	gamePtrSecond = IOCContainer::instanceClass().resolveClass<BlackJack <SillyBot>>();
	gamePtrSecond->game(&bot2, NUMBER_OF_ROUNDS);
	cout << "SillyBot has: ";
	cout << bot2.getCash() << " money\n";

	system("pause");
	return 0;
}