/*
Author:   Cashton Christensen
Date: 	4/10/2018
Purpose:  To store 400,000 char arrays (strings) in a hash table and search for them among many others.
*/

#include<iostream>
#include<cstring>
#include<cstdlib>
#include <fstream>
using namespace std;

class hash
{
public:
    //hash table
    string * hashTable;
    int tableSize, unusedCounter, totalProbes, successes;
    float fails;

    //constructor
    hash(int size)
    {
      hashTable = new string[size];
      tableSize = size;
      unusedCounter = size;
      successes = 0;
      fails = 0;
      totalProbes = 0;
      for(int i = 0; i < tableSize; i++)
        hashTable[i] = " ";
    }

    //insert function
    void hashInsert(int pos, string key)
    {
      if(unusedCounter == 0) return;  //CHECKS IF TABLE IS FULL
      while(hashTable[pos] != " ") //LOOKS FOR THE NEAREST UNUSED SPOT FOR KEY - Collision Handler
      {
        pos++;
        if(pos == tableSize) pos = 0;
      }
      hashTable[pos] = key;
      unusedCounter--;
      return;
    }

    //search function
    void hashSearch(int pos, string key)
    {
      totalProbes++;
      int count = 1;
      //pos has different KEY - Collision Handler
      while((hashTable[pos] != " ") && (hashTable[pos] != key) && (count != tableSize))
      {
        pos++;
        if(pos == tableSize) pos = 0;
        totalProbes++;
        count++;
      }
      //pos is empty
      if(hashTable[pos] == " ") fails++;
      //pos has KEY
      if(hashTable[pos] == key) successes++;
      return;
    }
};

//hash function - converts char array to int
//PAGE 329
// Use folding on a string, summed 4 bytes at a time
int sfold(string key, int tableSize)
{
  unsigned int * lkey = (unsigned int * )key.c_str();
  int intlength = strlen(key.c_str()) / 4;
  unsigned int sum = 0;
  for(int i = 0; i < intlength; i++)
    sum += lkey[i];

  // Now deal with the extra chars at the end
  int extra = strlen(key.c_str()) - intlength * 4;
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
  char * lineArray;
  ifstream inFile;

  //ASSIGN KEY
  inFile.open("/home/win.thackerw/271/sort.dat");
  if(!inFile.good())
    return 1;
  for(int i = 0; i < 400000; i++)
  {
    inFile >> line;
    pos = sfold(line, tableSize);
    table.hashInsert(pos, line);
  }
  inFile.close();

  //SEARCH FOR KEY
  inFile.open("/home/win.thackerw/271/search.dat");
  if(!inFile.good())
    return 1;
  while(inFile >> line)
  {
    pos = sfold(line, tableSize);
    table.hashSearch(pos, line);
  }
  inFile.close();

  float avgProbes = table.totalProbes / (table.fails + table.successes);

  cout << "\tTotal # Probes: " << table.totalProbes << endl;
  cout << "\tAvg # Probes: " << avgProbes << endl;
  cout << "\tTotal Unsuccessful: " << table.fails << endl;
  cout << "\tTotal Successful: " << table.successes << endl;

  return 0;
};
