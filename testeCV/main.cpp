#include <iostream>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

int main() {

    double scale = 2.0;
    CascadeClassifier faceCascade;
    faceCascade.load("C:\\opencv\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_alt.xml");

	VideoCapture cap(0);
	if (!cap.isOpened()) {
		cout << "Erro ao inicializar a camera!" << endl;
		return -1;
	}

	const char* windowName = "Webcam Feed";
    namedWindow(windowName, WINDOW_AUTOSIZE);

	while (1) {

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
            cout << "X = " << area.x << endl;
            cout << "Y = " << area.y << endl;
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
