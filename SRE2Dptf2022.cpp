#define _CRT_SECURE_NO_WARNINGS

#include < iostream >
#include < fstream >
#include < string >
#include < io.h >
#include < dos.h >
#include < conio.h >
#include < stdlib.h >
#include < sstream >
#include < stdio.h >
#include < iomanip >
#include < istream >
#include < math.h >

using namespace std;

void OnZTransform(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary);
void runSRE2D(char imageFileName[], int xd, int yd);
void OnInverseZTransformReconstruct(char filename[], int rcxres, int rcyres, double m_Real, double m_Imaginary);
void OnInverseZTransformSamplePTF(char filename[], int rcxres, int rcyres, double m_Real, double m_Imaginary, char m_scaleON);

// declare a class by the name 'ZTransform2019'
class ZTransform2019 {

	// the point is to assign to 'n1' and 'n2' 
	// the correct values from the command console
	int n1; // matrix size x (number of pixels along the x direction)
	int n2; // matrix size y (number of pixels along the y direction)

// declare the class methods
// and embed the methods body
// in the class specification
public:

	// declare a method that returns the number
	// of pixels of the image along the x direction
	int getNofPixelsX(void) { return this->n1; };

	// declare a method that returns the number
	// of pixels of the image along the y direction
	int getNofPixelsY(void) { return this->n2; };

	// declare a method that sets the number
	// of pixels of the image along the x direction
	void setNofPixelsX(int x) { this->n1 = x; };

	// declare a method that sets the number 
	// of pixels of the image along the y direction
	void setNofPixelsY(int y) { this->n2 = y; };

public:
	// declare a structure ' data ' that defines the
	// pointers to pointers to the image
	struct data {

		double** Signal; // declare the pointer to pointer to the matrix (image) 

	}*pointer; // pointer to the element of the structure 'data'
			   // the pointer points to the memory address of the
			   // pointers to pointers 
public:

	// constructor of the class 'ZTransform2019'
	ZTransform2019(int x, int y) : n1(x), n2(y) { };

	// declare the prototype of the 
	// function 'allocateData'
	// the function belongs to the 
	// sets of methods of the class 'ZTransform2019'
	void allocateData();

	// declare the prototype of the 
	// function 'save'
	// the function belongs to the 
	// sets of methods of the class 'ZTransform2019'
	void save();

	// destructor of the class 'ZTransform2019'
	~ZTransform2019() { }

};

void ZTransform2019::allocateData() { // allocate data


	// (1) allocate struct 'data' (begin)
	// define a pointer by the name 'pointer'
	// and assign to it the instance of the
	// structure 'data' (the instance is a
	// memory address
	pointer = new data;

	// assign to the pointer to a pointer 'Signal' (pointer->Signal)
	// the instance of the memory address of the pointer to pointer
	// *[this->n2]. Practically define the memory address of the 
	// rows of the matrix containing the image 'Signal'.
	pointer->Signal = new double* [this->n2];


	for (int v = 0; v < this->n2; v++) { // (1)
	// at each iteration of the for loop
	// assign to the pointer 'Signal[v]' the instance 
	// of the memory address of the pointer [this-n1].
	// Practically define the memory address of the 
	// columns of the matrices containing the image:
	// 'Signal.

		pointer->Signal[v] = new double[this->n1];


	} // (1) allocate struct 'data' (end)


  // (2) initialize (begin)
	for (int v = 0; v < this->n2; v++) { // (a)

		for (int f = 0; f < this->n1; f++) { // (b)

		// at each iteration of the two for loops
		// initializes the value of the pixel of
		// the image to zero. This is done for the
		// image 'Signal'.
		pointer->Signal[v][f] = (double)0.0;


		} //(b)

	} //(a)
   // (2) initialize (end)

} // allocate data


void ZTransform2019::save() { // saveImages

	// declare a pointer to file
	// to be used to read the image
	FILE* savedata;
	// declare a string which contains
	// the file name of the image
	char outputFile[128];

	// assign the name string "Signal.img"
	// to the string 'outputFile'
	sprintf(outputFile, "%s", "Signal.img");

	// open the image file in write-binary mode
	if ((savedata = fopen(outputFile, "wb")) == NULL)
	{
		// alert the user of possible failure in opening the file
		std::cout << "Cannot open output file, Now Exit..." << endl;
		exit(0);

	}
	else { // (save)


		for (int v = 0; v < this->n2; v++) { // (a)

			for (int f = 0; f < this->n1; f++)

				// at each iteration of the for loop saves the pixel
				// value contained at the memory address: ' &pointer->Signal[v][f] '
				fwrite(&pointer->Signal[v][f], sizeof(double), 1, savedata);

		} // (a)

		// close the file afer saving
		fclose(savedata);

	} // (save)

} // saveImages

class SRE2D2013 {

	int n1; // matrix size x
	int n2; // matrix size y

public:

	int getNofPixelsX(void) { return this->n1; };

	int getNofPixelsY(void) { return this->n2; };

	void setNofPixelsX(int x) { this->n1 = x; };

	void setNofPixelsY(int y) { this->n2 = y; };

public:

	struct data {

		double** fMRI; // pointer to the matrix entry 

		double** ICF; // pointer to the matrix entry

	}*pointer; // pointer to the matrices

public:

	SRE2D2013(int x, int y) : n1(x), n2(y) { };// constructor 

	void allocateData();

	~SRE2D2013() { } // destructor

};

