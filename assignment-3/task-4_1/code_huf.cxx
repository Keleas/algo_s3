#include <huffman.h>

class MyPriority
{
public:
    bool operator()(Node*& node1, Node*& node2) {
        if(node1->key > node2->key) return true;
        return false;
    }
};

std::vector<uint8_t> code;
std::map<char,std::vector<uint8_t> > table;

void BuildTable(Node *root)
{
    if(root->left() != nullptr) {
        code.push_back('0');
        BuildTable(root->left());
    }
    if(root->right() != nullptr) {
        code.push_back('1');
        BuildTable(root->right());
    }
    if(root->right() == nullptr && root->left() == nullptr) table[root->data] = code;

    code.pop_back();
}

void encode(const std::string &original)
{
    std::ifstream ifs(original);
    std::map<char,int> arr;

    while(!ifs.eof) {
        char c = ifs.get();

    }

    for(size_t i = 0; i < text.size(); ++i) {
        ++arr[(unsigned char)text[i]];
    }

    std::map<char, int>::iterator cur;

    std::priority_queue<Node*, std::vector<Node*>, MyPriority > que;
    for(cur = arr.begin(); cur != arr.end(); ++cur) {
        Node* bin_node = new Node( (*cur).first, (*cur).second);
        que.push(bin_node);
    }

    while(que.size() > 1) {
        Node* cur1 = que.top();
        que.pop();
        Node* cur2 = que.top();
        que.pop();
        Node* new_cur = new Node(cur1, cur2, cur1->key+cur2->key);
        que.push(new_cur);
    }

    Node* head = que.top();
    que.pop();

    BuildTable(head);

    std::string new_s;
    for(size_t i = 0; i < text.size(); ++i) {
        std::vector<uint8_t> x = table[text[i]];
        for(size_t j = 0; j < x.size(); ++j) {
            new_s.push_back(x[j]);
        }
    }
    return new_s;

}
