#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();


//-----------Constantes de los materiales ---------------


	 G4double a, z, density, temperature, pressure;
  G4int nelements;

  G4Element* N = new G4Element("Nitrogen", "N", z=7 , a=14.01*g/mole);
  G4Element* H = new G4Element("Hydrogen", "H", z=1 , a=1.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8 , a=16.00*g/mole);

	//G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double energy[]={ 2.034*eV, 2.068*eV, 2.103*eV, 2.139*eV,
                2.177*eV, 2.216*eV, 2.256*eV, 2.298*eV,
                2.341*eV, 2.386*eV, 2.433*eV, 2.481*eV,
                2.532*eV, 2.585*eV, 2.640*eV, 2.697*eV,
                2.757*eV, 2.820*eV, 2.885*eV, 2.954*eV,
                3.026*eV, 3.102*eV, 3.181*eV, 3.265*eV,
                3.353*eV, 3.446*eV, 3.545*eV, 3.649*eV,
                3.760*eV, 3.877*eV, 4.002*eV, 4.136*eV };
	
const G4int nEntries = sizeof(energy)/sizeof(G4double);
//	G4double rindexAerogel[2] = {1.1,1.1};
//	G4double rindexWorld[2] = {1.0, 1.0};
//	G4double rindexTank[2] = {1.53, 1.56};

//	G4double absorptionCoefficient[2] = {10.4*m, 0.4*m }; 
	G4double pi  = 3.14159265358979323846;
//------------------------------------------
   G4double rindexTank[] =
              { 1.3435, 1.344,  1.3445, 1.345,  1.3455,
                1.346,  1.3465, 1.347,  1.3475, 1.348,
                1.3485, 1.3492, 1.35,   1.3505, 1.351,
                1.3518, 1.3522, 1.3530, 1.3535, 1.354,
                1.3545, 1.355,  1.3555, 1.356,  1.3568,
                1.3572, 1.358,  1.3585, 1.359,  1.3595,
                1.36,   1.3608};

    assert(sizeof(rindexTank) == sizeof(energy));

    G4double absorptionCoefficient[] =
             {3.448*m,  4.082*m,  6.329*m,  9.174*m, 12.346*m, 13.889*m,
             15.152*m, 17.241*m, 18.868*m, 20.000*m, 26.316*m, 35.714*m,
             45.455*m, 47.619*m, 52.632*m, 52.632*m, 55.556*m, 52.632*m,
             52.632*m, 47.619*m, 45.455*m, 41.667*m, 37.037*m, 33.333*m,
             30.000*m, 28.500*m, 27.000*m, 24.500*m, 22.000*m, 19.500*m,
             17.500*m, 14.500*m };



 G4double energy_water[] = {
       1.56962*eV, 1.58974*eV, 1.61039*eV, 1.63157*eV,
       1.65333*eV, 1.67567*eV, 1.69863*eV, 1.72222*eV,
       1.74647*eV, 1.77142*eV, 1.7971 *eV, 1.82352*eV,
       1.85074*eV, 1.87878*eV, 1.90769*eV, 1.93749*eV,
       1.96825*eV, 1.99999*eV, 2.03278*eV, 2.06666*eV,
       2.10169*eV, 2.13793*eV, 2.17543*eV, 2.21428*eV,
       2.25454*eV, 2.29629*eV, 2.33962*eV, 2.38461*eV,
       2.43137*eV, 2.47999*eV, 2.53061*eV, 2.58333*eV,
       2.63829*eV, 2.69565*eV, 2.75555*eV, 2.81817*eV,
       2.88371*eV, 2.95237*eV, 3.02438*eV, 3.09999*eV,
       3.17948*eV, 3.26315*eV, 3.35134*eV, 3.44444*eV,
       3.54285*eV, 3.64705*eV, 3.75757*eV, 3.87499*eV,
       3.99999*eV, 4.13332*eV, 4.27585*eV, 4.42856*eV,
       4.59258*eV, 4.76922*eV, 4.95999*eV, 5.16665*eV,
       5.39129*eV, 5.63635*eV, 5.90475*eV, 6.19998*eV
    };

    const G4int numentries_water = sizeof(energy_water)/sizeof(G4double);

    //assume 100 times larger than the rayleigh scattering for now.
    G4double mie_water[] = {
       167024.4*m, 158726.7*m, 150742  *m,
       143062.5*m, 135680.2*m, 128587.4*m,
       121776.3*m, 115239.5*m, 108969.5*m,
       102958.8*m, 97200.35*m, 91686.86*m,
       86411.33*m, 81366.79*m, 76546.42*m,
       71943.46*m, 67551.29*m, 63363.36*m,
       59373.25*m, 55574.61*m, 51961.24*m,
       48527.00*m, 45265.87*m, 42171.94*m,
       39239.39*m, 36462.50*m, 33835.68*m,
       31353.41*m, 29010.30*m, 26801.03*m,
       24720.42*m, 22763.36*m, 20924.88*m,
       19200.07*m, 17584.16*m, 16072.45*m,
       14660.38*m, 13343.46*m, 12117.33*m,
       10977.70*m, 9920.416*m, 8941.407*m,
       8036.711*m, 7202.470*m, 6434.927*m,
       5730.429*m, 5085.425*m, 4496.467*m,
       3960.210*m, 3473.413*m, 3032.937*m,
       2635.746*m, 2278.907*m, 1959.588*m,
       1675.064*m, 1422.710*m, 1200.004*m,
       1004.528*m, 833.9666*m, 686.1063*m
    };


