
#include <iostream>
#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
namespace fs = std::filesystem;

std::string uploaded_folder_path = "./raw_data/";
std::string processed_folder_path = "./processed_data/";

int main()
{

	std::cout << "Dataset generator : " << std::endl;

	std::cout << "CMFD CONVERSION" << std::endl;

	// CMFD LOOP


	int cmfdFileCount = distance(fs::directory_iterator(uploaded_folder_path + "/CMFD/"), fs::directory_iterator());
	int cmfdLoopCount = 1;
	int cmfdSeparationPoint = cmfdFileCount / 2;

	for (const auto & entry : fs::directory_iterator(uploaded_folder_path + "/CMFD/")) {

		cout << "Converting " << entry.path().filename() << " file" << endl;

		string inputImagePath = samples::findFile(entry.path().string());
		Mat inputImage = imread(inputImagePath, IMREAD_COLOR);

		Mat outputImage;

		resize(inputImage, outputImage, Size(), 0.1, 0.1, INTER_LINEAR);
		cvtColor(outputImage, outputImage, COLOR_RGB2GRAY);

		string outputImagePath;

		if (cmfdLoopCount > cmfdSeparationPoint) {
			outputImagePath = processed_folder_path + "/CMFD/training/" + entry.path().filename().string();
		}
		else {
			outputImagePath = processed_folder_path + "/CMFD/testing/" + entry.path().filename().string();
		}

		imwrite(outputImagePath, outputImage);

		cmfdLoopCount++;

	}

	cout << "IMFD CONVERSION" << endl;

	// IMFD LOOP

	int imfdFileCount = distance(fs::directory_iterator(uploaded_folder_path + "/IMFD/"), fs::directory_iterator());
	int imfdLoopCount = 1;
	int imfdSeparationPoint = imfdFileCount / 2;

	for (const auto & entry : fs::directory_iterator(uploaded_folder_path + "/IMFD/")) {

		cout << "Converting " << entry.path().filename() << " file" << endl;

		string inputImagePath = samples::findFile(entry.path().string());
		Mat inputImage = imread(inputImagePath, IMREAD_COLOR);

		Mat outputImage;

		resize(inputImage, outputImage, Size(), 0.1, 0.1, INTER_LINEAR);
		cvtColor(outputImage, outputImage, COLOR_RGB2GRAY);

		string outputImagePath;

		if (imfdLoopCount > imfdSeparationPoint) {
			outputImagePath = processed_folder_path + "/IMFD/training/" + entry.path().filename().string();
		}
		else {
			outputImagePath = processed_folder_path + "/IMFD/testing/" + entry.path().filename().string();
		}

		imwrite(outputImagePath, outputImage);

		imfdLoopCount++;

	}

	return 0;

}