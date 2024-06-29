#include<bits/stdc++.h>
using namespace std;

multimap<string, string> labelmap;

struct node {
    string first;
    string second;
    string third;
};


string hexadecimal(int &num){
   string hex;
    int a=abs(num);
    if (a==0){
        return "000000";
    } 

    while (a > 0) {
        int rem = a % 16;
        char hexChar;
        
        if (0 <= rem && rem <= 9)
            hexChar = '0' + rem;
        else if (rem == 10)
            hexChar = 'a';
        else if (rem == 11)
            hexChar = 'b';
        else if (rem == 12)
            hexChar = 'c';
        else if (rem == 13)
            hexChar = 'd';
        else if (rem == 14)
            hexChar = 'e';
        else if (rem == 15)
            hexChar = 'f';

        hex.push_back(hexChar);
        a = a / 16;
    }

    int x = 6 - hex.length();
    while (x > 0) {
        char rem = '0';
        hex.push_back(rem);
        x--;
    }
    reverse(hex.begin(), hex.end());
    return hex;
}

int stringToInt(const std::string& str) {
    int result = 0;
    for (char c : str) {
        result = result * 10 + (c - '0');
    }
    return result;
}


string twocomplement(const string  &num_str) {
   int a=stringToInt(num_str); 
    if(a>=0){
        return hexadecimal(a); 
    }else{
        int k=pow(2,24)+a;
        return hexadecimal(k);
    }
}



bool checksfordigit(string &s) {
    for (int i = 0; i < s.length(); i++) {
        if (i == 0 && s[i] == '-') continue;
        if (!isdigit(s[i])) return false;
    }
    return true;
}



void replaceVariables(vector<node> &inst) {
    unordered_map<string, int> offsetmap;

    // Replacing labels with values
    for (int i = 0; i < inst.size(); i++) {

        auto labelIt = labelmap.find(inst[i].third);
        if (!inst[i].third.empty() && labelIt != labelmap.end()) {
            inst[i].third = labelIt->second;
        }

        // Assuming you want to store offsets for certain instructions
        if (!inst[i].first.empty()) {
            offsetmap[inst[i].first] = i;
        }
    }

    for (int i = 0; i < inst.size(); i++) {
        if (inst[i].second == "call" || inst[i].second == "brz" || inst[i].second == "brlz" || inst[i].second == "br") {
            auto it = offsetmap.find(inst[i].third);
            if (it != offsetmap.end()) {
                inst[i].third = to_string( it->second - i );
            }
        }
    }

    cout << "Replacing variables..." << endl;
}

void pass2(vector<node> inst) {
    vector<string> str;
    vector<string> obj;
    int i = 0;
    string st;
    string s;
    while (i < inst.size()) {
        if (inst[i].second == "ldc") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "ldc " + twocomplement(inst[i].third) + "00";
            s=twocomplement(inst[i].third)+"00";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "adc") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "adc " + twocomplement(inst[i].third) + "01";
            s=twocomplement(inst[i].third)+"01";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "ldl") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "ldl " + twocomplement(inst[i].third) + "02";
             s=twocomplement(inst[i].third)+"02";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "stl") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "stl " + twocomplement(inst[i].third) + "03";
             s=twocomplement(inst[i].third)+"03";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "ldn") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "ldn " + twocomplement(inst[i].third) + "04";
             s=twocomplement(inst[i].third)+"04";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "stnl") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "stnl " + twocomplement(inst[i].third) + "05";
             s=twocomplement(inst[i].third)+"05";
            obj.push_back(s);
            str.push_back(st);
        } else if (inst[i].second == "add") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "add " + twocomplement(inst[i].third) + "06";
             s=twocomplement(inst[i].third)+"06";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "sub") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "sub " + twocomplement(inst[i].third) + "07";
             s=twocomplement(inst[i].third)+"07";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "shl") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "shl " + "00000008";
             s=+"00000008";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "shr") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "shr " + "00000009";
            s="00000009";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "adj") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "adj " + twocomplement(inst[i].third) + "0a";
            s=twocomplement(inst[i].third)+"0a";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "a2sp") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "a2sp " + twocomplement(inst[i].third) + "0b";
            s=twocomplement(inst[i].third)+"0b";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "sp2a") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "sp2a " + twocomplement(inst[i].third) + "0c";
            s=twocomplement(inst[i].third)+"0c";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "call") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "call " + twocomplement(inst[i].third) + "0d";
            s=twocomplement(inst[i].third)+"0d";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "return") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "return " + "0000000e";
            s="0000000e";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "brz") {
            st.clear();
            s.clear();
             st = hexadecimal(i) + " " + "brz " + twocomplement(inst[i].third) + "0f";
             s=twocomplement(inst[i].third)+"0f";
            obj.push_back(s); 
            str.push_back(st);
            i++;
        } else if (inst[i].second == "brlz") {
             st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "brlz " + twocomplement(inst[i].third) + "10";
             s=twocomplement(inst[i].third)+"10";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "br") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "br " + twocomplement(inst[i].third) + "11";
             s=twocomplement(inst[i].third)+"11";
            obj.push_back(s);
            str.push_back(st);
            i++;
        } else if (inst[i].second == "HALT") {
            st.clear();
            s.clear();
            st = hexadecimal(i) + " " + "HALT " + "00000012";
            s="00000012";
            obj.push_back(s);
            str.push_back(st);
            i++;
        }
    }

    ofstream pc("pass_2.txt");
    if (pc.is_open()) {
        for (const string &st : str) {
            pc << st << endl;
        }
        pc.close();
        cout << "pass_2.txt created successfully" << endl;
    } else {
        cout << "Failed to open pass_2.txt" << endl;
    }
    
    ofstream pc_file("obj.txt");
    if (pc_file.is_open()) {
        for (const string &st : obj) {
            pc_file << st << endl;
        }
        pc_file.close();
        cout << "obj.txt created successfully" << endl;
    } else {
        cout << "Failed to open obj.txt" << endl;
    }


}

