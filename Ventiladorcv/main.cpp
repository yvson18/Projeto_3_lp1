/*
    Programmers: Yvson Nunes
                 Isaac Nobrega:
                 Miguel Elias

    30/03/2020

*/

#include <iostream>
#include <iomanip>
#include "SerialPort.h"
#include <string>
#include <string.h>
#include <ctime>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2\core\types.hpp>
#include <vector>

using namespace std;
using namespace cv;

char output[MAX_DATA_LENGTH]; // recebe saidas do arduino
char port[] = "\\\\.\\COM3";
char incoming[MAX_DATA_LENGTH];

bool envio(int flag, int flagAnterior, time_t timer, time_t *tempo)
{
    time(&timer);
    *tempo = (flag != flagAnterior)? time(&timer) : *tempo;
    if(difftime(timer, *tempo) >= 1.5)
    {
        time(tempo);
        return true;
    }else{
        return false;
    }
}

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
    int flag = 3, flagAnterior = 0;
    time_t timer, tempo;
    bool enable = false;
    double constante_magica_x, constante_magica_y;
    double unidade_x;
    retangulo = (getWindowImageRect("Webcam Feed"));
    unidade_x = retangulo.width / 9.0;
    constante_magica_x = retangulo.x;
    constante_magica_y = retangulo.y;
    char charArray_1[8] = {'1','3','5',',','0','0','\n'};
    char charArray_2[8] = {'1','2','3',',','7','5','\n'};
    char charArray_3[8] = {'1','1','2',',','5','0','\n'};
    char charArray_4[8] = {'1','0','1',',','2','5','\n'};
    char charArray_5[7] = {'9','0',',','0','0','\n'};
    char charArray_6[7] = {'7','8',',','7','5','\n'};
    char charArray_7[7] = {'6','7',',','5','0','\n'};
    char charArray_8[7] = {'5','6',',','2','5','\n'};
    char charArray_9[7] = {'4','5',',','0','0','\n'};

     while(arduino.isConnected()){

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

            flagAnterior = flag;

            flag = (constante_magica_x <= centro.x && centro.x < (constante_magica_x + unidade_x))? 1 :
                        ((constante_magica_x + unidade_x) <= centro.x && centro.x < (constante_magica_x + (2 * unidade_x)))? 2 :
                            ((constante_magica_x + (2 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (3 * unidade_x)))? 3 :
                                ((constante_magica_x + (3 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (4 * unidade_x)))? 4 :
                                    ((constante_magica_x + (4 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (5 * unidade_x)))? 5 :
                                       ((constante_magica_x + (5 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (6 * unidade_x)))? 6 :
                                           ((constante_magica_x + (6 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (7 * unidade_x)))? 7 :
                                               ((constante_magica_x + (6 * unidade_x)) <= centro.x && centro.x < (constante_magica_x + (8 * unidade_x)))? 8 : 9;

            enable = envio(flag, flagAnterior, timer, &tempo);
            if(enable)
            {
                switch(flag)
                {
                    case 1:
                        arduino.writeSerialPort(charArray_1,MAX_DATA_LENGTH);
                        cout << charArray_1 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 2:
                        arduino.writeSerialPort(charArray_2,MAX_DATA_LENGTH);
                        cout << charArray_2 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 3:
                        arduino.writeSerialPort(charArray_3,MAX_DATA_LENGTH);
                        cout << charArray_3 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 4:
                        arduino.writeSerialPort(charArray_4,MAX_DATA_LENGTH);
                        cout << charArray_4 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 5:
                        arduino.writeSerialPort(charArray_5,MAX_DATA_LENGTH);
                        cout << charArray_5 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 6:
                        arduino.writeSerialPort(charArray_6,MAX_DATA_LENGTH);
                        cout << charArray_6 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 7:
                        arduino.writeSerialPort(charArray_7,MAX_DATA_LENGTH);
                        cout << charArray_7 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 8:
                        arduino.writeSerialPort(charArray_8,MAX_DATA_LENGTH);
                        cout << charArray_8 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    case 9:
                        arduino.writeSerialPort(charArray_9,MAX_DATA_LENGTH);
                        cout << charArray_9 << endl;
                        arduino.readSerialPort(output,MAX_DATA_LENGTH);
                        break;
                    default:
                        cout << "Ocorreu umm erro inesperado, por favor, reinicie o  programa." << endl;
                        break;
                }
            }
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