//---------------------------------------------------------------
//						MATRIALES
//---------------------------------------------------------------

//  -Aerogel-

	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);//6
	SiO2->AddElement(nist->FindOrBuildElement("Si"),1);//6
	SiO2->AddElement(nist->FindOrBuildElement("O"),2);//6

	G4Material *tankMat = new G4Material("tankMat", 1.000*g/cm3, 2);//6
	tankMat->AddElement(nist->FindOrBuildElement("H"),2);//6
	tankMat->AddElement(nist->FindOrBuildElement("O"),1);//6

	G4Element *C =nist->FindOrBuildElement("C");//6

	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);//6
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(tankMat, 37.4*perCent);
	Aerogel->AddElement (C, 0.1*perCent);

	G4MaterialPropertiesTable *mptAerogel =new G4MaterialPropertiesTable();
	mptAerogel ->AddProperty("RINDEX", {1.239841939*eV/0.9}, {1.1}, 1);
	//mptAerogel ->AddProperty("RINDEX", energy, rindexAerogel, 2);

	Aerogel->SetMaterialPropertiesTable(mptAerogel);
//----------------------------------------------------------------------
// -Habitación
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	//mptWorld ->AddProperty("RINDEX", {1.239841939*eV/0.9}, {1.0}, 1);
	//mptWorld->AddProperty("RINDEX",energy, rindexWorld, 2);

	//worldMat->SetMaterialPropertiesTable(mptWorld);
//---------------------------------------------------------------------
//  -MAterial interno del Estanque: Agua

	//G4Material *tankMat = nist->FindOrBuildMaterial("G4_WATER");
	 // G4Material* tankMat = new G4Material("tankMat", density= 1.0*g/cm3, nelements=2);
  //tankMat->AddElement(H, 2);
  //tankMat->AddElement(O, 1);



   G4MaterialPropertiesTable* waterMPT = tankMat->GetMaterialPropertiesTable();

	G4MaterialPropertiesTable *mptTank = new G4MaterialPropertiesTable();
	mptTank->AddProperty("RINDEX",energy, rindexTank, nEntries);
	tankMat->SetMaterialPropertiesTable(mptTank);
	mptTank->AddProperty("ABSLENGTH", energy, absorptionCoefficient, nEntries);
	tankMat->SetMaterialPropertiesTable(mptTank);

	G4double mie_water_const[3]={0.99,0.99,0.8};

    mptTank->AddProperty("MIEHG",energy_water,mie_water,numentries_water);
    tankMat->SetMaterialPropertiesTable(mptTank);
    mptTank->AddConstProperty("MIEHG_FORWARD",mie_water_const[0]);
    tankMat->SetMaterialPropertiesTable(mptTank);
    mptTank->AddConstProperty("MIEHG_BACKWARD",mie_water_const[1]);
    tankMat->SetMaterialPropertiesTable(mptTank);
    mptTank->AddConstProperty("MIEHG_FORWARD_RATIO",mie_water_const[2]);
    tankMat->SetMaterialPropertiesTable(mptTank);
//-----------------------------------------------------------------------
// Definir las longitudes de onda correspondientes a 300 nm y 650 nm
G4double lambda_min = 300.0 * nm;
G4double lambda_max = 650.0 * nm;
G4double energy_min = h_Planck * c_light / lambda_max;
G4double energy_max = h_Planck * c_light / lambda_min;

// Crear un corte de producción con el rango de energía deseado
G4ProductionCuts* cuts = new G4ProductionCuts();
cuts->SetProductionCut(1.0 * mm);  // Ajusta el valor según sea necesario
cuts->SetProductionCut(energy_min);
cuts->SetProductionCut(energy_max);

// Asignar los cortes de producción a la región de interés
//G4Region* cherenkovRegion = new G4Region("CherenkovRegion");
//cherenkovRegion->SetProductionCuts(cuts);

// Asignar la región de interés a la fuente
//particleSource->SetRegion(cherenkovRegion);
//G4ProductionCuts* outerCuts = new G4ProductionCuts();
//outerCuts->SetProductionCut(1.0 * nm);  // Ajustar según sea necesario

// Asignar los cortes de producción a la región exterior al tanque
//G4Region* outerRegion = new G4Region("OuterRegion");
//outerRegion->SetProductionCuts(outerCuts);

