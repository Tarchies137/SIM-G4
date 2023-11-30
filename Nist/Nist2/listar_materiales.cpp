#include "G4NistManager.hh"
#include <iostream>

int main() {
    G4NistManager* nistManager = G4NistManager::Instance();
    
    // Obtener la lista de nombres de materiales predefinidos
    const std::vector<G4String>& materialNames = nistManager->GetNistMaterialNames();

    // Imprimir los nombres de los materiales
    for (const auto& name : materialNames) {
        std::cout << name << std::endl;
    }

    return 0;
}