void SRE2D2013::allocateData() { // allocate data


	 // (1) allocate struct 'data' (begin)
	pointer = new data;

	pointer->fMRI = new double* [this->n2];

	pointer->ICF = new double* [this->n2];


	for (int v = 0; v < this->n2; v++) { // (1)

		pointer->fMRI[v] = new double[this->n1];

		pointer->ICF[v] = new double[this->n1];

	} // (1) allocate struct 'data' (end)


	  // (2) initialize (begin)
	for (int v = 0; v < this->n2; v++) { // (a)

		for (int f = 0; f < this->n1; f++) { // (b)

			pointer->fMRI[v][f] = (double)0.0;

			pointer->ICF[v][f] = (double)0.0;

		} //(b)

	} //(a)
   // (2) initialize (end)

} // allocate data


int main(int argc, char* argv[]) {

	if (argc < 7) {
		std::cout << endl;
		std::cout << "Please type the image file name" << endl;
		std::cout << "Please make sure that the image format is Analyze 'double': 64 bits real" << endl;
		std::cout << "Please enter the following values: " << endl;
		std::cout << "The number of pixels along the X direction (integer)" << endl;
		std::cout << "The number of pixels along the Y direction (integer)" << endl;
		std::cout << "The value of the real part of the complex number, (double) in: [0.01, 1]" << endl;
		std::cout << "The value of the imaginary part of the complex number, (double) in: [0, 1]" << endl;
		std::cout << "Please type 'o' to keep the PTF original, or 's' to scale the PTF" << endl;
		std::cout << endl;
		exit(0);
	}

	else { // run the program (begin)

		char imageFileName[128];
		char tfimageName[300];
		char icfimageName[300];

		sprintf(imageFileName, "%s", argv[1]);

		int m_rcxres = atoi(argv[2]);
		int m_rcyres = atoi(argv[3]);

		// reads from the command console the
		// value of the complex number
		double m_Real = atof(argv[4]);
		double m_Imaginary = atof(argv[5]);

		unsigned char m_scaleON = 'o';

		m_scaleON = tolower(*argv[6]);


		if (m_Real < (double)0.01 || m_Real >(double) 1.0)
		{

			std::cout << "To use the filter please enter" << endl;
			std::cout << "the real part of the complex number, (double) in: [0.01, 1]" << endl;
			std::cout << "The suggested value is 0.5" << endl;
			exit(0);

		}

		if (m_Imaginary < (double)0.0 || m_Imaginary >(double) 1.0)
		{

			std::cout << "To use the filter please enter" << endl;
			std::cout << "the imaginary part of the complex number, (double) in: [0, 1]" << endl;
			std::cout << "The suggested value is 0.5" << endl;
			exit(0);

		}


		// inform the user of the image size 
		// (number of rows and number of columns
		// of the matrix containing the image)
		std::cout << "The number of pixels along the X direction is: " << atoi(argv[2]) << endl;
		std::cout << "The number of pixels along the Y direction is: " << atoi(argv[3]) << endl;
		std::cout << "The value of m_Real is: " << m_Real << endl;
		std::cout << "The value of m_Imaginary is: " << m_Imaginary << endl;

		if (tolower(m_scaleON) == 'o')
			std::cout << "The program keeps the PTF non-scaled: " << m_scaleON << endl;
		else if (tolower(m_scaleON) == 's')
			std::cout << "The program scales the PTF: " << m_scaleON << endl;

		double pi = 3.141592;
		double Zphase = (double)2.0 * pi * atan2((double)m_Imaginary, (double)m_Real) / ((double)m_rcxres * m_rcyres);
		double magnitude = (double)sqrt((double)m_Real * m_Real + (double)m_Imaginary * m_Imaginary);

		std::cout << "The magnitude of the Complex number is: " << magnitude << endl;
		std::cout << "The phase of the Complex number is: " << Zphase << endl;

		// assign to the char string 'outputFile'
		char outputFile[128] = "SRE2D.log";

		// declare a pointer to a file by the
		// name 'savedata'
		FILE* savedata;

		if ((savedata = fopen(outputFile, "w")) == NULL)
		{
			// alert the user of possible failure in opening the file
			std::cout << "Cannot open output file, Now Exit..." << endl;
			exit(0);

		}
		else { // save to log file

			// save into the log file the image size 
			// (number of rows and number of columns
			// of the matrix containing the image)
			fprintf(savedata, "%s%d\n", "The number of pixels along the X direction is: ", m_rcxres);
			fprintf(savedata, "%s%d\n", "The number of pixels along the Y direction is: ", m_rcyres);
			fprintf(savedata, "%s%lf\n", "The value of m_Real is: ", m_Real);
			fprintf(savedata, "%s%lf\n", "The value of m_Imaginary is: ", m_Imaginary);
			fprintf(savedata, "%s%lf\n", "The magnitude of the Complex number is: ", magnitude);
			fprintf(savedata, "%s%lf\n", "The phase of the Complex number is: ", Zphase);	

			if (tolower(m_scaleON) == 'o')
				fprintf(savedata, "%s\n", "The program keeps the PTF non-scaled");
			else if (tolower(m_scaleON) == 's')
				fprintf(savedata, "%s\n", "The program scales the PTF");

			fclose(savedata);

		} // save to log file (end)


		// call to the constructor 'Z' so to create
		// an object of type 'Z'. The data type of 'Z'
		// is 'ZTransform2019'
		ZTransform2019 Z(m_rcxres, m_rcyres);

		// the object of type 'Z' 
		// sends a message (invokes)
		// to the method 'allocateData()'
		Z.allocateData();

		/// read image file (begin)
		// declare a file pointer
		FILE* pf;

		// open the file containing the image to
		// process. The image to process is by the
		// name of the string contained by 'imageFileName'
		if ((pf = fopen(imageFileName, "rb")) == NULL)
		{
			// alert the user and save into the log file 
			// the event that the program cannot open the 
			// file containing the image to process
			std::cout << "Cannot open file: " << imageFileName << endl;
			exit(0);

		}
		else { // else

			double number;

			for (int i1 = 0; i1 < m_rcyres; i1++) {// x dim

				for (int i2 = 0; i2 < m_rcxres; i2++) { // y dim

				// at each iteration of the two for loops
				// the program reads the pixel value from the
				// file containing the image and 
				fread(&number, sizeof(double), 1, pf);

					// assigns the pixel value 'number' to the
					// pixel value 'Z.pointer->Signal[i1][i2]'
					// where 'Z' invokes the pointer to the 
					// image 'Signal' at the matrix location '[i1][i2]'
					Z.pointer->Signal[i1][i2] = (double)number;

				} // y dim

			}  // x dim 

			// close the file containg the image to process 	
			fclose(pf);


		} // else 
		/// read image file (end)

		std::cout << "Image data loaded" << endl;

		// save all of the images
		// the object 'Z' invokes (sends a message)
		// the method by the name of 'save()'
		Z.save();


		std::cout << "Now calculating the Direct Z Transform of the Image..." << endl;
		OnZTransform(imageFileName, m_rcxres, m_rcyres, m_Real, m_Imaginary);

		std::cout << "Now calculating the ICF..." << endl;
		runSRE2D(imageFileName, m_rcxres, m_rcyres);
		
		sprintf(icfimageName, "%s", "ICF_SRE2D.img");
		std::cout << "Now calculating the Direct Z Transform of ICF..." << endl;
		OnZTransform(icfimageName, m_rcxres, m_rcyres, m_Real, m_Imaginary);

		std::cout << "Now calculating the Transfer Function..." << endl;
		OnInverseZTransformSamplePTF(imageFileName, m_rcxres, m_rcyres, m_Real, m_Imaginary, m_scaleON);
	
		sprintf(tfimageName, "%s", "TF.img");
		std::cout << "Now calculating the Direct Z Transform of the Transfer Function..." << endl;
		OnZTransform(tfimageName, m_rcxres, m_rcyres, m_Real, m_Imaginary);

		std::cout << "Now calculating the Inverse Z Transform to reconstruct the Images..." << endl;
		OnInverseZTransformReconstruct(imageFileName, m_rcxres, m_rcyres, m_Real, m_Imaginary);

		
		// alert the user of the end of the program
		std::cout << "End of Computation..." << endl;
		std::cout << endl;

		// delete the memory address
		// allocated to the images
		// do this by the command 'delete'
		// applied to the object 'Z' which
		// invokes the pointer to the data
		// structure 'data' containing the image
		// 'Signal'
		delete Z.pointer;

		// the object 'Z' invokes the
		// class destructor
		Z.~ZTransform2019();

	} // run the program (end)

	return 0;
} // end of main 