//----------------------------------------------------------------------
//  -Tyvek
	G4Material* Tyvek = new G4Material("Tyvek", 0.94 * g / cm3, 2);
	Tyvek->AddElement(nist->FindOrBuildElement("H"),4);
	Tyvek->AddElement(nist->FindOrBuildElement("C"),2);
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//						VOLUMENES
//-----------------------------------------------------------------------
//  -Habitacion: Caja de 3mx3mx3m con aire se incluye en la simulación 
// para considerar las partículas entrando desde fuera del estanque	

	G4Box *solidWorld 				= new G4Box("solidWorld", 3*m, 3*m, 3*m);
	G4LogicalVolume *logicWorld 	= new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
	//logicWorld->SetRegion(cherenkovRegion);
	G4VPhysicalVolume *physWorld	= new G4PVPlacement(
		0, 
		G4ThreeVector( 0., 0., 0.), 
		logicWorld, 
		"physWorld", 
		0, 
		false, 
		0, 
		true);	
//---------------------------------------------------------------------------------
//  -Estanque: Estanque de 1.2m de diámetro y 1.2m de altura. contiene Agua 

	G4Tubs *solidRadiator = new G4Tubs("solidRadiator", 0., 1.2*m, 1.2*m, 0., 2 * pi);
	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator,tankMat, "logicalRadiator");//material worldmat para reducir el procesamiento, cambiar a tankmat
	G4RotationMatrix* rotation = new G4RotationMatrix();
	//________________________________
	// Asignar la región de interés a los volúmenes del estanque
    //logicRadiator->SetRegion(cherenkovRegion);
	//logicRadiator->SetRegion(outerRegion);		//CutOff
	//-------------------------------------
	rotation->rotateX(90. * degree); 			//Se rota para visualizarlo vetical
	G4VPhysicalVolume *physRadiator = new G4PVPlacement(
		rotation, 
		G4ThreeVector(0., 0., 0.), 
		logicRadiator, 
		"physRadiator", 
		logicWorld, 
		false, 
		0, 
		true);
//------------------------------------------------------------------------------------------
// -Capa de Tyvek 
/*	G4Tubs *solidTyvek = new G4Tubs("solidTyvek", 1.2*m, 1.2*m+0.01*mm, 1.2*m, 0., 2 * pi);
	G4LogicalVolume *logicTyvek = 
	new G4LogicalVolume(solidTyvek,
						Tyvek, 
						"logicalTyvek");
	//G4RotationMatrix* rotation = new G4RotationMatrix();
	//rotation->rotateX(90. * degree); 			
	G4VPhysicalVolume *physTyvek = new G4PVPlacement(
		rotation, 										//usamos el mismo parámetro que el estanque
		G4ThreeVector(0., 0., 0*m), 
		logicTyvek, 
		"physTyvek", 
		logicWorld, 
		false, 
		0, 
		true);
// Crear el sólido para la superficie reflectora 

	// Asociar una superficie óptica reflectante a la capa de Tyvek
/* G4OpticalSurface* tyvekSurface = new G4OpticalSurface("TyvekSurface");
tyvekSurface->SetType(dielectric_metal);
tyvekSurface->SetFinish(polished);
tyvekSurface->SetModel(glisur);

*/


//--------------------------------------------------------------------
//  SUPERFICIE REFLECTORA

// Crear la superficie óptica para las caras internas del tanque
G4OpticalSurface* opticalSurface = new G4OpticalSurface("OpticalSurfaceInternal");
opticalSurface->SetType(dielectric_metal);				// superficie mate
opticalSurface->SetFinish(ground); 	// mate pintada por detras
opticalSurface->SetModel(unified);				//modelo reflección difusa

// Crear la relación de reflexiy transmisión

G4double reflectividad  = 0.9; // 
G4double eficiencia = 0.1;  // 
//G4double transmitancia=0;//
G4MaterialPropertiesTable* surfaceProperties = new G4MaterialPropertiesTable();
surfaceProperties->AddProperty("REFLECTIVITY", {2.0*eV, 3.5*eV}, {reflectividad, reflectividad});
surfaceProperties->AddProperty("EFFICIENCY",{2.0*eV, 3.5*eV}, {eficiencia, eficiencia});
//surfaceProperties->AddProperty("TRANSMITTANCE", {2.0*eV, 3.5*eV};, {transmitancia, transmitancia});


// Asignar las propiedades a la superficie óptica
opticalSurface->SetMaterialPropertiesTable(surfaceProperties);

// Crear la interfaz entre el material del tubo y el material tankMat
//new G4LogicalBorderSurface("OpticalSurfaceInternal", physRadiator, physWorld, opticalSurface);

//----------------------------------------------------------------------------------------	
	G4Tubs *solidDetector = new G4Tubs("solidDetector", 0., 0.15*m, 0.1*m,0., 2 * pi);

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

	G4VPhysicalVolume *physDetector = new 
	G4PVPlacement(rotation, //se aplica misma rotacion que el estanque 
		G4ThreeVector(0,1.1*m,0), logicDetector,"physDetector",logicWorld, false, 0, true);
		//
	//

	//for(G4int i=0;i<100;i++)
	///{
		//for(G4int j=0; j<100; j++)
		//{
		//	G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100,0.49*m), logicDetector,"physDetector",logicWorld, false, j+i*100, true);
		//}
	//}
//-----------------------------------------------------------------------------------------
	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}
