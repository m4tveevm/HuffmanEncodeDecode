#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char ch, int freq, Node* left = nullptr, Node* right = nullptr)
            : ch(ch), freq(freq), left(left), right(right) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

string serialize(Node* root) {
    if (!root) return "#";
    return to_string((unsigned char)root->ch) + " " + to_string(root->freq) + " " + serialize(root->left) + " " + serialize(root->right);
}

Node* deserialize(istringstream &in) {
    string val;
    if (!(in >> val) || val == "#") return nullptr;
    char ch = stoi(val);
    int freq;
    in >> freq;
    Node* node = new Node(ch, freq, deserialize(in), deserialize(in));
    return node;
}

void generateCodes(const Node* node, const string& prefix, map<char, string>& huffmanCode) {
    if (!node) return;
    if (!node->left && !node->right) {
        huffmanCode[node->ch] = prefix;
    }
    generateCodes(node->left, prefix + "0", huffmanCode);
    generateCodes(node->right, prefix + "1", huffmanCode);
}

string encode(const string& text, const map<char, string>& huffmanCode) {
    string encoded;
    for (char c : text) {
        encoded += huffmanCode.at(c);
    }
    return encoded;
}

string decode(const Node* root, const string& str) {
    string result;
    const Node* node = root;
    for (char bit : str) {
        node = (bit == '0') ? node->left : node->right;
        if (!node) throw runtime_error("Decoding error: Invalid Huffman tree path.");
        if (!node->left && !node->right) {
            result += node->ch;
            node = root;
        }
    }
    return result;
}

string readFile(const string& filename) {
    ifstream file(filename, ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void writeFile(const string& filename, const string& data) {
    ofstream file(filename, ios::binary);
    file << data;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " -z/-zip/-u/-unzip <input_file> <output_file>" << endl;
        return 1;
    }

    string mode = argv[1];
    string inputFile = argv[2];
    string outputFile = argv[3];

    if (mode == "-z" || mode == "-zip") {
        string text = readFile(inputFile);
        map<char, int> freq;
        for (char ch : text) {
            freq[ch]++;
        }

        priority_queue<Node*, vector<Node*>, Compare> pq;
        for (auto& p : freq) {
            pq.push(new Node(p.first, p.second));
        }

        while (pq.size() != 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            pq.push(new Node('\0', left->freq + right->freq, left, right));
        }

        Node* root = pq.top();
        map<char, string> huffmanCode;
        generateCodes(root, "", huffmanCode);

        string encodedText = encode(text, huffmanCode);
        stringstream ss;
        ss << serialize(root) << "\n" << encodedText;

        writeFile(outputFile, ss.str());
        cout << "File encoded successfully." << endl;
    } else if (mode == "-u" || mode == "-unzip") {
        string content = readFile(inputFile);
        istringstream ss(content);
        string serializedTree;
        getline(ss, serializedTree);

        istringstream treeStream(serializedTree);
        Node* root = deserialize(treeStream);

        string encodedText;
        getline(ss, encodedText);

        try {
            string decodedText = decode(root, encodedText);
            writeFile(outputFile, decodedText);
            cout << "File decoded successfully." << endl;
        } catch (const exception& e) {
            cerr << "Decoding failed: " << e.what() << endl;
            return 2;
        }
    } else {
        cerr << "Invalid mode. Use -z/-zip to compress or -u/-unzip to decompress." << endl;
        return 2;
    }

    return 0;
}
