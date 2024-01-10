#ifndef __STRUCTS
#define __STRUCTS

#include <string>
#include <vector>
using namespace std;

struct wordcount {
    string wordname;
    int count;
};

struct textFile {

    string fileName;
    vector<wordcount> word_count;
};

struct DocumentItem {
    string documentName;
    int count;
};

struct WordItem {
    WordItem(string word) : word(word), left(nullptr), right(nullptr), height(0) {}
    WordItem( const string & theElement, WordItem *lt, WordItem *rt, int h = 0 )
            : word( theElement ), left( lt ), right( rt ), height( h ) { }
    string word;
    WordItem* left;
    WordItem* right;
    vector<DocumentItem> details;
    int height;
};

struct FileContents {
    string FileName;
    vector<string> FileContent;

    FileContents(string filename, vector<string> content);
};

FileContents::FileContents(string filename, vector<string> content) {
    FileName = filename;
    FileContent = content;
}


#endif