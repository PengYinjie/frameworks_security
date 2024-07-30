/*
 * Copyright (C) 2022-2024 Xiaomi Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <nuttx/config.h>
#include <stdio.h>
#include <string.h>

#include <alipay_ca_api.h>

static char* item_name[] = {
    "alipay_private_key",
    "alipay_share_key",
    "alipay_seed",
    "alipay_timediff",
    "alipay_nick_name",
    "alipay_logon_id",
    "alipay_bind_flag",
};

static uint8_t buffer[512];
static uint32_t len;

int main(int argc, FAR char* argv[])
{
    int item;

    if (argc != 3 && argc != 4) {
        return -1;
    }

    item = atoi(argv[2]);

    if (item > 6) {
        return -1;
    }

    if (strcmp(argv[1], "check") == 0) {
        if (is_alipay_tee_data_exited(item_name[item]) == true) {
            printf("item is exited.\n");
        } else {
            printf("item is not exited.\n");
        }
    }

    if (strcmp(argv[1], "delete") == 0) {
        if (alipay_tee_data_delete(item_name[item]) == 0) {
            printf("item del successfully.\n");
        } else {
            printf("item del fail.\n");
        }
    }

    if (strcmp(argv[1], "read") == 0) {
        len = 512;
        memset(buffer, 0, 512);

        if (alipay_tee_data_read(item_name[item], buffer, &len) == 0) {
            printf("item read successfully. len = %" PRId32 "\n", len);
            printf("item:%s\n", buffer);
        } else {
            printf("item read fail.\n");
        }
    }

    if (strcmp(argv[1], "write") == 0) {
        if (alipay_tee_data_write(item_name[item], (const uint8_t*)argv[3],
                strlen(argv[3]))
            == 0) {
            printf("item write successfully.\n");
        } else {
            printf("item write fail.\n");
        }
    }

    return 0;
}