#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include "Functions.h"
#include "Media.h"

using namespace std;

bool isDigits(string str1) {
    return (str1.find_first_not_of("-1234567890") == string::npos);
}

bool isValidType(string type) {
    return (type.find_first_not_of("MBS") == string::npos);
}
 
int readMediaList(istream& inFile, ostream& outFile, vector<Media*>& mediaLib) {
    //The input line and each word in the line.
    string line, word;
    // Creates a temporary media that will be added to the vector.
    Media* tempMedia;
    // Stores the words in the (expected) order: type, title, name, rating, genre, length, year.
    vector<string> words;
    string type, title, name, genre;
    // Stores the first letter of the type.
    char tyChar;
    int rating, length, year;
    while (getline(inFile, line)) {
        stringstream inss(line);
        words.clear();
        while (getline(inss, word, ',')) {
            words.push_back(word);
        }
        // Ends the loop if the quit chracter is found.
        if (words.at(0) == "Q") {
            break;
        }
        type = words.at(0);
        if (!isValidType(type)) {
            outFile << "Error- Invalid type: " << line << "\n" << endl;
            continue;
        }
        title = words.at(1);
        name = words.at(2);
        genre = words.at(4);
        try {
            rating = stoi(words.at(3));
            length = stoi(words.at(5));
            year = stoi(words.at(6));
        }
        // Invalid items in the numeric fields.
        catch (invalid_argument) {
            outFile << "Error- invalid stoi argument: " << line << "\n" << endl;
            continue;
        }
        if (rating <= 0 || length <= 0 || year <= 0) {
            outFile << "Error- numeric value <= 0: " << line << "\n" << endl;
            continue;
        }
        if (rating > 10) {
            outFile << "Error- invalid rating: " << line << "\n" << endl;
            continue;
        }
        if (year < 1920 || year > 2024) {
            outFile << "Error- invalid year: " << line << "\n" << endl;
            continue;
        }
        tyChar = type.at(0);
        tempMedia = new Media(tyChar, title, name, rating, genre, length, year);
        mediaLib.push_back(tempMedia);
    }
    return 0;
}

void printMedia(ostream& outFile, vector<Media*>& media) {
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your Media List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year" << setw(8) << "Rating" << "Type" << endl;
    for (int i = 0; i < media.size(); i++) {
        outFile << left << setw(4) << i + 1 << setw(40) << media.at(i)->getTitle() << setw(8) 
             << media.at(i)->getYearReleased() << setw(8) << media.at(i)->getRating() << media.at(i)->getType() << endl;
    }
    outFile << "\n\n" << endl;
}

