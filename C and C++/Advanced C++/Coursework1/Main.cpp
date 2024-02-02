#include "Main.h"

int main()
{
	PrepareNames();
	//Test();
	string input;
	Data* data = new Data(10);
	HANDLE hPipe;
	do {
		while (input != "connect" && input != "exit") {
			cout << "Type \'connect\' to connect, \'exit\' to exit.\n";
			cin >> input;
		}
		if (input == "exit") {
			cout << "Exiting.\n";
			return 0;
		}
		cout << "Attempting to open pipe..\n";
		hPipe = CreateFileA("\\\\.\\pipe\\ics0025", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) {
			cout << "Pipe failed, error " << GetLastError() << endl;
			return 1;
		}
		cout << "Pipe successful\n";
		char* pipeInput = new char[PIPE_INPUT_BUFFER_SIZE];
		strcpy_s(pipeInput, PIPE_INPUT_BUFFER_SIZE, "ready");
		HANDLE hExitEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
		HANDLE hPipeEvent = CreateEventA(NULL, FALSE, FALSE, NULL);
		bool isWritten = false;
		thread WriterThread{ Writer(hPipe, hPipeEvent, hExitEvent, data, isWritten, pipeInput) };
		thread ReaderThread{ Reader(hPipe, hPipeEvent, hExitEvent, data, isWritten) };
		cout << "Now reading from the server. Type \'stop\' to stop.\n";
		while (1) {
			cin >> input;
			if (input == "stop") {
				SetEvent(hExitEvent);
				break;
			}
			else if( input == "connect")
			{
				cout << "Already connected.\n";
			}
			else
			{
				cout << "Invalid command.\n";
			}
		}
		ReaderThread.join();
		WriterThread.join();
		delete[] pipeInput;
		CloseHandle(hExitEvent);
		CloseHandle(hPipeEvent);
		CloseHandle(hPipe);
		do {
			cout << "Type \'connect\' to connect again, \'exit\' to exit.\n";
			cin >> input;
		} while (input != "connect" && input != "exit");
	} while (input == "connect");
	cout << "Disconnected. These items are in the structure.\n";
	data->PrintAll();
	delete data;
	return 0;
}

static const char* NamesFile = "Birds.txt"; // http://www.jimpalt.org/birdwatcher/name.html 941 names of different birds, ASCII code, OD OA after each row
default_random_engine Generator;
static uniform_int_distribution<int> NameDistribution;
static vector<string> Names;
uniform_int_distribution<int> GroupDistribution('A', 'Z');
uniform_int_distribution<int> SubgroupDistribution(0, 99);

void PrepareNames()
{
	ifstream file;
	file.open(NamesFile, fstream::in);
	if (!file.good())
		throw exception("Unable to open the names file");
	char buf[100];
	while (file.good())
	{
		file.getline(buf, 100);
		if (buf[0])
			Names.push_back(string(buf));
	}
	file.close();
	uniform_int_distribution<int> distr(0, Names.size() - 1);
	NameDistribution = distr;

}

string CreateRandomName()
{
	int i = NameDistribution(Generator);
	return Names[i];
}


