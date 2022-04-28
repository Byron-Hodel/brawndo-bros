//
//  TipsView.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/26/22.
//

import SwiftUI

struct TipsView: View {
    let tips: [Tip]
    init() {
         let url = Bundle.main.url(forResource: "tips",withExtension: "json")!
        let data = try! Data(contentsOf:url)
        tips = try! JSONDecoder().decode([Tip].self, from: data)
    }
    var body: some View {
        List(tips, id: \.title, children: \.item) {tip in
            if tip.title != nil {
                Label(tip.title, systemImage:
                        "quote.bubble")
                    .font(.headline)
            }
            
            
            if tip.Threshold != nil {
                Label(tip.Threshold!, systemImage:
                            "quote.bubble")
                        .font(.headline)
            }
            if tip.Current != nil {
                    Label(tip.Current!, systemImage:
                                "quote.bubble")
                            .font(.headline)
            }
            if tip.Action != nil {
                    Label(tip.Action!, systemImage:
                            "quote.bubble")
                            .font(.headline)
            }
            if tip.Dosage != nil {
                    Label(tip.Dosage!, systemImage:
                                "quote.bubble")
                            .font(.headline)
            }
        
        }
        .navigationTitle("Tips")
    }
}


struct TipsView_Previews: PreviewProvider {
    static var previews: some View {
        TipsView()
    }
}
