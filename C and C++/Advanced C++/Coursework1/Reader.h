#pragma once
class Reader
{
private:
	HANDLE hFileHandle, hPipeEvent, hExitEvent;
	Data* pData;
	bool& isWritten;
public:
	Reader(HANDLE& h1, HANDLE& h2, HANDLE& h3, Data* data, bool& b1) : hFileHandle(h1), hPipeEvent(h2), hExitEvent(h3), pData(data), isWritten(b1) { }

	void operator() ()
	{
		while (1) {
			if (!isWritten) {
				if (WaitForSingleObject(hExitEvent, EXIT_TIMEOUT) == WAIT_OBJECT_0) {
					cout << "Reader stopped.\n";
					break;
				}
				continue;
			}
			unsigned long nReadBytes = 0; // prepare reading from COM1
			char* pBuffer = new char[N_BYTES_TO_READ];
			OVERLAPPED Overlapped;
			memset(&Overlapped, 0, sizeof Overlapped);
			Overlapped.hEvent = hPipeEvent;
			HANDLE hEvents[] = { Overlapped.hEvent, hExitEvent };
			bool NoData = true;
			if (!ReadFile(hFileHandle, pBuffer, N_BYTES_TO_READ, &nReadBytes, &Overlapped))
			{ // has not read immediately
				int error = GetLastError();
				switch (error)
				{
				case ERROR_IO_PENDING:
					switch (WaitForMultipleObjects(2, hEvents, FALSE, TIMEOUT))
					{ // waiting for response from pipe
					case WAIT_OBJECT_0:
						GetOverlappedResult(hFileHandle, &Overlapped, &nReadBytes, FALSE);
						cout << pBuffer << endl;
						if(nReadBytes > 5) //completely arbitrary minimum item length
						{
							NoData = false;
						}// Got some data, waiting ended
						break;
					case WAIT_OBJECT_0 + 1:
						cout << "Reading broken off" << endl;
						break; // to user has broken the ending off
					case WAIT_TIMEOUT:
						cout << "Timeout period " << TIMEOUT << "ms elapsed, nothing was received. Press a key to exit" << endl;
						break; // timeout
					default:
						cout << "Reading failed, error " << GetLastError() << ". Press a key to exit" << endl;
						break; // some system errors
					}
					break;
				default: // some system errors
					cout << "Reading failed, error " << GetLastError() << ". Press a key to exit" << endl;
					break;
				}
			}
			else
			{ // has read immediately
				GetOverlappedResult(hFileHandle, &Overlapped, &nReadBytes, FALSE);
				cout << pBuffer << endl;
				NoData = false;
			}
			if (!NoData)
			{ // writes the received data into a disk file
				cout << nReadBytes << " was read" << endl;
				char group = pBuffer[0];
				char* pTemp = new char[20];
				if (pBuffer[3] != ' ') { //is number 1 or 2 digits
					strncpy_s(pTemp, 20, pBuffer + 2, 2);
				}
				else {
					strncpy_s(pTemp, 20, pBuffer + 2, 1);
				}
				int subgroup = atoi(pTemp);
				char* pName = strchr(pBuffer, '<')+1;
				char* pNameEnd = strrchr(pBuffer, '>');
				*pNameEnd = '\0';
				pNameEnd++;
				if (pNameEnd[3] != ' ') { //is number 1 or 2 digits
					strncpy_s(pTemp, 20, pNameEnd + 1, 3);
				}
				else {
					strncpy_s(pTemp, 20, pNameEnd + 1, 2);
				}
				int day = atoi(pTemp);
				char* pMonthStart = strchr(pNameEnd + 1, ' ');
				char* pYearStart = strrchr(pNameEnd, ' ');
				int year = atoi(pYearStart+1);
				char month[4];
				strncpy_s(month, 4, pMonthStart+1, 3);
				int iMonth = 0;
				if (!strcmp(month, "Jan")) {
					iMonth = 1;
				}
				else if (!strcmp(month, "Feb")) {
					iMonth = 2;
				}
				else if (!strcmp(month, "Mar")) {
					iMonth = 3;
				}
				else if (!strcmp(month, "Apr")) {
					iMonth = 4;
				}
				else if (!strcmp(month, "May")) {
					iMonth = 5;
				}
				else if (!strcmp(month, "Jun")) {
					iMonth = 6;
				}
				else if (!strcmp(month, "Jul")) {
					iMonth = 7;
				}
				else if (!strcmp(month, "Aug")) {
					iMonth = 8;
				}
				else if (!strcmp(month, "Sep")) {
					iMonth = 9;
				}
				else if (!strcmp(month, "Oct")) {
					iMonth = 10;
				}
				else if (!strcmp(month, "Nov")) {
					iMonth = 11;
				}
				else if (!strcmp(month, "Dec")) {
					iMonth = 12;
				}
				Date date(day, iMonth, year);
				if (pData->InsertItem(group, subgroup, pName, date)) {
					cout << "Item inserted to data structure.\n";
				}
				delete[] pBuffer;
				delete[] pTemp;
				isWritten = false; //allow writing again
			}
			else {
				delete[] pBuffer;
				SetEvent(hExitEvent);
				break;
			}
		}
	}
};