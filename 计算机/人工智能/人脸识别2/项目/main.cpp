#include "LBPH.h"
#include "Hog.h"
#include "Haar.h"
//#include "label.h"
#include <string>
#include <vector>
#include <fstream> 
#include <iostream>
#include <queue>
using namespace std;

static const string data_path[3] = { 
	"E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\famous48\\x24x24.txt",
	"E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\famous48\\y24x24.txt",
	"E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\famous48\\z24x24.txt" 
};

static const string LBPH_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LBPH\\lbph_train.txt";
static const string LBPH_test_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LBPH\\lbph_test.txt";
static const string LBPH_testLHH_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LBPH\\lbph_testLHH.txt";

static const string Hog_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Hog\\histograms_train.txt";
static const string Hog_test_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Hog\\histograms_test.txt";
static const string Hog_testLHH_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Hog\\histograms_testLHH.txt";

static const string Haar_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Haar\\haar_train.txt";
static const string Haar_test_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Haar\\haar_test.txt";
static const string Haar_testLHH_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\Haar\\haar_testLHH.txt";

static const string LHH_LBPH_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LHH_system\\LHH_LBPH_train.txt";
static const string LHH_Hog_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LHH_system\\LHH_Hog_train.txt";
static const string LHH_Haar_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LHH_system\\LHH_Haar_train.txt";
static const string LHH_weight_train_path = "E:\\Gdansk University of Technology\\Fourth_Semester\\ArtificialIntelligence\\Project\\LHH_system\\LHH_Weight_train.txt";

static const int divide_max = 4;
static const int divide_lhh = 3;
// all 6835 data lines.
static const int test_num = 6835 / (divide_max + 1);
static const int train_lhh_num = 6835 / (divide_max + 1) + ((6835 % (divide_max + 1) < 4) ? 0 : 1);
static const int train_classifier_num = 6835 - test_num - train_lhh_num;
static const int classNum = 48;
static const float adjustWeight = 0.2f;
static const float weightChangeThreshold = 0.5f;


#pragma region Train sub-classifier

