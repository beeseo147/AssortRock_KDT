// 01-09.FileIO.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <fstream>
#include "ThirdParty/inicpp.h"

int main()
{
	// 1. 기본 C++ file IO
	// 2. ini 파일 IO
	// 3. json 파일 IO

	// 절대경로: 특정 드라이브를 기준으로 (C:\...) 시작하는 경로 (C:\Dir\Test.txt)
	// 상대경로: 특정 기준점으로 부터 시작하는 경로 "Dir\Test.txt" "Dir/Test.txt"

	// 1. 기본 C++ file IO(Input Output)
	{
		// file write
		// output file stream: ofstream
		{
			std::ofstream OutputStream = std::ofstream("Test.txt", std::ios::out);
			if (OutputStream.is_open())
			{
				std::string String = "Hello File!\n";
				OutputStream.write(String.data(), String.size());
				//OutputStream << String /*<< std::endl*/;

				int Int = 10;
				OutputStream.write(reinterpret_cast<char*>(&Int), sizeof(Int));

				OutputStream.close(); // 파일 닫기
			}
		}

		{
			// file load
			std::ifstream InputStream("Test.txt", std::ios::in);
			if (InputStream.is_open())
			{
				std::string String;
				String.resize(12);
				InputStream.read(String.data(), String.size());
				//InputStream >> String;

				int Int = 0;
				InputStream.read(reinterpret_cast<char*>(&Int), sizeof(int));

				InputStream.close();
			}
		}

		// 1. 기본 C++ file IO binary
		{
			std::ofstream OutputStream = std::ofstream("TestBinary.txt", std::ios::out | std::ios::binary);
			if (OutputStream.is_open())
			{
				std::string String = "Hello File!\n";
				OutputStream.write(String.data(), String.size());
				//OutputStream << String /*<< std::endl*/;

				int Int = 10;
				OutputStream.write(reinterpret_cast<char*>(&Int), sizeof(Int));

				OutputStream.close(); // 파일 닫기
			}
		}
		{
			// file load
			std::ifstream InputStream("TestBinary.txt", std::ios::in | std::ios::binary);
			if (InputStream.is_open())
			{
				std::string String;
				String.resize(12);
				InputStream.read(String.data(), String.size());
				//InputStream >> String;

				int Int = 0;
				InputStream.read(reinterpret_cast<char*>(&Int), sizeof(int));

				InputStream.close();
			}
		}
	}

	// 2. ini file IO
	{
		// wirte
		{
			ini::IniFile File;
			File["Section"]["Key"] = "Value";
			File["Section"]["Key2"] = 1000;

			File["Graphics"]["Width"] = 1920;
			File["Graphics"]["Height"] = 1080;

			File.save("IniFile.ini");
		}
		// load
		{
			ini::IniFile File("IniFile.ini");
			std::string Value = File["Section"]["Key"].as<std::string>();
			int Value2 = File["Section"]["Key2"].as<int>();

			int Width = File["Graphics"]["Width"].as<int>();
			int Height = File["Graphics"]["Height"].as<int>();
		}
	}


}