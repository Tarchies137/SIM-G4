#include <iostream>
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"

int main() {
    // Obtén una instancia del G4NistManager
    G4NistManager* nistManager = G4NistManager::Instance();

    // Imprime la lista de elementos disponibles en la base de datos NIST
    G4cout << "Lista de elementos disponibles:" << G4endl;
    const G4ElementTable* elementTable = nistManager->GetElement();
    for (G4ElementTable::const_iterator it = elementTable->begin(); it != elementTable->end(); ++it) {
        G4cout << (*it)->GetName() << G4endl;
    }

    // Imprime la lista de materiales disponibles en la base de datos NIST
    G4cout << "Lista de materiales disponibles:" << G4endl;
    const G4MaterialTable* materialTable = nistManager->GetMaterial();
    for (G4MaterialTable::const_iterator it = materialTable->begin(); it != materialTable->end(); ++it) {
        G4cout << (*it)->GetName() << G4endl;
    }

    return 0;
}