void OnZTransform(char imageFilename[], int rcxres, int rcyres, double m_Real, double m_Imaginary)
{

	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp;
	int k2, k3, w, t;

	double pi = 3.141592;

	double* ZSpaceR = 0;
	double* ZSpaceI = 0;
	double* Signal = 0;

	FILE* logfile;

	char logfilename[128] = "Z-T.log";

	if ((logfile = fopen(logfilename, "w+")) == NULL)
	{

		printf("%s\n %s\n", "Unable to open log File", "Now Exit");

		exit(0);

	}
	else { // allocate memory 


		if ((ZSpaceR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			exit(0);

		}

		if ((ZSpaceI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			exit(0);

		}

		if ((Signal = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			free(ZSpaceI);
			exit(0);

		}

	} // allocate memory 

	//// read image data and initialize pointers
	double number = 0.0;

	for (i = 0; i < NofYpixels; i++)
	{
		for (j = 0; j < NofXpixels; j++)
		{

			index = ((j * NofYpixels) + i);

			*(ZSpaceR + index) = (double)0.0;

			*(ZSpaceI + index) = (double)0.0;

		}

	}

	FILE* pf;
	char SignalFilename[128];
	double readData;

	sprintf(SignalFilename, "%s", imageFilename);

	if ((pf = fopen(SignalFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to read Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // read data


		for (i = 0; i < rcyres; i++)
		{ ///read signal data
			for (j = 0; j < rcxres; j++)
			{

				index = ((j * rcyres) + i);

				fread(&readData, sizeof(double), 1, pf);

				*(Signal + index) = (double)readData;

			}
		} ///read signal data

		fprintf(logfile, "%s\n", "Signal Read in DOUBLE (64bits) format");

		fclose(pf);
	} // save data

	double phase;
	double exponent, r;
	double complexRZ, complexIZ;

	double magnitude = (double)sqrt((double)m_Real * m_Real + (double)m_Imaginary * m_Imaginary);
	double Zphase = (double)2.0 * pi * atan2((double)m_Imaginary, (double)m_Real) / ((double)NofXpixels * NofYpixels);

	///// Z Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///calculate Z-Space data

		for (j = 0; j < NofXpixels; j++)
		{


			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy * NofYpixels) + dx);

			w = ((j * NofYpixels) + i);

			for (int s = 0; s < NofYpixels; s++)
			{ ///calculate Z-Space data 
				for (int p = 0; p < NofXpixels; p++)
				{


					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds * NofXpixels) + dp);

					t = ((p * NofYpixels) + s);


					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels * NofYpixels));

					exponent = (double)2.0 * pi * t * (double)Zphase / ((double)pow((double)NofXpixels * NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double)pow((double)magnitude, -(double)exponent);


					complexRZ = (double)cos((double)phase) + (double)sin((double)phase);

					complexIZ = -(double)sin((double)phase) + (double)cos((double)phase);


					*(ZSpaceR + w) += (double)*(Signal + t) * (double)complexRZ * (double)r;

					*(ZSpaceI + w) += (double)*(Signal + t) * (double)complexIZ * (double)r;
				}

			}///calculate Z-Space data 


		}
	} ///calculate Z-Space data
	///// Z Transform //////

	double savedata = 0.0;
	char Zfilename[128];

	sprintf(Zfilename, "%s%s", "Z-SpaceR-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Real) in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");


		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				savedata = (double)*(ZSpaceR + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Z-Space Signal (Real) Saved");

		fclose(pf);
	} // save data



	sprintf(Zfilename, "%s%s", "Z-SpaceI-", imageFilename);

	fprintf(logfile, "%s\t%s\n", "Now Saving Z-Space Signal (Imaginary) in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save Z-Space Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				savedata = (double)*(ZSpaceI + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Z-Space Signal (Imaginary) Saved");

		fclose(pf);

	} // save data

	sprintf(Zfilename, "%s%s", "Z-SpaceM-", imageFilename);

	fprintf_s(logfile, "%s\t%s\n", "Now Saving Z-Space Magnitude of the Signal in File: ", Zfilename);

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data	

	 // save a zero image (begin)
		for (int s = 0; s < NofYpixels; s++)
		{
			for (int p = 0; p < NofXpixels; p++)
			{

				savedata = (double)0.0;

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} // save a zero image (end)

		fclose(pf);

	}

	if ((pf = fopen(Zfilename, "wb+")) == NULL)
	{

		fprintf_s(logfile, "%s\n", "Cannot open file to save Z-Space Magnitude of the Signal");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(Signal);

		exit(0);

	}
	else { // save data

	    // Z-Space Magnitude (begin)
		for (int s = 0; s < (int)NofYpixels; s++)
		{
			for (int p = 0; p < (int)NofXpixels; p++)
			{


				index = ((p * NofYpixels) + s);

				savedata = (double)sqrt((double)*(ZSpaceR + index) * (double)*(ZSpaceR + index) +
					                    (double)*(ZSpaceI + index) * (double)*(ZSpaceI + index));

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} // Z-Space Magnitude (end)

		fprintf_s(logfile, "%s\n", "Z-Space Magnitude of the Signal Saved");

		fclose(pf);
	} // save data

	printf("%s\n", "Z Processing Completed");
	fprintf_s(logfile, "%s\n", "Z Processing Completed");

	fclose(logfile);


	// FIFO memory deallocation method
	free(ZSpaceR);
	free(ZSpaceI);
	free(Signal);

}

