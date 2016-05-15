#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

/**
 * Declaration
 */
struct symbol_t
{
    unsigned char ch;
    unsigned short hz;
};

vector<symbol_t> symbols_vector;
ifstream file_stream;
streambuf* stream_buffer;

bool operator < (const symbol_t& a, const symbol_t& b);
void parse();
void report();


/**
 * Main
 */
int main(int argc, char** argv)
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " FILE" << endl;
        exit(1);
    }

    file_stream.open(argv[1], ifstream::in);

    if (file_stream)
    {
        parse();
        sort(symbols_vector.begin(), symbols_vector.end());
        report();
    }
    else
    {
        cerr << "ERROR: unable to open file: '" <<  argv[1] << "'" << endl;
    }

    file_stream.close();
    return 0;
}


/**
 * Implementation
 */
bool operator < (const symbol_t& a, const symbol_t& b)
{
    return a.hz < b.hz;
}

void parse()
{
    size_t i = 0;
    symbol_t symbol = {'\0', 1};

    stream_buffer = file_stream.rdbuf();

    // Read char by char from the file
    while (stream_buffer->sgetc() != EOF)
    {
        // Get the next symbol in the file
        symbol.ch = stream_buffer->sbumpc();

        // Scroll symbols_vector to discover if the current symbol already exists
        for (i = 0; i < symbols_vector.size(); i++)
        {
            // if true the symbol already exists in symbols_vector
            if (symbols_vector[i].ch == symbol.ch)
            {
                symbols_vector[i].hz++;  // Increase frequency of the symbol in the symbols_vector
                break;
            }
        }

        // If true, there is a new symbol to add to symbols_vector
        if (i == symbols_vector.size())
        {
            symbols_vector.push_back(symbol);
        }
    }

    return;
}

void report()
{
    for (size_t i = 0; i < symbols_vector.size(); i++)
    {
        cout << "No. "          << i
             << "\tCode: "      << (int) symbols_vector[i].ch
             << "\tChar: "      << (char) ((symbols_vector[i].ch > 32) ? symbols_vector[i].ch : ' ')
             << "\t\tFreqency: "  << symbols_vector[i].hz
             << endl;
    }

    cout << "\nTotal symbols: " << symbols_vector.size() << endl;

    return;
}

