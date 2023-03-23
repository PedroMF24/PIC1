#include <iostream>
#include <complex>
#include <functional>
#include <numeric>

#include "SM.h"

using namespace std;

// LEP analysis
/*
if (MA1 < 100.0 && MH20 < 80.0) {
      if (MA1 - MH20 >= 8.0) {
         icycle = 1;
         return;
      }
}*/

// DONE!
void InitMatrices(double ImVdagV[4][4], complex<double> UdagU[2][2], complex<double> VdagV[4][4], complex<double> UdagV[2][4]) {
    // Matrix UDagU
    // For the Inert 2HDM is the identity matrix in 2x2
	for (int j = 0; j < 2; j++) {
		for (int k = 0; k < 2; k++) {
			if (j == k) {
				UdagU[j][k] = 1.0;
			}
			else {
				UdagU[j][k] = 0.0;
			}
		}
	}

    // Matrix UDagV
    // 2x4 complex matrix
   for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
            UdagV[j][k] = 0.0;
      }
   }
   UdagV[0][0] = complex<double>(0.0, 1.0);
   UdagV[0][1] = 1.0;
   UdagV[0][2] = 0.0;
   UdagV[0][3] = 0.0;
   UdagV[1][0] = 0.0;
   UdagV[1][1] = 0.0;
   UdagV[1][2] = 1.0;
   UdagV[1][3] = complex<double>(0.0, 1.0);

   // Matrix ImVdagV
   // 4x4 real matrix
   // Set all the values to 0
   for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
            ImVdagV[i][j] = 0;
      }
   }
   // Set specific values
   ImVdagV[0][1] = -1;
   ImVdagV[1][0] = 1;
   ImVdagV[2][3] = 1;
   ImVdagV[3][2] = -1;

   // Matrix VdagV
   // 4x4 complex matrix
   // Set matrix to identity
   for (int j = 0; j < 4; j++) {
      for (int k = 0; k < 4; k++) {
            if (j == k) {
               VdagV[j][k] = 1.0;
            }
            else {
               VdagV[j][k] = 0.0;
            }
      }
   }
   VdagV[0][1] = complex<double>(0.0, -1.0);
   VdagV[1][0] = complex<double>(0.0, 1.0);
   VdagV[2][3] = complex<double>(0.0, 1.0);
   VdagV[3][2] = complex<double>(0.0, -1.0);
}

double STU(double MH10, double MH20, double MA1, double MC1)
{

   if (ST(MH10, MH20, MA1, MC1) == 1.0 && UU(MH10, MH20, MA1, MC1) == 1.0) 
   {
      return 1.0;
   }
   else 
   {
      return 0.0;
   }
}

struct data
{
      double g ; // gauge coupling parameter g = e = p4πα ∼ 0,30
      double alpha ; // the fine-structure constant e^2/4pi = g^2s^2_W/(4π) ~ 1/137 
      double G_F ; // Fermi constant G0_F = G_F/(hbar*c)^3 = https://en.wikipedia.org/wiki/Fermi%27s_interaction
      double mW = 80.385; 
      double mZ = 91.1875; 
      double thetaW ; // https://en.wikipedia.org/wiki/Weinberg_angle
      double mH = 125.14; 
      double GW ; 
      double GZ ; 
      double pi = 3.141592;
      int iboson;
};