void runSRE2D(char imageFileName[], int xd, int yd)
{

	int n1 = xd;
	int n2 = yd;

	double XPixelSize = 1.0;
	double YPixelSize = 1.0;

	double x_misplacement_X = 0.5;
	double y_misplacement_Y = 0.5;

	double theta = 0.0;
	
	double misplacement_X = ((double)1.0 - (cos((double)theta) + sin((double)theta)) + x_misplacement_X);
	double misplacement_Y = ((double)1.0 - (-sin((double)theta) + cos((double)theta)) + y_misplacement_Y);

	misplacement_X = ((double)misplacement_X / XPixelSize);
	misplacement_Y = ((double)misplacement_Y / YPixelSize);

	//////////////////***********//////////////////////
	// Above formula scales the misplacement to the  //
	// pixel size the same way the following formula //
	// would do: (min - misplacement)/(min - max)    //  
	//////////////////***********//////////////////////

	int PAD = 1;

	SRE2D2013 SRE(n1 + PAD * 2, n2 + PAD * 2);

	SRE.allocateData();

	/// read image file (begin)
	FILE* pf;

	if ((pf = fopen(imageFileName, "rb+")) == NULL)
	{

		std::cout << "Cannot open file: " << imageFileName << endl;
		exit(0);

	}
	else { // else

		double number;


		for (int v = PAD + 1; v < n2 + PAD + 1; v++) { // (a)

			for (int f = PAD + 1; f < n1 + PAD + 1; f++) { // (b)

				fread(&number, sizeof(double), 1, pf);

				SRE.pointer->fMRI[v][f] = (double)number;

			} // y dim

		}  // x dim 


		fclose(pf);


	} // else 
	/// read image file (end)


	double k = 0, s = 0;

	// calculate ICF (begin)
	for (int i1 = PAD + 2; i1 < n2 + PAD; i1++) { // (a)

		for (int i2 = PAD + 2; i2 < n1 + PAD; i2++) { // (b)

			k = (double)SRE.pointer->fMRI[i1][i2] * misplacement_X * misplacement_Y +
				(misplacement_X * misplacement_Y * misplacement_X / 2.0) *
				(SRE.pointer->fMRI[i1 + 1][i2] - SRE.pointer->fMRI[i1][i2]) +
				(misplacement_X * misplacement_Y * misplacement_Y / 2.0) *
				(SRE.pointer->fMRI[i1][i2 + 1] - SRE.pointer->fMRI[i1][i2]) +
				(misplacement_X * misplacement_X * misplacement_Y * misplacement_Y / 4.0) *
				(SRE.pointer->fMRI[i1 + 1][i2 + 1] + SRE.pointer->fMRI[i1][i2] - SRE.pointer->fMRI[i1 + 1][i2] - SRE.pointer->fMRI[i1][i2 + 1]);

			s = (double)SRE.pointer->fMRI[i1][i2] * misplacement_X * misplacement_Y;

			if ((double)s == 0.0 && (double)k == 0.0) SRE.pointer->ICF[i1][i2] = (double)1.0; // de l'Hopital

			else if ((double)s == 0.0 && (double)k != 0.0) SRE.pointer->ICF[i1][i2] = (double)0.0;

			else if ((double)s != 0.0 && (double)k == 0.0) SRE.pointer->ICF[i1][i2] = (double)0.0;

			else  if ((double)s != 0.0 && (double)k != 0.0) SRE.pointer->ICF[i1][i2] = (double)s / k;


		} // y dim

	}  // x dim

	std::cout << "Intensity-Curvature Functional Calculated" << endl;
	// calculate ICF(end)


	char outputFile[200];
	FILE* writeimage;

	sprintf(outputFile, "%s", "ICF_SRE2D.img");

	if ((writeimage = fopen(outputFile, "wb+")) == NULL)
	{

		std::cout << "Cannot open output file, Now Exit..." << endl;

	}
	else { // (save)


		for (int v = PAD + 1; v < n2 + PAD + 1; v++) { // (a)

			for (int f = PAD + 1; f < n1 + PAD + 1; f++) { // b

				if ((v == PAD + 1) && (f == PAD + 1))
				{

					 fwrite(&SRE.pointer->ICF[v+1][f+1], sizeof(double), 1, writeimage);

				} 

				if ( v == PAD + 1 )
				{

					 fwrite(&SRE.pointer->ICF[v+1][f], sizeof(double), 1, writeimage);

				} else if (v == n2 + PAD)
				{

					 fwrite(&SRE.pointer->ICF[v-1][f], sizeof(double), 1, writeimage);

				} else if (f == PAD + 1)
				{

					 fwrite(&SRE.pointer->ICF[v][f+1], sizeof(double), 1, writeimage);

				} else if (f == n1 + PAD)
				{

					 fwrite(&SRE.pointer->ICF[v][f-1], sizeof(double), 1, writeimage);

				}

				else fwrite(&SRE.pointer->ICF[v][f], sizeof(double), 1, writeimage);

			} // b

		} // (a)

		fclose(writeimage);

	} // (save)

	delete SRE.pointer;
	SRE.~SRE2D2013();

}

