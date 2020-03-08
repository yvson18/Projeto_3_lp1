#include <iostream>
#include "SerialPort.h"
#include <string>
#include <string.h>

using namespace std;

char output[MAX_DATA_LENGTH]; // recebe saidas do arduino
char port[] = "\\\\.\\COM3";
char incoming[MAX_DATA_LENGTH];


int main(){

    SerialPort arduino(port);

    if(arduino.isConnected()){
        cout << "Conexao estabelecida"<<endl;
    }else{
        cout << "Falha na Conexao"<<endl;
    }

    while(arduino.isConnected()){

        string command;
        getline(std::cin,command);
        cout << command << endl;
        char *charArray = new char[command.size()+1];

        copy(command.begin(),command.end(),charArray);
        charArray[command.size()] = '\n';

        arduino.writeSerialPort(charArray,MAX_DATA_LENGTH);
        arduino.readSerialPort(output,MAX_DATA_LENGTH);

        cout << output;

        delete charArray;
    }



    return 0;
}
