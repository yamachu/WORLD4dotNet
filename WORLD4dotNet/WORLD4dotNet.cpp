// これは メイン DLL ファイルです。

#include "stdafx.h"

#include "WORLD4dotNet.h"
#include <memory.h>
#include <malloc.h>

// 2D-arrays idea is here
// http://stackoverflow.com/a/26717663

void WORLD4dotNet::Core::WORLD::CheapTrick(array<Double>^ x, int x_length, int fs,
	array<Double>^ time_axis, array<Double>^ f0, int f0_length,
	Options::CheapTrickOption % option, array<Double, 2>^ spectrogram)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_spectrogram = &spectrogram[0, 0];

	IntPtr ptr_option = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	Marshal::StructureToPtr(option, ptr_option,false);

	// Cast to 2D-array
	int dimOuter = spectrogram->GetLength(0);
	int dimInner = spectrogram->GetLength(1);
	double **ptr_spec = (double**)alloca(sizeof(double*) * dimOuter);
	double *tmpPtr = ptr_spectrogram;

	for (int i = 0; i < dimOuter; i++) {
		ptr_spec[i] = tmpPtr;
		tmpPtr += dimInner;
	}

	::CheapTrick(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, (CheapTrickOption*)ptr_option.ToPointer(), ptr_spec);

	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_spectrogram = nullptr;
	Marshal::FreeHGlobal(ptr_option);
}

void WORLD4dotNet::Core::WORLD::InitializeCheapTrickOption(Options::CheapTrickOption % option)
{
	CheapTrickOption tmpOption;
	::InitializeCheapTrickOption(&tmpOption);
	IntPtr tmpPtr = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	option = (Options::CheapTrickOption)Marshal::PtrToStructure(IntPtr(&tmpOption), option.GetType());
}

int  WORLD4dotNet::Core::WORLD::GetFFTSizeForCheapTrick(int fs, const Options::CheapTrickOption % option)
{
	IntPtr ptr_option = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	Marshal::StructureToPtr(option, ptr_option, false);

	int fft_size = ::GetFFTSizeForCheapTrick(fs, (const CheapTrickOption*)ptr_option.ToPointer());
	Marshal::FreeHGlobal(ptr_option);
	return fft_size;
}

void WORLD4dotNet::Core::WORLD::D4C(array<Double>^ x, int x_length, int fs, 
	array<Double>^ time_axis, array<Double>^ f0, int f0_length, int fft_size,
	Options::D4COption % option, array<Double, 2>^ aperiodicity)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_aperiodicity = &aperiodicity[0, 0];

	IntPtr ptr_option = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	Marshal::StructureToPtr(option, ptr_option, false);

	// Cast to 2D-array
	int dimOuter = aperiodicity->GetLength(0);
	int dimInner = aperiodicity->GetLength(1);
	double **ptr_aperi = (double**)alloca(sizeof(double*) * dimOuter);
	double *tmpPtr = ptr_aperiodicity;

	for (int i = 0; i < dimOuter; i++) {
		ptr_aperi[i] = tmpPtr;
		tmpPtr += dimInner;
	}

	::D4C(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, fft_size, (D4COption*)ptr_option.ToPointer(), ptr_aperi);

	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_aperiodicity = nullptr;
	Marshal::FreeHGlobal(ptr_option);
}

void WORLD4dotNet::Core::WORLD::InitializeD4COption(Options::D4COption % option)
{
	D4COption tmpOption;
	::InitializeD4COption(&tmpOption);
	IntPtr tmpPtr = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	option = (Options::D4COption)Marshal::PtrToStructure(IntPtr(&tmpOption),option.GetType());
}

void WORLD4dotNet::Core::WORLD::Dio(array<Double>^ x, int x_length, int fs,
	Options::DioOption % option, array<Double>^ time_axis, array<Double>^ f0)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_f0 = &f0[0];

	IntPtr ptr_option = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	Marshal::StructureToPtr(option, ptr_option, false);

	::Dio(ptr_x, x_length, fs, (const DioOption*)ptr_option.ToPointer(), ptr_time_axis, ptr_f0);

	ptr_x = nullptr;
	ptr_time_axis = nullptr;
	ptr_f0 = nullptr;
	Marshal::FreeHGlobal(ptr_option);
}

void WORLD4dotNet::Core::WORLD::InitializeDioOption(Options::DioOption % option)
{
	DioOption tmpOption;
	::InitializeDioOption(&tmpOption);
	IntPtr tmpPtr = Marshal::AllocHGlobal(Marshal::SizeOf(option));
	option = (Options::DioOption)Marshal::PtrToStructure(IntPtr(&tmpOption), option.GetType());
}

