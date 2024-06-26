/*
 * Copyright (C) 2015-2022 IoT.bzh Company
 * Author: Fulup Ar Foll <fulup@iot.bzh>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <sys/types.h>

#define PCSC_HANDLE_MAGIC 852963147
#define PCSC_DFLT_TIMEOUT 60 // default reader change status in seconds
#define PCSC_READER_DEV_MAX 8
#define PCSC_MIFARE_STATUS_LEN 2 // number of byte added to read buffer for Mifare status
#define PCSC_MIFARE_KEY_LEN 6 // keyA/B len (byte)
#define PCSC_MIFARE_ACL_LEN 3+1 // Access Control Bits len (3 bytes + 1 byte userdata)

// redefine debug/log to avoid conflict
#ifndef EXT_EMERGENCY
#include <rp-utils/rp-verbose.h>
#define EXT_EMERGENCY(...)            RP_EMERGENCY(__VA_ARGS__)
#define EXT_ALERT(...)                RP_ALERT(__VA_ARGS__)
#define EXT_CRITICAL(...)             RP_CRITICAL(__VA_ARGS__)
#define EXT_ERROR(...)                RP_ERROR(__VA_ARGS__)
#define EXT_WARNING(...)              RP_WARNING(__VA_ARGS__)
#define EXT_NOTICE(...)               RP_NOTICE(__VA_ARGS__)
#define EXT_INFO(...)                 RP_INFO(__VA_ARGS__)
#define EXT_DEBUG(...)                RP_DEBUG(__VA_ARGS__)
#endif

typedef enum {
    PCSC_OPT_UNKNOWN=0,
    PCSC_OPT_TIMEOUT,
    PCSC_OPT_VERBOSE,
} pcscOptsE;

typedef enum {
    ATR_UNKNOWN=0,
    ATR_MIFARE_1K,
    ATR_MIFARE_4K,
    ATR_MIFARE_UL,
    ATR_MIFARE_MINI,
    ATR_FELICA_212K,
    ATR_FELICA_424K,
    ATR_BANK_FR,
} atrCardidEnumT;

typedef enum {
    PCSC_MONITOR_UNKNOWN=0,
    PCSC_MONITOR_WAIT,
    PCSC_MONITOR_CANCEL,
    PCSC_MONITOR_KILL,
} pcscMonitorActionE;

typedef struct {
    const char *uid;
    u_int8_t *kval;
    u_int8_t klen;
    u_int8_t kidx;
} pcscKeyT;

typedef struct {
    u_int8_t *acls;
    u_int8_t alen;
    pcscKeyT *keyA;
    pcscKeyT *keyB;
} pcscTrailerT;

typedef struct pcscHandleS pcscHandleT; // opaque handle for client apps
typedef int (*pcscStatusCbT) (pcscHandleT *handle, ulong state, void*ctx);

pcscHandleT *pcscConnect (const char *uid, const char *readerName);
int pcscDisconnect (pcscHandleT *handle);
int pcscSetOpt (pcscHandleT *handle, pcscOptsE opt, ulong value);
const char* pcscReaderName (pcscHandleT *handle);
const char* pcscErrorMsg (pcscHandleT *handle);
u_int64_t pcscGetCardUuid (pcscHandleT *handle);

int pcscReaderCheck (pcscHandleT *handle, int ticks);
ulong pcscMonitorReader (pcscHandleT *handle, pcscStatusCbT callback, void *ctx);
int pcscMonitorWait (pcscHandleT *handle, pcscMonitorActionE action, ulong tid);
pcscHandleT *pcscList(const char** readerList, ulong *readerMax);

const pcscKeyT *pcscNewKey (const char *uid, u_int8_t *value, size_t len);
int pcscReadUuid (pcscHandleT *handle, const char *uid, u_int8_t *data, ulong *dlen);
int pcsWriteTrailer (pcscHandleT *handle, const char *uid, u_int8_t secIdx, u_int8_t blkIdx, const pcscKeyT *key, const pcscTrailerT *trailer);
int pcsWriteBlock (pcscHandleT *handle, const char *uid, u_int8_t secIdx, u_int8_t blkIdx, u_int8_t *dataBuf, ulong dataLen, const pcscKeyT *key);
int pcscReadBlock (pcscHandleT *handle, const char *uid, u_int8_t secIdx, u_int8_t blkIdx, u_int8_t *data, ulong dataLen, const pcscKeyT *key);