void printType(ostream& outFile, vector<Media*>& media, char type) {
    string dispType;
    // Chooses a type for use in displaying.
    switch (type) {
        case 'M':
            dispType = "Movie";
            break;
        case 'S':
            dispType = "Song";
            break;
        case 'B':
            dispType = "Book";
            break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year" << "Rating" << endl;
    for (int i = 0; i < media.size(); i++) {
        if (media.at(i)->getType() == type) {
            outFile << left << setw(4) << i + 1 << setw(40) << media.at(i)->getTitle() << setw(8) << media.at(i)->getYearReleased() << media.at(i)->getRating() << endl;
        }
    }
    outFile << "\n\n" << endl;
}

void printRating(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, int rating) {
    if (rating > 10 || rating < 0) {
        errFile << "Error- rating of " << rating << " is invaild\n" << endl;
        return;
    }
    string dispType;
    // Chooses a type for use in displaying.
    switch (type) {
    case 'M':
        dispType = "Movie";
        break;
    case 'S':
        dispType = "Song";
        break;
    case 'B':
        dispType = "Book";
        break;
    case 'A':
        dispType = "Media";
        break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year" << "Rating" << endl;
    // Checks if all media will be output or only a specific type.
    if (type != 'A') {
        for (int i = 0; i < media.size(); i++) {
            if (media.at(i)->getType() == type && media.at(i)->getRating() >= rating) {
                outFile << left << setw(4) << i + 1 << setw(40) << media.at(i)->getTitle() << setw(8) << media.at(i)->getYearReleased() << media.at(i)->getRating() << endl;
            }
        }
    }
    else {
        for (int i = 0; i < media.size(); i++) {
            if (media.at(i)->getRating() >= rating) {
                outFile << left << setw(4) << i + 1 << setw(40) << media.at(i)->getTitle() << setw(8) << media.at(i)->getYearReleased() << media.at(i)->getRating() << endl;
            }
        }
    }
    outFile << "\n\n" << endl;
}

void printGenre(ostream& outFile, ostream& errFile, vector<Media*>& media, char type, string genre) {
    string dispType;
    // Stores if any media has been output.
    bool printed = false;
    // Chooses a type for use in displaying.
    switch (type) {
    case 'M':
        dispType = "Movie";
        break;
    case 'S':
        dispType = "Song";
        break;
    case 'B':
        dispType = "Book";
        break;
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your " << dispType << " List\n" << endl;
    outFile << left << setw(4) << "#" << setw(40) << "Title" << setw(8) << "Year" << setw(8) << "Rating" << "Genre" << endl;
    for (int i = 0; i < media.size(); i++) {
        if (media.at(i)->getType() == type && media.at(i)->getGenre() == genre) {
            printed = true;
            outFile << left << setw(4) << i + 1 << setw(40) << media.at(i)->getTitle() << setw(8) << media.at(i)->getYearReleased() 
                 << setw(8) << media.at(i)->getRating() << media.at(i)->getGenre() << endl;
        }
    }
    // If not media of the genre found, output and error.
    if (!printed) {
        outFile << "No items of genre " << genre << endl;
        errFile << "Error - No items of genre " << genre << "\n" <<endl;
    }
    outFile << "\n\n" << endl;
}

void printTotals(ostream& outFile, const vector<Media*>& media) {
    int numMovie = 0, numBook = 0, numSong = 0;
    char type;
    for (int i = 0; i < media.size(); i++) {
        // Totals the number of types.
        type = media.at(i)->getType();
        switch (type) {
        case 'M':
            numMovie++;
            break;
        case 'S':
            numSong++;
            break;
        case 'B':
            numBook++;
            break;
        }
    }
    outFile << setfill('+') << setw(60) << "" << setfill(' ') << endl;
    outFile << "            Your media library" << endl;
    outFile << setw(3) << "#" << "Type" << endl;
    outFile << setw(3) << numMovie << "Movies" << endl;
    outFile << setw(3) << numBook << "Books" << endl;
    outFile << setw(3) << numSong << "Songs" << endl;
    outFile << setw(3) << numMovie + numBook + numSong << "Items" << endl;
    outFile << "\n\n" << endl;
}

void addNewItem(ostream& errFile, ostream& outFile, vector<Media*>& media, const vector<string>& tokens) {
    // The temporary media to be added to the vector.
    Media* tempMedia;
    string type, title, name, genre;
    char tyChar;
    int rating, length, year;

    type = tokens.at(1);
    tyChar = type.at(0);
    title = tokens.at(2);
    name = tokens.at(3);
    genre = tokens.at(5);
    if (!isValidType(type)) {
        errFile << "Cannot add item- Invalid type: " << type << "\n" << endl;
        return;
    }

    try {
        rating = stoi(tokens.at(4));
        length = stoi(tokens.at(6));
        year = stoi(tokens.at(7));
    }
    // Invalid items in the numeric fields.
    catch (invalid_argument) {
        errFile << "Cannot add item- invalid stoi argument: " << title << "\n" << endl;
        return;
    }
    if (rating <= 0 || length <= 0 || year <= 0) {
        errFile << "Cannot add item- numeric value <= 0: " << title << "\n" << endl;
        return;
    }
    if (rating > 10) {
        errFile << "Cannot add item- invaild rating: " << title << "\n" << endl;
        return;
    }
    if (year < 1920 || year > 2024) {
        errFile << "Cannot add item- invalid year: " << title << "\n" << endl;
        return;
    }
    tempMedia = new Media(tyChar, title, name, rating, genre, length, year);
    outFile << title << " was added to your list\n\n" << endl;
    media.push_back(tempMedia);
}