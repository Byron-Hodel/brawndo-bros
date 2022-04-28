//
//  Tip.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/26/22.
//

import Foundation

struct Tip: Decodable {
    let title: String
    let volume: [Tip]?
    let Threshold: String?
    let Current: String?
    let Action: String?
    let Dosage: String?
    let item: [Tip]?
}

struct Item: Decodable {
    let Threshold: String
    let Current: String
    let Action: String
    let Dosage: String
}
