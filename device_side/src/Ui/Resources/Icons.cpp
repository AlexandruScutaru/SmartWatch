#include "Icons.h"

#include <array>
#include <unordered_map>

#define ReturnIcon(iconType, iconMap) {\
        auto it = iconMap.find(iconType);\
        if (it != iconMap.end()) {\
            return it->second.data();\
        }\
        return iconMap[iconType].data();\
    }


namespace icons {
    namespace {
        struct EnumClassHasher {
            template <typename T>
            int operator()(T t) const {
                return static_cast<int>(t);
            }
        };

        using icon8_t  = std::array<uint8_t,   8>;
        using icon16_t = std::array<uint8_t,  32>;
        using icon32_t = std::array<uint8_t, 128>;

        std::unordered_map<IconType, icon8_t, EnumClassHasher> mIcons8 = {
            {
                IconType::UNKNOWN,
                {
                    0b00111000, //    ##   
                    0b01000100, //   #  #  
                    0b01000100, //   #  #  
                    0b00001000, //     #   
                    0b00010000, //    #    
                    0b00010000, //    #    
                    0b00000000, //         
                    0b00010000, //    #    
                }
            },
            {
                IconType::SETTINGS,
                {
                    0b00011000, //    #   
                    0b11011011, // ## ## ##
                    0b11111111, // ########
                    0b01100110, //  ##  ## 
                    0b01100110, //  ##  ## 
                    0b11111111, // ########
                    0b11011011, // ## ## ##
                    0b00011000, //    ##   
                }
            },
            {
                IconType::GAMES,
                {
                    0b00011100, //    ###  
                    0b00011100, //    ###  
                    0b00001000, //     #   
                    0b00001000, //     #   
                    0b00001000, //     #   
                    0b00001000, //     #   
                    0b11111111, // ########
                    0b11111111, // ########
                }
            },
            {
                IconType::CHECK_MARK,
                {
                    0b00000001, //       #
                    0b00000011, //      ##
                    0b00000110, //     ## 
                    0b10001100, //#   ##  
                    0b11011100, //## ###  
                    0b01111000, // ####   
                    0b01110000, // ###    
                    0b00110000, //  ##    
                }
            },
        };

        std::unordered_map<IconType, icon16_t, EnumClassHasher> mIcons16 = {
            {
                IconType::UNKNOWN,
                {
                    0b00000011, 0b11000000, //       ####      
                    0b00000111, 0b11100000, //      ######     
                    0b00001110, 0b01110000, //     ###  ###    
                    0b00001100, 0b00110000, //     ##    ##    
                    0b00001100, 0b00110000, //     ##    ##    
                    0b00001100, 0b00110000, //     ##    ##    
                    0b00000000, 0b01110000, //          ###    
                    0b00000000, 0b11100000, //         ###     
                    0b00000001, 0b11000000, //        ###     
                    0b00000011, 0b10000000, //       ###       
                    0b00000011, 0b00000000, //       ##        
                    0b00000011, 0b00000000, //       ##        
                    0b00000011, 0b00000000, //       ##        
                    0b00000000, 0b00000000, //                 
                    0b00000011, 0b00000000, //       ##        
                    0b00000011, 0b00000000, //       ##        
                }
            },
            {
                IconType::SETTINGS,
                {
                    0b00000011, 0b11000000, //       ####      
                    0b00000011, 0b11000000, //       ####      
                    0b01100111, 0b11100110, //  ##  ######  ## 
                    0b11111111, 0b11111111, // ################
                    0b11111111, 0b11111111, // ################
                    0b11111111, 0b11111111, // ################
                    0b01111110, 0b01111110, //  ######  ###### 
                    0b00111100, 0b00111100, //   ####    ####  
                    0b00111100, 0b00111100, //   ####    ####  
                    0b01111110, 0b01111110, //  ######  ###### 
                    0b11111111, 0b11111111, // ################
                    0b11111111, 0b11111111, // ################
                    0b11111111, 0b11111111, // ################
                    0b01100111, 0b11100110, //  ##  ######  ## 
                    0b00000011, 0b11000000, //       ####      
                    0b00000011, 0b11000000, //       ####      
                }
            },
            {
                IconType::GAMES,
                {
                    0b00000001, 0b10000000, //        ##       
                    0b00000011, 0b11000000, //       ####      
                    0b00000111, 0b11100000, //      ######     
                    0b00000111, 0b11100000, //      ######     
                    0b00000011, 0b11000000, //       ####      
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b00000001, 0b10000000, //        ##       
                    0b11111111, 0b11111111, // ################
                    0b11010111, 0b11111111, // ## # ###########
                    0b11111111, 0b11111111, // ################
                    0b11111111, 0b11111111, // ################
                }
            },
            {
                IconType::CHECK_MARK,
                {
                    0b00000000,0b00000000, //                
                    0b00000000,0b00000001, //               #
                    0b00000000,0b00000011, //              ##
                    0b00000000,0b00000110, //             ## 
                    0b00000000,0b00001110, //            ### 
                    0b00000000,0b00011100, //           ###  
                    0b11000000,0b00111000, //##        ###   
                    0b11100000,0b01111000, //###      ####   
                    0b01110000,0b11110000, // ###    ####    
                    0b00111001,0b11100000, //  ###  ####     
                    0b00011111,0b11100000, //   ########     
                    0b00011111,0b11000000, //   #######      
                    0b00001111,0b10000000, //    #####       
                    0b00000111,0b10000000, //     ####       
                    0b00000011,0b00000000, //      ##        
                    0b00000000,0b00000000, //                
                }
            },
        };

