//
//  Locations.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/25/22.
//

import Foundation


class Locations: ObservableObject {
    let places: [Location]
    
    var primary: Location
    {
        places[0]
    }
    
    init() {
        let url = Bundle.main.url(forResource: "locations",withExtension: "json")!
        let data = try! Data(contentsOf:url)
        places = try! JSONDecoder().decode([Location].self, from: data)
    }
    
}