double ST(double MH10, double MH20, double MA1, double MC1)
{
   data common;
   double mneu[4], mch[2], ImVdagV[4][4], S, T, U, Corr, a1, a2, a3, a4, a5, a6;
   complex<double> UdagU[2][2], UdagV[2][4], VdagV[4][4];
   
   common.g = 0.0;
   common.alpha = 0.0;
   common.G_F = 0.0;
   common.mW = 0.0; 
   common.mZ = 0.0; 
   common.thetaW = 0.0; 
   common.mH = 0.0; 
   common.GW = 0.0; 
   common.GZ = 0.0; 
   common.pi = 0.0; 
   common.iboson = 0;
   
   mneu[1] = common.mZ;
   mneu[2] = MH10;
   mneu[3] = MH20;
   mneu[4] = MA1;
   
   mch[1] = common.mW;
   mch[2] = MC1;
   
   Evaluate_Matrices(ImVdagV, UdagU, VdagV, UdagV);
   Calculate_STU(mneu, mch, ImVdagV, UdagU, VdagV, UdagV, S, T, U);
   
   // Data from 95% CL and Gfitter 2014
   // ArXiv 1407.3792
   a1 = -0.34215919;
   a2 = 0.77604111;
   a3 = -0.52618813;
   a4 = -0.03202802;
   a5 = 0.05277964;
   a6 = 0.00136192;
   
   Corr = (a1 * pow(S,2)) + (a2 * S * T) + (a3 * pow(T,2)) + (a4 * S) + (a5 * T) + a6;
   
   if (Corr > 0.0)
   {
      return 1.0;
   }
   else
   {
      return 0.0;
   }
}

double UU(double MH10, double MH20, double MA1, double MC1) {
      int j, k, iboson, nns, ncs;
      double g, alpha, G_F, mW, mZ, thetaW, GW, GZ, pi, mh;
      double ImVdagV[4][4];
      complex<double> UdagU[2][2], VdagV[4][4], UdagV[2][4];
      double mch[2], mneu[4], S, T, U, Corr, UUL, ULL;
      double a1, a2, a3, a4, a5, a6;
      double MH10, MH20, v, v1, v2, v3;

      nns=4;
      ncs=2;

      StandardModel model;
      
      mneu[1]= model.GetSMValue("MZ");
      mneu[2]=MH10;
      mneu[3]=MH20;
      mneu[4]=MA1;

      mch[2]=MC1;

      Evaluate_Matrices(ImVdagV,UdagU,VdagV,UdagV);
      
      Calculate_STU(mneu,mch,ImVdagV,UdagU,
                  VdagV,UdagV,S,T,U);

      ULL=0.03-0.10; // U lower limit
      UUL=0.03+0.10; // U upper limit

      if((U > ULL) && (U < UUL)) {
         return 1;
      } else {
         return 0;
      }
}

    // double M[2][2];
    // int k = 0;
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         M[i][j] = k;
    //         k++;
    //     }
    // }
    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 2; j++)
    //     {
    //         cout << M[i][j];
    //     }
    //     cout << endl;
    // }



void Evaluate_Matrices(double ImVdagV[4][4], complex<double> UdagU[2][2], complex<double> VdagV[4][4], complex<double> UdagV[2][4]);


