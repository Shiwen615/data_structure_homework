#include<iostream>
#include<bitset>

class Set
{
private:
    std::bitset<256> bitdata;
public:
    Set(char *const inputs){
        for (int i = 0;inputs[i] != '\0'; i++)
        {
            // std::cout << inputs[i] << " ";
            bitdata[int(inputs[i])] = true;
        }
    }
    Set(std::bitset<256> bitdata):bitdata(bitdata){};

    friend std::ostream &operator<<(std::ostream &output, const Set &set);
    friend bool in(const char &c, const Set &set);

    Set operator+(Set set2){
        return Set(bitdata | set2.bitdata);
    }

    Set operator*(Set set2){
        return Set(bitdata & set2.bitdata);
    }

    Set operator-(Set set2){
        return Set(bitdata & set2.bitdata.flip());
    }

    bool operator>=(Set set2){
        return (*this * set2).bitdata == set2.bitdata;
    }
};

bool in(const char &c, Set &set){
    std::bitset<256> cbit;
    cbit[int(c)] = true;
    return set >= Set(cbit);
}
std::ostream &operator<<(std::ostream &output, const Set &set){
    for (int i = 0; i < 256; i++)
    {
        if(set.bitdata[i]){
            output << char(i);
        }
    }
    output << std::endl;
    return output;
}

int main(int argc, char const *argv[])
{
    std::cout << Set('c') << std::endl;
    char s1[] = "abcdef";
    // char s2[] = "chfeechi";
    char s2[] = "cef";
    Set set1(s1);
    Set set2(s2);
    std::cout << set1 + set2;
    std::cout << set1 * set2;
    std::cout << set1 - set2;
    std::cout << (set1 >= set2) << std::endl;
    std::cout << in('c', set1) << std::endl;
    return 0;
}