int  WORLD4dotNet::Core::WORLD::GetSamplesForDIO(int fs, int x_length, double frame_period)
{
	return ::GetSamplesForDIO(fs, x_length, frame_period);
}

void WORLD4dotNet::Core::WORLD::StoneMask(array<Double>^ x, int x_length, int fs,
	array<Double>^ time_axis, array<Double>^ f0, int f0_length, array<Double>^ refined_f0)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_time_axis = &time_axis[0];
	pin_ptr<Double> ptr_refined_f0 = &refined_f0[0];
	::StoneMask(ptr_x, x_length, fs, ptr_time_axis, ptr_f0, f0_length, ptr_refined_f0);
	ptr_x = nullptr;
	ptr_f0 = nullptr;
	ptr_time_axis = nullptr;
	ptr_refined_f0 = nullptr;
}

void WORLD4dotNet::Core::WORLD::Synthesis(array<Double>^ f0, int f0_length,
	array<Double, 2>^ spectrogram, array<Double, 2>^ aperiodicity, int fft_size,
	double frame_period, int fs, int y_length, array<Double>^ y)
{
	pin_ptr<Double> ptr_f0 = &f0[0];
	pin_ptr<Double> ptr_y = &y[0];
	pin_ptr<Double> ptr_spectrogram = &spectrogram[0, 0];
	pin_ptr<Double> ptr_aperiodicity = &aperiodicity[0, 0];

	// Cast to 2D-array
	int dimSpecOuter = spectrogram->GetLength(0);
	int dimSpecInner = spectrogram->GetLength(1);
	int dimAperiOuter = aperiodicity->GetLength(0);
	int dimAperiInner = aperiodicity->GetLength(1);
	double **ptr_spec = (double**)alloca(sizeof(double*) * dimSpecOuter);
	double **ptr_aperi = (double**)alloca(sizeof(double*) * dimSpecOuter);
	double *tmpPtr = ptr_spectrogram;

	for (int i = 0; i < dimSpecOuter; i++) {
		ptr_spec[i] = tmpPtr;
		tmpPtr += dimSpecInner;
	}
	tmpPtr = ptr_aperiodicity;
	for (int i = 0; i < dimAperiOuter; i++) {
		ptr_aperi[i] = tmpPtr;
		tmpPtr += dimAperiInner;
	}

	::Synthesis(ptr_f0, f0_length, ptr_spec, ptr_aperi, fft_size, frame_period, fs, y_length, ptr_y);
	ptr_f0 = nullptr;
	ptr_y = nullptr;
	ptr_spectrogram = nullptr;
	ptr_aperiodicity = nullptr;
}

void WORLD4dotNet::Utils::FileIO::WavRead(String ^ filename, int % fs, int % nbit,
	array<Double>^ x)
{
	pin_ptr<int> ptr_fs = &fs;
	pin_ptr<int> ptr_nbit = &nbit;
	pin_ptr<Double> ptr_x = &x[0];

	char* ptr_filename = (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer();

	::wavread(ptr_filename, ptr_fs, ptr_nbit, ptr_x);
	ptr_fs = nullptr;
	ptr_nbit = nullptr;
	ptr_x = nullptr;
	Marshal::FreeHGlobal(IntPtr(ptr_filename));
}

void WORLD4dotNet::Utils::FileIO::WavWrite(array<double>^ x, int x_length, int fs,
	int nbit, String ^ filename)
{
	pin_ptr<Double> ptr_x = &x[0];
	char* ptr_filename = (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer();
	::wavwrite(ptr_x, x_length, fs, nbit, ptr_filename);
	Marshal::FreeHGlobal(IntPtr(ptr_filename));
	ptr_x = nullptr;
}

int WORLD4dotNet::Utils::FileIO::GetAudioLength(String ^ filename)
{
	char* ptr_filename = (char*)Marshal::StringToHGlobalAnsi(filename).ToPointer();
	int length = ::GetAudioLength(ptr_filename);
	Marshal::FreeHGlobal(IntPtr(ptr_filename));
	return length;
}

void WORLD4dotNet::Utils::MatlabFunctions::interp1(array<double>^ x, array<double>^ y, int x_length, array<double>^ xi, int xi_length, array<double>^ yi)
{
	pin_ptr<Double> ptr_x = &x[0];
	pin_ptr<Double> ptr_y = &y[0];
	pin_ptr<Double> ptr_xi = &xi[0];
	pin_ptr<Double> ptr_yi = &yi[0];
	::interp1(ptr_x, ptr_y, x_length, ptr_xi, xi_length, ptr_yi);
	ptr_x = nullptr;
	ptr_y = nullptr;
	ptr_xi = nullptr;
	ptr_yi = nullptr;
}
