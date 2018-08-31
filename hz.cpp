#include <map>
#include <fstream>
#include <iostream>

static std::map<int, size_t> parse(std::ifstream &stream);
static void report(const std::map<int, size_t> &symbols);

int main(int argc, char **argv) {
    std::ifstream stream;

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILE" << std::endl;
        return 1;
    }

    stream.open(argv[1], std::ifstream::in);
    if (stream) {
        report(parse(stream));
        stream.close();
        return 0;
    }

    std::cerr << "ERROR: unable to open file: '" << argv[1] << "'" << std::endl;
    return 2;
}

std::map<int, size_t> parse(std::ifstream &stream) {
    std::map<int, size_t> symbols;
    for (int c = stream.get(); EOF != c; c = stream.get()) {
        auto it = symbols.find(c);
        if (it == symbols.end()) {
            symbols[c] = 1;
        } else {
            it->second++;
        }
    }
    return symbols;
}

void report(const std::map<int, size_t> &symbols) {
    size_t i = 1;
    for (const auto &pair : symbols) {
        const auto ch = pair.first;
        std::cout << "No: " << i++
                  << "\tASCII: " << ch
                  << "\tCh: " << (isprint(ch) ? static_cast<char>(ch) : ' ')
                  << "\tHz: " << pair.second
                  << std::endl;
    }
    std::cout << std::endl << "Total symbols: " << symbols.size() << std::endl;
}
