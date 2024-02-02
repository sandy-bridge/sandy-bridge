#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <random>
#include <fstream>
#include <sstream>
#include <optional>
#include <set>
#include <map>
#include <tuple>
#include <initializer_list>
#include <thread>
//To do

#include "stdio.h"
#include "time.h"
#include "Windows.h"
#include "tchar.h"
#include "conio.h"


#define TIMEOUT 10*1000UL
#define EXIT_TIMEOUT 10UL
#define N_BYTES_TO_READ 128UL
#define PIPE_INPUT_BUFFER_SIZE 10UL

using namespace std;

#include "Date.h"
#include "Item.h"
#include "Data.h"
#include "Writer.h"
#include "Reader.h"
//To do


void PrepareNames();
string CreateRandomName();
void Test();
