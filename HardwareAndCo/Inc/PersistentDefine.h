//==================================================================================
//==================================================================================
// File: PersistentDefine.h
// Description: Persistent storage configuration and memory layout definitions
// 
// Copyright (c) 2025 Dad Design.
//==================================================================================
//==================================================================================

#pragma once

//**********************************************************************************
// Includes
//**********************************************************************************
#include "main.h"
#include "FlashDefine.h"

//**********************************************************************************
// Flasher Storage Configuration
//**********************************************************************************

// Base address of external QSPI flash (16 MB total)
constexpr uint32_t FLASHER_ADDRESS  = FLASH_ADDRESS;      // Base QSPI Flash address
constexpr uint32_t FLASHER_MEM_SIZE = 16 * 1024 * 1024;   // 16 MB total size

//**********************************************************************************
// Block Storage Manager Configuration
//**********************************************************************************

// Block Storage Manager region (upper 8 MB of flash)
constexpr uint32_t BLOCK_STORAGE_ADDRESS  = FLASH_ADDRESS + (8 * 1024 * 1024);  // Offset 8 MB
constexpr uint32_t BLOCK_STORAGE_MEM_SIZE = 8 * 1024 * 1024;                    // 8 MB storage region

//***End of file**************************************************************
