// WORLD4dotNet.h

#pragma once
#include "WORLD\cheaptrick.h"
#include "WORLD\d4c.h"
#include "WORLD\dio.h"
#include "WORLD\stonemask.h"
#include "WORLD\synthesis.h"
#include "WORLD\matlabfunctions.h"

using namespace System;
using namespace System::Runtime::InteropServices;

namespace WORLD4dotNet {
	namespace Options {
		[StructLayout(LayoutKind::Sequential)]
		public value struct DioOption
		{
			double f0_floor;
			double f0_ceil;
			double channels_in_octave;
			double frame_period;
			int speed;
			double allowed_range;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value struct CheapTrickOption {
			double q1;
		};

		[StructLayout(LayoutKind::Sequential)]
		public value struct D4COption {
			double dummy;
		};
	}

	namespace Core {
		public ref class WORLD
		{
			// TODO: このクラスの、ユーザーのメソッドをここに追加してください。
		public:
			// CheapTrick
			static void CheapTrick(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
				int f0_length, Options::CheapTrickOption % option, array<Double, 2> ^spectrogram);
			static void InitializeCheapTrickOption([Out]Options::CheapTrickOption %option);
			static int GetFFTSizeForCheapTrick(int fs);

			// D4C
			static void D4C(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
				int f0_length, int fft_size, Options::D4COption % option, array<Double, 2> ^aperiodicity);
			static void InitializeD4COption([Out]Options::D4COption %option);

			// DIO
			static void Dio(array<Double> ^x, int x_length, int fs, Options::DioOption % option,
				array<Double> ^time_axis, array<Double> ^f0);
			static void InitializeDioOption([Out]Options::DioOption % option);
			static int GetSamplesForDIO(int fs, int x_length, double frame_period);

			// StoneMask
			static void StoneMask(array<Double> ^x, int x_length, int fs, array<Double> ^time_axis, array<Double> ^f0,
				int f0_length, array<Double> ^refined_f0);

			// Synthesis
			static void Synthesis(array<Double> ^f0, int f0_length, array<Double, 2> ^spectrogram,
				array<Double, 2> ^aperiodicity, int fft_size, double frame_period, int fs,
				int y_length, array<Double> ^y);			
		};
	}

	namespace Utils {
		public ref class FileIO
		{
		public:
			// matlabfunction
			static void WavRead(String^ filename, [Out]int %fs, [Out]int %nbit, [Out]int %wav_length,
				[Out]array<Double> ^%wav_form);
			static void WavWrite(array<double> ^x, int x_length, int fs, int nbit, String ^filename);
		};
		public ref class MatlabFunctions
		{
		public:
			static void interp1(array<double> ^x, array<double> ^y, int x_length, array<double> ^xi, int xi_length,
				array<double> ^yi);
		};
	}


}
