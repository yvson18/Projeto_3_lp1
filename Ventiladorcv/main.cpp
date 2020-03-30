/*

                        O QUE TA COMENTADO DO ARDUINO OU DE COISAS QUE TU ACHA QUE EH DO
                        ARDUINO DEIXA ELAS COMENTADAS MSM MORO JO?

*/
#include <iostream>
#include <iomanip>
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
    Rect retangulo;

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
    double angulo_x, angulo_y, constante_magica_x, constante_magica_y;
    double unidade_x, unidade_y, dummy_x, dummy_y;
    double s;
    retangulo = (getWindowImageRect("Webcam Feed"));
    unidade_x = retangulo.width / 90.0;
    unidade_y = retangulo.height / 22.5;
    string coordenadaX = "90,0", coordenadaY = "0,0";
    Point centro_janela(retangulo.x + (retangulo.width / 2), retangulo.y + (retangulo.height / 2));
    constante_magica_x = retangulo.x;
    constante_magica_y = retangulo.y;

    cout << centro_janela.x << "\n" << centro_janela.y << endl;
    cout << constante_magica_x << endl;
    cout << constante_magica_y << endl;
    cout << unidade_x << "," << unidade_y << endl;
    cout<< "[" << retangulo.tl().x << "," << retangulo.tl().y << "]" <<  "[" << retangulo.br().x << "," << retangulo.br().y << "]" << endl;

    while(1){ //  como n tera nenhum arduino contigo deixa isso while 1 para funcionar para os teus testes

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

            Point centro(scale * (area.x + (area.width / 2)) + constante_magica_x, scale * (area.y + (area.height / 2)) + constante_magica_y);
            cout << "[" << centro.x << "," << centro.y << "]" << endl;



            angulo_x = 90 - (centro.x - centro_janela.x) / unidade_x;
            s = 5.625 -(centro.y - centro_janela.y)/unidade_y;
            angulo_y = (s >= 0)? s : 0;



                dummy_x = (int)angulo_x;
                dummy_y = (int)angulo_y;
                coordenadaX = to_string(dummy_x);
                coordenadaY = to_string(dummy_y);

            string command = coordenadaX + " " + coordenadaY;

            cout << command << endl;

            char *charArray = new char[command.size()+1];

            copy(command.begin(),command.end(),charArray);
            charArray[command.size()] = '\n';

            arduino.writeSerialPort(charArray,MAX_DATA_LENGTH);
            arduino.readSerialPort(output,MAX_DATA_LENGTH);

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

    return 0;
}
