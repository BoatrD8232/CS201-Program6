#pragma once
#include <string>
#include <iostream>
using namespace std;

class Media {

private :
  char type;
  string title;
  string name;
  int rating;
  string genre;
  int length;
  int yearReleased;

public:
	//PRE: The default constructor, takes no arguments.
	//POST: Sets all the string members to the empty string and all int members to -1;
  Media();

  //PRE: Takes in values for the type, title, name, rating, genre, length, and year.
  //POST: Sets the data members with the above inputs.
  Media (char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear);
  void setType  (char c);
  void setTitle (string t);
  void setName  (string n);
  void setRating (int r);
  void setGenre(string g);
  void setLength(int l);
  void setYearReleased (int yr);


  char   getType();
  string getTitle();
  string getName();
  int    getRating();
  string getGenre();
  int    getLength();
  int    getYearReleased();

  
 
};
