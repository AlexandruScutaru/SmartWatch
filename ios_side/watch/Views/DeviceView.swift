//
//  DeviceView.swift
//  watch
//
//  Created by Alex Scutaru on 10/21/21.
//

import SwiftUI

struct DeviceView: View {
    var body: some View {
        VStack(alignment: .center, spacing: 20) {
            Spacer()
            Image("watch_illustration")
                .resizable()
                .aspectRatio(contentMode: .fit)
                .frame(width: 200)
            
            Button(action: {
            }) {
                Text("Pair with device").padding(5).foregroundColor(/*@START_MENU_TOKEN@*/.green/*@END_MENU_TOKEN@*/)
            }
            Spacer()
            Spacer()
        }
    }
}

struct DeviceView_Previews: PreviewProvider {
    static var previews: some View {
        DeviceView()
    }
}