void Train_SubClassifier()
{
	int L;
	int N;
	ifstream file;
	ofstream train_file, test_file,test_fileLHH, train_file2, test_file2, test_file2LHH, train_file3, test_file3, test_file3LHH;
	train_file.open(LBPH_train_path, std::ios::out);
	test_file.open(LBPH_test_path, std::ios::out);
	test_fileLHH.open(LBPH_testLHH_path, std::ios::out);
	train_file2.open(Hog_train_path, std::ios::out);
	test_file2.open(Hog_test_path, std::ios::out);
	test_file2LHH.open(Hog_testLHH_path, std::ios::out);
	train_file3.open(Haar_train_path, std::ios::out);
	test_file3.open(Haar_test_path, std::ios::out);
	test_file3LHH.open(Haar_testLHH_path, std::ios::out);

	//int index_train = 0;
	//int index_test = 0;
	int divide = 0; // 0,1,2,->train, 3->train LHH system, 4->test

	for (int file_index = 0; file_index < 3; file_index++)
	{
		file.open(data_path[file_index], std::ios::in);
		file >> L;
		file >> N;
		//cout << L << N << endl;

		float img[sizeX][sizeY];
		vector<int>lab(8);

		int imgy = 0;
		int imgx = 0;
		for (int line_index = 0; line_index < L; line_index++)
		{
			cout << line_index << endl;
			// LBPH
			for (int data_index = 0; data_index < N; data_index++)
			{
				file >> img[imgx][imgy];
				
				imgy++;
				if (imgy == sizeY)
				{
					imgy = 0;
					imgx++;
				}
				if (imgx == sizeX)
				{
					imgx = 0;
				}
			}
			LBPH lbph(img);
			Hog hog(img);
			Haar haar(img);
			
			//Label label(lab);

			if (divide < divide_lhh)
			{
				for (auto& i : lbph.ULBPH)
				{
					train_file << i << " ";
				}
				for (auto& i : hog.hogHist)
				{
					train_file2 << i << " ";
				}
				for (auto& i : haar.haarVector)
				{
					train_file3 << i << " ";
				}				
				
				// label
				for (int label_index = 0; label_index < 8; label_index++)
				{
					file >> lab[label_index];
					train_file << lab[label_index] << " ";
					train_file2 << lab[label_index] << " ";
					train_file3 << lab[label_index] << " ";
				}
				train_file << "\n";
				train_file2 << "\n";
				train_file3 << "\n";

				//train[index_train] = lbph;
				//label_train[index_train] = lab;
				//index_train++;
				divide++;
			}
			else if (divide < divide_max)
			{
				for (auto& i : lbph.ULBPH)
				{
					test_fileLHH << i << " ";
				}
				for (auto& i : hog.hogHist)
				{
					test_file2LHH << i << " ";
				}
				for (auto& i : haar.haarVector)
				{
					test_file3LHH << i << " ";
				}
				// label
				for (int label_index = 0; label_index < 8; label_index++)
				{
					file >> lab[label_index];
					test_fileLHH << lab[label_index] << " ";
					test_file2LHH << lab[label_index] << " ";
					test_file3LHH << lab[label_index] << " ";
				}
				test_fileLHH << "\n";
				test_file2LHH << "\n";
				test_file3LHH << "\n";
				divide++;
			}
			else
			{
				for (auto& i : lbph.ULBPH)
				{
					test_file << i << " ";
				}
				for (auto& i : hog.hogHist)
				{
					test_file2 << i << " ";
				}
				for (auto& i : haar.haarVector)
				{
					test_file3 << i << " ";
				}
				// label
				for (int label_index = 0; label_index < 8; label_index++)
				{
					file >> lab[label_index];
					test_file << lab[label_index] << " ";
					test_file2 << lab[label_index] << " ";
					test_file3 << lab[label_index] << " ";
				}
				test_file << "\n";
				test_file2 << "\n";
				test_file3 << "\n";
				//test[index_test] = lbph;
				//label_test[index_test] = lab;
				//index_test++;
				divide = 0;
			}
		}	
		file.close();
	}
	train_file.close();
	train_file2.close();
	train_file3.close();

	test_file.close();
	test_file2.close();
	test_file3.close();

	//----------------------------------------------------------------------------------------------------
	//// test ULBPH --
	////float error[48] = { 0 };
	//int class_person = 0;
	//int num_test = 0;
	//int num_error_class = 0;
	//int num_error_sex = 0;
	//int num_error_race = 0;
	//int num_error_class_total = 0;
	//int num_error_sex_total = 0;
	//int num_error_race_total = 0;
	//for (int j = 0;j < test_num;j++)
	//{
	//	if (label_test[j][2] != class_person)
	//	{
	//		//error[class_person] = float(num_error_class) / num_test;
	//		cout << "person" << class_person << " error rate:" << endl
	//			<< "\tclass\t" << float(num_error_class) / num_test << endl
	//			<< "\tsex\t" << float(num_error_sex) / num_test <<endl
	//			<< "\trace\t" << float(num_error_race) / num_test <<endl;
	//		class_person = label_test[j][2];
	//		num_error_class_total += num_error_class;
	//		num_error_sex_total += num_error_sex;
	//		num_error_race_total += num_error_race;
	//		num_test = 0;
	//		num_error_class = 0;
	//		num_error_sex = 0;
	//		num_error_race = 0;
	//	}
	//	float minDis = FLT_MAX;
	//	vector<int> label_sample;
	//	for (int i = 0; i< train_num;i++)
	//	{
	//		float temp = train[i] - test[j];
	//		if (temp < minDis)
	//		{
	//			minDis = temp;
	//			label_sample = label_train[i];
	//		}
	//	}
	//	num_test++;
	//	if (label_sample[2] != label_test[j][2])
	//	{
	//		num_error_class++;
	//	}
	//	if (label_sample[3] != label_test[j][3])
	//	{
	//		num_error_sex++;
	//	}
	//	if (label_sample[4] != label_test[j][4])
	//	{
	//		num_error_race++;
	//	}

	//}

	////error[47] = num_error_class / num_test;
	//cout << "person" << class_person << " error rate:" << endl
	//	<< "\tclass\t" << float(num_error_class) / num_test << endl
	//	<< "\tsex\t" << float(num_error_sex) / num_test << endl
	//	<< "\trace\t" << float(num_error_race) / num_test << endl;

	//num_error_class_total += num_error_class;
	//num_error_sex_total += num_error_sex;
	//num_error_race_total += num_error_race;
	//cout << "tatal error rate:" <<endl
	//	<< "\tclass\t" << float(num_error_class_total) / test_num << endl
	//	<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
	//	<< "\trace\t" << float(num_error_race_total) / test_num << endl;


	//return 0;
}

#pragma endregion

#pragma region LHH_LBPH