void OnInverseZTransformSamplePTF(char filename[], int rcxres, int rcyres, double m_Real, double m_Imaginary, char m_scaleON)
{

	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp;
	int k2, k3, w, t;

	double pi = 3.141592;

	double phase;

	//2010
	double emittingSource = 1.4145; // 2021
	double scale = ((double)rcxres * rcyres * emittingSource);
	//2010

	FILE* logfile;
	char logfilename[128] = "INV-ZT.log";

	FILE* image;
	char imageFilename[256];

	double* ZSpaceR = 0;
	double* ZSpaceI = 0;
	double* reconSignal = 0;
	double* ICFR = 0;
	double* ICFI = 0;

	if ((logfile = fopen(logfilename, "w+")) == NULL)
	{

		exit(0);

	}
	else { // allocate memory


		printf("%s\n", "Now INV Z Processing...");
		fprintf(logfile, "%s\n", "Now INV Z Processing...");

		if ((ZSpaceR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			exit(0);

		}

		if ((ZSpaceI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			exit(0);

		}


		if ((reconSignal = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Imaginary Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			free(ZSpaceI);

			exit(0);

		}

		if ((ICFR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			free(ZSpaceR);
			free(ZSpaceI);
			free(reconSignal);

			exit(0);

		}

		if ((ICFI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(ZSpaceR);
			free(ZSpaceI);
			free(reconSignal);
			free(ICFR);

			exit(0);

		}

	} // allocate memory


	//// read image data and initialize pointers
	sprintf(imageFilename, "%s%s", "Z-SpaceR-", filename);

	if ((image = fopen(imageFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(ICFR);
		free(ICFI);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(ZSpaceR + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers


	char imageFilename2[128];

	sprintf(imageFilename2, "%s%s", "Z-SpaceI-", filename);


	if ((image = fopen(imageFilename2, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename2);

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(ICFR);
		free(ICFI);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(ZSpaceI + index) = (double)number;

			}

		}

		fclose(image);


		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				*(reconSignal + index) = (double)0.0;

			}

		}


	}// read data and initialize pointers


	//// read image data and initialize pointers
	sprintf(imageFilename, "%s", "Z-SpaceR-ICF_SRE2D.img");

	if ((image = fopen(imageFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(ICFR);
		free(ICFI);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(ICFR + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers

	//// read image data and initialize pointers
	sprintf(imageFilename, "%s", "Z-SpaceI-ICF_SRE2D.img");

	if ((image = fopen(imageFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(ICFR);
		free(ICFI);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(ICFI + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers

	double real = 0.0, imaginary = 0.0;
	double realICF = 0.0, imaginaryICF = 0.0;
	double realComponent = 0.0, imaginaryComponent = 0.0;
	double exponent, r;

	double magnitude = (double)sqrt((double)m_Real * m_Real + (double)m_Imaginary * m_Imaginary);
	double Zphase = (double)2.0 * pi * atan2((double)m_Imaginary, (double)m_Real) / ((double)NofXpixels * NofYpixels);

	///// INV Z Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///process Z-Space data

		for (j = 0; j < NofXpixels; j++)
		{

			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy * NofYpixels) + dx);

			w = ((j * NofYpixels) + i);

			real = (double)0.0;
			imaginary = (double)0.0;

			realICF = (double)0.0;
			imaginaryICF = (double)0.0;

			for (int s = 0; s < NofYpixels; s++)
			{ ///process Z-Space data

				for (int p = 0; p < NofXpixels; p++)
				{

					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds * NofXpixels) + dp);

					t = ((p * NofYpixels) + s);


					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels * NofYpixels));

					exponent = (double)2.0 * pi * t * (double)Zphase / ((double)pow((double)NofXpixels * NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double)pow((double)magnitude, (double)exponent);

					// calculate Pulse Transfer Function (begin)
					realICF += (((double)*(ICFR + t)) * (double)cos((double)phase)) -
						       (((double)*(ICFI + t)) * (double)sin((double)phase));

					real += (((double)*(ZSpaceR + t)) * (double)cos((double)phase)) -
						    (((double)*(ZSpaceI + t)) * (double)sin((double)phase));

					realICF *= (double)r;

					real *= (double)r;


				    imaginaryICF += (((double)*(ICFR + t)) * (double)sin((double)phase)) +
						            (((double)*(ICFI + t)) * (double)cos((double)phase));

					imaginary += (((double)*(ZSpaceR + t)) * (double)sin((double)phase)) +
						         (((double)*(ZSpaceI + t)) * (double)cos((double)phase));


					imaginaryICF *= (double)r;

					imaginary *= (double)r;
				    // calculate Pulse Transfer Function (end)

				}

			}///process Z-Space data 
			
			if ( ((double)real * real) != 0.0 )
			{

			realComponent = ((double)realICF * realICF) / ((double)real * real);

			if ((_isnan((double)realComponent)) == 0) {}

			else { realComponent = (double)0.0; }

			}
			else { realComponent = (double)0.0; }


			if ( ((double)imaginary * imaginary) != 0.0 )
			{

			imaginaryComponent = ((double)imaginaryICF * imaginaryICF) / ((double)imaginary * imaginary);

			if ((_isnan((double)imaginaryComponent)) == 0) {}

			else { imaginaryComponent = (double)0.0; }

			} 
			else { imaginaryComponent = (double)0.0; }


			*(reconSignal + w) = (double)sqrt(((double)realComponent) + ((double)imaginaryComponent));

			*(reconSignal + w) /= (double)scale;
			
		}
	} ///process Z-Space data


	double savedata = 0.0;
	FILE* pf;
	char reconFilename[128];

	sprintf(reconFilename, "%s", "TF.img");

	fprintf(logfile, "%s\t%s\n", "Now Saving TF in File: ", reconFilename);

	if ((pf = fopen(reconFilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save TF");

		// FIFO memory deallocation method
		free(ZSpaceR);
		free(ZSpaceI);
		free(reconSignal);
		free(ICFR);
		free(ICFI);

		exit(0);

	}
	else { // save data


		if (tolower(m_scaleON) == 's')
		{
			//// Procedure to scale (begin)
			double max = *(reconSignal);
			double min = *(reconSignal);

			for (i = 0; i < NofYpixels; i++)
			{ ///save Z-Space data
				for (j = 0; j < NofXpixels; j++)
				{

					index = ((j * NofYpixels) + i);

					if (*(reconSignal + index) > (double)max)

						max = (double)*(reconSignal + index);

					if (*(reconSignal + index) < (double)min)

						min = (double)*(reconSignal + index);

				} // y dim

			}  // x dim
			/// compute max and min of data (end)

			for (i = 0; i < NofYpixels; i++)
			{ ///save Z-Space data
				for (j = 0; j < NofXpixels; j++)
				{

					index = ((j * NofYpixels) + i);

					if (max == min) *(reconSignal + index) = (double)0.0;

					else {

						*(reconSignal + index) = (double)fabs((min - (double)*(reconSignal + index)) / (min - max));

						*(reconSignal + index) *= (double)1000.0;

						*(reconSignal + index) = ((double)1.0 - (double)exp(-(double)*(reconSignal + index))) /
							((double)1.0 + (double)exp(-(double)*(reconSignal + index)));

					}

				} // y dim

			}  // x dim
			//// Procedure to scale (end)
		}
		else { //do not scale 
		}
		
		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				savedata = (double)*(reconSignal + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "TF Saved");

		fclose(pf);
	} // save data


	printf("%s\n", "Inverse Z Processing Completed");
	fprintf(logfile, "%s\n", "Inverse Z Processing Completed");

	fclose(logfile);


	// FIFO memory deallocation method
	free(ZSpaceR);
	free(ZSpaceI);
	free(reconSignal);
	free(ICFR);
	free(ICFI);

}


void OnInverseZTransformReconstruct(char filename[], int rcxres, int rcyres, double m_Real, double m_Imaginary)
{

	int NofXpixels = rcxres;
	int NofYpixels = rcyres;

	int i, j, index;
	int dx, dy;
	int ds, dp;
	int k2, k3, w, t;

	double pi = 3.141592;

	double phase;

	//2010
	double emittingSource = 1.4145; // 2021
	double scale = ((double)rcxres * rcyres * emittingSource);
	//2010

	FILE* logfile;
	char logfilename[128] = "INV-ZT.log";

	FILE* image;
	char imageFilename[256];

	double* icfR = 0;
	double* icfI = 0;
	double* reconSignal = 0;
	double* tfR = 0;
	double* tfI = 0;
	double* mraR = 0;
	double* mraI = 0;
	double* reconICF = 0;

	if ((logfile = fopen(logfilename, "w+")) == NULL)
	{

		exit(0);

	}
	else { // allocate memory


		printf("%s\n", "Now INV Z Processing...");
		fprintf(logfile, "%s\n", "Now INV Z Processing...");

		if ((icfR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			exit(0);

		}

		if ((icfI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(icfR);
			exit(0);

		}


		if ((reconSignal = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Imaginary Image data: Exit");

			// FIFO memory deallocation method
			free(icfR);
			free(icfI);

			exit(0);

		}

		if ((tfR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			free(icfR);
			free(icfI);
			free(reconSignal);

			exit(0);

		}

		if ((tfI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(icfR);
			free(icfI);
			free(reconSignal);
			free(tfR);

			exit(0);

		}


		if ((mraR = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			free(icfR);
			free(icfI);
			free(reconSignal);
			free(tfR);
			free(tfI);
			exit(0);

		}

		if ((mraI = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Real Image data: Exit");

			// FIFO memory deallocation method
			free(icfR);
			free(icfI);
			free(reconSignal);
			free(tfR);
			free(tfI);
			free(mraR);
			exit(0);

		}

		if ((reconICF = (double*)calloc(NofXpixels * NofYpixels, sizeof(double))) == NULL)
		{

			fprintf(logfile, "%s\n", "Not enough memory to allocate Imaginary Image data: Exit");

			// FIFO memory deallocation method
			free(icfR);
			free(icfI);
			free(reconSignal);
			free(tfR);
			free(tfI);
			free(mraR);
			free(mraI);
			exit(0);

		}
	} // allocate memory

	char imageFilename2[128];

	//// read image data and initialize pointers
	sprintf(imageFilename2, "%s", "Z-SpaceR-ICF_SRE2D.img");

	if ((image = fopen(imageFilename2, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);
		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(icfR + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers

	sprintf(imageFilename2, "%s", "Z-SpaceI-ICF_SRE2D.img");

	if ((image = fopen(imageFilename2, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename2);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(icfI + index) = (double)number;

			}

		}

		fclose(image);

	}


	//// read image data and initialize pointers
	sprintf(imageFilename2, "%s%s", "Z-SpaceR-", filename);

	if ((image = fopen(imageFilename2, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(mraR + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers

	sprintf(imageFilename2, "%s%s", "Z-SpaceI-", filename);

	if ((image = fopen(imageFilename2, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename2);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(mraI + index) = (double)number;

			}

		}

		fclose(image);

	}

	for (i = 0; i < NofYpixels; i++)
	{
		for (j = 0; j < NofXpixels; j++)
		{

			index = ((j * NofYpixels) + i);

			*(reconSignal + index) = (double)0.0;

		}


	}// read data and initialize pointers

	for (i = 0; i < NofYpixels; i++)
	{
		for (j = 0; j < NofXpixels; j++)
		{

			index = ((j * NofYpixels) + i);

			*(reconICF + index) = (double)0.0;

		}


	}// read data and initialize pointers

	//// read image data and initialize pointers
	sprintf(imageFilename, "%s", "Z-SpaceR-TF.img");

	if ((image = fopen(imageFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(tfR + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers

	//// read image data and initialize pointers
	sprintf(imageFilename, "%s", "Z-SpaceI-TF.img");

	if ((image = fopen(imageFilename, "rb+")) == NULL)
	{

		fprintf(logfile, "%s%s\n", "Cannot open Image File: ", imageFilename);

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // read data and initialize pointers

		double number = 0.0;

		for (i = 0; i < NofYpixels; i++)
		{
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				fread(&number, sizeof(double), 1, image);

				*(tfI + index) = (double)number;


			}

		}

		fclose(image);

	}// read data and initialize pointers


	double realTF = 0.0, imaginaryTF = 0.0;
	double realICF = 0.0, imaginaryICF = 0.0;
	double realMRA = 0.0, imaginaryMRA = 0.0;
	double realComponent = 0.0, imaginaryComponent = 0.0;
	double exponent, r;

	double magnitude = (double)sqrt((double)m_Real * m_Real + (double)m_Imaginary * m_Imaginary);
	double Zphase = (double)2.0 * pi * atan2((double)m_Imaginary, (double)m_Real) / ((double)NofXpixels * NofYpixels);

	///// INV Z Transform //////
	for (i = 0; i < NofYpixels; i++)
	{ ///process Z-Space data

		for (j = 0; j < NofXpixels; j++)
		{

			dx = ((int)i - NofYpixels / 2);
			dy = ((int)j - NofXpixels / 2);

			k2 = ((int)(dy * NofYpixels) + dx);

			w = ((j * NofYpixels) + i);


			realTF = (double)0.0;
			imaginaryTF = (double)0.0;

			realICF = (double)0.0;
			imaginaryICF = (double)0.0;

			realMRA = (double)0.0;
			imaginaryMRA = (double)0.0;

			for (int s = 0; s < NofYpixels; s++)
			{ ///process Z-Space data

				for (int p = 0; p < NofXpixels; p++)
				{

					ds = ((int)s - NofYpixels / 2);
					dp = ((int)p - NofXpixels / 2);

					k3 = ((int)(ds * NofXpixels) + dp);

					t = ((p * NofYpixels) + s);


					phase = ((double)(2.0 * pi * k2 * k3) / ((double)NofXpixels * NofYpixels));

					exponent = (double)2.0 * pi * t * (double)Zphase / ((double)pow((double)NofXpixels * NofYpixels, 2.0));

					exponent = (double)fabs((double)exponent);

					r = (double)pow((double)magnitude, (double)exponent);

					// reconstruct Images (begin)
					realTF += (((double)*(tfR + t)) * (double)cos((double)phase)) -
						      (((double)*(tfI + t)) * (double)sin((double)phase));

					realICF += (((double)*(icfR + t)) * (double)cos((double)phase)) -
						       (((double)*(icfI + t)) * (double)sin((double)phase));

					realMRA += (((double)*(mraR + t)) * (double)cos((double)phase)) -
						       (((double)*(mraI + t)) * (double)sin((double)phase));

					realTF *= (double)r;

					realICF *= (double)r;

					realMRA *= (double)r;


					imaginaryTF += (((double)*(tfR + t)) * (double)sin((double)phase)) +
						           (((double)*(tfI + t)) * (double)cos((double)phase));

					imaginaryICF += (((double)*(icfR + t)) * (double)sin((double)phase)) +
						            (((double)*(icfI + t)) * (double)cos((double)phase));

					imaginaryMRA += (((double)*(mraR + t)) * (double)sin((double)phase)) +
						            (((double)*(mraI + t)) * (double)cos((double)phase));

					imaginaryTF *= (double)r;

					imaginaryICF *= (double)r;

					imaginaryMRA *= (double)r;
					// reconstruct Images (end)

				}

			}///process Z-Space data 

			// reconstruct MRA (begin)
			if (((double)realTF * realTF) != 0.0)
			{

				realComponent = ((double)realICF * realICF) / ((double)realTF * realTF);

				if ((_isnan((double)realComponent)) == 0) {}

				else { realComponent = (double)0.0; }

			}
			else { realComponent = (double)0.0; }

			if (((double)imaginaryTF * imaginaryTF) != 0.0)
			{

				imaginaryComponent = ((double)imaginaryICF * imaginaryICF) / ((double)imaginaryTF * imaginaryTF);

				if ((_isnan((double)imaginaryComponent)) == 0) {}

				else { imaginaryComponent = (double)0.0; }

			}
			else { imaginaryComponent = (double)0.0; }

			*(reconSignal + w) = (double)sqrt(((double)realComponent) + ((double)imaginaryComponent));

			*(reconSignal + w) /= (double)scale;
			// reconstruct MRA (end)


			// reconstruct ICF (begin)
			realComponent = ((double)realMRA * realMRA) * ((double)realTF * realTF);

			if ((_isnan((double)realComponent)) == 0) {}

			else { realComponent = (double)0.0; }


			imaginaryComponent = ((double)imaginaryMRA * imaginaryMRA) * ((double)imaginaryTF * imaginaryTF);

			if ((_isnan((double)imaginaryComponent)) == 0) {}

			else { imaginaryComponent = (double)0.0; }


			*(reconICF + w) = (double)sqrt(((double)realComponent) + ((double)imaginaryComponent));

			*(reconICF + w) /= (double)scale;
			// reconstruct ICF (end)

		}
	} ///process Z-Space data
	///// INV Z Transform //////


	double savedata = 0.0;
	FILE* pf;
	char reconFilename[128];

	sprintf(reconFilename, "%s%s", "recon-", filename);

	fprintf(logfile, "%s\t%s\n", "Now Saving reconstructed image in File: ", reconFilename);

	if ((pf = fopen(reconFilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save reconstructed image");

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				savedata = (double)*(reconSignal + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Reconstructed Image Saved");

		fclose(pf);
	} // save data


	sprintf(reconFilename, "%s", "recon-SRE2D-ICF.img");

	fprintf(logfile, "%s\t%s\n", "Now Saving reconstructed image in File: ", reconFilename);

	if ((pf = fopen(reconFilename, "wb+")) == NULL)
	{

		fprintf(logfile, "%s\n", "Cannot open file to save reconstructed image");

		// FIFO memory deallocation method
		free(icfR);
		free(icfI);
		free(reconSignal);
		free(tfR);
		free(tfI);
		free(mraR);
		free(mraI);
		free(reconICF);

		exit(0);

	}
	else { // save data


		for (i = 0; i < NofYpixels; i++)
		{ ///save Z-Space data
			for (j = 0; j < NofXpixels; j++)
			{

				index = ((j * NofYpixels) + i);

				savedata = (double)*(reconICF + index);

				fwrite(&savedata, sizeof(double), 1, pf);

			}
		} ///save Z-Space data

		fprintf(logfile, "%s\n", "Reconstructed ICF Image Saved");

		fclose(pf);
	} // save data


	printf("%s\n", "Inverse Z Processing Completed");
	fprintf(logfile, "%s\n", "Inverse Z Processing Completed");

	fclose(logfile);


	// FIFO memory deallocation method
	free(icfR);
	free(icfI);
	free(reconSignal);
	free(tfR);
	free(tfI);
	free(mraR);
	free(mraI);
	free(reconICF);

}