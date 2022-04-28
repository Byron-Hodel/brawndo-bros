//
//  ContentView.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/20/22.
//

import SwiftUI

struct ContentView: View {
    let location: Location
   
    var body: some View {
        ScrollView{
            
            Image(location.pictures[0])
                .resizable()
                .scaledToFit()
        Text(location.name)
            .font(.largeTitle)
            .bold()
            .multilineTextAlignment(.center)
            Text(verbatim: location.volume)
            .font(.title)
            .foregroundColor(.secondary)
            
        Text(location.description)
            .padding(.horizontal)
            
        Text ("Did you know?")
            .font(.largeTitle)
            .bold()
            .padding(.top)
            Text(verbatim: location.more)
                .padding(.horizontal)
    
            
        }
        .navigationTitle("Discover")
    
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        NavigationView{
            ContentView(location: Location.example)
        }
       
    }
}
