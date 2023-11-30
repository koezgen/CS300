#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "AVLSearchTree.h"
using namespace std;

// Kanat Ozgen

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

bool isInside(string filename, vector<DocumentItem> textfile)
{
    bool flag = false;

    for (int i = 0; i < textfile.size(); i++)
    {
        if (textfile[i].documentName == filename)
        {
            flag = true;
        }
    }

    return flag;
}

int main() {

    // The Tree of Life
    AVLSearchTree<string, WordItem *> myTree("item_not_found");

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

    // Process the files and hold them inside a dynamically allocated
    // Array that holds the file data and the file name.
    vector<FileContents> file_contents;
    for (int i = 0; i < file_names.size(); i++)
    {
        ifstream file;
        file.open(file_names[i]);
        string processed_file;

        while (!file.eof())
        {
            string line;
            getline(file, line);
            processed_file += line + " ";
        }

        processed_file = tolowercase(processed_file);
        vector<string> parsed_processed_file = return_parsed_input(processed_file);

        FileContents filecontent(file_names[i], parsed_processed_file);
        file_contents.push_back(filecontent);
    }

    for (int i = 0; i < file_contents.size(); i++)
    {
        for (int j = 0; j < file_contents[i].FileContent.size(); j++)
        {
            // Checking if the word appears in the tree
            if (myTree.find(file_contents[i].FileContent[j])->word == "item_not_found")
            {
                myTree.insert(file_contents[i].FileContent[j]);
                WordItem *worditem = myTree.find(file_contents[i].FileContent[j]);
                DocumentItem documentitem;
                documentitem.documentName = file_contents[i].FileName;
                documentitem.count = 1;
                worditem->details.push_back(documentitem);
            }

            else
            {
                WordItem *worditem = myTree.find(file_contents[i].FileContent[j]);
                if (isInside(file_contents[i].FileName, worditem->details))
                {
                    for (int k = 0; k < worditem->details.size(); k++)
                    {
                        if (worditem->details[k].documentName == file_contents[i].FileName)
                        {
                            worditem->details[k].count++;
                        }
                    }
                }

                else
                {
                    DocumentItem documentitem;
                    documentitem.documentName = file_contents[i].FileName;
                    documentitem.count = 1;
                    worditem->details.push_back(documentitem);
                }
            }
        }
    }

    cin.clear();
    cin.ignore();

    // Get the input line from the user.
    string input_line;
    cout << endl << "Enter queried words in one line: ";
    getline(cin, input_line);
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
                myTree.remove(parsed_input.at(parsed_input.size() - 1));
                cout << parsed_input.at(parsed_input.size() - 1) << " has been REMOVED" << endl;
                parsed_input.pop_back();
            }
        }

        else
        {
            for (int i = 0; i < parsed_input.size(); i++)
            {
                WordItem *worditem = myTree.find(parsed_input[i]);

                if (worditem->word != "item_not_found")
                {
                    for (int i = 0; i < worditem->details.size(); i++)
                    {
                        if (!isInside(worditem->details[i].documentName, file_responses))
                        {
                            textFile textfile;
                            textfile.fileName = worditem->details[i].documentName;

                            wordcount wcount;
                            wcount.wordname = worditem->word;

                            textfile.word_count.push_back(wcount);

                            file_responses.push_back(textfile);
                        }

                        else
                        {
                            for (int j = 0; j < file_responses.size(); j++)
                            {
                                if (file_responses[j].fileName == worditem->details[i].documentName)
                                {
                                    wordcount wcount;
                                    wcount.wordname = worditem->word;
                                    wcount.count = worditem->details[i].count;

                                    file_responses[j].word_count.push_back(wcount);
                                }
                            }
                        }
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
                        cout << file_responses[i].word_count[file_responses[i].word_count.size() - 1].wordname << " was found "
                             << file_responses[i].word_count[file_responses[i].word_count.size() - 1].count << " times";
                        file_responses[i].word_count.pop_back();

                        if (!file_responses[i].word_count.empty())
                        {
                            cout << ", ";
                        }
                    }

                    cout << endl;

                }

                cout << endl;

            }

        }

        cout << "Enter queried words in one line: ";
        getline(cin, input_line);
    }

    return 0;
}
