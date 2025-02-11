#ifndef __ANDROID_SYS_H
#define __ANDROID_SYS_H
/* 
Implementação de android sys com implementação de funções de pegar os globals como status de memoria... e versão do android com saida usando o enum.
*/
#pragma once
typedef enum {
    ANDROID_UNKNOWN = -1,
    ANDROID_BASE = 1,          
    ANDROID_CUPCAKE = 3,       
    ANDROID_DONUT = 4,         
    ANDROID_ECLAIR = 5,        
    ANDROID_FROYO = 8,         
    ANDROID_GINGERBREAD = 9,   
    ANDROID_HONEYCOMB = 11,    
    ANDROID_ICE_CREAM_SANDWICH = 14,  
    ANDROID_JELLY_BEAN = 16,   
    ANDROID_KITKAT = 19,       
    ANDROID_LOLLIPOP = 21,     
    ANDROID_MARSHMALLOW = 23,  
    ANDROID_NOUGAT = 24,       
    ANDROID_OREO = 26,         
    ANDROID_PIE = 28,          
    ANDROID_10 = 29,           
    ANDROID_11 = 30,           
    ANDROID_12 = 31,           
    ANDROID_12L = 32,          
    ANDROID_13 = 33,           
    ANDROID_14 = 34            
} AndroidVersion;
typedef struct {
      long int total_ram;
      long int free_ram;
      long int shared_ram;
      int proc;
} AndroidGlobals;
extern AndroidGlobals android_globals();
extern AndroidVersion get_android_version();
#endif