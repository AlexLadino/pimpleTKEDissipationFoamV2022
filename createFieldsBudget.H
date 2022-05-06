/*
UPrime = U - UMean;
pPrime = p - pMean;
// TKE instantanea
k = 0.5*magSqr(UPrime);
kMean = 0.5*tr(UPrime2Mean);
// TKE Budget terms
// convectionTKE (hacer fieldAverage convectionTKEMean)
convectionTKE = -UMean & fvc::grad(k);
// Production (se calcula en fase de postProcesamiento)
prodTKEMean = -UPrime2Mean && fvc::grad(UMean);
// viscous dissipation (hacer fieldAverage dissipationTKEMean)
dissipationTKE = -turbulence->nuEff()*tr(grad(UPrime)&grad(UPrime).T());
// transport Viscous Diffusion (en fase de postProcesamiento)
viscousDiffusionTKEMean = turbulence->nuEff()*fvc::laplacian(kMean); 
// Transport Velocity-Pressure Gradient 
// 1. hacer fieldAverage pressureDiffusionTKEFieldMean
// 2. en fase de postProcesamiento hacer -div(pressureDiffusionTKEFieldMean);
pressureDiffusionTKEField = pPrime*UPrime;
// Transport by turbulence
// 1. hacer fieldAverage turbulenceTransportTKEFieldMean
// 2. en fase de postProcesamiento hacer -div(turbulenceTransportTKEFieldMean);
turbulenceTransportTKEField = k*UPrime;
*/

Info<< "Reading field UMean\n" << endl;
volVectorField UMean
(
    IOobject
    (
        "UMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

Info<< "Reading field pMean\n" << endl;
volScalarField pMean
(
    IOobject
    (
        "pMean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

Info<< "Reading field UPrime2Mean\n" << endl;
volSymmTensorField UPrime2Mean
(
    IOobject
    (
        "UPrime2Mean",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    ),
    mesh
);

volVectorField UPrime
(
    IOobject
    (
        "UPrime",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,   
      dimensionedVector
      (
           "UPrime", 
           dimVelocity,
           vector(0.0,0.0,0.0)
      )
);

/*
volTensorField gradUPrime
(
    IOobject
    (
        "gradUPrime",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,   
      dimensionedVector
      (
           "gradUPrime", 
           dimVelocity/dimLength,
           tensor(0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0)
      )
);
*/

volTensorField gradUPrime(fvc::grad(UPrime));

volScalarField pPrime
(
    IOobject
    (
        "pPrime",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    
      dimensionedScalar
      (
           "pPrime", 
           dimVelocity*dimVelocity,
           0.0
      )
);

volScalarField k
(
    IOobject
    (
        "k",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    
      dimensionedScalar
      (
           "k", 
           dimVelocity*dimVelocity,
           0.0
      )
);

/*
volScalarField kMean
(
    IOobject
    (
        "kMean",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,   
      dimensionedScalar
      (
           "kMean", 
           dimVelocity*dimVelocity,
           0.0
      )
);
*/ 

volScalarField convectionTKE
(
    IOobject
    (
        "convectionTKE",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
      dimensionedScalar
      (
            "convectionTKE", 
            dimVelocity*dimVelocity/dimTime,
            0.0
      )
);

volScalarField dissipationTKE
(
    IOobject
    (
        "dissipationTKE",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
      dimensionedScalar
      (
            "dissipationTKE", 
            dimVelocity*dimVelocity/dimTime,
            0.0
      )
);

volVectorField pressureDiffusionTKEField
(
    IOobject
    (
        "pressureDiffusionTKEField",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,   
      dimensionedVector
      (
           "pressureDiffusionTKEField", 
           dimVelocity*dimVelocity*dimLength/dimTime,
           vector(0.0,0.0,0.0)
      )
);

volVectorField turbulenceTransportTKEField
(
    IOobject
    (
        "turbulenceTransportTKEField",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,   
      dimensionedVector
      (
           "turbulenceTransportTKEField", 
           dimVelocity*dimVelocity*dimVelocity,
           vector(0.0,0.0,0.0)
      )
);

