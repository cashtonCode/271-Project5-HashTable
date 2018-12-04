#include<iostream>
#include<cstring>
#include<cstdlib>
#include <fstream>
using namespace std;

class hash
{
public:
    //hash table
    char * hashTable;
    int tableSize, unusedCounter, totalProbes, successes, fails;

    //constructor
    hash(int size)
    {
      hashTable = new char[size];
      tableSize = size;
      unusedCounter = size;
      successes = 0;
      fails = 0;
      totalProbes = 0;
      for(int i = 0; i < tableSize; i++)
        hashTable[i] = ' ';
    }

    //insert function
    void hashInsert(int pos, const char * key)
    {
      int check;
      if(unusedCounter == 0)//CHECKS IF TABLE IS FULL
        return;
      if(hashTable[pos] == ' ')//CHECKS IF POSITION IS EMPTY
      {
        hashTable[pos] = key;
        unusedCounter -= 1;
        return;
      }
      //LOOKS FOR THE NEAREST UNUSED SPOT FOR KEY
      do {
        pos += 1;
        totalProbes++;
        check = hashTable[pos];
      } while(check == ' ');

      hashTable[pos] = key;
      unusedCounter -= 1;
    }

    //search function
    bool hashSearch(int pos, char key)
    {
      int check;
      if(hashTable[pos] == ' ')//CHECKS IF POS IS EMPTY
      {
        fails++;
        return false;
      }
      if(hashTable[pos] == key)//CHECKS IF POS HAS KEY
      {
        successes++;
        return true;
      }

      //LOOKS FOR KEY OR EMPTY SPOT
      int count = 1;
      do {
        pos += 1;
        totalProbes++;
        check = hashTable[pos];
        count++;
        if(hashTable[pos] == ' ')//CHECKS IF POS IS EMPTY
        {
          fails++;
          return false;
        }
        if(hashTable[pos] == key)//CHECKS IF POS HAS KEY
        {
          successes++;
          return true;
        }
        if(pos == tableSize) pos = 0;
      } while(check != key && key != ' ' && count < tableSize);

      return false;
    }

};


//hash function - converts char array to int
//PAGE 329
// Use folding on a string, summed 4 bytes at a time
int sfold(const char * key, int tableSize)
{
  unsigned int * lkey = (unsigned int * )key;
  int intlength = strlen(key) / 4;
  unsigned int sum = 0;
  for(int i = 0; i < intlength; i++)
    sum += lkey[i];

  // Now deal with the extra chars at the end
  int extra = strlen(key) - intlength * 4;
  char temp[4];
  lkey = (unsigned int * )temp;
  lkey[0] = 0;
  for(int i = 0; i < extra; i++)
    temp[i] = key[intlength * 4 + i];
  sum += lkey[0];

  return sum % tableSize;
};


// time ./a.out #
int main(int argc, char* argv[])
{
  int tableSize = atoi(argv[1]), pos;
  hash table(tableSize);

  string line;
  bool status;
  char * lineArray;
  ifstream inFile;

  //ASSIGN KEY
  inFile.open("/home/win.thackerw/271/sort.dat");
  if(!inFile.good())
    return 1;
  for(int i = 0; i < 400000; i++)
  {
    inFile >> line;
    //lineArray = line.c_str();
    pos = sfold(line.c_str(), tableSize);
    table.hashInsert(pos, line.c_str());
  }
  inFile.close();

  //SEARCH FOR KEY
  inFile.open("/home/win.thackerw/271/sort.dat");
  if(!inFile.good())
    return 1;
  cout << "before search" << endl;

  int count = 0;

  while(inFile >> line)
  {
    lineArray = line.c_str();
    pos = sfold(lineArray);
    status = table.hashSearch(pos, lineArray);
  }
  cout << "after search" << endl;
  inFile.close();

  cout << "Total # Probes: " << table.totalProbes << endl;
  cout << "Total Unsuccessful: " << table.fails << endl;
  cout << "Total Successful: " << table.successes << endl;


  return 0;
};