void LHH_LBPH()
{
	// all 6835 data lines.
	vector<LBPH> LBPH_train(train_classifier_num);
	vector<LBPH> LBPH_test(test_num);
	vector<vector<int>> label_train(train_classifier_num, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	ifstream file;
	ofstream lhhFile;

	// train file reading
	file.open(LBPH_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_train[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_train[i][j];
		}
	}
	file.close();

	// test file reading
	file.open(LBPH_testLHH_path, std::ios::in);
	for (int i = 0; i < train_lhh_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_test[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_test[i][j];
		}
	}
	file.close();

	lhhFile.open(LHH_LBPH_train_path, std::ios::out);
	// Test
	int class_person = 0;
	int num_test = 0;
	int num_error_class = 0;
	int num_error_sex = 0;
	int num_error_race = 0;
	int num_error_class_total = 0;
	int num_error_sex_total = 0;
	int num_error_race_total = 0;
	for (int j = 0; j < train_lhh_num; j++)
	{
		if (label_test[j][2] != class_person)
		{
			//error[class_person] = float(num_error_class) / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;

			//record the 1 - error rate
			lhhFile << 1.0f - float(num_error_class) / num_test << " ";

			class_person = label_test[j][2];
			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;
			num_test = 0;
			num_error_class = 0;
			num_error_sex = 0;
			num_error_race = 0;
		}
		float minDis = FLT_MAX;
		vector<int> label_sample;
		for (int i = 0; i < train_classifier_num; i++)
		{
			float temp = LBPH_train[i] - LBPH_test[j];
			if (temp < minDis)
			{
				minDis = temp;
				label_sample = label_train[i];
			}
		}
		num_test++;
		if (label_sample[2] != label_test[j][2])
		{
			num_error_class++;
		}
		if (label_sample[3] != label_test[j][3])
		{
			num_error_sex++;
		}
		if (label_sample[4] != label_test[j][4])
		{
			num_error_race++;
		}

	}

	//error[47] = num_error_class / num_test;
	cout << "person" << class_person << " error rate:" << endl
		<< "\tclass\t" << float(num_error_class) / num_test << endl
		<< "\tsex\t" << float(num_error_sex) / num_test << endl
		<< "\trace\t" << float(num_error_race) / num_test << endl;

	//record the error rate
	lhhFile << 1.0f - float(num_error_class) / num_test << " ";

	num_error_class_total += num_error_class;
	num_error_sex_total += num_error_sex;
	num_error_race_total += num_error_race;
	cout << "tatal error rate:" << endl
		<< "\tclass\t" << float(num_error_class_total) / test_num << endl
		<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
		<< "\trace\t" << float(num_error_race_total) / test_num << endl;

	lhhFile.close();
	return;
}

#pragma endregion

#pragma region LHH_Hog v2.0

void LHH_Hog()
{
	vector<Hog> hogs_train(train_classifier_num);
	vector<Hog> hogs_test(test_num);
	vector<vector<int>> label_train(train_classifier_num, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	ifstream file;
	ofstream lhhFile;

	// train file reading
	file.open(Hog_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// test file reading
	file.open(Hog_testLHH_path, std::ios::in);
	for (int i = 0; i < train_lhh_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_test[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	lhhFile.open(LHH_Hog_train_path, std::ios::out);
	// Test
	int class_person = 0;
	int num_test = 0;
	int num_error_class = 0;
	int num_error_sex = 0;
	int num_error_race = 0;
	int num_error_class_total = 0;
	int num_error_sex_total = 0;
	int num_error_race_total = 0;
	for (int j = 0; j < train_lhh_num; j++)
	{
		if (label_test[j][2] != class_person)
		{
			//error[class_person] = float(num_error_class) / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;

			lhhFile << 1.0f - float(num_error_class) / num_test << " ";

			class_person = label_test[j][2];
			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;
			num_test = 0;
			num_error_class = 0;
			num_error_sex = 0;
			num_error_race = 0;
		}
		float minDis = FLT_MAX;
		vector<int> label_sample;
		for (int i = 0; i < train_classifier_num; i++)
		{
			float temp = hogs_train[i] - hogs_test[j];
			if (temp < minDis)
			{
				minDis = temp;
				label_sample = label_train[i];
			}
		}
		num_test++;
		if (label_sample[2] != label_test[j][2])
		{
			num_error_class++;
		}
		if (label_sample[3] != label_test[j][3])
		{
			num_error_sex++;
		}
		if (label_sample[4] != label_test[j][4])
		{
			num_error_race++;
		}

	}

	//error[47] = num_error_class / num_test;
	cout << "person" << class_person << " error rate:" << endl
		<< "\tclass\t" << float(num_error_class) / num_test << endl
		<< "\tsex\t" << float(num_error_sex) / num_test << endl
		<< "\trace\t" << float(num_error_race) / num_test << endl;

	lhhFile << 1.0f - float(num_error_class) / num_test << " ";

	num_error_class_total += num_error_class;
	num_error_sex_total += num_error_sex;
	num_error_race_total += num_error_race;
	cout << "tatal error rate:" << endl
		<< "\tclass\t" << float(num_error_class_total) / test_num << endl
		<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
		<< "\trace\t" << float(num_error_race_total) / test_num << endl;

	lhhFile.close();

	return;
}

#pragma endregion

#pragma region LHH_Haar

void LHH_Haar()
{
	vector<Haar> haars_train(train_classifier_num);
	vector<Haar> haars_test(test_num);
	vector<vector<int>> label_train(train_classifier_num, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	ifstream file;
	ofstream lhhFile;

	// train file reading
	file.open(Haar_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_train[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// test file reading
	file.open(Haar_testLHH_path, std::ios::in);
	for (int i = 0; i < train_lhh_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_test[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	lhhFile.open(LHH_Haar_train_path, std::ios::out);
	// Test
	int class_person = 0;
	int num_test = 0;
	int num_error_class = 0;
	int num_error_sex = 0;
	int num_error_race = 0;
	int num_error_class_total = 0;
	int num_error_sex_total = 0;
	int num_error_race_total = 0;
	for (int j = 0; j < train_lhh_num; j++)
	{
		if (label_test[j][2] != class_person)
		{
			//error[class_person] = float(num_error_class) / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;

			lhhFile << 1.0f - float(num_error_class) / num_test << " ";

			class_person = label_test[j][2];
			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;
			num_test = 0;
			num_error_class = 0;
			num_error_sex = 0;
			num_error_race = 0;
		}
		float minDis = FLT_MAX;
		vector<int> label_sample;
		for (int i = 0; i < train_classifier_num; i++)
		{
			float temp = haars_train[i] - haars_test[j];
			if (temp < minDis)
			{
				minDis = temp;
				label_sample = label_train[i];
			}
		}
		num_test++;
		if (label_sample[2] != label_test[j][2])
		{
			num_error_class++;
		}
		if (label_sample[3] != label_test[j][3])
		{
			num_error_sex++;
		}
		if (label_sample[4] != label_test[j][4])
		{
			num_error_race++;
		}

	}

	//error[47] = num_error_class / num_test;
	cout << "person" << class_person << " error rate:" << endl
		<< "\tclass\t" << float(num_error_class) / num_test << endl
		<< "\tsex\t" << float(num_error_sex) / num_test << endl
		<< "\trace\t" << float(num_error_race) / num_test << endl;

	lhhFile << 1.0f - float(num_error_class) / num_test << " ";

	num_error_class_total += num_error_class;
	num_error_sex_total += num_error_sex;
	num_error_race_total += num_error_race;
	cout << "tatal error rate:" << endl
		<< "\tclass\t" << float(num_error_class_total) / test_num << endl
		<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
		<< "\trace\t" << float(num_error_race_total) / test_num << endl;

	lhhFile.close();

	return;
}

#pragma endregion

#pragma region LHH weight train

void Train_LHH_weights()
{
	vector<LBPH> LBPH_train(train_classifier_num);
	vector<Hog> hogs_train(train_classifier_num);
	vector<Haar> haars_train(train_classifier_num);
	vector<LBPH> LBPH_test(test_num);
	vector<Hog> hogs_test(test_num);
	vector<Haar> haars_test(test_num);
	vector<vector<int>> label_train(train_classifier_num, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	float LHH_LBPH[classNum];
	float LHH_Hog[classNum];
	float LHH_Haar[classNum];
	ifstream file;
	ifstream lhhFile1;
	ifstream lhhFile2;
	ifstream lhhFile3;
	ofstream lhhWeightFile;


#pragma region LBPH read
	// train file reading
	file.open(LBPH_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_train[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_train[i][j];
		}
	}
	file.close();

	// test file reading
	file.open(LBPH_testLHH_path, std::ios::in);
	for (int i = 0; i < train_lhh_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_test[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_test[i][j];
		}
	}
	file.close();
#pragma endregion

#pragma region Hog read

	// train file reading
	file.open(Hog_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// test file reading
	file.open(Hog_testLHH_path, std::ios::in);
	for (int i = 0; i < train_lhh_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_test[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

#pragma endregion

#pragma region Haar read
	// Haar train file reading
	file.open(Haar_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_train[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// Haar test file reading
	file.open(Haar_testLHH_path, std::ios::in);
	for (int i = 0; i < test_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_test[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();
#pragma endregion

	lhhWeightFile.open(LHH_weight_train_path, std::ios::out);
	float weight_threshold = 0.5f;
	float error_min = 1.0f;
	float weight_threshold_min = 0.5f;
	float weight_adjust_min = 0.0f;
	for (; weight_threshold > 0.1; weight_threshold -= 0.1)
	{
		float weight_adjust = 0.0f;
		for (; weight_adjust < 1.1; weight_adjust += 0.1)
		{
#pragma region LHH read
			lhhFile1.open(LHH_LBPH_train_path, std::ios::in);
			lhhFile2.open(LHH_Hog_train_path, std::ios::in);
			lhhFile3.open(LHH_Haar_train_path, std::ios::in);
			for (int i = 0; i < classNum; i++)
			{
				cout << i << endl;
				string tempR;
				lhhFile1 >> tempR;
				LHH_LBPH[i] = stof(tempR);
				if (LHH_LBPH[i] < weight_threshold)
				{
					LHH_LBPH[i] = 1 - LHH_LBPH[i] + weight_adjust;
				}
				lhhFile2 >> tempR;
				LHH_Hog[i] = stof(tempR);
				if (LHH_Hog[i] < weight_threshold)
				{
					LHH_Hog[i] = 1 - LHH_Hog[i] + weight_adjust;
				}
				lhhFile3 >> tempR;
				LHH_Haar[i] = stof(tempR);
				if (LHH_Haar[i] < weight_threshold)
				{
					LHH_Haar[i] = 1 - LHH_Haar[i] + weight_adjust;
				}
			}
			lhhFile1.close();
			lhhFile2.close();
			lhhFile3.close();

#pragma endregion

			// Test
			int class_person = 0;
			int num_test = 0;
			int num_error_class = 0;
			int num_error_sex = 0;
			int num_error_race = 0;
			int num_error_class_total = 0;
			int num_error_sex_total = 0;
			int num_error_race_total = 0;
			for (int j = 0; j < train_lhh_num; j++)
			{
				if (label_test[j][2] != class_person)
				{
					//error[class_person] = float(num_error_class) / num_test;
					cout << "person" << class_person << " error rate:" << endl
						<< "\tclass\t" << float(num_error_class) / num_test << endl
						<< "\tsex\t" << float(num_error_sex) / num_test << endl
						<< "\trace\t" << float(num_error_race) / num_test << endl;


					class_person = label_test[j][2];
					num_error_class_total += num_error_class;
					num_error_sex_total += num_error_sex;
					num_error_race_total += num_error_race;
					num_test = 0;
					num_error_class = 0;
					num_error_sex = 0;
					num_error_race = 0;
				}

#pragma region Priority queue rank
				//find top 5 closed people for each sub classifier
				priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_LBPH;
				priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_Hog;
				priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_Haar;

				for (int i = 0; i < train_classifier_num; i++)
				{
					float temp1 = LBPH_train[i] - LBPH_test[j];
					float temp2 = hogs_train[i] - hogs_test[j];
					float temp3 = haars_train[i] - haars_test[j];
					top5_LBPH.push(pair<float, vector<int>>(temp1, label_train[i]));
					top5_Hog.push(pair<float, vector<int>>(temp2, label_train[i]));
					top5_Haar.push(pair<float, vector<int>>(temp3, label_train[i]));
				}

#pragma endregion

				//vote for top 5
				float vote[classNum] = { 0 };
				vector<vector<int>> voteRes_LBPH(5, vector<int>(8));
				vector<vector<int>> voteRes_Hog(5, vector<int>(8));
				vector<vector<int>> voteRes_Haar(5, vector<int>(8));

				for (int i = 0; i < 5; i++)
				{
					vote[top5_LBPH.top().second[2]] += LHH_LBPH[top5_LBPH.top().second[2]];
					vote[top5_Hog.top().second[2]] += LHH_LBPH[top5_Hog.top().second[2]];
					vote[top5_Haar.top().second[2]] += LHH_LBPH[top5_Haar.top().second[2]];

					voteRes_LBPH[i] = top5_LBPH.top().second;
					voteRes_Hog[i] = top5_Hog.top().second;
					voteRes_Haar[i] = top5_Haar.top().second;

					top5_LBPH.pop();
					top5_Hog.pop();
					top5_Haar.pop();
				}
				int label_sample = max_element(vote, vote + classNum) - vote;

				num_test++;

				if (label_sample != label_test[j][2])
				{
					num_error_class++;

					float e = 0; //correct rate
					int sample_sex, sample_race;

					for (int i = 0; i < 5; i++)
					{
						if (voteRes_LBPH[i][2] == label_sample)
						{
							if (e < LHH_LBPH[label_sample])
							{
								e = LHH_LBPH[label_sample];
								sample_sex = voteRes_LBPH[i][3];
								sample_race = voteRes_LBPH[i][4];
							}
						}
						if (voteRes_Hog[i][2] == label_sample)
						{
							if (e < LHH_Hog[label_sample])
							{
								e = LHH_Hog[label_sample];
								sample_sex = voteRes_Hog[i][3];
								sample_race = voteRes_Hog[i][4];
							}
						}
						if (voteRes_Haar[i][2] == label_sample)
						{
							if (e < LHH_Haar[label_sample])
							{
								e = LHH_Haar[label_sample];
								sample_sex = voteRes_Haar[i][3];
								sample_race = voteRes_Haar[i][4];
							}
						}
					}

					if (sample_sex != label_test[j][3])
					{
						num_error_sex++;
					}
					if (sample_race != label_test[j][4])
					{
						num_error_race++;
					}
				}

			}

			//error[47] = num_error_class / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;

			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;

			float temp_e = float(num_error_class_total) / test_num;
			cout << "tatal error rate:" << endl
				<< "\tclass\t" << temp_e << endl
				<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
				<< "\trace\t" << float(num_error_race_total) / test_num << endl;

			lhhWeightFile << "weight_threshold :" << weight_threshold << " weight_adjust : " << weight_adjust << " total error rate : " << temp_e << endl;
			cout << "weight_threshold :" << weight_threshold << " weight_adjust : " << weight_adjust << " total error rate : " << temp_e << endl;

			if (temp_e < error_min)
			{
				error_min = temp_e;
				weight_adjust_min = weight_adjust;
				weight_threshold_min = weight_threshold;
			}
		}
	}
	cout << "adjust min :" << weight_adjust_min << " weight min : " << weight_threshold_min << " total error rate : " << error_min << endl;
	lhhWeightFile << "adjust min :" << weight_adjust_min << " weight min : " << weight_threshold_min << " total error rate : " << error_min << endl;
	lhhWeightFile.close();
	return;
}

#pragma endregion

#pragma region TEST_LHH

void Test_LHH()
{
	vector<LBPH> LBPH_train(train_classifier_num
		+ train_lhh_num
	);
	vector<Hog> hogs_train(train_classifier_num
		+ train_lhh_num
	);
	vector<Haar> haars_train(train_classifier_num
		+ train_lhh_num
	);
	vector<LBPH> LBPH_test(test_num);
	vector<Hog> hogs_test(test_num);
	vector<Haar> haars_test(test_num);
	vector<vector<int>> label_train(train_classifier_num
		+ train_lhh_num
		, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	float LHH_LBPH[classNum];
	float LHH_Hog[classNum];
	float LHH_Haar[classNum];
	ifstream file;
	ifstream lhhFile1;
	ifstream lhhFile2;
	ifstream lhhFile3;

#pragma region LBPH read
	// train file reading
	file.open(LBPH_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_train[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_train[i][j];
		}
	}
	file.close();

	file.open(LBPH_testLHH_path, std::ios::in);
	for (int i = train_classifier_num; i < train_classifier_num + train_lhh_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_train[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_train[i][j];
		}
	}
	file.close();

	// test file reading
	file.open(LBPH_test_path, std::ios::in);
	for (int i = 0; i < test_num; i++)
	{
		for (int j = 0; j < LBPH_blockXY59; j++)
		{
			file >> LBPH_test[i].ULBPH[j];
		}
		for (int j = 0; j < 8; j++)
		{
			file >> label_test[i][j];
		}
	}
	file.close();
#pragma endregion

#pragma region Hog read

	// train file reading
	file.open(Hog_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	file.open(Hog_testLHH_path, std::ios::in);
	for (int i = train_classifier_num; i < train_classifier_num + train_lhh_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// test file reading
	file.open(Hog_test_path, std::ios::in);
	for (int i = 0; i < test_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Hog_num_features; indexCol++)
		{
			file >> tempR;
			hogs_test[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

#pragma endregion

#pragma region Haar read
	// Haar train file reading
	file.open(Haar_train_path, std::ios::in);
	for (int i = 0; i < train_classifier_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_train[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	file.open(Haar_testLHH_path, std::ios::in);
	for (int i = train_classifier_num; i < train_classifier_num + train_lhh_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
		}
	}
	file.close();

	// Haar test file reading
	file.open(Haar_test_path, std::ios::in);
	for (int i = 0; i < test_num; i++)
	{
		cout << i << endl;
		string tempR;
		for (int indexCol = 0; indexCol < Haar_num_features; indexCol++)
		{
			file >> tempR;
			haars_test[i].haarVector[indexCol] = stof(tempR);
		}

		for (int index_attr = 0; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}
	}
	file.close();
#pragma endregion

#pragma region LHH read

	lhhFile1.open(LHH_LBPH_train_path, std::ios::in);
	lhhFile2.open(LHH_Hog_train_path, std::ios::in);
	lhhFile3.open(LHH_Haar_train_path, std::ios::in);
	for (int i = 0; i < classNum; i++)
	{
		cout << i << endl;
		string tempR;
		lhhFile1 >> tempR;
		LHH_LBPH[i] = stof(tempR);
		if (LHH_LBPH[i] < weightChangeThreshold)
		{
			LHH_LBPH[i] = 1 - LHH_LBPH[i] + adjustWeight;
		}
		lhhFile2 >> tempR;
		LHH_Hog[i] = stof(tempR);
		if (LHH_Hog[i] < weightChangeThreshold)
		{
			LHH_Hog[i] = 1 - LHH_Hog[i] + adjustWeight;
		}
		lhhFile3 >> tempR;
		LHH_Haar[i] = stof(tempR);
		if (LHH_Haar[i] < weightChangeThreshold)
		{
			LHH_Haar[i] = 1 - LHH_Haar[i] + adjustWeight;
		}
	}
	lhhFile1.close();
	lhhFile2.close();
	lhhFile3.close();

#pragma endregion

	// Test
	int class_person = 0;
	int num_test = 0;
	int num_error_class = 0;
	int num_error_sex = 0;
	int num_error_race = 0;
	int num_error_class_total = 0;
	int num_error_sex_total = 0;
	int num_error_race_total = 0;
	for (int j = 0; j < test_num; j++)
	{
		if (label_test[j][2] != class_person)
		{
			//error[class_person] = float(num_error_class) / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;


			class_person = label_test[j][2];
			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;
			num_test = 0;
			num_error_class = 0;
			num_error_sex = 0;
			num_error_race = 0;
		}

#pragma region Priority queue rank
		//find top 5 closed people for each sub classifier
		priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_LBPH;
		priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_Hog;
		priority_queue<pair<float, vector<int>>, vector<pair<float, vector<int>>>, greater<pair<float, vector<int>>>> top5_Haar;

		for (int i = 0; i < train_classifier_num
			+ train_lhh_num
			; i++)
		{
			float temp1 = LBPH_train[i] - LBPH_test[j];
			float temp2 = hogs_train[i] - hogs_test[j];
			float temp3 = haars_train[i] - haars_test[j];
			top5_LBPH.push(pair<float, vector<int>>(temp1, label_train[i]));
			top5_Hog.push(pair<float, vector<int>>(temp2, label_train[i]));
			top5_Haar.push(pair<float, vector<int>>(temp3, label_train[i]));
		}
#pragma endregion

		//vote for top 5
		float vote[classNum] = { 0 };
		vector<vector<int>> voteRes_LBPH(5, vector<int>(8));
		vector<vector<int>> voteRes_Hog(5, vector<int>(8));
		vector<vector<int>> voteRes_Haar(5, vector<int>(8));

		for (int i = 0; i < 5; i++)
		{
			vote[top5_LBPH.top().second[2]] += LHH_LBPH[top5_LBPH.top().second[2]];
			vote[top5_Hog.top().second[2]] += LHH_LBPH[top5_Hog.top().second[2]];
			vote[top5_Haar.top().second[2]] += LHH_LBPH[top5_Haar.top().second[2]];

			voteRes_LBPH[i] = top5_LBPH.top().second;
			voteRes_Hog[i] = top5_Hog.top().second;
			voteRes_Haar[i] = top5_Haar.top().second;

			top5_LBPH.pop();
			top5_Hog.pop();
			top5_Haar.pop();
		}
		int label_sample = max_element(vote, vote + classNum) - vote;
		//if (vote[23] != 0)
		//{
		//	label_sample = 23;
		//}
		//if (vote[22] != 0)
		//{
		//	label_sample = 22;
		//}
		//if (vote[21] != 0)
		//{
		//	label_sample = 21;
		//}

		num_test++;

		if (label_sample != label_test[j][2])
		{
			num_error_class++;
			int e = 0; //correct rate
			int sample_sex, sample_race;

			for (int i = 0; i < 5; i++)
			{
				if (voteRes_LBPH[i][2] == label_sample)
				{
					if (e < LHH_LBPH[label_sample])
					{
						e = LHH_LBPH[label_sample];
						sample_sex = voteRes_LBPH[i][3];
						sample_race = voteRes_LBPH[i][4];
					}
				}
				if (voteRes_Hog[i][2] == label_sample)
				{
					if (e < LHH_Hog[label_sample])
					{
						e = LHH_Hog[label_sample];
						sample_sex = voteRes_Hog[i][3];
						sample_race = voteRes_Hog[i][4];
					}
				}
				if (voteRes_Haar[i][2] == label_sample)
				{
					if (e < LHH_Haar[label_sample])
					{
						e = LHH_Haar[label_sample];
						sample_sex = voteRes_Haar[i][3];
						sample_race = voteRes_Haar[i][4];
					}
				}
			}

			if (sample_sex != label_test[j][3])
			{
				num_error_sex++;
			}
			if (sample_race != label_test[j][4])
			{
				num_error_race++;
			}
		}

	}

	//error[47] = num_error_class / num_test;
	cout << "person" << class_person << " error rate:" << endl
		<< "\tclass\t" << float(num_error_class) / num_test << endl
		<< "\tsex\t" << float(num_error_sex) / num_test << endl
		<< "\trace\t" << float(num_error_race) / num_test << endl;

	num_error_class_total += num_error_class;
	num_error_sex_total += num_error_sex;
	num_error_race_total += num_error_race;
	cout << "tatal error rate:" << endl
		<< "\tclass\t" << float(num_error_class_total) / test_num << endl
		<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
		<< "\trace\t" << float(num_error_race_total) / test_num << endl;

	return;
}

#pragma endregion

#pragma region Hog v1.0
/*
int main()
{
	vector<Hog> hogs_train(train_num);
	vector<Hog> hogs_test(test_num);
	vector<vector<int>> label_train(train_num, vector<int>(8));
	vector<vector<int>> label_test(test_num, vector<int>(8));
	ifstream file;

	// train file reading
	file.open(Hog_train_path, std::ios::in);
	for (int i = 0; i < train_num; i++)
	{
		cout << i << endl;
		string tempR;
		file >> tempR;	//people
		label_train[i][0] = stoi(tempR.substr(1));
		for (int index_attr = 1; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_train[i][index_attr] = stoi(tempR);
			//cout << label_train[i][index_attr] << " ";
		}
		//cout << "\n";
		file >> tempR;	//first number with '[['
		hogs_train[i].hogHist[0] = stof(tempR.substr(2));
		int indexCol = 1;
		for (; indexCol < num_hog; indexCol++)
		{
			file >> tempR;
			hogs_train[i].hogHist[indexCol] = stof(tempR);
			//cout << hogs_train[i].hogHist[indexCol] << " ";
		}
		//cout << "\n";
	}
	file.close();

	// test file reading
	file.open(Hog_test_path, std::ios::in);
	for (int i = 0; i < test_num; i++)
	{
		cout << i << endl;
		string tempR;
		file >> tempR;	//people
		label_test[i][0] = stoi(tempR.substr(1));
		for (int index_attr = 1; index_attr < 8; index_attr++)
		{
			file >> tempR;
			label_test[i][index_attr] = stoi(tempR);
		}

		file >> tempR;	//first number with '[['
		hogs_test[i].hogHist[0] = stof(tempR.substr(2));
		int indexCol = 1;
		for (; indexCol < num_hog; indexCol++)
		{
			file >> tempR;
			hogs_test[i].hogHist[indexCol] = stof(tempR);
		}
	}
	file.close();

	// Test
	int class_person = 0;
	int num_test = 0;
	int num_error_class = 0;
	int num_error_sex = 0;
	int num_error_race = 0;
	int num_error_class_total = 0;
	int num_error_sex_total = 0;
	int num_error_race_total = 0;
	for (int j = 0; j < test_num; j++)
	{
		if (label_test[j][2] != class_person)
		{
			//error[class_person] = float(num_error_class) / num_test;
			cout << "person" << class_person << " error rate:" << endl
				<< "\tclass\t" << float(num_error_class) / num_test << endl
				<< "\tsex\t" << float(num_error_sex) / num_test << endl
				<< "\trace\t" << float(num_error_race) / num_test << endl;
			class_person = label_test[j][2];
			num_error_class_total += num_error_class;
			num_error_sex_total += num_error_sex;
			num_error_race_total += num_error_race;
			num_test = 0;
			num_error_class = 0;
			num_error_sex = 0;
			num_error_race = 0;
		}
		float minDis = FLT_MAX;
		vector<int> label_sample;
		for (int i = 0; i < train_num; i++)
		{
			float temp = hogs_train[i] - hogs_test[j];
			if (temp < minDis)
			{
				minDis = temp;
				label_sample = label_train[i];
			}
		}
		num_test++;
		if (label_sample[2] != label_test[j][2])
		{
			num_error_class++;
		}
		if (label_sample[3] != label_test[j][3])
		{
			num_error_sex++;
		}
		if (label_sample[4] != label_test[j][4])
		{
			num_error_race++;
		}

	}

	//error[47] = num_error_class / num_test;
	cout << "person" << class_person << " error rate:" << endl
		<< "\tclass\t" << float(num_error_class) / num_test << endl
		<< "\tsex\t" << float(num_error_sex) / num_test << endl
		<< "\trace\t" << float(num_error_race) / num_test << endl;

	num_error_class_total += num_error_class;
	num_error_sex_total += num_error_sex;
	num_error_race_total += num_error_race;
	cout << "tatal error rate:" << endl
		<< "\tclass\t" << float(num_error_class_total) / test_num << endl
		<< "\tsex\t" << float(num_error_sex_total) / test_num << endl
		<< "\trace\t" << float(num_error_race_total) / test_num << endl;


	return 0;

}
*/
#pragma endregion

int main()
{
	//Train_SubClassifier();
	//LHH_LBPH();
	//LHH_Hog();
	//LHH_Haar();
	//Train_LHH_weights();
	Test_LHH();
}