void Test()
{
	Data* pData = new Data(20);
	pData->PrintAll();
	cout << endl;


	cout << (pData->InsertItem('E', 86, "Kaljutuvi") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('E', 86, "Kassikakk", Date(29, 10, 2021)) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('E', 86, "Koskel") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('E', 87, "Ristpart", Date()) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('B', 10, "Varblane") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('#', 73, "Varblane") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('B', 120, "Varblane") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('B', 73, "") ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertItem('E', 86, "Kassikakk", Date(29, 10, 2021)) ? "Inserted" : "Not inserted") << endl;
	cout << endl;

	pData->PrintItem('Q', 19, "Mute Swan");
	pData->PrintItem('E', 86, "Kassikakk");
	try
	{
		pData->PrintItem('E', 10, "XXX");
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	try
	{
		pData->PrintItem('Z', 10, "XXX");
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	cout << endl;

	cout << "Items in group E subgroup 86: " << pData->CountSubgroupItems('E', 86) << endl;
	cout << "Items in group E subgroup 87: " << pData->CountSubgroupItems('E', 87) << endl;
	cout << "Items in group B subgroup 10: " << pData->CountSubgroupItems('B', 10) << endl;
	cout << "Items in group X subgroup 10: " << pData->CountSubgroupItems('X', 10) << endl;
	cout << "Items in group Z subgroup 10: " << pData->CountSubgroupItems('Z', 10) << endl;
	cout << endl;

	pData->PrintSubgroup('E', 86);
	pData->PrintSubgroup('E', 87);
	pData->PrintSubgroup('B', 10);
	try
	{
		pData->PrintSubgroup('X', 10);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	try
	{
		pData->PrintSubgroup('Z', 10);
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	cout << endl;

	cout << "Items in group E: " << pData->CountGroupItems('E') << endl;
	cout << "Items in group B: " << pData->CountGroupItems('B') << endl;
	cout << "Items in group X: " << pData->CountGroupItems('X') << endl;
	cout << endl;

	pData->PrintGroup('E');
	pData->PrintGroup('B');
	try
	{
		pData->PrintGroup('Z');
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	cout << endl;

	cout << (pData->InsertSubgroup('W', 10, { {"Meigas", Date()}, {"Rasvatihane", nullopt} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('E', 88, { {"Turteltuvi", Date(17, 9, 2021)} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('E', 89, { {"Lepalind", Date()}, {"Toonekurg", nullopt}, {"Lepalind", Date()} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('T', 93, { {"Sinitihane", nullopt} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('#', 93, { {"Sinitihane", nullopt} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('T', 110, { {"Sinitihane", nullopt} }) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertSubgroup('T', 94, { { "Piiritaja", Date() }, { "", Date() }, { "Punarind", Date() } }) ? "Inserted" : "Not inserted") << endl;
	pData->PrintGroup('E');
	pData->PrintGroup('W');
	cout << endl;

	tuple<string, optional<Date>> t1("Rohevint", Date(16, 9, 2021)), t2("Sootihane", Date(15, 9, 2021));
	tuple<string, optional<Date>> t3("Luik", nullopt);
	tuple<string, optional<Date>> t4("Nepp", Date()), t5("Lagle", Date()), t6("Metsis", Date());
	tuple<string, optional<Date>> t7("Kuldnokk", Date()), t8("Sookurg", Date()), t9("Kuldnokk", Date());
	cout << (pData->InsertGroup('S', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('R', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t7, t8, t9 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('W', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('#', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('W', { 10, 120, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('W', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ { "", Date() } },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('W', { 10, 30 },
		{
			{ t1, t2 },
			{ t3 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	cout << (pData->InsertGroup('W', { 10, 20, 30 },
		{
			{ t1, t2 },
			{ t4, t5, t6 }
		}) ? "Inserted" : "Not inserted") << endl;
	pData->PrintGroup('S');
	cout << endl;

	cout << (pData->RemoveItem('Q', 19, "Mute Swan") ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveItem('J', 43, "Iraq Babbler") ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveItem('E', 86, "Kassikakk") ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveItem('E', 10, "XXX") ? "Removed" : "Not removed") << endl;
	pData->PrintGroup('J');
	pData->PrintGroup('E');
	try
	{
		pData->PrintGroup('Q');
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	cout << endl;

	cout << (pData->RemoveSubgroup('Y', 45) ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveSubgroup('E', 86) ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveSubgroup('E', 10) ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveSubgroup('U', 1) ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveSubgroup('#', 1) ? "Removed" : "Not removed") << endl;
	pData->PrintGroup('E');
	try
	{
		pData->PrintGroup('Y');
	}
	catch (const invalid_argument& e)
	{
		cout << e.what();
	}
	cout << endl;

	cout << (pData->RemoveGroup('N') ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveGroup('P') ? "Removed" : "Not removed") << endl;
	cout << (pData->RemoveGroup('U') ? "Removed" : "Not removed") << endl;
	pData->PrintAll();
	cout << "The data structure contains " << pData->CountItems() << " items" << endl;
	delete pData;
}
