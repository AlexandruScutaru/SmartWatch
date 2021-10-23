//
//  ContentView.swift
//  watch
//
//  Created by Alex Scutaru on 10/18/21.
//

import SwiftUI

struct TabViewItem: View
{
    let tabName: String
    let imageName: String

    var body: some View {
        VStack(alignment: .center) {
            Image(imageName)
            Text(tabName)
        }
    }
}

struct ContentView: View {
    var body: some View {
        TabView(selection: .constant(1)) {
            DeviceTabView().padding(.horizontal).tabItem {
                TabViewItem(tabName: "Device", imageName: "devices_icon")
            }.tag(1)
            SettingsTabView().padding(.horizontal).tabItem {
                TabViewItem(tabName: "Settings", imageName: "settings_icon")
            }.tag(2)
        }.accentColor(.green)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView().preferredColorScheme(.dark)
        //ForEach(ColorScheme.allCases, id: \.self) {
        //     ContentView().preferredColorScheme($0)
        //}
    }
}