bool allCharactersAreAlphabetic(const string& str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

void errors(vector<node> &inst, int stop) {
    int x = 0;
    string er;
    vector<string> error;
    for (auto it = labelmap.begin(); it != labelmap.end(); it++) {
        if (it != labelmap.end() && next(it) != labelmap.end() && it->first == next(it)->first) {
            string e = it->first + " duplicate label";
            error.push_back(e);
        }
    }
    for (int i = 0; i < inst.size(); i++) {
        if (inst[i].second == "ldc" || inst[i].second == "data" || inst[i].second == "adc" || inst[i].second == "ldl" || inst[i].second == "stl" || inst[i].second == "ldnl" || inst[i].second == "stnl" ||
            inst[i].second == "adj" || inst[i].second == "call" || inst[i].second == "brz" || inst[i].second == "brlz" || inst[i].second == "br") {

            if(inst[i].third.empty()){
               er.clear();
                er = hexadecimal(i) + " missing operand";
                error.push_back(er);
                x++;  
            }else{
                if(allCharactersAreAlphabetic(inst[i].third)){
                  er.clear();
                  er=hexadecimal(i) + " no such label";
                  error.push_back(er);
                 x++;
                }else  if (!checksfordigit(inst[i].third)){
                 er.clear();
                 er = hexadecimal(i) + " not a number";
                 error.push_back(er);
                 x++;
                }
            }
        } else if (inst[i].second == "add" || inst[i].second == "a2sp" || inst[i].second == "sp2a" || inst[i].second == "sub" || inst[i].second == "shl" || inst[i].second == "shr" || inst[i].second == "return" || inst[i].second == "HALT") {
            if (!inst[i].third.empty()) {
                er.clear();
                er = hexadecimal(i) + " unexpected operand";
                error.push_back(er);
                x++;
            }
        } else {
            if(!inst[i].second.empty()){
              x++;
              er = hexadecimal(i) + " bogus mnemonic";
              error.push_back(er);
            }else{
                if(inst[i].third.empty()){
                   x++;
                  er=hexadecimal(i)+" bogus label name";
                  error.push_back(er);
                }
            }
        }
       
        
      
    }
    if (x > 0) {
        ofstream pblm("error.txt");
        if (pblm.is_open()) {
            for (const string &st : error) {
                pblm << st << endl;
            }
            pblm.close();
        } else {
            cout << "Failed to open error.txt" << endl;
        }
        cout << "Number of errors: " << x << endl;
    } else {
        cout << "No errors" << endl;
        pass2(inst);
    }
}

void pass1(vector<node> &inst) {
    vector<string> str;
    int stop = 0;
    for (int i = 0; i < inst.size(); i++) {
        string s;

        if (!inst[i].first.empty()) {
            s = inst[i].first;
            s += " ";
            s += hexadecimal(i);
            str.push_back(s);
        }

        if (inst[i].second == "HALT") {
            stop = i;
        }
    }

    ofstream pc("pass_1.txt");
    if (pc.is_open()) {
        for (const string &st : str) {
            pc << st << endl;
        }
        pc.close();
        cout << "pass_1.txt created successfully." << endl;
    } else {
        cerr << "Failed to open pass_1.txt" << endl;
    }

    errors(inst, stop);
}

int main() {
    node out;
    vector<node> instruction;
    ifstream infile("test.txt"); // Input file containing assembly code
    string line;

    int present_add = 0;
    while (getline(infile, line)) {
        stringstream ss(line);
        string symbol;
        bool label_present = false;
        string mnemonic = "";
        string label = "";
        string value = "";

        while (ss >> symbol) {
            if (symbol[0] == ';') // Ignore comments
                break;

            if (!label_present && symbol[symbol.size() - 1] == ':') {
                // This symbol is a label
                label = symbol.substr(0, symbol.size() - 1);
                label_present = true;
            } else if (mnemonic.empty()) {
                // This symbol is the mnemonic
                mnemonic = symbol;
            } else {
                // This symbol is the value
                value = symbol;
            }
        }
        if (!label.empty() && !value.empty() && mnemonic == "data") {
            labelmap.insert({label, value});
        }

        // Output the formatted instruction
        if (!mnemonic.empty()) {
            out.first = label;
            out.second = mnemonic;
            out.third = value;
            instruction.push_back(out);
        }

        // Increment address only if the line is not a comment
        if (symbol[0] != ';') {
            present_add++;
        }
    }
    replaceVariables(instruction);
    pass1(instruction);
    

    return 0;
}
