//==================================================================================
//==================================================================================
// File: HardwareAndCo.h
// Description: Centralized initialization and management of OSCAR_P01A01
//              hardware resources and software components (TFT display, GUI,
//              DSP modules, etc.)
//
// Copyright (c) 2025 Dad Design.
//==================================================================================
//==================================================================================

#pragma once

//**********************************************************************************
// Includes
//**********************************************************************************
#include "main.h"
#include "Sections.h"

//**********************************************************************************
// General defines
//**********************************************************************************
#define GUI_UPDATE_MS      300     // GUI update interval in milliseconds
#define MIDI_UPDATE_MS     100     // MIDI update interval in milliseconds
#define MONITOR_UPDATE_MS  200     // Monitor update interval in milliseconds
#define GENERAL_UPDATE_MS  100     // General system update interval in milliseconds
constexpr float MIN_DRY = -40.0f;  // Minimum dry signal level cDryWet
constexpr float MAX_DRY  = 0.0f;     // Maximum dry signal level cDryWet
constexpr float FAD_TIME = 1.5f;   // Dry/Wet Fading time in second

//**********************************************************************************
// External functions
//**********************************************************************************
extern void Error_Handler(void);              // System error handler
extern void MPU_Config(void);                 // Memory Protection Unit configuration
extern void HardwareAndCoInitialize(void);    // Hardware initialization function
extern void MainLoop(void);                   // Main application loop

//**********************************************************************************
// SDRAM configuration
//**********************************************************************************
#include "IS42S16320.h"
#define SDRAM_ADDRESS  0xC0000000  // SDRAM base address

//**********************************************************************************
// FLASH - W25Q128 in double mode
//**********************************************************************************
#include "W25Q128.h"
extern DadDrivers::cW25Q128 __Flash;  // External flash memory instance

//**********************************************************************************
// Persistent storage
//**********************************************************************************
#include "cFlasherStorage.h"
// Read files saved in flash memory using DadFlasher utility
extern DadPersistentStorage::cFlasherStorage __FlasherStorage;

#include "cBlockStorageManager.h"
// Read and write data on persistent block storage
extern DadPersistentStorage::cBlockStorageManager __BlockStorageManager;

//**********************************************************************************
// Display - ST7789
//**********************************************************************************
#include "cDisplay.h"
extern DadGFX::cDisplay __Display;  // Main display instance

//**********************************************************************************
// Audio Manager
//**********************************************************************************
#include "AudioManager.h"

#define AUDIO_BUFFER_SIZE  4        // Audio buffer size in samples
#define SAMPLING_RATE      48000.0f // Audio sampling rate in Hz

// Real-time refresh rate derived from audio parameters, filters, etc.
constexpr float RT_RATE = SAMPLING_RATE / (float)AUDIO_BUFFER_SIZE;

//**********************************************************************************
// System states
//**********************************************************************************
enum eOnOff {
    ByPass = 0,  // Bypass mode - audio passes through without processing
    Off,         // System off state
    On           // System on state with audio processing
};

extern eOnOff   __MemOnOff;  // Current audio processing state
extern eOnOff   __OnOffCmd;  // Target state (requested by user)
extern uint32_t __CT;        // Cycle counter for LED activity feedback

//**********************************************************************************
// System monitor (conditional compilation)
//**********************************************************************************
#ifdef MONITOR
#include "cMonitor.h"
extern DadUtilities::cMonitor __Monitor;  // System monitor instance
extern volatile float CPULoad;            // CPU load percentage
extern volatile float EffectTime;         // Effect processing time
extern volatile float Frequency;          // Current operating frequency
#endif

//**********************************************************************************
// Switches
//**********************************************************************************
#include "cSwitch.h"
extern DadDrivers::cSwitch __Switch1;  // First hardware switch
extern DadDrivers::cSwitch __Switch2;  // Second hardware switch

//**********************************************************************************
// Encoders
//**********************************************************************************
#include "cEncoder.h"
extern DadDrivers::cEncoder __Encoder1;  // First rotary encoder
extern DadDrivers::cEncoder __Encoder2;  // Second rotary encoder
extern DadDrivers::cEncoder __Encoder3;  // Third rotary encoder
extern DadDrivers::cEncoder __Encoder0;  // Fourth rotary encoder

//**********************************************************************************
// SoftSPI and Dry/Wet (PGA2310 PGA2311 PGA2320)
//**********************************************************************************
#include "cSoftSPI.h"
extern DadDrivers::cSoftSPI __SoftSPI;  // Software SPI implementation
#include "cDryWet.h"
extern DadDrivers::cDryWet __DryWet;    // DryWet Manager

//**********************************************************************************
// MIDI interface
//**********************************************************************************
#include "cMidi.h"
extern DadDrivers::cMidi __Midi;  // MIDI interface instance

// -----------------------------------------------------------------------------
// Wrapper functions for MIDI USB callbacks
extern "C" {
void OnNoteOn(uint8_t channel, uint8_t note, uint8_t velocity);          // Note on event handler
void OnNoteOff(uint8_t channel, uint8_t note, uint8_t velocity);         // Note off event handler
void OnControlChange(uint8_t channel, uint8_t control, uint8_t value);   // Control change handler
void OnProgramChange(uint8_t channel, uint8_t program);                  // Program change handler
}

//**********************************************************************************
// GUI system
//**********************************************************************************
#include "MainGUI.h"
extern DadGUI::cMainGUI __GUI;  // Main graphical user interface

//***End of file**************************************************************
