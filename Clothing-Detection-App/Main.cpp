// Main.cpp : main project file.
#include "CameraForm.h"
using namespace ClothingDetectionApp;
[STAThreadAttribute]
int Main(array<System::String^>^ args)
{
	// Enabling Windows XP visual effects first
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	// Create the main window and run it
	Application::Run(gcnew CameraForm());
	return 0;
}