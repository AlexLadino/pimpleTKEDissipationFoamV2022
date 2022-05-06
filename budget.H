      Info<< "Calculando UPrime" << nl << endl;
      UPrime = U - UMean;
      Info<< "Calculando gradUPrime" << nl << endl;      
      gradUPrime = fvc::grad(UPrime);
      Info<< "Calculando pPrime" << nl << endl;      
      pPrime = p - pMean;
      // TKE instantanea
      Info<< "Calculando k" << nl << endl;      
      k = 0.5*magSqr(UPrime);
      // Info<< "Calculando kMean" << nl << endl;      
      // kMean = 0.5*tr(UPrime2Mean);
 
      // TKE Budget terms
      // convectionTKE (hacer fieldAverage convectionTKEMean)
      Info<< "Calculando convectionTKE" << nl << endl;
      convectionTKE = -UMean & fvc::grad(k);
      // Production (se calcula en fase de postProcesamiento)
            // prodTKEMean = -UPrime2Mean && fvc::grad(UMean);
      // viscous dissipation (hacer fieldAverage dissipationTKEMean)
      Info<< "Calculando dissipationTKE" << nl << endl;      
      dissipationTKE = -turbulence->nuEff()*tr(gradUPrime & gradUPrime.T());
      // transport Viscous Diffusion (se calcula en fase de postProcesamiento)
            // viscousDiffusionTKEMean = turbulence->nuEff()*fvc::laplacian(kMean); 
      // Transport Velocity-Pressure Gradient 
      // 1. hacer fieldAverage pressureDiffusionTKEFieldMean
      // 2. en fase de postProcesamiento hacer -div(pressureDiffusionTKEFieldMean);
      Info<< "Calculando pressureDiffusionTKEField" << nl << endl;      
      pressureDiffusionTKEField = pPrime*UPrime;
      // Transport by turbulence
      // 1. hacer fieldAverage turbulenceTransportTKEFieldMean
      // 2. en fase de postProcesamiento hacer -div(turbulenceTransportTKEFieldMean);
      Info<< "Calculando turbulenceTransportTKEField" << nl << endl;      
      turbulenceTransportTKEField = k*UPrime;


