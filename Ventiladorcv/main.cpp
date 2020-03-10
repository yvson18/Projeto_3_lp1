/*

                        O QUE TA COMENTADO DO ARDUINO OU DE COISAS QUE TU ACHA QUE EH DO
                        ARDUINO DEIXA ELAS COMENTADAS MSM MORO JO?

*/
#include <iostream>
#include "SerialPort.h"
#include <string>
#include <string.h>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

char output[MAX_DATA_LENGTH]; // recebe saidas do arduino
char port[] = "\\\\.\\COM3";
char incoming[MAX_DATA_LENGTH];


int main(){

    SerialPort arduino(port);

    double scale = 2.0;
    CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

    if(arduino.isConnected()){
        cout << "Conexao estabelecida"<<endl;
    }else{
        cout << "Falha na Conexao"<<endl;
    }

    VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Erro ao inicializar a camera!" << endl;
		return -1;
	}

	const char* windowName = "Webcam Feed";
    namedWindow(windowName, WINDOW_AUTOSIZE);


    while(arduino.isConnected()){ //  como n tera nenhum arduino contigo deixa isso while 1 para funcionar para os teus testes

        Mat frame;
		bool bSuccess = cap.read(frame);

        Mat grayscale;
        cvtColor(frame, grayscale, COLOR_BGR2GRAY);
        resize(grayscale, grayscale, Size(grayscale.size().width/scale, grayscale.size().height/scale));

        vector<Rect> faces;
        faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30,30));

         for(Rect area : faces){

            Scalar drawColor = Scalar(255,0,0);
            rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)), Point(cvRound((area.x + area.width - 1)*scale), cvRound((area.y + area.height - 1)*scale)), drawColor);


            /*
            Isaac, quando tu for fazer, tu so deve designar o valor convertido do angulo
            para essas strings ae (coordx, coordy).
            Ademais, observações complementares são:  tenta deixar tudo em uma faixa  de valores entre 0 e 180 e
            alem disso , cuida para que se tenha uma faixa de tolerancia do tipo que se o usuario
            se mover so um pouco n varie o input dos angulos que tu vai atribuir as coordx e coordy
            pq se n vai ficar muito sensivel
            */

            string coordenadaX = to_string(area.x);
            string coordenadaY = to_string(area.y);
            string command = coordenadaY + " " + coordenadaX;

            cout << command << endl;

            char *charArray = new char[command.size()+1];

            copy(command.begin(),command.end(),charArray);
            charArray[command.size()] = '\n';

            //arduino.writeSerialPort(charArray,MAX_DATA_LENGTH);
            //arduino.readSerialPort(output,MAX_DATA_LENGTH);

             delete charArray;


        }

        if (!bSuccess) {
			cout << "Error reading frame from camera feed" << endl;
			break;
		}

		imshow(windowName, frame);
            switch(waitKey(10)) {
            case 1:
                return 0;
            }
        }


        //string command;
        //getline(std::cin,command);
        //cout << command << endl;
        //char *charArray = new char[command.size()+1];

        //copy(command.begin(),command.end(),charArray);
        //charArray[command.size()] = '\n';

        //arduino.writeSerialPort(charArray,MAX_DATA_LENGTH);
        //arduino.readSerialPort(output,MAX_DATA_LENGTH);

        //cout << output;

        //delete charArray;






    return 0;
}
