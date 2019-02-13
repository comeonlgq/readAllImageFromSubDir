#include <iostream>
#include <vector>
#include<stdio.h>
#include<io.h>
#include <string>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

using namespace std;
vector<string> res;


vector<string> listdir(const string &path)
{

	string dir = path;
	vector<string> s;
	_finddata_t fileDir;
	long lfDir;

	if ((lfDir = _findfirst(dir.c_str(), &fileDir)) == -1l)
		printf("No file is found\n");
	else {
		do {

			string str(fileDir.name);
			if (str.find('.') == -1)
				s.push_back(str);


		} while (_findnext(lfDir, &fileDir) == 0);
	}
	_findclose(lfDir);
	return s;

}

void findfile(const string &str)
{
	string s = str;
	vector<string> tmp = listdir(s + "\\*");
	for (int i = 0; i < tmp.size(); i++)
	{
		string temp = s + "\\" + tmp[i];
		res.push_back(temp);
		findfile(temp);
	}
}

int main()
{

	string s = "D:\\images\\lfw";
	findfile(s);

	for (int i = 0; i < res.size(); i++)
	{
		//	printf("%s\n", res[i]);
		//	cout << res[i] << endl;
		const boost::filesystem::path path(res[i]);

		if (boost::filesystem::is_directory(path) == false)
		{
			throw std::invalid_argument(
				"we expect to receive a path to a directory");
		}

		boost::filesystem::directory_iterator the_directory_iterator;

		the_directory_iterator = boost::filesystem::directory_iterator(path);
		boost::filesystem::directory_iterator directory_end_it;
		while (the_directory_iterator != directory_end_it)
		{
			std::string input_image_path = the_directory_iterator->path().string();
			std::cout << "input_image_path : " << input_image_path << std::endl;

			std::string input_image_name = the_directory_iterator->path().filename().string();
			std::cout << "input_image_name : " << input_image_name << std::endl;

			the_directory_iterator++;
			char * ch = (char*)input_image_path.data();

			cv::Mat img = cv::imread(ch);
			cv::imshow("img", img);
			cv::waitKey(10);
			string dest = input_image_name;
			dest = "D:\\FaceImg\\" + dest;
			
			cv::imwrite(dest, img);
		}
	}

	//getchar();
	system("pause");
	return 0;
}