// C++
void Calculate_STU(double mneu[4], double mch[2], double ImVdagV[4][4], 
      complex<double> UdagU[2][2], complex<double> VdagV[4][4], 
      complex<double> UdagV[2][4], double& S, double& T, double& U) {

   int j, k;
   int nns = 4;
   int ncs = 2;
   double mW2, mZ2, mh2, z[nns], w[nns], zp[ncs], wp[ncs], wH, zH;
   double sw2, cw2;
   double g, alpha, G_F, mW, mZ, thetaW, mH, GW, GZ, pi;
   // double model.Gstu, model.model.Ghatstu, model.Fbigstu;

   StandardModel model;

// Common block data
   mW = model.GetSMValue("MW");
   G_F = model.GetSMValue("G_FERMI");
   g = sqrt(8.0 * mW * mW * G_F / sqrt(2.0)); 
   alpha = model.GetSMValue("ALPHA"); 
   mZ = model.GetSMValue("MZ"); 
   thetaW = asin(sqrt(model.GetSMValue("S2TW")));
   mH = model.GetSMValue("MHIGGS"); 
   GW = model.GetSMValue("GAW"); // 
   GZ = model.GetSMValue("GAZ"); 
   pi = acos(-1);
   // int iboson = data[10];

   mW2 = mW * mW;
   mZ2 = mZ * mZ;
   mh2 = mH * mH;
   sw2 = sin(thetaW) * sin(thetaW);
   cw2 = cos(thetaW) * cos(thetaW);

   for (j = 0; j < nns; ++j)
   {
      z[j] = pow(mneu[j], 2) / mZ2;
      w[j] = pow(mneu[j], 2) / mW2;
   }

   for (j = 0; j < ncs; ++j)
   {
      zp[j] = pow(mch[j], 2) / mZ2;
      wp[j] = pow(mch[j], 2) / mW2;
   }

   zH = pow(mH, 2) / mZ2;
   wH = pow(mH, 2) / mW2;

// Evaluate T from the formulas in arXiv: 0802.4353
   T = 0.0;

   for (j = 1; j < ncs; ++j)
   {
      for (k = 1; k < nns; ++k)
      {
         T += pow(abs(UdagV[j][k]), 2) * model.Fbigstu(pow(mch[j], 2), pow(mneu[k], 2));
      }
   }

   for (j = 1; j < nns - 1; ++j)
   {
      for (k = j + 1; k < nns; ++k)
      {
         T -= pow(ImVdagV[j][k], 2) * model.Fbigstu(pow(mneu[j], 2), pow(mneu[k], 2));
      }
   }

   for (j = 1; j < ncs - 1; ++j)
   {
      for (k = j + 1; k < ncs; ++k)
      {
         T -= 2.0 * pow(abs(UdagU[j][k]), 2) * model.Fbigstu(pow(mch[j], 2), pow(mch[k], 2));
      }
   }

   for (j = 1; j < nns; ++j)
   {
      T += 3.0 * pow(ImVdagV[0][j], 2) * (model.Fbigstu(mZ2, pow(mneu[j], 2)) - model.Fbigstu(mW2, pow(mneu[j], 2)));
   }

   T -= 3.0 * (model.Fbigstu(mZ2, mh2) - model.Fbigstu(mW2, mh2));

   T *= (1.0 / (16.0 * pi * sw2 * mW2)); // sw? g^2/64pi^2?

// Evaluate S from the formulas in arXiv: 0802.4353
   S = 0.0;

   for (j = 1; j < ncs; ++j)
   {
      S += pow(2.0 * sw2 - real(UdagU[j][j]), 2) * model.Gstu(zp[j], zp[j]);
   }

   for (j = 1; j < ncs - 1; ++j)
   {
      for (k = j + 1; k < ncs; ++k)
      {
         S += 2.0 * pow(abs(UdagU[j][k]), 2) * model.Gstu(zp[j], zp[k]);
      }
   }

   for (j = 1; j < nns - 1; ++j)
   {
      for (k = j + 1; k < nns; ++k)
      {
         S += pow(ImVdagV[j][k], 2) * model.Gstu(z[j], z[k]);
      }
   }

   for (j = 1; j < ncs; ++j)
   {
      S -= 2.0 * real(UdagU[j][j]) * log(pow(mch[j], 2));
   }

   for (j = 1; j < nns; ++j)
   {
      S += real(VdagV[j][j]) * log(pow(mneu[j], 2));
      S += pow(ImVdagV[0][j], 2) * model.Ghatstu(z[j]);
   }

   S -= model.Ghatstu(zH) + log(pow(mH, 2));

   S *= 1/(24*M_PI); // S *= (1.0 / (24.0 * pi * sw2));

// Evaluate U from the formulas in arXiv: 0802.4353
   U = 0.0;

for (int j = 1; j < ncs; ++j) 
{
   for (int k = 1; k < nns; ++k) 
   {
      U += pow(abs(UdagV[j][k]), 2) * model.Gstu(wp[j], w[k]);
   }
}

for (int j = 1; j < ncs; ++j) 
{
   U -= pow((2.0 * sw2 - real(UdagU[j][j])), 2) * model.Gstu(zp[j], zp[j]);
}

for (int j = 1; j < ncs - 1; ++j) 
{
   for (int k = j + 1; k < ncs; ++k) 
   {
      U -= 2.0 * pow(abs(UdagU[j][k]), 2) * model.Gstu(zp[j], zp[k]);
   }
}

for (int j = 1; j < nns - 1; ++j) 
{
   for (int k = j + 1; k < nns; ++k) 
   {
      U -= pow(ImVdagV[j][k], 2) * model.Gstu(z[j], z[k]);
   }
}

for (int j = 1; j < nns; ++j) {
  U += pow(ImVdagV[1][j], 2) * (model.Ghatstu(w[j]) - model.Ghatstu(z[j]));
}

U -= model.Ghatstu(wH) + model.Ghatstu(zH);
U *= (1.0 / (24.0 * M_PI));

// =======================================================0

   // for (j = 1; j < ncs; ++j)
   // {
   //    for (k = 1; k < nns; ++k)
   //    {
   //       U += pow(abs(UdagV[j][k]), 2) * model.Gstu(zp[j], z[k]);
   //    }
   // }

   // for (j = 1; j < ncs - 1; ++j)
   // {
   //    for (k = j + 1; k < ncs; ++k)
   //    {
   //       U += 2.0 * pow(abs(UdagU[j][k]), 2) * model.Gstu(zp[j], zp[k]);
   //    }
   // }

   // for (j = 1; j < nns - 1; ++j)
   // {
   //    for (k = j + 1; k < nns; ++k)
   //    {
   //       U -= 2.0 * pow(ImVdagV[j][k], 2) * model.Gstu(z[j], z[k]);
   //    }
   // }

   // for (j = 1; j < ncs; ++j)
   // {
   //    U += real(UdagU[j][j]) * model.model.Ghatstu(zp[j]);
   // }

   // for (j = 1; j < nns; ++j)
   // {
   //    U -= real(VdagV[j][j]) * model.model.Ghatstu(z[j]);
   //    U -= pow(ImVdagV[0][j], 2) * model.Fbigstu(mW2, pow(mneu[j], 2));
   // }

   // U += model.model.Ghatstu(zH) - model.Fbigstu(mW2, mh2);

   // U *= (1.0 / (24.0 * pi * sw2));

   // Convert to the electroweak oblique parameters

   // S = 4.0 * pi * (S - alpha / (4.0 * sw2));
   // T = 4.0 * pi * T;
   // U = 4.0 * pi * U;
}

