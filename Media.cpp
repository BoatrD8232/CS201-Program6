#include <string>
#include <iostream>
#include "Media.h"
using namespace std;

Media::Media(){
  this->type = ' ';
  this->title = " ";
  this->name = " ";
  this->rating = -1;
  this->genre = " ";
  this->length = -1;
  this->yearReleased = -1;

}

Media::Media(char inType, string inTitle, string inName, int inRating, string inGenre, int inLength, int inYear) {
	type = inType;
	title = inTitle;
	name = inName;
	rating = inRating;
	genre = inGenre;
	length = inLength;
	yearReleased = inYear;
}

void Media::setType(char c) { type = c; }
void Media::setTitle(string t) { title = t; }
void Media::setName(string n) { name = n; }
void Media::setRating(int r) { rating = r; }
void Media::setGenre(string g) { genre = g; }
void Media::setLength(int l) { length = l; }
void Media::setYearReleased(int yr) { yearReleased = yr; }

char   Media::getType() { return type; }
string Media::getTitle() { return title; }
string Media::getName() { return name; }
int    Media::getRating() { return rating; }
string Media::getGenre() { return genre; }
int    Media::getLength() { return length; }
int    Media::getYearReleased() { return yearReleased; }


 
 