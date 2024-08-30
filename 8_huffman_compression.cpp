#include <iostream>
    using std::cout;
    using std::endl;
#include <fstream>
    using std::ifstream;
    using std::ofstream;
#include <string>
    using std::string;
#include <unordered_map>
    using std::unordered_map;
#include <queue>
    using std::priority_queue;

class Node {
public:
    int freq;
    char ch;
    Node *left;
    Node *right;
    Node(char ch, int freq) {
        this->freq = freq;
        this->ch = ch;
        left = nullptr;
        right = nullptr;
    }

    Node(Node *n1, Node *n2) {
        this->freq = n1->freq + n2->freq;
        bool n1_left = n1->ch < n2->ch;
        this->ch = n1_left ? n1->ch : n2->ch;
        this->left = n1_left ? n1 : n2;
        this->right = n1_left ? n2 : n1;
    }
};

Node *buildHuffmanTree(unordered_map<char, int> &char_freq) {
    auto compare = [](Node *l, Node *r) {
        if (l->freq == r->freq) {
            return l->ch > r->ch;
        }
        return l->freq > r->freq;
    };
    priority_queue<Node *, std::vector<Node *>, decltype(compare)> pq(compare);

    for (auto &pair : char_freq) {
        pq.emplace(new Node(pair.first, pair.second));
    }

    while (pq.size() > 1)
    {
        Node *n1, *n2;
        n1 = pq.top();
        pq.pop();
        n2 = pq.top();
        pq.pop();
        Node *parent = new Node(n1, n2);
        pq.emplace(parent);

    }
    return pq.top();
}

void generateHuffmanCode(Node *root, string str, unordered_map<char, string> &huffman_code) {
    if (!(root->left || root->right))
    {
        huffman_code[root->ch] = str;
        cout << root->ch << ": " << str << endl;
        return;
    }
    generateHuffmanCode(root->left, str + "0", huffman_code);
    generateHuffmanCode(root->right, str + "1", huffman_code);

}

int main(int argc, char const *argv[])
{
    // if (argc != 4)
    if (false)
    {
        cout << "usage: ./8_huffman_compression <--encoding|--decoding> <input_file>" << endl;
    } else if (string(argv[1]) == "--encoding") {
        string in_name(argv[2]);
        ifstream in_file(in_name);
        string out_name = in_name.substr(0, in_name.find(".")) + ".compressed";
        unordered_map<char, int> char_freq;
        char ch;
        while (in_file.get(ch)) {
            char_freq[ch]++;
        }

        // for (auto &&i : char_freq)
        // {
        //     cout << i.first << " = " << i.second << endl;
        // }

        Node *root = buildHuffmanTree(char_freq);
        unordered_map<char, string> huffman_code;
        generateHuffmanCode(root, "", huffman_code);

        ofstream out_file(out_name, std::ios::binary);

        // write header
        size_t char_freq_size = char_freq.size();
        out_file.write(reinterpret_cast<const char*>(&char_freq_size), sizeof(char_freq_size));
        for (auto &&pair : char_freq)
        {
            out_file.write(&pair.first, sizeof(char));
            out_file.write(reinterpret_cast<const char*>(&pair.second), sizeof(int));
        }

        // write data
        in_file.clear();
        in_file.seekg(0);
        string buffer;
        while (in_file.get(ch))
        {
            buffer += huffman_code[ch];
        }
        while (buffer.size() >= 8)
        {
            char byte = 0;
            for (size_t i = 0; i < 8; i++)
            {
                byte = (byte << 1) | (buffer[i] - '0');
            }
            out_file.put(byte);
            buffer = buffer.substr(8);
        }

        // write last byte
        if (!buffer.empty())
        {
            char byte = 0;
            for (size_t i = 0; i < buffer.size(); i++)
            {
                byte = (byte << 1) | (buffer[i] - '0');
            }

            byte <<= (8 - buffer.size());
            out_file.put(byte);
        }


        in_file.close();
        out_file.close();
    } else if (string(argv[1]) == "--decoding") {
        string in_name(argv[2]);
        ifstream in_file(in_name, std::ios::binary);
        string out_name = in_name.substr(0, in_name.find(".")) + ".decoded";
        ofstream out_file(out_name);

        size_t char_freq_size;
        in_file.read(reinterpret_cast<char*>(&char_freq_size), sizeof(char_freq_size));
        unordered_map<char, int> char_freq;
        for (size_t i = 0; i < char_freq_size; i++)
        {
            char ch;
            int freq;
            in_file.read(&ch, sizeof(char));
            in_file.read(reinterpret_cast<char*>(&freq), sizeof(int));
            char_freq[ch] = freq;
        }

        Node *root = buildHuffmanTree(char_freq);
        Node *current = root;
        uint total_chars = 0;
        for (auto &&pair : char_freq)
        {
            total_chars += pair.second;
        }
        uint decode_chars = 0;
        char byte;
        while (in_file.get(byte) && decode_chars < total_chars) {
            for (int i = 7; i >= 0 && decode_chars < total_chars; i--)
            {
                bool bit = (byte >> i) & 1;
                if (bit)
                {
                    current = current->right;
                } else
                {
                    current = current->left;
                }

                if (current->left == nullptr && current->right == nullptr)
                {
                    out_file.put(current->ch);
                    current = root;
                    decode_chars++;
                }
            }
        }
        in_file.close();
        out_file.close();
        system("chmod 0111 " + out_name);
    }

    return 0;
}