        std::unordered_map<IconType, icon32_t, EnumClassHasher> mIcons32 = {
            {
                IconType::UNKNOWN,
                {
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00111111, 0b11111100, 0b00000000, //           ############          
                    0b00000000, 0b00111111, 0b11111100, 0b00000000, //           ############          
                    0b00000000, 0b11111100, 0b00111111, 0b00000000, //         ######    ######        
                    0b00000000, 0b11111100, 0b00111111, 0b00000000, //         ######    ######        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b11110000, 0b00001111, 0b00000000, //         ####        ####        
                    0b00000000, 0b00000000, 0b00111111, 0b00000000, //                   ######        
                    0b00000000, 0b00000000, 0b00111111, 0b00000000, //                   ######        
                    0b00000000, 0b00000000, 0b11111100, 0b00000000, //                 ######          
                    0b00000000, 0b00000000, 0b11111100, 0b00000000, //                 ######          
                    0b00000000, 0b00000011, 0b11110000, 0b00000000, //               ######            
                    0b00000000, 0b00000011, 0b11110000, 0b00000000, //               ######            
                    0b00000000, 0b00001111, 0b11000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b11000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00000000, 0b00000000, 0b00000000, //                                 
                    0b00000000, 0b00000000, 0b00000000, 0b00000000, //                                 
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                    0b00000000, 0b00001111, 0b00000000, 0b00000000, //             ####                
                }
            },
            {
                IconType::SETTINGS,
                {
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00011000, 0b00111111, 0b11111100, 0b00011000, //    ##     ############     ##   
                    0b00111110, 0b01111111, 0b11111110, 0b01111100, //   #####  ##############  #####  
                    0b00111111, 0b11111111, 0b11111111, 0b11111100, //   ############################  
                    0b01111111, 0b11111111, 0b11111111, 0b11111110, //  ############################## 
                    0b01111111, 0b11111111, 0b11111111, 0b11111110, //  ############################## 
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                    0b11111111, 0b11111100, 0b00111111, 0b11111111, // ##############    ##############
                    0b01111111, 0b11110000, 0b00001111, 0b11111110, //  ###########        ########### 
                    0b00011111, 0b11110000, 0b00001111, 0b11111000, //    #########        #########   
                    0b00001111, 0b11100000, 0b00000111, 0b11110000, //     #######          #######    
                    0b00001111, 0b11100000, 0b00000111, 0b11110000, //     #######          #######    
                    0b00001111, 0b11100000, 0b00000111, 0b11110000, //     #######          #######    
                    0b00001111, 0b11100000, 0b00000111, 0b11110000, //     #######          #######    
                    0b00011111, 0b11110000, 0b00001111, 0b11111000, //    #########        #########   
                    0b01111111, 0b11110000, 0b00001111, 0b11111110, //  ###########        ########### 
                    0b11111111, 0b11111100, 0b00111111, 0b11111111, // ##############    ##############
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                    0b01111111, 0b11111111, 0b11111111, 0b11111110, //  ############################## 
                    0b01111111, 0b11111111, 0b11111111, 0b11111110, //  ############################## 
                    0b00111111, 0b11111111, 0b11111111, 0b11111100, //   ############################  
                    0b00111110, 0b01111111, 0b11111110, 0b01111100, //   #####  ##############  #####  
                    0b00011000, 0b00111111, 0b11111100, 0b00011000, //    ##     ############     ##   
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                }
            },
            {
                IconType::GAMES,
                {
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00011111, 0b11111000, 0b00000000, //            ##########           
                    0b00000000, 0b00011111, 0b11111000, 0b00000000, //            ##########           
                    0b00000000, 0b00011111, 0b11111000, 0b00000000, //            ##########           
                    0b00000000, 0b00011111, 0b11111000, 0b00000000, //            ##########           
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00001111, 0b11110000, 0b00000000, //             ########            
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b00000000, 0b00000011, 0b11000000, 0b00000000, //               ####              
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                    0b11110111, 0b10111111, 0b11111111, 0b11111111, // #### #### ######################
                    0b11100011, 0b00011111, 0b11111111, 0b11111111, // ###   ##   #####################
                    0b11110111, 0b10111111, 0b11111111, 0b11111111, // #### #### ######################
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                    0b11111111, 0b11111111, 0b11111111, 0b11111111, // ################################
                }
            },
        };
    }

    const uint8_t* const getIcon8(IconType icon) {
        ReturnIcon(icon, mIcons8);
    }

    const uint8_t* const getIcon16(IconType icon) {
        ReturnIcon(icon, mIcons16);
    }

    const uint8_t* const getIcon32(IconType icon) {
        ReturnIcon(icon, mIcons32);
    }
}
