//
//  Location.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/25/22.
//

import Foundation

struct Location: Decodable, Identifiable {
    let id: Int
    let name: String
    let volume: String
    let description: String
    let more: String
    let pictures: [String]
    let advisory: String
 
    static let example = Location(id: 1, name:"Plant", volume: "Soil Moisture", description: "Is the amount of water used, including the water vapor, in an unsaturated Soil.", more: "The amount of soil moisture can have significantly different implications depending on location", pictures: ["Soil Moisture"], advisory: " The sensor moisture level below the trigger threshold? is the pump currently off?")
}

