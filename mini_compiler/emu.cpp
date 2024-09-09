#include<iostream>
#include<bits/stdc++.h>
using namespace std;


class print{
	public:
		string first,second,third,four;
		int five;
};
map<int,int> memory;
unordered_map<string,string> labelMap;
unordered_map<string,string> offsetmap;
stack<int> A, B, SP;
bool check(string &s) {
    for (int i = 0; i < s.length(); ++i) {
        if (i == 0 && s[i] == '-') {
            continue; // Skip the negative sign at the beginning
        }
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}
int con(const std::string& str) {
    int result;
    stringstream ss(str);
    ss >> result;
    return result;
}
void replaceLabelsWithValues(vector<print>& passfunc) {
    unordered_map<string, int> labelAddresses;
    // Find addresses of all labels
    for (int i = 0; i < passfunc.size(); i++) {
        if (!passfunc[i].first.empty()) {
            labelAddresses[passfunc[i].first] = i;
        }
    }
    // Replace labels with values
    for (int i = 0; i < passfunc.size(); i++) {
        if(!passfunc[i].third.empty() && labelMap.find(passfunc[i].third) != labelMap.end()) {
            passfunc[i].third = labelMap[passfunc[i].third];
            passfunc[i].five = con(passfunc[i].third);
        }
        else if(passfunc[i].second == "brz" || passfunc[i].second == "brlz" || passfunc[i].second == "br" || passfunc[i].second == "call") {
            if (!passfunc[i].third.empty() && !check(passfunc[i].third)) {
                int target_address = i;
                int label_address = labelAddresses[passfunc[i].third];
                offsetmap[passfunc[i].third]=to_string(label_address-target_address );
                passfunc[i].third = to_string(label_address-target_address );
                passfunc[i].five = label_address-target_address;
            }
        }
        else{
            passfunc[i].five = con(passfunc[i].third);
        }
    }
}
void emulator(vector<print> &passfunc, int stop) {
    int i = 0;
    while(i!=stop){
        if(passfunc[i].second == "ldc") {
          B.push(A.top());
          A.push(passfunc[i].five);
          i++;
        }

        else if(passfunc[i].second == "adc") {
           A.push(A.top()+passfunc[i].five);
           i++;
         }

	   else if (passfunc[i].second == "ldl") {
            B.push(A.top());
            A.push(memory[SP.top()+passfunc[i].five]);
            i++;
         }

        else if(passfunc[i].second == "stl") {
            memory[SP.top()+passfunc[i].five]=A.top();
            A.push(B.top());
            i++;
        }


      else if(passfunc[i].second == "ldnl") {
         A.push(memory[A.top()+passfunc[i].five]);
         i++;
       }
       else if(passfunc[i].second == "stnl") {
           memory[A.top()+passfunc[i].five]=B.top();
           i++;
        }


		else if(passfunc[i].second=="add"){
		    passfunc[i].five=A.top()+B.top();
			A.push(A.top()+B.top());
			i++;
		}
		else if(passfunc[i].second=="sub"){
		    passfunc[i].five=B.top()-A.top();
			A.push(B.top()-A.top());
			cout<<endl<<" B "<<B.top()<<" A "<<A.top()<<" pass "<<passfunc[i].five<<endl;
			i++;
		}
		else if(passfunc[i].second=="shl"){
		    int avalue=A.top();
		    int bvalue=B.top();
		    passfunc[i].five= (bvalue << avalue);
			A.push(bvalue << avalue);
			i++;
		}
		else if(passfunc[i].second=="shr"){
		    int avalue=A.top();
		    int bvalue=B.top();
		    passfunc[i].five= (bvalue >> avalue);
			A.push(bvalue >> avalue);
			i++;
		}
		else if (passfunc[i].second == "adj") {
             SP.push(SP.top()+passfunc[i].five);
             i++;
        }
		else if(passfunc[i].second=="a2sp"){
		    passfunc[i].five=B.top();
		    SP.push(A.top());
		    A.push(B.top());
		    i++;
		}
		else if(passfunc[i].second=="sp2a"){
		    passfunc[i].five=SP.top();
		    A.push(SP.top());
		    B.push(A.top());
		    i++;
		}
		else if(passfunc[i].second=="call"){
		   // cout<<"yo "<<passfunc[i].five<<" fuck"<<endl;
		    B.push(A.top());
		    A.push(i);
		    i=i+passfunc[i].five;
		}
		else if(passfunc[i].second=="return"){
			i=A.top();
			A.push(B.top());
			passfunc[i].five=B.top();
		}
	    else if(passfunc[i].second == "brz") {
             if(A.top()==0){
                 i=i+passfunc[i].five;
             }
             else{
                 i++;
             }
         }
         else if(passfunc[i].second == "brlz") {
             if(A.top() < 0) {
                i=i+passfunc[i].five;
             }
             else{
                 i++;
             }
         }

	      else if(passfunc[i].second == "br") {
              i=i+passfunc[i].five;
          }
          else{
              i++;
          }
         cout<<endl<<" mnemonic "<<passfunc[i].second<<" value "<<passfunc[i].third<<" fake "<<passfunc[i].five<<endl;
         }
}
void printMemoryContents(const map<int, int>& memory) {
    cout << "Memory contents:" << endl;
    cout<<memory.size();
    for (const auto& pair : memory) {
        cout << "Memory address: " << pair.first << ", Value: " << pair.second << endl;
    }
}

int main() {
    int stop;
    print help;
    vector<print> passfunc;
    ifstream infile("test.txt");
    // Input file containing assembly code
    string line;
    int current_address = 0;
    while (getline(infile, line)) {
        stringstream ss(line);
        string token;
        bool label_found = false;

        string label = "";
        string mnemonic = "";
        string value = "";

        while (ss >> token) {
            if (token[0] == ';') // Ignore comments
                break;

            if (!label_found && token[token.size() - 1] == ':') {
                // This token is a label
                label = token.substr(0, token.size() - 1);
                label_found = true;
            } else if (mnemonic.empty()) {
                // This token is the mnemonic
                mnemonic = token;
            } else {
                // This token is the value
                value = token;
            }
        }
        if (!label.empty() && !value.empty() && mnemonic == "data") {
            labelMap[label] = value;
        }
        if (mnemonic == "HALT") {
            passfunc.push_back({label, mnemonic, value});
            stop = current_address; // Exit the loop when HALT is encountered
        }

        // Output the formatted instruction
        if (!mnemonic.empty()) {
            passfunc.push_back({label, mnemonic, value});
        }

        // Increment address only if the line is not a comment
        if (token[0] != ';') {
            ++current_address;
        }
    }

    A.push(0);
    B.push(0);
    SP.push(0);
    replaceLabelsWithValues(passfunc);
    // cout<<"yo";
    emulator(passfunc, stop);
   printMemoryContents(memory);

    return 0;
}