void CheckSTU(double S, double T, double U) {
   const double Shat = 0.05;
   const double That = 0.09;
   const double Uhat = 0.01;

   double xSTU[3] = {S - Shat, T - That, U - Uhat};
   double aux_arr[3];
   double ChiSqSTU = 0;

   /*
    * 
   */

   const double C_Inverse[3][3] = {{836.17, -952.128, -445.745},
                        {-952.128, 1276.6, 696.809},
                        {-445.745, 696.809, 506.383}};

   // Product of matrices
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         aux_arr[i] = C_Inverse[i][j] * xSTU[j];
      }
      ChiSqSTU += aux_arr[i] * xSTU[i];
   }

   // Inner product function does it better!
   /*
   * The arguments for the std::inner_product function are as follows:
   * 1. The first two arguments are the two vectors (or arrays) to be multiplied.
   * 2. The third argument is the matrix (or array) to be multiplied by the vectors.
   * 3. The fourth argument is the initial value of the dot product (default is 0.0).
   */
   ChiSqSTU = inner_product(xSTU, xSTU + 3, C_Inverse, 0.0);
   
   int check = (ChiSqSTU <= 8.025) ? 1 : 0;
}



void Model() {
// MH 2 [50; 800] GeV; (5.18)
// MA 2 [50; 800] GeV; (5.19)
// MH± 2 [70; 800] GeV; (5.20)
// λ2 2 [0:001; 8π] GeV; (5.21)
// λ345 2 [−2; 8π] GeV: (5.22)

/*
   BFB // Done
   Perturbative Uni // Done
   Global Minimum // Done

   SM Higgs mass // Done
   SM Higgs width // NOPE
   STU // Doing
   Charged Scalar Mass (setup) // Done
   Charged scalar life time // Not done
   Beyond SM physics (HB, Exclude region) // Not done
   Relic density // Not done
*/
}