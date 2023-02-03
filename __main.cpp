// HuffmanCode.cpp : Defines the entry point for the console application.
//

// C++ program to encode and decode a string using
// Huffman Coding.
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <vector>
#include <cmath>
#include <fstream>
#include <deque>
#include <functional>
#include <sys/stat.h>
#include <math.h>
#include <iomanip>
#include <algorithm>

#define MAX_TREE_HT 256
#define DATAPATTERNNUM 256
#define TLC 2.32

using namespace std;
void Fucking_WriteFile(string fuckingpath, string fuckingstring);

// to map each character its huffman value
map<string, string> Table;

// to store the frequency of character of the input data
map<string, int> Freq;

map<string, double> DataBER;

const double lowerBER = 0.16;
const double eraseBER = 0.5; //000
const double aBER = 0.3;	 //001
const double bBER = 0.4;	 //010
const double cBER = 2.2;	 //011
const double dBER = 2.0;	 //100
const double eBER = 3.0;	 //101
const double fBER = 5.2;	 //110
const double gBER = 8.0;	 //111
const double upperBER = 1.5;

// A Huffman tree node
struct MinHeapNode
{
	string data;						// One of the input characters
	int freq;							// Frequency of the character
	MinHeapNode *D, *C, *B, *A, *Erase; // Left and right child

	MinHeapNode(string data, int freq)
	{
		D = NULL;
		C = NULL;
		B = NULL;
		A = NULL;
		Erase = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// utility function for the priority queue
struct compare
{
	bool operator()(MinHeapNode *l, MinHeapNode *r)
	{
		return (l->freq > r->freq);
	}
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode *root, string str)
{
	if (!root)
		return;
	if (root->data != "$$")
		cout << root->data << ": " << str << "\n";
	printCodes(root->D, str + "4");
	printCodes(root->C, str + "3");
	printCodes(root->B, str + "2");
	printCodes(root->A, str + "1");
	printCodes(root->Erase, str + "0");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode *root, string str)
{
	if (root == NULL)
		return;
	if (root->data != "$$")
		Table[root->data] = str;
	storeCodes(root->D, str + "4");
	storeCodes(root->C, str + "3");
	storeCodes(root->B, str + "2");
	storeCodes(root->A, str + "1");
	storeCodes(root->Erase, str + "0");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
	struct MinHeapNode *D, *C, *B, *A, *Erase, *top;
	for (map<string, int>::iterator v = Freq.begin(); v != Freq.end(); v++)
		minHeap.push(new MinHeapNode(v->first, v->second));
	while (minHeap.size() != 1)
	{
		if (minHeap.size() >= 5)
		{
			D = minHeap.top();
			minHeap.pop();
			C = minHeap.top();
			minHeap.pop();
			B = minHeap.top();
			minHeap.pop();
			A = minHeap.top();
			minHeap.pop();
			Erase = minHeap.top();
			minHeap.pop();
			top = new MinHeapNode("$$", D->freq + C->freq + B->freq + A->freq + Erase->freq);
			top->D = D;
			top->C = C;
			top->B = B;
			top->A = A;
			top->Erase = Erase;
			minHeap.push(top);
		}
		else if (minHeap.size() == 4)
		{
			C = minHeap.top();
			minHeap.pop();
			B = minHeap.top();
			minHeap.pop();
			A = minHeap.top();
			minHeap.pop();
			Erase = minHeap.top();
			minHeap.pop();
			top = new MinHeapNode("$$", C->freq + B->freq + A->freq + Erase->freq);
			top->D = NULL;
			top->C = C;
			top->B = B;
			top->A = A;
			top->Erase = Erase;
			minHeap.push(top);
			break;
		}
		else if (minHeap.size() == 3)
		{
			B = minHeap.top();
			minHeap.pop();
			A = minHeap.top();
			minHeap.pop();
			Erase = minHeap.top();
			minHeap.pop();
			top = new MinHeapNode("$$", B->freq + A->freq + Erase->freq);
			top->D = NULL;
			top->C = NULL;
			top->B = B;
			top->A = A;
			top->Erase = Erase;
			minHeap.push(top);
			break;
		}
		else if (minHeap.size() == 2)
		{
			A = minHeap.top();
			minHeap.pop();
			Erase = minHeap.top();
			minHeap.pop();
			top = new MinHeapNode("$$", A->freq + Erase->freq);
			top->D = NULL;
			top->C = NULL;
			top->B = NULL;
			top->A = A;
			top->Erase = Erase;
			minHeap.push(top);
			break;
		}
	}
	storeCodes(minHeap.top(), "");
}

/*Code改到這裡*/

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
	string two = "00";
	double BER = 0;

	for (int i = 0; i < n; i += 2)
	{
		two[0] = str[i];
		two[1] = str[i + 1];

		for (int j = i; j < i + 2; ++j)
		{
			switch (str[j])
			{
			case '0':
				BER = BER + eraseBER + lowerBER;
				break;
			case '1':
				BER = BER + aBER + lowerBER;
				break;
			case '2':
				BER = BER + bBER + lowerBER;
				break;
			case '3':
				BER = BER + cBER + lowerBER;
				break;
			case '4':
				BER = BER + dBER + lowerBER;
				break;
			case '5':
				BER = BER + eBER + lowerBER;
				break;
			case '6':
				BER = BER + fBER + lowerBER;
				break;
			case '7':
				BER = BER + gBER + lowerBER;
				break;
			case '8':
				BER = BER + eraseBER + upperBER;
				break;
			case '9':
				BER = BER + aBER + upperBER;
				break;
			case 'A':
				BER = BER + bBER + upperBER;
				break;
			case 'B':
				BER = BER + cBER + upperBER;
				break;
			case 'C':
				BER = BER + dBER + upperBER;
				break;
			case 'D':
				BER = BER + eBER + upperBER;
				break;
			case 'E':
				BER = BER + fBER + upperBER;
				break;
			case 'F':
				BER = BER + gBER + upperBER;
				break;
			}
		}
		Freq[two]++;
		DataBER[two] = BER;
		BER = 0;
	}
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode *root, string s)
{
	string ans = "";
	struct MinHeapNode *curr = root;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '4')
			curr = curr->D;
		else if (s[i] == '3')
			curr = curr->C;
		else if (s[i] == '2')
			curr = curr->B;
		else if (s[i] == '1')
			curr = curr->A;
		else if (s[i] == '0')
			curr = curr->Erase;

