#pragma once
class Writer {
	private:
		HANDLE& hFileHandle, hPipeEvent, hExitEvent;
		Data* pData;
		bool& isWritten;
		char* pipeInput;
	public:
		Writer(HANDLE& h1, HANDLE& h2, HANDLE& h3, Data* data, bool& b1, char* c1) : hFileHandle(h1), hPipeEvent(h2), hExitEvent(h3), pData(data), isWritten(b1), pipeInput(c1) { };

		void operator() () {
			while (1) {
				if (isWritten) {
					if (WaitForSingleObject(hExitEvent, EXIT_TIMEOUT) == WAIT_OBJECT_0) {
						cout << "Writer stopping. Sending stop signal.\n";
						strcpy_s(pipeInput, PIPE_INPUT_BUFFER_SIZE, "stop");
						break; //remove break to make it wait for item before stopping for a "clean exit"
					}
					continue;
				}
				OVERLAPPED Overlapped;
				memset(&Overlapped, 0, sizeof Overlapped);
				Overlapped.hEvent = hPipeEvent;
				HANDLE hEvents[] = { Overlapped.hEvent, hExitEvent };
				unsigned long writtenBytes;
				cout << "Writing now.\n";
				if (!strcmp(pipeInput, "ready")) {
					isWritten = true;
				}
				else
				{
					isWritten = false;
				}
				if (!WriteFile(hFileHandle, pipeInput, strlen(pipeInput)+1, &writtenBytes, &Overlapped))
				{ // has not written immediately
					int error = GetLastError();
					switch (error)
					{
					case ERROR_IO_PENDING:
						switch (WaitForMultipleObjects(2, hEvents, FALSE, TIMEOUT))
						{ // waiting for response from pipe
						case WAIT_OBJECT_0:
							GetOverlappedResult(hFileHandle, &Overlapped, &writtenBytes, FALSE);
							cout << "Request sent. Wrote " << writtenBytes << " characters.\n";
							if (writtenBytes != strlen(pipeInput) + 1) {
								cout << "Bytes not matching.\n";
							}
							break;
						case WAIT_OBJECT_0 + 1:
							cout << "Writing broken off" << endl;
							break;
						case WAIT_TIMEOUT:
							cout << "Timeout period " << TIMEOUT << "ms elapsed, nothing was received. Type stop to exit" << endl;
							break; // timeout
						default:
							cout << "Waiting failed, error " << GetLastError() << ". Type stop to exit" << endl;
							break; // some system errors
						}
						break;
					default: // some system errors
						cout << "Writing failed, error " << GetLastError() << ". Type stop to exit" << endl;
						break;
					}
				}
				else {
					GetOverlappedResult(hFileHandle, &Overlapped, &writtenBytes, FALSE);
					cout << "Request sent. Wrote " << writtenBytes << " characters.\n";
				}
				if (!strcmp(pipeInput, "stop")) {
					break;
				}
			}
		}
};