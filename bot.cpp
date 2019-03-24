#include "bot.h"

using namespace std;

bot::bot(DWORD pid){
    phandle = OpenProcess(PROCESS_VM_READ,0,pid);
    if(!phandle){
        cout << "handle error";
    }
}
bot::~bot(){
    CloseHandle(phandle);
}

/*byte* readMemory(HANDLE phandle, DWORD address, int length) {
    byte *buffer = new byte[length];
    SIZE_T bytesRead;
    ReadProcessMemory(phandle, (void *)address, buffer, length, &bytesRead);
    return buffer;
}*/


//DWORD a1x = 0x0CADA490;
//DWORD a1y = 0x0D012510;
DWORD64 chessA1 = 0x21DCD97106C;

int offset = 4;

DWORD64 bot::findA1(){
    DWORD64 start = 0x0;
    int* mem[32];
    bool found = false;
    ReadProcessMemory(phandle,(void*)start,&mem,sizeof(mem),0);
    for(int i=0;i<32;i++){
        cout << mem[i] << endl;
    }
    return start;
}

void bot::updateArray(){
    DWORD64 a1 = findA1();
    cout << a1 << endl;
   /* int temp = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            int index = i*8+j;
            ReadProcessMemory(phandle,(void*)chessA1+((index+2*i)*offset),&arr[index],sizeof(arr[index]),0);
        }
    }*/
}

string bot::getFEN(){
    string fenPiece = getFENpiece();
    int fullmove = getFullMove();
    char active = 'w';
    char castling = '-';
    char passant = '-';
    char halfmove = '0';
    string fen = fenPiece+" "+active+" "+castling+" "+passant+" "+halfmove+" "+std::to_string(fullmove);
    return fen;
}

int bot::getFullMove(){
    int fullMove = 0;
    DWORD adr = 0x0CB125F4;
    while(fullMove == 0 || fullMove == 88){
        ReadProcessMemory(phandle,(void*)adr,&fullMove,sizeof(fullMove),0);
    }
    return fullMove;
}

char getPieceLetter(int piece){
    switch(piece) {
        case 1: return 'P';
        case 2: return 'N';
        case 3: return 'B';
        case 4: return 'R';
        case 5: return 'Q';
        case 6: return 'K';

        case 9: return 'p';
        case 10: return 'n';
        case 11: return 'b';
        case 12: return 'r';
        case 13: return 'q';
        case 14: return 'k';

        default: return NULL;
   }
}

string bot::getFENRank(int row){
    string output = "";
    int nullCount = 0;
    for(int i=0;i<8;i++){
        int index = (row-1)*8+i;
        char pieceLetter = getPieceLetter(arr[index]);
        if(pieceLetter){
            if(nullCount>0){
                output += std::to_string(nullCount);
                nullCount=0;
            }
            output += pieceLetter;
        } else {
            nullCount++;
        }
    }
    if(nullCount>0){
        output += std::to_string(nullCount);
    }
    return output;
}

//FEN begynner oppe til venstre
string bot::getFENpiece(){
    string output = "";
    for(int row=8;row>=1;row--){
        if(row!=8){
            output += "/";
        }
        output += getFENRank(row);
    }
    return output;
}
void bot::printArray(){
    for(int i=7;i>=0;i--){
        for(int j=1;j<9;j++){
            int index = (i*8)+j;
            cout << arr[index-1] << " ";
        }
        cout << endl;
    }
}