#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "CppUnitTest.h"

/* include your project file
 * change relative path to match your project */
#include "../../../../Projects/Project1/Project1/OULink.h"
#include "../../../../Projects/Project1/Project1/OULinkedList.h"
#include "../../../../Projects/Project1/Project1/OULinkedListEnumerator.h"
#include "../../../../Projects/Project1/Project1/Comparator.h"
#include "../../../../Projects/Project1/Project1/TemplatedArray.h"
#include "../../../../Projects/Project1/Project1/NvraRecord.h"
#include "../../../../Projects/Project1/Project1/NvraComparator.h"
#include "../../../../Projects/Project1/Project1/NvraComparator.cpp"
#include "../../../../Projects/Project1/Project1/NvraRecord.cpp"
#include "../../../../Projects/Project1/Project1/Search.h"
#include "../../../../Projects/Project1/Project1/Sorter.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests {
	TEST_CLASS(UnitTest1) {
public:

	/* methods for unit testing */

	TemplatedArray<int> ta;

	void createArray() {
		for (int i = 0; i < 10; ++i) {
			int* j = new int(i);
			ta.add(j);
		}


		try {
			ta.addAt(new int(52), 3);
		} catch (ExceptionIndexOutOfRange ex) {
			Logger::WriteMessage("OUT OF BOUNDS");
		}
	}

	template<typename T>
	char& convertIntToString(T num) {
		char* str;
		TemplatedArray<T> list;
		bool isNeg = false;

		// check for neg value and add sign at end if needed
		if (num < 0) {
			isNeg = true;
			num = -num;
		}

		// loop through to split int into ind. value
		T testingNum = num;
		T resultNum = 0;

		while (0 != num) {
			resultNum = num % 10;
			list.add(&resultNum);
			num /= 10;
		}

		reverseArr(list);

		// add one addition char if neg
		if (isNeg) {
			str = new char[list.getSize() + 2];
			str[list.getSize()] = '-';
		} else {
			str = new char[list.getSize() + 1];
		}

		str[list.getSize()] = 0;

		for (int i = 0; i < list.getSize(); ++i) {
			str[i] = '0' + list[i];
		}

		return *str;
	}

	template<typename T>
	void reverseArr(TemplatedArray<T>& list) {
		T temp;
		T temp2;
		unsigned long size = list.getSize();
		for (int i = 0; i < size / 2; ++i) {
			temp = list[i];
			temp2 = list[size - 1 - i];
			list.replaceAt(&temp2, i);
			list.replaceAt(&temp, size - 1 - i);
		}
	}

	template<typename T>
	long long linSearch(TemplatedArray<T>& list, T key) {
		for (unsigned long i = 0; i < list.getSize(); ++i) {
			if (list[i] == key) {
				return i;
			}
		}

		// did not find
		return -1;
	}



	TEST_METHOD(TEST_TemplatedArrayGet) {
		createArray();
		Assert::AreEqual(ta.get(0), 0);
		Assert::AreEqual(ta.get(1), 1);
		Assert::AreEqual(ta.get(2), 2);
		Assert::AreEqual(ta.get(3), 52);
		Assert::AreEqual(ta.get(4), 3);
		Assert::AreEqual(5, ta.get(6));
	}

	TEST_METHOD(TEST_TemplatedArrayReplaceAt) {
		createArray();
		int* t = new int(876);
		ta.replaceAt(t, 0);
		Assert::AreEqual(876, ta.get(0));
	}

	TEST_METHOD(TEST_TemplatedArrayAdd) {
		NvraRecord rec;
		rec.addNum(1);
		Assert::AreEqual(1, (int)rec.getNum(0));
	}

	TEST_METHOD(TEST_NvraComparator_IntValues) {
		NvraRecord rec1;
		NvraRecord rec2;
		rec1.addNum(3);
		rec2.addNum(4);
		NvraComparator c(0);
		Logger::WriteMessage("NvraComparator 0.0: ");
		Assert::AreEqual(-1, c.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");

		rec1.setNum(4, 20);
		rec2.setNum(4, 20);
		NvraComparator c2(23);
		Logger::WriteMessage("NvraComparator 0.1: ");
		Assert::AreEqual(0, c2.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");

		rec1.setNum(4, 5);
		rec2.setNum(3, 5);
		NvraComparator c3(6);
		Logger::WriteMessage("NvraComparator 0.2: ");
		Assert::AreEqual(1, c3.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");
	}

	TEST_METHOD(TEST_NvraComparator_StringValues) {
		NvraRecord rec1;
		NvraRecord rec2;
		rec1.addString("K");
		rec2.addString("L");
		NvraComparator c(3);
		Logger::WriteMessage(rec1.getString(0).c_str());
		Logger::WriteMessage("NvraComparator 1.0: ");
		Assert::AreEqual(-1, c.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");


		rec1.addString("z");
		rec2.addString("ab");
		NvraComparator c2(11);
		Logger::WriteMessage(rec1.getString(0).c_str());
		Logger::WriteMessage("NvraComparator 1.1: ");
		Assert::AreEqual(1, c2.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");

		rec1.addString("abc");
		rec2.addString("abc");
		NvraComparator c3(12);
		Logger::WriteMessage(rec1.getString(0).c_str());
		Logger::WriteMessage("NvraComparator 1.2: ");
		Assert::AreEqual(0, c3.compare(rec1, rec2));
		Logger::WriteMessage("PASSED");
	}


	TEST_METHOD(TestSearchMethod1) {

		int testNumber = 5;

		const int arrSize = 20;
		TemplatedArray<NvraRecord> arr;
		NvraRecord* rec = new NvraRecord();
		NvraComparator c(0);
		(*rec).addNum(testNumber);


		for (unsigned int i = 0; i < arrSize; ++i) {
			NvraRecord* tempNvra = new NvraRecord();
			(*tempNvra).addNum(i);
			arr.add(tempNvra);
			delete tempNvra;
			Logger::WriteMessage("Ran Loop...");
		}

		for (int i = 0; i < 19; ++i) {
			NvraRecord* tempNvra = new NvraRecord();
			(*tempNvra).addNum(5);
			arr.addAt(tempNvra, 5);
			delete tempNvra;
			Logger::WriteMessage("Ran Loop2...");
		}

		Sorter<NvraRecord>::sort(arr, c);

		int temp = 0;
		temp = (int)binarySearch((*rec), arr, c);


		Logger::WriteMessage("Value: " + temp);

		Assert::AreEqual(5, temp);
		Assert::AreNotEqual(12, temp);
		Assert::AreNotEqual(6, temp);
	}

	TEST_METHOD(TestQuickSort) {
		const int arrSize = 20;

		const unsigned long testValue = 14;

		TemplatedArray<NvraRecord> tempArr(arrSize);
		NvraComparator c(0);

		for (unsigned long i = 0; i < arrSize; ++i) {
			NvraRecord* rec = new NvraRecord();
			(*rec).addNum(arrSize - 1 - i);
			tempArr.add(rec);
			delete rec;
		}

		try {
			Sorter<NvraRecord>::sort(tempArr, c);
		} catch (ExceptionIndexOutOfRange ex) {
			Logger::WriteMessage("OUT of Range!!");
		}

		Assert::AreEqual((int)testValue, (int)tempArr[testValue].getNum(0));
	}

	TEST_METHOD(NvraComp0) {
		NvraRecord rec1;
		NvraRecord rec2;
		rec1.setNum(4, 18);
		rec2.setNum(4, 18);
		NvraComparator c(21);
		Assert::AreEqual(0, c.compare(rec1, rec2));
	}

	TEST_METHOD(NvraComp1) {
		NvraRecord rec1;
		NvraRecord rec2;
		rec1.setNum(100, 18);
		rec2.setNum(4, 18);
		NvraComparator c(21);
		Assert::AreEqual(1, c.compare(rec1, rec2));
	}

	TEST_METHOD(NvraComp2) {
		NvraRecord rec1;
		NvraRecord rec2;
		rec1.setNum(0, 18);
		rec2.setNum(4, 18);
		NvraComparator c(21);
		Assert::AreEqual(-1, c.compare(rec1, rec2));
	}

	TEST_METHOD(IntToString) {
		int i = 23465160;
		std::string s = &convertIntToString(i);
		Logger::WriteMessage(&convertIntToString(i));
	}



	TEST_METHOD(LinkList_Append_And_LE_Next) {
		// requires working append, comparator, and list enum
		NvraComparator* comp = new NvraComparator(0);
		OULinkedList<NvraRecord>* tempList = new OULinkedList<NvraRecord>(comp);

		for (unsigned long i = 0; i < 20; ++i) {
			NvraRecord* tempRec = new NvraRecord();
			tempRec->addNum(i);
			if (!(*tempList).append(tempRec)) {
				throw std::exception();
			} else {
				Logger::WriteMessage("Appended record");
			}
		}

		OULinkedListEnumerator<NvraRecord> list_enum = tempList->enumerator();

		for (unsigned int i = 0; i < tempList->getSize(); ++i) {
			Assert::AreEqual(list_enum.next().getNum(0), i);
		}
		

		delete tempList;
		delete comp;
	}

	TEST_METHOD(ListEnum_Next) {
		NvraComparator* comp = new NvraComparator(0);
		OULinkedList<NvraRecord>* tempList = new OULinkedList<NvraRecord>(comp);

		OULinkedListEnumerator<NvraRecord> list_enum = tempList->enumerator();

		try {
			list_enum.next();
			Assert::Fail;
		} catch (...) {
			// test passed
		}
	}

	};
}