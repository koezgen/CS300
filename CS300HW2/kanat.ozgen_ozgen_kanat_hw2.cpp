#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <cctype>
#include "AVLSearchTree.h"
using namespace std;

// Kanat Ozgen



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
    string word;
    vector<DocumentItem> details;
};

struct FileContents {
    string FileName;
    string FileContent;

    FileContents(string filename, string content);
};

FileContents::FileContents(string filename, string content) {
    FileName = filename;
    FileContent = content;
}

string tolowercase(string & str)
{
    string var = str;
    for (int i = 0; i < var.size(); i++)
    {
        var[i] = tolower(var[i]);
    }

    return var;
}

vector<string> return_parsed_input(string & input)
{
    vector<string> parsed;
    istringstream iss(input);
    string word;

    while (iss >> word)
    {
        parsed.push_back(word);
    }

    return parsed;
}

bool isInside(string filename, vector<textFile> textfile)
{
    bool flag = false;

    for (int i = 0; i < textfile.size(); i++)
    {
        if (textfile[i].fileName == filename)
        {
            flag = true;
        }
    }

    return flag;
}

int main() {

    // The Tree of Life
    AVLSearchTree<string, WordItem *> myTree;

    // The variables that will hold the necessary
    // Information in gathering the file names.
    vector<string> file_names;
    int file_count;
    string file_name;

    cout << "Enter number of input files: ";
    cin >> file_count;

    for (int i = 1; i <= file_count; i++)
    {
        cout << "Enter " << i << ". file name: ";
        cin >> file_name;
        file_names.push_back(file_name);
    }

    // TODO: Necessary implementation for data structures.

    // Process the files and hold them inside a dynamically allocated
    // Array that holds the file data and the file name.
    vector<FileContents> file_contents;
    for (int i = 0; i < file_names.size(); i++)
    {
        ifstream file;
        file.open(file_names[i]);
        string processed_file;
        file >> processed_file;
        file.close();

        processed_file = tolowercase(processed_file);

        FileContents filecontent(file_names[i], processed_file);
        file_contents.push_back(filecontent);
    }

    // TODO: Write the AVL Search Tree Functionality in finding the number counts in different files.

    // Get the input line from the user.
    string input_line;
    cout << endl << "Enter queried words in one line: ";
    cin >> input_line;
    while (input_line != "ENDOFINPUT")
    {
        // First we need to parse the input line into a vector array.
        // For this, for the sake of keeping the codebase clean,
        // A function will be called.
        vector<string> parsed_input = return_parsed_input(input_line);

        // Now this is important. Due to the fact that I fetch Word Items
        // From the AVL Tree, I need to save them inside a specific format.
        // Because of the desired console output stream format.
        vector<textFile> file_responses;

        // Case where the REMOVE command is entered
        if (parsed_input.at(0) == "REMOVE")
        {
            // Loop to actually remove everything that comes after the remove keyword.
            while (parsed_input.size() != 1)
            {
                cout << parsed_input.at(parsed_input.size() - 1) << "has been REMOVED" << endl;
                parsed_input.pop_back();
            }
        }

        else
        {
            for (int i = 0; i < parsed_input.size(); i++)
            {
                // TODO: Get the response from the AVL for this word.

                WordItem worditem;
                // Add the files to the file_responses vector if the file
                // Is not present in the array.

                for (int i = 0; i < worditem.details.size(); i++)
                {
                    if (!isInside(worditem.details[i].documentName, file_responses))
                    {
                        textFile textfile;
                        textfile.fileName = worditem.details[i].documentName;

                        wordcount wcount;
                        wcount.wordname = worditem.word;

                        textfile.word_count.push_back(wcount);

                        file_responses.push_back(textfile);
                    }
                }
            }

            if (file_responses.empty())
            {
                cout << "No document contains the given query" << endl << endl;
            }

            else
            {
                for (int i = 0; i < file_responses.size(); i++)
                {
                    cout << "in Document " << file_responses[i].fileName << ", ";

                    while (!file_responses[i].word_count.empty())
                    {
                        cout << file_responses[i].word_count[file_responses[i].word_count.size() - 1].wordname << "found "
                             << file_responses[i].word_count[file_responses[i].word_count.size() - 1].count << "times, ";
                        file_responses[i].word_count.pop_back();
                    }
                }
            }

        }

        cout << "Enter queried words in one line: ";
        cin >> input_line;
    }


    return 0;
}
