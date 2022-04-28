//
//  UltraPlant5000App.swift
//  UltraPlant5000
//
//  Created by nimco2 on 4/20/22.
//

import SwiftUI

@main
struct UltraPlant5000App: App {
    @State var locatoions = Locations()
    
    var body: some Scene {
        WindowGroup{
            TabView {
                NavigationView {
                    ContentView(location: Locations().primary)
                }
                .tabItem {
                    Image (systemName: "airplane.circle.fill")
                    Text("Discover")
                }
                NavigationView {
                    WorldView()
                }
                .tabItem {
                    Image (systemName: "star.fill")
                    Text("Location")
                }
                NavigationView {
                    TipsView()
                }
                .tabItem { Image (systemName: "List.bullet")
                    Text("Tips")
                    
                }

            }
            //.environmentObject(Locations)
        }
    }
}

        
        
        
        
        
       

