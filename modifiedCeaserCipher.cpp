#include<bits/stdc++.h>
using namespace std;


int checkfirstUnvis(vector<int>&arr){
    int n=arr.size();
    int ans;
    for(int i=1;i<=n;i++){
        if(!arr[i]){
            ans=i;
            arr[i]=1;
            break;
        }
    }
     return ans;
     
}

vector<int> keyGenerator(string key){
    int ckey1=0,ckey2=0;
    vector<int>ascii;
    for(auto i:key){
        ascii.push_back(int(i));
    }
    int n=ascii.size();
    for(int i=0;i<n;i++){
        ckey1=ckey1*10+ascii[i];
        ascii[i]=(ascii[i]%5)+1;
    }
    vector<int>vis(n+1,0);
    //for(auto i:ascii)cout<<i<<" ";
    for(int i=0;i<n;i++){
        int num=ascii[i];
        if(!vis[num]){
            vis[num]=1;
        }
        else{
           int firstunvis=checkfirstUnvis(vis);
           ascii[i]=firstunvis;
        }
    }
    string temp;
    for(auto i:ascii){
        temp+=to_string(i);
    }
    ckey2=stoi(temp);
    vector<int>keys(2);
    keys[0]=ckey1;
    keys[1]=ckey2;
    return keys;
}

int random1,q;
int mvisited[127]={0};
int GetNextRandom(int ckey1){
    random1=q%127;
    q=random1+3*ckey1;
    while(mvisited[random1]){
        random1=(random1+1)%127;
    }
    //cout<<random1<<endl;
    mvisited[random1]=1;
    return random1;
}

map<int,char>substitutionMap;
map<int,char>inversemap;

void Initialize(int &ckey1){
    for(int i=0;i<33;i++){
        substitutionMap[i]=char(i);
    }
    for(int i=127;i<255;i++){
        substitutionMap[i]=char(i);
    }
    // int ckey1=1260356;
    for(int i=33;i<127;i++){
        int rand=GetNextRandom(ckey1);
        substitutionMap[i-1]=char(rand);
    }
    for(auto i:substitutionMap){
        inversemap[i.second]=i.first;
    }
}

void getmatrix(vector<vector<char>>&mat,string &ctext){
    int ind=0;
    int N=mat.size();
    int clen=ctext.size();
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(ind<clen){
                mat[i][j]=ctext[ind];
            }
            else
              mat[i][j]=' ';
            ind++;
        }
    }
}

void print(vector<vector<char>>&mat){
    int N=mat.size();
    for(int i=0;i<N;i++){
        for(char j:mat[i]){
            cout<<j<<" ";
        }cout<<endl;
    }
}

string getstrFromMat(vector<vector<char>>&mat,string key2){
    string ctext2;
    int N=mat.size();
    for(auto i:key2){
        int colind=(i-'0')-1;
        for(int i=0;i<N;i++){
            ctext2+=mat[i][colind];
        }
    }
    return ctext2;
}


void encryption(string plaintext,string key){
    int N=key.size();
    vector<vector<char>>matrix(N,vector<char>(N));
    vector<int>twokeys=keyGenerator(key);
    int ckey1=twokeys[0];
    //cout<<ckey1<<" "<<twokeys[1]<<endl;
    Initialize(ckey1);
    
    string ciphertext1;
    for(auto i:plaintext){
        int ind=int(i);
        ciphertext1+=substitutionMap[ind];
    }
   cout<<"ciphertext1: "<<ciphertext1<<endl;
   // storing ciphertext1 into matrix
    getmatrix(matrix,ciphertext1);
    // printitng matrix
      //print(matrix);
    string ckey2=to_string(twokeys[1]);
    //cout<<ckey2<<endl;
    // double column operation
    // first time
    // getstrFromMat give string after doing column operation
    string ctext2=getstrFromMat(matrix,ckey2);
    
    // second time
    // getmatrix arrange the cipertext into matrix form
     getmatrix(matrix,ctext2);
     
    // get final cipher after applying 2nd column operation 
    string cipher=getstrFromMat(matrix,ckey2);
    
    cout<<"cipher text::"<<cipher<<endl;
}


void getdecrptMat(vector<vector<char>>&mat,string &ctext){
    int N=mat.size();
    int clen=ctext.size();
    int ind=0;
    for(int j=0;j<N;j++){
        for(int i=0;i<N;i++){
            if(ind<clen){
                mat[i][j]=ctext[ind];
            }
            else
              mat[i][j]=' ';
            ind++;
        }
    }
}

string getptextFromMat(vector<vector<char>>&mat,string &ckey2){
    string ptext;
    int N=mat.size();

    for(int k=0;k<N;k++){
        int i=0,j=ckey2.size()-1;
        bool alt=true;
        while(i<=j){
            int colind;
            if(alt){
                colind=(ckey2[i]-'0')-1;
                i++;
                alt=false;
            }
            else{
                colind=(ckey2[j]-'0')-1;
                j--;
                alt=true;
            }
            ptext+=mat[k][colind];
        }
    }
    return ptext;
}

void decryption(string ciphertext,string key){
    int N=key.size();
    vector<vector<char>>matrix(N,vector<char>(N));
    vector<int>twokeys=keyGenerator(key);
    int ckey1=twokeys[0];
    string ckey2=to_string(twokeys[1]);
    Initialize(ckey1);
    // first reverse column operation
    getdecrptMat(matrix,ciphertext);
    
    string ctext1=getptextFromMat(matrix,ckey2);
    cout<<"cipher text1:"<<ctext1<<endl;
    // 2nd time revesre column
    getdecrptMat(matrix,ctext1);
    string cptext0=getptextFromMat(matrix,ckey2);
    //
    string plaintext;
    for(auto i:cptext0){
        plaintext+=char(inversemap[i]);
    }
   cout<<" plain text is::"<<plaintext<<endl;
}


int main(){
    for(int i=0;i<32;i++)mvisited[i]=1;
    // encrption part
       //string key="qwert";
       //string plaintext="enemy attacks tonight";
            // cout<<"enter plain text to encrpyt\n";
            // string plaintxt,key;
            // getline(cin,plaintxt);
            // cout<<"enter key \n";
            // cin>>key;
            // encryption(plaintxt,key);


    // decrption part
      string ciphertxt="LM^ve   o oBB oSk^FF oOT]";
      string key="qwert";
        // cout<<"enter cipher text to decrpyt\n";
        // string ciphertxt,key;
        // getline(cin,ciphertxt);
        // cout<<"enter key \n";
        // cin>>key;
        decryption(ciphertxt,key);
     
    return 0;
}