		// reached leaf node
		if (curr->D == NULL && curr->C == NULL && curr->B == NULL && curr->A == NULL && curr->Erase == NULL)
		{
			ans += curr->data;
			curr = root;
		}
	}
	// cout<<ans<<endl;
	return ans + '\0';
}

// Driver program to test above functions
int main(int argc, char *argv[])
{
	//5LC
	ifstream fin;
	ofstream fout;
	string fileName = argv[1];
	int pos = fileName.find_last_of('/');
	string dir = fileName.substr(0, pos);
	string name = fileName.substr(pos + 1, fileName.length() - pos);
	string keyword = "Preprocess";
	fileName.replace(fileName.find(keyword), keyword.size(), "HuffmanOutput/5LC_Output/Frequency");
	cout << fileName << endl;
	dir.replace(dir.find(keyword), keyword.size(), "HuffmanOutput/5LC_Output/Frequency");
	cout << dir << endl;
	dir = "mkdir -p " + dir;
	const int dir_err = system(dir.c_str());
	if (dir_err == -1)
		cout << "create error!";
	fin.open(argv[1]);
	fileName = fileName.substr(0, fileName.find_last_of('.')) + ".txt";
	fout.open(fileName);
	//compare
	ofstream fcompare;
	fcompare.open("compare.csv", ios::app);
	pos = name.find_last_of('_');
	string output_name = name.substr(0, pos);
	pos = name.find("_output") + 7;
	string output_number = name.substr(pos, name.find(".") - pos);
	fcompare << output_name << ',';
	fcompare << output_number << ',';

	string buffer;
	string str;
	int j = 0;

	if (!fin)
		std::cout << "檔案無法開啟\n";
	else
	{
		while (getline(fin, buffer))
		{
			if (j == 0)
			{
				str = buffer;
				j = 1;
			}
			else
				str = str + buffer;
		}
	}
	cout << str.size() << endl;
	string encodedString, decodedString;

	calcFreq(str, str.size());

	HuffmanCodes(str.size());

	/*計算壓縮率*/
	double CR = 0, BeforeCapacity = 0, AfterCapacity = 0; //Before：壓縮前大小，After：壓縮後大小
	double CellCost = 0;
	double BER = 0, BeforeBER = 0, BufferBER = 0, AfterBER = 0;
	/*各Data Pattern的BER*/

	//	double BERstatus[4] = { eraseBER, aBER, cBER, bBER};
	int yee = 0, k = 0;

	int freq[DATAPATTERNNUM], freqCount = 0;

	fout << "Frequency of each state : " << endl;
	vector<std::pair<std::string, int>> tmp(Freq.cbegin(), Freq.cend());
	std::sort(tmp.begin(), tmp.end(), [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
		return a.second > b.second;
	});
	for (const auto &p : tmp)
	{
		for (char ch : p.first)
		{
			fout << ch;
		}
		fout << ' ' << p.second << endl;
	}
	for (auto x = Freq.begin(); x != Freq.end(); x++)
	{
		freq[freqCount] = x->second;
		BeforeCapacity += x->second;
		freqCount++;
	}
	freqCount = 0;
	fout << std::endl;
	BeforeCapacity *= 8; //壓縮前大小，一個Data Pattern為8 bits

	for (auto x = DataBER.begin(); x != DataBER.end(); x++)
	{
		BeforeBER += x->second * freq[k];
		k++;
	}

	fout << "Status mapping : 4 = D, 3 = C, 2 = B, 1 = A, 0 = Erase" << std::endl;
	char a = '$';
	int count = 0;
	int pattern_number = 0;
	//	cout << "Character With there Frequencies:\n";
	for (auto v = Table.begin(); v != Table.end(); v++)
	{ //計算壓縮後大小
		//		cout << v->first << ' ' << v->second << endl;
		for (int i = 0; i < 10; ++i)
		{
			if (v->second[i] == '\0')
				break;
			else
			{
				a = v->second[i];
				count++;
				if (a == '4')
				{ //D
					BufferBER += dBER;
				}
				else if (a == '3')
				{ //C
					BufferBER += cBER;
				}
				else if (a == '2')
				{ //B
					BufferBER += bBER;
				}
				else if (a == '1')
				{ //A
					BufferBER += aBER;
				}
				else if (a == '0')
				{ //Erase
					BufferBER += eraseBER;
				}
			}
		}
		AfterBER += BufferBER * freq[freqCount];
		BufferBER = 0;
		count *= freq[freqCount++];
		CellCost += count;
		AfterCapacity += TLC * count; //一個狀態為3 bits
		count = 0;
		pattern_number++;
		for (char ch : v->first)
		{
			fout << ch;
		}
		fout << ' ' << v->second << endl;
	}
	fout << "pattern number : " << pattern_number << endl;
	fout << endl;

	cout << "Uncompression Cell number : " << setprecision(0) << fixed << ceil(BeforeCapacity / 3) << endl;
	fout << "Uncompression Cell number : " << setprecision(0) << fixed << ceil(BeforeCapacity / 3) << endl;
	cout << "Compression Cell number : " << setprecision(0) << fixed << CellCost << endl;
	fout << "Compression Cell number : " << setprecision(0) << fixed << CellCost << endl;
	CR = (CellCost)*300 / BeforeCapacity;
	cout << "Compression Rate(CR) (%) : " << std::setprecision(3) << fixed << CR << "%" << endl;
	fout << "Compression Rate(CR) (%) : " << std::setprecision(3) << fixed << CR << "%" << endl;

	BER = (AfterBER - BeforeBER) * 100 / BeforeBER;
	cout << "Uncompression bit error rate(BER) : " << std::setprecision(2) << fixed << BeforeBER << endl;
	cout << "Compression bit error rate(BER) : " << std::setprecision(2) << fixed << AfterBER << endl;
	cout << "bit error rate difference(%) : " << std::setprecision(3) << fixed << BER << "%" << endl;
	fout << "Uncompression bit error rate(BER) : " << std::setprecision(2) << fixed << BeforeBER << endl;
	fout << "Compression bit error rate(BER) : " << std::setprecision(2) << fixed << AfterBER << endl;
	fout << "bit error rate difference(%) : " << std::setprecision(3) << fixed << BER << "%" << endl;
	fcompare << std::setprecision(3) << fixed << BER << "%,";
	fcompare << std::setprecision(3) << fixed << CR << "%,";
	fcompare << "5" << endl;
	fcompare.close();

	string BestFitString;
	int CClemon = 0;
	for (int i = 0; i < str.size(); i += 2)
	{
		string two = "00";
		double Yee = 0;
		two[0] = str[i];
		two[1] = str[i + 1];
		BestFitString += Table[two];
		encodedString += Table[two];
		CClemon += 2;
		if ((CClemon == 8192) || (i == str.size() - 2))
		{
			Yee = BestFitString.size() / 8192.0;
			//			fout2 << Yee << endl;
			BestFitString = "";
			CClemon = 0;
		}
	}

	//	cout << "\nEncoded Huffman data:\n" << encodedString << endl;

	decodedString = decode_file(minHeap.top(), encodedString);
	//	cout << "\nDecoded Huffman Data:\n" << decodedString << endl;
	//	cout << sizeof(map<int, int>) << "\t" << sizeof(Table) << "\t" << sizeof(Freq) << "\t" << sizeof(char) << endl;

	// 2020/10/22
	fileName = argv[1];
	keyword = "Preprocess";
	fileName.replace(fileName.find(keyword), keyword.size(), "HuffmanOutput/5LC_Output/Frequency");

	// 2020/10/22
	string fileName2 = fileName;
	//

	keyword = ".txt";
	fileName2.replace(fileName2.find(keyword), keyword.size(), "_compressd_5LC.txt");
	Fucking_WriteFile(fileName2.c_str(), encodedString);

	string fileName3 = fileName;
	fileName3.replace(fileName3.find(keyword), keyword.size(), "_uncompressd_5LC.txt");
	Fucking_WriteFile(fileName3.c_str(), decodedString);
	return 0;
}

/*
write binary file
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void Fucking_WriteFile(string fuckingpath, string fuckingstring)
{

	const char *buffer = fuckingstring.c_str();
	// unsigned char *buffer;
	// if (posix_memalign((void **)&buffer, 512, sizeof(fuckingstring)))
	// {
	//     perror("posix_memalign failed");
	//     exit(1);
	// }
	// memset(buffer, 'f', BUF_SIZE);
	cout << fuckingpath << endl;
	int fd = open(fuckingpath.c_str(), O_WRONLY | O_CREAT);
	if (fd < 0)
    {
        perror("open file failed\n");
        exit(1);
    }
	int ret = write(fd, buffer, fuckingstring.size());
    if (ret<0)
        perror("write file failed\n");
	else
		printf("write success\n");
    close(fd);
}