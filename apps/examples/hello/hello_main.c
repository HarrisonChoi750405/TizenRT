/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************
 * examples/hello/hello_main.c
 *
 *   Copyright (C) 2008, 2011-2012 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>
#include <stdio.h>

#include <iotbus/iotbus_error.h>
#include <iotbus/iotbus_spi.h>
/****************************************************************************
 * hello_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int hello_main(int argc, char *argv[])
#endif
{
	printf("Hello, IOTBUS SPI!!\n");
	
    unsigned char txbuf[64] = { 'T', 'i', 'z', 'e', 'n', 'R', 'T', 0 };
	unsigned char rxbuf[64] = {	0, };

	int ret;
	int i;
    int len = 8;

	struct iotbus_spi_config_s config = {
		(char)8,    // bits_per_word, MSB default.
		0,          // chip_select
		12000000,   // frequency in Hz
		IOTBUS_SPI_MODE0,   // clk mode
	};

	iotbus_spi_context_h m_spi = iotbus_spi_open(3, &config);

	ret = iotbus_spi_write(m_spi, txbuf, len);
	if (ret != IOTBUS_ERROR_NONE) {
		printf("[SPI] Write Error1[%d] !\n", ret);
		return 0;
	}
    printf("[SPI] Step1 %d\n", ret);

    printf("Recv[before] : 0x%x\n", rxbuf[0]);
    ret = iotbus_spi_recv(m_spi, rxbuf, len);
	if (ret != IOTBUS_ERROR_NONE) {
		printf("[SPI] Recv Error1[%d] !\n", ret);
		return 0;
	}
    printf("Recv[after][%d] : \n==> ", ret);
    for (i = 0; i < len; i++) {
        printf("0x%x ", rxbuf[i]);
    }

    iotbus_spi_close(m_spi);
    printf("\nSPI test done.\n");

	return 0;
}
