#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
	G4NistManager *nist = G4NistManager::Instance();


//-----------Constantes de los materiales ---------------

	G4double energy[2] = {1.239841939*eV/0.9, 1.239841939*eV/0.2};
	G4double rindexAerogel[2] = {1.1,1.1};
	G4double rindexWorld[2] = {1.0, 1.0};
	G4double rindexTank[2] = {1.33, 1.33};


	G4double pi  = 3.14159265358979323846;


//---------------------------------------------------------------
//						MATRIALES
//---------------------------------------------------------------

//  -Aerogel-

	G4Material *SiO2 = new G4Material("SiO2", 2.201*g/cm3, 2);//6
	SiO2->AddElement(nist->FindOrBuildElement("Si"),1);//6
	SiO2->AddElement(nist->FindOrBuildElement("O"),2);//6

	G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2);//6
	H2O->AddElement(nist->FindOrBuildElement("H"),2);//6
	H2O->AddElement(nist->FindOrBuildElement("O"),1);//6

	G4Element *C =nist->FindOrBuildElement("C");//6

	G4Material *Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);//6
	Aerogel->AddMaterial(SiO2, 62.5*perCent);
	Aerogel->AddMaterial(H2O, 37.4*perCent);
	Aerogel->AddElement (C, 0.1*perCent);

	G4MaterialPropertiesTable *mptAerogel =new G4MaterialPropertiesTable();
	mptAerogel ->AddProperty("RINDEX", {1.239841939*eV/0.9}, {1.1}, 1);
	//mptAerogel ->AddProperty("RINDEX", energy, rindexAerogel, 2);

	Aerogel->SetMaterialPropertiesTable(mptAerogel);
//----------------------------------------------------------------------
// -Habitación
	G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
	

	G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
	mptWorld ->AddProperty("RINDEX", {1.239841939*eV/0.9}, {1.0}, 1);
	//mptWorld->AddProperty("RINDEX",energy, rindexWorld, 2);

	worldMat->SetMaterialPropertiesTable(mptWorld);
//---------------------------------------------------------------------
//  -Estanque

	G4Material *tankMat = nist->FindOrBuildMaterial("G4_WATER");

   G4MaterialPropertiesTable* waterMPT = tankMat->GetMaterialPropertiesTable();

//	G4MaterialPropertiesTable *mptTank = new G4MaterialPropertiesTable();
//	mptTank->AddProperty("RINDEX",energy, rindexTank, 2);
//	tankMat->SetMaterialPropertiesTable(mptTank);

//----------------------------------------------------------------------
//  -Tyvek
	G4Material* Tyvek = new G4Material("Tyvek", 0.94 * g / cm3, 2);
	Tyvek->AddElement(nist->FindOrBuildElement("H"),4);
	Tyvek->AddElement(nist->FindOrBuildElement("C"),2);
//-----------------------------------------------------------------------

//-----------------------------------------------------------------------
//						VOLUMENES
//-----------------------------------------------------------------------
//  -Habitacion: Caja de 5mx5mx5m con aire se incluye en la simulación 
// para considerar las partículas entrando desde fuera del estanque	

	G4Box *solidWorld 				= new G4Box("solidWorld", 5*m, 5*m, 5*m);
	G4LogicalVolume *logicWorld 	= new G4LogicalVolume(solidWorld,worldMat,"logicWorld");
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
	G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator,tankMat, "logicalRadiator");
	G4RotationMatrix* rotation = new G4RotationMatrix();
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
	G4Tubs *solidTyvek = new G4Tubs("solidTyvek", 1.2*m, 1.2*m+0.01*mm, 1.2*m, 0., 2 * pi);
	G4LogicalVolume *logicTyvek = new G4LogicalVolume(solidTyvek,Tyvek, "logicalTyvek");
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
//G4OpticalSurface* tyvekSurface = new G4OpticalSurface("TyvekSurface");
//tyvekSurface->SetType(dielectric_metal);
//tyvekSurface->SetFinish(polished);
//tyvekSurface->SetModel(glisur);


//----------------------------------------------------------------------------------------	
	G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

	logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

	//for(G4int i=0;i<100;i++)
	///{
		//for(G4int j=0; j<100; j++)
		//{
		//	G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100,-0.5*m+(j+0.5)*m/100,0.49*m), logicDetector,"physDetector",logicWorld, false, j+i*100, true);
		//}
	//}

	return physWorld;
}

void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

	logicDetector->SetSensitiveDetector(sensDet);
}