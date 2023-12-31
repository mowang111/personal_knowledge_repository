---

excalidraw-plugin: parsed
tags: [excalidraw]

---
==⚠  Switch to EXCALIDRAW VIEW in the MORE OPTIONS menu of this document. ⚠==


# Text Elements
BIOS ^AAHf5351

ROM芯片 ^S82djdMI

内存 ^B4EHBOZB

0X00000 ^CBsAVB2j

0XFFFF0: BIOS程序启动地址 ^c7Kl1ICe

CS寄存器 ^CO1sA6BW

IP寄存器 ^A9YA5ita

+ ^2hdXk0iP

1. 刚上电时CS:IP强制指向BIOS启动程序 ^C3Z7wumb

CPU ^YcI5MFM8

2. BIOS初始化CPU，内存 ^iX6un4jk

3 ^jo64nKQX

BIOS一部分程序 ^TmlahKcV

4. 枚举本地设备，并初始化
进行相关检查 ^AeMxmWjf

中断表 ^4gGSSW1V

0X003FF ^0wRJXZpB

0X00400 ^8rY6sKFt

0X004FF ^32qaKsHw

BIOS数据区 ^0g7sYRFs

0X0e05b ^rFY61RuN

中断服务程序 ^8V5us58V

主板 ^WP1p8grd

3. 复制自己的一部分到内存 ^cAVv9qhB

2 ^0Nbpkr9o

5. 在内存中构建中断表，BIOS数据区，加载中断服务程序 ^bKhOEiKX

4 5 6  ^mVtGA8Vo

4 B ^tRxb0JQG

256个条目 ^lLo765cP

6. 搜索可引导的设备 ^QBCwF3Rg

硬盘 ^Hgwc3UXw

第1个扇区（256个字节）MBR ^I1ihMEfF

GRUB启动程序 ^ljK2TUxh

分区表 ^lsKNW5u4

7. MBR被BIOS装载到0x7c00地址开始的内存空间, 控制权交给MBR ^LLQlshHk

0X7c00 ^YgEoam6l

7 ^UFie4zz8

%%
# Drawing
```json
{
	"type": "excalidraw",
	"version": 2,
	"source": "https://github.com/zsviczian/obsidian-excalidraw-plugin/releases/tag/1.9.19",
	"elements": [
		{
			"id": "xVqyH_xZBkA9tJ364oU2F",
			"type": "rectangle",
			"x": -452.75,
			"y": -210.56253814697266,
			"width": 848,
			"height": 835,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 146909786,
			"version": 628,
			"versionNonce": 653629658,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160691793,
			"link": null,
			"locked": false
		},
		{
			"id": "_Ydn-ND2DyQyksEKnnkr5",
			"type": "rectangle",
			"x": -419.4166564941406,
			"y": -189.56249237060547,
			"width": 269.66668701171875,
			"height": 90.33334350585938,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 506715654,
			"version": 289,
			"versionNonce": 527464902,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160691793,
			"link": null,
			"locked": false
		},
		{
			"id": "hnlbiZxWn7X0_O3aORrkp",
			"type": "diamond",
			"x": -406.8269230769231,
			"y": -181.22911834716797,
			"width": 139,
			"height": 76,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 1798113498,
			"version": 479,
			"versionNonce": 1327865946,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "AAHf5351"
				}
			],
			"updated": 1701160872416,
			"link": null,
			"locked": false
		},
		{
			"id": "AAHf5351",
			"type": "text",
			"x": -363.1369053767278,
			"y": -155.72911834716797,
			"width": 52.119964599609375,
			"height": 25,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1968621722,
			"version": 113,
			"versionNonce": 1829012762,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160872417,
			"link": null,
			"locked": false,
			"text": "BIOS",
			"rawText": "BIOS",
			"fontSize": 20,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 17,
			"containerId": "hnlbiZxWn7X0_O3aORrkp",
			"originalText": "BIOS",
			"lineHeight": 1.25
		},
		{
			"id": "S82djdMI",
			"type": "text",
			"x": -252.08343505859375,
			"y": -154.56249237060547,
			"width": 116.75997924804688,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 418272966,
			"version": 133,
			"versionNonce": 1717199302,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "V2dRdbDFhRi651-schvHa",
					"type": "arrow"
				}
			],
			"updated": 1701160827834,
			"link": null,
			"locked": false,
			"text": "ROM芯片",
			"rawText": "ROM芯片",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "ROM芯片",
			"lineHeight": 1.25
		},
		{
			"id": "Aj8iLlVkW2W6C_GhfTNM6",
			"type": "rectangle",
			"x": -373.08331298828125,
			"y": -62.229209899902344,
			"width": 173.3333740234375,
			"height": 661.3333740234375,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 1236905050,
			"version": 413,
			"versionNonce": 235225158,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "V2dRdbDFhRi651-schvHa",
					"type": "arrow"
				},
				{
					"id": "zx5--kx3ofcZ736ox8Xv_",
					"type": "arrow"
				}
			],
			"updated": 1701160691793,
			"link": null,
			"locked": false
		},
		{
			"id": "B4EHBOZB",
			"type": "text",
			"x": -311.7501220703125,
			"y": -57.895835876464844,
			"width": 56,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 205878618,
			"version": 186,
			"versionNonce": 1793737306,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827835,
			"link": null,
			"locked": false,
			"text": "内存",
			"rawText": "内存",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "内存",
			"lineHeight": 1.25
		},
		{
			"id": "5kSlMAo7c7c9HTlIMF5Fr",
			"type": "line",
			"x": -223.74993896484375,
			"y": -61.56252288818359,
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 571929498,
			"version": 246,
			"versionNonce": 356599686,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160691793,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			],
			"lastCommittedPoint": [
				87.33331298828125,
				-1.33331298828125
			],
			"startBinding": null,
			"endBinding": null,
			"startArrowhead": null,
			"endArrowhead": null
		},
		{
			"id": "CBsAVB2j",
			"type": "text",
			"x": -222.75006103515625,
			"y": -89.56249237060547,
			"width": 94.51995849609375,
			"height": 25,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 620148678,
			"version": 173,
			"versionNonce": 1237905306,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160838877,
			"link": null,
			"locked": false,
			"text": "0X00000",
			"rawText": "0X00000",
			"fontSize": 20,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 17,
			"containerId": null,
			"originalText": "0X00000",
			"lineHeight": 1.25
		},
		{
			"id": "qUVHy5wuKzsSvhrs9BneQ",
			"type": "line",
			"x": -404.41668701171875,
			"y": -145.56246185302734,
			"width": 0,
			"height": 138.66668701171875,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 440000582,
			"version": 148,
			"versionNonce": 1039820486,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160691793,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					0,
					-138.66668701171875
				]
			],
			"lastCommittedPoint": [
				0,
				-138.66668701171875
			],
			"startBinding": null,
			"endBinding": null,
			"startArrowhead": null,
			"endArrowhead": null
		},
		{
			"id": "c7Kl1ICe",
			"type": "text",
			"x": -443.08343505859375,
			"y": -322.2291793823242,
			"width": 381.30389404296875,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 923413830,
			"version": 167,
			"versionNonce": 810903706,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160827837,
			"link": null,
			"locked": false,
			"text": "0XFFFF0: BIOS程序启动地址",
			"rawText": "0XFFFF0: BIOS程序启动地址",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "0XFFFF0: BIOS程序启动地址",
			"lineHeight": 1.25
		},
		{
			"id": "MZ10VUXKtG0jQrXW72Owv",
			"type": "rectangle",
			"x": 202.02777099609398,
			"y": 23.548642476399777,
			"width": 160,
			"height": 67,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 594792666,
			"version": 178,
			"versionNonce": 718074886,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "CO1sA6BW"
				},
				{
					"id": "ocApPZuZE0bD39D1R7B4p",
					"type": "arrow"
				}
			],
			"updated": 1701160908474,
			"link": null,
			"locked": false
		},
		{
			"id": "CO1sA6BW",
			"type": "text",
			"x": 222.49977874755882,
			"y": 39.54864247639978,
			"width": 119.05598449707031,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1896011974,
			"version": 151,
			"versionNonce": 1851556678,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160908474,
			"link": null,
			"locked": false,
			"text": "CS寄存器",
			"rawText": "CS寄存器",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 24,
			"containerId": "MZ10VUXKtG0jQrXW72Owv",
			"originalText": "CS寄存器",
			"lineHeight": 1.25
		},
		{
			"type": "rectangle",
			"version": 267,
			"versionNonce": 263727750,
			"isDeleted": false,
			"id": "7MupZCgOZsQ8Z3pLzynDw",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 202.36102294921898,
			"y": 104.82641347249353,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 161,
			"height": 54,
			"seed": 1049630938,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"boundElements": [
				{
					"type": "text",
					"id": "A9YA5ita"
				}
			],
			"updated": 1701160908474,
			"link": null,
			"locked": false
		},
		{
			"type": "text",
			"version": 257,
			"versionNonce": 765258182,
			"isDeleted": false,
			"id": "A9YA5ita",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 223.97702789306663,
			"y": 114.32641347249353,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 117.76799011230469,
			"height": 35,
			"seed": 1770778010,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160908474,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "IP寄存器",
			"rawText": "IP寄存器",
			"textAlign": "center",
			"verticalAlign": "middle",
			"containerId": "7MupZCgOZsQ8Z3pLzynDw",
			"originalText": "IP寄存器",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"id": "2hdXk0iP",
			"type": "text",
			"x": 255.36102294921898,
			"y": 66.5486729939779,
			"width": 17.5,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1433118214,
			"version": 155,
			"versionNonce": 120045830,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160908474,
			"link": null,
			"locked": false,
			"text": "+",
			"rawText": "+",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "+",
			"lineHeight": 1.25
		},
		{
			"id": "C3Z7wumb",
			"type": "text",
			"x": 514.4724324544271,
			"y": -165.1180547078451,
			"width": 513.827880859375,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1043750490,
			"version": 534,
			"versionNonce": 1895299546,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160827841,
			"link": null,
			"locked": false,
			"text": "1. 刚上电时CS:IP强制指向BIOS启动程序",
			"rawText": "1. 刚上电时CS:IP强制指向BIOS启动程序",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "1. 刚上电时CS:IP强制指向BIOS启动程序",
			"lineHeight": 1.25
		},
		{
			"id": "J7FngYY7s1_spaAMzVgX3",
			"type": "rectangle",
			"x": 223.91672770182322,
			"y": 233.32645416259766,
			"width": 110,
			"height": 180,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 2117857818,
			"version": 233,
			"versionNonce": 1876275270,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "YcI5MFM8"
				}
			],
			"updated": 1701160908474,
			"link": null,
			"locked": false
		},
		{
			"id": "YcI5MFM8",
			"type": "text",
			"x": 250.65073649088572,
			"y": 305.82645416259766,
			"width": 56.531982421875,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 431144582,
			"version": 178,
			"versionNonce": 1132705670,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160908474,
			"link": null,
			"locked": false,
			"text": "CPU",
			"rawText": "CPU",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 24,
			"containerId": "J7FngYY7s1_spaAMzVgX3",
			"originalText": "CPU",
			"lineHeight": 1.25
		},
		{
			"id": "iX6un4jk",
			"type": "text",
			"x": 514.4724324544271,
			"y": -110.22917938232422,
			"width": 339.10791015625,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1209118406,
			"version": 239,
			"versionNonce": 328576838,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827843,
			"link": null,
			"locked": false,
			"text": "2. BIOS初始化CPU，内存",
			"rawText": "2. BIOS初始化CPU，内存",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "2. BIOS初始化CPU，内存",
			"lineHeight": 1.25
		},
		{
			"id": "jo64nKQX",
			"type": "text",
			"x": -474.7243605393629,
			"y": -17.818908104529783,
			"width": 19.0679931640625,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 538768582,
			"version": 470,
			"versionNonce": 1766276314,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827843,
			"link": null,
			"locked": false,
			"text": "3",
			"rawText": "3",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "3",
			"lineHeight": 1.25
		},
		{
			"id": "V2dRdbDFhRi651-schvHa",
			"type": "arrow",
			"x": -339.4423499474159,
			"y": -107.40862039419324,
			"width": 104.97433706430286,
			"height": 264.9638452887216,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 1695524806,
			"version": 1018,
			"versionNonce": 1476621702,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160882120,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					-104.97433706430286,
					97.84615854116589
				],
				[
					-37.64102407602161,
					264.9638452887216
				]
			],
			"lastCommittedPoint": [
				-126.66668701171875,
				216.66668701171875
			],
			"startBinding": null,
			"endBinding": {
				"elementId": "PG2uwwj1PQGWj5r9p1_rv",
				"focus": -0.8355339056329033,
				"gap": 9.3333740234375
			},
			"startArrowhead": null,
			"endArrowhead": "arrow"
		},
		{
			"id": "PG2uwwj1PQGWj5r9p1_rv",
			"type": "rectangle",
			"x": -367.75,
			"y": 140.77088165283203,
			"width": 164,
			"height": 80,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 1711929434,
			"version": 312,
			"versionNonce": 2042532250,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "TmlahKcV"
				},
				{
					"id": "V2dRdbDFhRi651-schvHa",
					"type": "arrow"
				}
			],
			"updated": 1701160827844,
			"link": null,
			"locked": false
		},
		{
			"id": "TmlahKcV",
			"type": "text",
			"x": -361.8099822998047,
			"y": 168.27088165283203,
			"width": 152.11996459960938,
			"height": 25,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 391124614,
			"version": 141,
			"versionNonce": 366778758,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160852766,
			"link": null,
			"locked": false,
			"text": "BIOS一部分程序",
			"rawText": "BIOS一部分程序",
			"fontSize": 20,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 17,
			"containerId": "PG2uwwj1PQGWj5r9p1_rv",
			"originalText": "BIOS一部分程序",
			"lineHeight": 1.25
		},
		{
			"id": "AeMxmWjf",
			"type": "text",
			"x": 514.4724324544271,
			"y": 7.822071368877687,
			"width": 347.59197998046875,
			"height": 70,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1832964250,
			"version": 353,
			"versionNonce": 595682182,
			"isDeleted": false,
			"boundElements": [],
			"updated": 1701160827846,
			"link": null,
			"locked": false,
			"text": "4. 枚举本地设备，并初始化\n进行相关检查",
			"rawText": "4. 枚举本地设备，并初始化\n进行相关检查",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 59,
			"containerId": null,
			"originalText": "4. 枚举本地设备，并初始化\n进行相关检查",
			"lineHeight": 1.25
		},
		{
			"type": "line",
			"version": 445,
			"versionNonce": 162709702,
			"isDeleted": false,
			"id": "nKWlB1BFT4Yuqfi2TAd0J",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -220.07424189799931,
			"y": 46.558096081763495,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"seed": 1270323994,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1701160691794,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			]
		},
		{
			"id": "4gGSSW1V",
			"type": "text",
			"x": -138.4850495167267,
			"y": -36.54967185778503,
			"width": 84,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 579495066,
			"version": 303,
			"versionNonce": 1461033050,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "sYuX6r0EbvAJYP2Q8x0vi",
					"type": "arrow"
				}
			],
			"updated": 1701160898722,
			"link": null,
			"locked": false,
			"text": "中断表",
			"rawText": "中断表",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "中断表",
			"lineHeight": 1.25
		},
		{
			"type": "text",
			"version": 310,
			"versionNonce": 555443590,
			"isDeleted": false,
			"id": "0wRJXZpB",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -194.34329223632812,
			"y": 22.937599182128906,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 89.81996154785156,
			"height": 25,
			"seed": 947573850,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160840418,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0X003FF",
			"rawText": "0X003FF",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0X003FF",
			"lineHeight": 1.25,
			"baseline": 17
		},
		{
			"type": "text",
			"version": 373,
			"versionNonce": 2088628058,
			"isDeleted": false,
			"id": "8rY6sKFt",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -196.01129150390625,
			"y": 50.604164123535156,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 93.55995178222656,
			"height": 25,
			"seed": 1705135558,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160842514,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0X00400",
			"rawText": "0X00400",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0X00400",
			"lineHeight": 1.25,
			"baseline": 17
		},
		{
			"type": "line",
			"version": 564,
			"versionNonce": 60933958,
			"isDeleted": false,
			"id": "hnwidt2dZ9Y6Gyp4fFRpj",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -220.75554534867405,
			"y": 96.02466879561544,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"seed": 371540998,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1701160691794,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			]
		},
		{
			"type": "text",
			"version": 423,
			"versionNonce": 1600991686,
			"isDeleted": false,
			"id": "32qaKsHw",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -197.17391967773438,
			"y": 73.2708511352539,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 88.99995422363281,
			"height": 25,
			"seed": 1414115590,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160844039,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0X004FF",
			"rawText": "0X004FF",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0X004FF",
			"lineHeight": 1.25,
			"baseline": 17
		},
		{
			"type": "text",
			"version": 355,
			"versionNonce": 1375783450,
			"isDeleted": false,
			"id": "0g7sYRFs",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -88.4158685146233,
			"y": 52.11692829621137,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 156.96795654296875,
			"height": 35,
			"seed": 1915196998,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160922922,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "BIOS数据区",
			"rawText": "BIOS数据区",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "BIOS数据区",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"type": "text",
			"version": 579,
			"versionNonce": 928716570,
			"isDeleted": false,
			"id": "rFY61RuN",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -188.01666259765625,
			"y": 215.8861888005183,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 86.69993591308594,
			"height": 25,
			"seed": 336572890,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160845536,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0X0e05b",
			"rawText": "0X0e05b",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0X0e05b",
			"lineHeight": 1.25,
			"baseline": 17
		},
		{
			"type": "line",
			"version": 704,
			"versionNonce": 1917850,
			"isDeleted": false,
			"id": "_kRLiCClDxffMP8GlFMME",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -217.20362228158106,
			"y": 249.33181222508838,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"seed": 739275226,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1701160704612,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			]
		},
		{
			"type": "line",
			"version": 1122,
			"versionNonce": 1414088986,
			"isDeleted": false,
			"id": "WGwcwcifHqpTSuQZLOrnh",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -215.05304931706453,
			"y": 280.8983883715871,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"seed": 1597156358,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1701160708231,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			]
		},
		{
			"type": "text",
			"version": 587,
			"versionNonce": 681826138,
			"isDeleted": false,
			"id": "8V5us58V",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -100.49554384671728,
			"y": 245.04012885460486,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 168,
			"height": 35,
			"seed": 528414042,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827850,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "中断服务程序",
			"rawText": "中断服务程序",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "中断服务程序",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"id": "WP1p8grd",
			"type": "text",
			"x": -32.41668701171875,
			"y": -247.06249237060547,
			"width": 56,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 50642202,
			"version": 67,
			"versionNonce": 439028358,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827851,
			"link": null,
			"locked": false,
			"text": "主板",
			"rawText": "主板",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "主板",
			"lineHeight": 1.25
		},
		{
			"type": "text",
			"version": 477,
			"versionNonce": 647699866,
			"isDeleted": false,
			"id": "cAVv9qhB",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 514.4724324544271,
			"y": -49.98422993854331,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 348.739990234375,
			"height": 35,
			"seed": 1811622406,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827852,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "3. 复制自己的一部分到内存",
			"rawText": "3. 复制自己的一部分到内存",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "3. 复制自己的一部分到内存",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"type": "text",
			"version": 533,
			"versionNonce": 2025099334,
			"isDeleted": false,
			"id": "0Nbpkr9o",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -350.2804204552118,
			"y": -181.061090415306,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"width": 19.935989379882812,
			"height": 35,
			"seed": 2066389958,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827853,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "2",
			"rawText": "2",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "2",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"type": "text",
			"version": 720,
			"versionNonce": 1702169562,
			"isDeleted": false,
			"id": "bKhOEiKX",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 515.4980108799078,
			"y": 89.70804645368446,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 727.9439697265625,
			"height": 35,
			"seed": 227291590,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827854,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "5. 在内存中构建中断表，BIOS数据区，加载中断服务程序",
			"rawText": "5. 在内存中构建中断表，BIOS数据区，加载中断服务程序",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "5. 在内存中构建中断表，BIOS数据区，加载中断服务程序",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"id": "mVtGA8Vo",
			"type": "text",
			"x": -315.9564980778456,
			"y": 135.60545105104018,
			"width": 95.14399719238281,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 929775494,
			"version": 189,
			"versionNonce": 201256454,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827854,
			"link": null,
			"locked": false,
			"text": "4 5 6 ",
			"rawText": "4 5 6 ",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "4 5 6 ",
			"lineHeight": 1.25
		},
		{
			"id": "CCPn4jbqBoBAHnAoovbHv",
			"type": "rectangle",
			"x": 5.0691742478758215,
			"y": -67.15089660520982,
			"width": 77.52129970452734,
			"height": 101.53846153846155,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 2122581766,
			"version": 124,
			"versionNonce": 218462534,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "sYuX6r0EbvAJYP2Q8x0vi",
					"type": "arrow"
				}
			],
			"updated": 1701160916454,
			"link": null,
			"locked": false
		},
		{
			"id": "qJmC-bEsHqPKqIuAeJ8_H",
			"type": "rectangle",
			"x": 10.120424999077727,
			"y": -46.63806044234934,
			"width": 66,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 514574534,
			"version": 86,
			"versionNonce": 1788007706,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "tRxb0JQG"
				}
			],
			"updated": 1701160918735,
			"link": null,
			"locked": false
		},
		{
			"id": "tRxb0JQG",
			"type": "text",
			"x": 24.450434459526946,
			"y": -41.63806044234934,
			"width": 37.33998107910156,
			"height": 25,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 708736518,
			"version": 40,
			"versionNonce": 913121754,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160918735,
			"link": null,
			"locked": false,
			"text": "4 B",
			"rawText": "4 B",
			"fontSize": 20,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 17,
			"containerId": "qJmC-bEsHqPKqIuAeJ8_H",
			"originalText": "4 B",
			"lineHeight": 1.25
		},
		{
			"id": "lLo765cP",
			"type": "text",
			"x": -13.050520388542282,
			"y": -106.95858891290226,
			"width": 139.1599884033203,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1693109318,
			"version": 93,
			"versionNonce": 1172424646,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160920423,
			"link": null,
			"locked": false,
			"text": "256个条目",
			"rawText": "256个条目",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "256个条目",
			"lineHeight": 1.25
		},
		{
			"id": "sYuX6r0EbvAJYP2Q8x0vi",
			"type": "arrow",
			"x": -47.05055168862259,
			"y": -23.336150652188344,
			"width": 35.709438226161865,
			"height": 1.3517408876393944,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 560712154,
			"version": 258,
			"versionNonce": 587227078,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160916454,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					35.709438226161865,
					1.3517408876393944
				]
			],
			"lastCommittedPoint": [
				38.974327674278925,
				-2.0512507512019056
			],
			"startBinding": {
				"elementId": "4gGSSW1V",
				"gap": 7.434497828104099,
				"focus": -0.3219607237905351
			},
			"endBinding": {
				"elementId": "CCPn4jbqBoBAHnAoovbHv",
				"gap": 16.410287710336547,
				"focus": 0.06727693509014045
			},
			"startArrowhead": null,
			"endArrowhead": "arrow"
		},
		{
			"type": "text",
			"version": 890,
			"versionNonce": 814443078,
			"isDeleted": false,
			"id": "QBCwF3Rg",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 517.0851020761517,
			"y": 143.55429420007886,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 263.59197998046875,
			"height": 35,
			"seed": 666411718,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827856,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "6. 搜索可引导的设备",
			"rawText": "6. 搜索可引导的设备",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "6. 搜索可引导的设备",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"id": "SLU4w88R-fXWxaYwXiimi",
			"type": "rectangle",
			"x": 509.37677265532807,
			"y": 673.9773241730358,
			"width": 176,
			"height": 168,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 3
			},
			"seed": 655161030,
			"version": 215,
			"versionNonce": 1913991514,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "Hgwc3UXw"
				}
			],
			"updated": 1701160739638,
			"link": null,
			"locked": false
		},
		{
			"id": "Hgwc3UXw",
			"type": "text",
			"x": 569.3767726553281,
			"y": 740.4773241730358,
			"width": 56,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1289396294,
			"version": 163,
			"versionNonce": 426914182,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827857,
			"link": null,
			"locked": false,
			"text": "硬盘",
			"rawText": "硬盘",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 24,
			"containerId": "SLU4w88R-fXWxaYwXiimi",
			"originalText": "硬盘",
			"lineHeight": 1.25
		},
		{
			"id": "rWCxq44NaplqR1mpV9KtJ",
			"type": "ellipse",
			"x": 527.1202371985972,
			"y": 686.6952572409442,
			"width": 56.41038161057713,
			"height": 52.30769230769238,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 1976809114,
			"version": 237,
			"versionNonce": 103293658,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "sJTa-7LazRYxMZ4rQesZV",
					"type": "arrow"
				}
			],
			"updated": 1701160739638,
			"link": null,
			"locked": false
		},
		{
			"id": "sJTa-7LazRYxMZ4rQesZV",
			"type": "arrow",
			"x": 572.2485049269627,
			"y": 686.6952572409442,
			"width": 62.564227764423094,
			"height": 82.0512507512019,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 1874384966,
			"version": 373,
			"versionNonce": 725805510,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160739800,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					62.564227764423094,
					-82.0512507512019
				]
			],
			"lastCommittedPoint": [
				62.564227764423094,
				-82.0512507512019
			],
			"startBinding": {
				"elementId": "rWCxq44NaplqR1mpV9KtJ",
				"focus": -0.0874059511904877,
				"gap": 4.430766383014756
			},
			"endBinding": null,
			"startArrowhead": null,
			"endArrowhead": "arrow"
		},
		{
			"id": "I1ihMEfF",
			"type": "text",
			"x": 655.3254280038858,
			"y": 579.7080464536847,
			"width": 375.53594970703125,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1055411034,
			"version": 211,
			"versionNonce": 985450138,
			"isDeleted": false,
			"boundElements": [
				{
					"id": "u6EqJcClvZqhFzK5gUG1-",
					"type": "arrow"
				}
			],
			"updated": 1701160827858,
			"link": null,
			"locked": false,
			"text": "第1个扇区（256个字节）MBR",
			"rawText": "第1个扇区（256个字节）MBR",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "第1个扇区（256个字节）MBR",
			"lineHeight": 1.25
		},
		{
			"id": "ljK2TUxh",
			"type": "text",
			"x": 806.0949091737574,
			"y": 627.8277410901032,
			"width": 193.42396545410156,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 267154182,
			"version": 388,
			"versionNonce": 1531179846,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160890947,
			"link": null,
			"locked": false,
			"text": "GRUB启动程序",
			"rawText": "GRUB启动程序",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "GRUB启动程序",
			"lineHeight": 1.25
		},
		{
			"id": "lsKNW5u4",
			"type": "text",
			"x": 808.1460660247188,
			"y": 683.2123564747186,
			"width": 84,
			"height": 35,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 1639393926,
			"version": 376,
			"versionNonce": 1311873670,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160890947,
			"link": null,
			"locked": false,
			"text": "分区表",
			"rawText": "分区表",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 24,
			"containerId": null,
			"originalText": "分区表",
			"lineHeight": 1.25
		},
		{
			"id": "MDxFBHEAiBFjZlNmy1heS",
			"type": "freedraw",
			"x": 795.8383737170269,
			"y": 639.9432196057281,
			"width": 29.74365234375,
			"height": 71.79480919471166,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 674292250,
			"version": 413,
			"versionNonce": 996694470,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160890947,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					0,
					-1.0256723257211888
				],
				[
					0,
					-2.051344651442264
				],
				[
					0,
					-3.0769230769230944
				],
				[
					-2.0513446514423777,
					-3.0769230769230944
				],
				[
					-3.0769230769230944,
					-3.0769230769230944
				],
				[
					-4.102689302884755,
					-3.0769230769230944
				],
				[
					-6.153846153846189,
					-3.0769230769230944
				],
				[
					-7.17961237980785,
					-3.0769230769230944
				],
				[
					-9.230769230769283,
					-3.0769230769230944
				],
				[
					-11.282113882211661,
					-3.0769230769230944
				],
				[
					-12.307692307692378,
					-3.0769230769230944
				],
				[
					-13.333458533653811,
					-3.0769230769230944
				],
				[
					-13.333458533653811,
					-2.051344651442264
				],
				[
					-13.333458533653811,
					-1.0256723257211888
				],
				[
					-13.333458533653811,
					0
				],
				[
					-14.359036959134755,
					1.0255784254808304
				],
				[
					-14.359036959134755,
					2.0512507512019056
				],
				[
					-14.359036959134755,
					3.0769230769230944
				],
				[
					-14.359036959134755,
					4.102501502403811
				],
				[
					-14.359036959134755,
					5.128173828125
				],
				[
					-14.359036959134755,
					6.153846153846189
				],
				[
					-14.359036959134755,
					7.179424579326906
				],
				[
					-14.359036959134755,
					8.205096905048094
				],
				[
					-14.359036959134755,
					9.230769230769283
				],
				[
					-14.359036959134755,
					10.25634765625
				],
				[
					-14.359036959134755,
					11.282019981971189
				],
				[
					-14.359036959134755,
					12.307692307692378
				],
				[
					-14.359036959134755,
					13.333270733173094
				],
				[
					-14.359036959134755,
					14.358943058894283
				],
				[
					-14.359036959134755,
					15.384615384615358
				],
				[
					-14.359036959134755,
					16.41019381009619
				],
				[
					-14.359036959134755,
					17.435866135817378
				],
				[
					-14.359036959134755,
					18.461538461538453
				],
				[
					-14.359036959134755,
					19.487116887019283
				],
				[
					-14.359036959134755,
					20.51278921274036
				],
				[
					-13.333458533653811,
					20.51278921274036
				],
				[
					-13.333458533653811,
					21.538461538461547
				],
				[
					-13.333458533653811,
					22.564039963942378
				],
				[
					-13.333458533653811,
					23.589712289663453
				],
				[
					-15.384615384615472,
					23.589712289663453
				],
				[
					-17.43596003605785,
					23.589712289663453
				],
				[
					-19.4873046875,
					23.589712289663453
				],
				[
					-20.512883112980944,
					23.589712289663453
				],
				[
					-21.53846153846166,
					23.589712289663453
				],
				[
					-22.564227764423094,
					23.589712289663453
				],
				[
					-21.53846153846166,
					24.61538461538464
				],
				[
					-20.512883112980944,
					25.64096304086536
				],
				[
					-19.4873046875,
					25.64096304086536
				],
				[
					-17.43596003605785,
					26.666635366586547
				],
				[
					-16.410381610576906,
					26.666635366586547
				],
				[
					-16.410381610576906,
					27.692307692307736
				],
				[
					-15.384615384615472,
					27.692307692307736
				],
				[
					-15.384615384615472,
					28.717886117788453
				],
				[
					-14.359036959134755,
					28.717886117788453
				],
				[
					-14.359036959134755,
					29.74355844350964
				],
				[
					-14.359036959134755,
					30.76923076923083
				],
				[
					-14.359036959134755,
					31.794809194711547
				],
				[
					-13.333458533653811,
					31.794809194711547
				],
				[
					-13.333458533653811,
					32.820481520432736
				],
				[
					-13.333458533653811,
					33.846153846153925
				],
				[
					-13.333458533653811,
					35.89740459735583
				],
				[
					-13.333458533653811,
					36.923076923076906
				],
				[
					-12.307692307692378,
					37.948655348557736
				],
				[
					-12.307692307692378,
					38.974327674278925
				],
				[
					-12.307692307692378,
					40
				],
				[
					-12.307692307692378,
					41.02557842548083
				],
				[
					-11.282113882211661,
					42.051250751201906
				],
				[
					-11.282113882211661,
					43.076923076923094
				],
				[
					-11.282113882211661,
					44.10250150240381
				],
				[
					-11.282113882211661,
					45.128173828125
				],
				[
					-11.282113882211661,
					47.179424579326906
				],
				[
					-11.282113882211661,
					48.205096905048094
				],
				[
					-11.282113882211661,
					49.23076923076928
				],
				[
					-10.256535456730717,
					50.25634765625
				],
				[
					-10.256535456730717,
					51.28201998197119
				],
				[
					-9.230769230769283,
					52.30769230769238
				],
				[
					-9.230769230769283,
					53.333270733173094
				],
				[
					-9.230769230769283,
					54.35894305889428
				],
				[
					-8.205190805288566,
					54.35894305889428
				],
				[
					-8.205190805288566,
					55.38461538461547
				],
				[
					-8.205190805288566,
					56.41019381009619
				],
				[
					-8.205190805288566,
					57.43586613581738
				],
				[
					-7.17961237980785,
					57.43586613581738
				],
				[
					-7.17961237980785,
					58.46153846153857
				],
				[
					-7.17961237980785,
					59.48711688701928
				],
				[
					-6.153846153846189,
					60.51278921274047
				],
				[
					-6.153846153846189,
					61.53846153846166
				],
				[
					-5.128267728365472,
					61.53846153846166
				],
				[
					-5.128267728365472,
					62.56403996394238
				],
				[
					-5.128267728365472,
					63.58971228966357
				],
				[
					-5.128267728365472,
					64.61538461538476
				],
				[
					-5.128267728365472,
					65.64096304086547
				],
				[
					-4.102689302884755,
					66.66663536658666
				],
				[
					-4.102689302884755,
					67.69230769230785
				],
				[
					-4.102689302884755,
					68.71788611778857
				],
				[
					-3.0769230769230944,
					68.71788611778857
				],
				[
					-2.0513446514423777,
					68.71788611778857
				],
				[
					-1.025766225961661,
					68.71788611778857
				],
				[
					0,
					67.69230769230785
				],
				[
					1.0255784254807168,
					66.66663536658666
				],
				[
					1.0255784254807168,
					65.64096304086547
				],
				[
					2.0511568509614335,
					65.64096304086547
				],
				[
					3.0769230769230944,
					64.61538461538476
				],
				[
					4.102501502403811,
					64.61538461538476
				],
				[
					5.128079927884528,
					63.58971228966357
				],
				[
					6.153846153846189,
					62.56403996394238
				],
				[
					7.179424579326906,
					61.53846153846166
				],
				[
					7.179424579326906,
					61.53846153846166
				]
			],
			"pressures": [],
			"simulatePressure": true,
			"lastCommittedPoint": [
				7.179424579326906,
				61.53846153846166
			]
		},
		{
			"type": "text",
			"version": 1074,
			"versionNonce": 461165830,
			"isDeleted": false,
			"id": "LLQlshHk",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": 517.9626579233187,
			"y": 203.04145803721815,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 859.1238403320312,
			"height": 35,
			"seed": 1489641178,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [],
			"updated": 1701160827861,
			"link": null,
			"locked": false,
			"fontSize": 28,
			"fontFamily": 1,
			"text": "7. MBR被BIOS装载到0x7c00地址开始的内存空间, 控制权交给MBR",
			"rawText": "7. MBR被BIOS装载到0x7c00地址开始的内存空间, 控制权交给MBR",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "7. MBR被BIOS装载到0x7c00地址开始的内存空间, 控制权交给MBR",
			"lineHeight": 1.25,
			"baseline": 24
		},
		{
			"type": "line",
			"version": 814,
			"versionNonce": 1293729498,
			"isDeleted": false,
			"id": "E_v7Rf6PJNWBX7LlevrJZ",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -213.95178466203757,
			"y": 425.25870756321507,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 98.6666259765625,
			"height": 1.33331298828125,
			"seed": 744338502,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"boundElements": [],
			"updated": 1701160715168,
			"link": null,
			"locked": false,
			"startBinding": null,
			"endBinding": null,
			"lastCommittedPoint": null,
			"startArrowhead": null,
			"endArrowhead": null,
			"points": [
				[
					0,
					0
				],
				[
					98.6666259765625,
					-1.33331298828125
				]
			]
		},
		{
			"type": "text",
			"version": 649,
			"versionNonce": 813004122,
			"isDeleted": false,
			"id": "YgEoam6l",
			"fillStyle": "hachure",
			"strokeWidth": 1,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"angle": 0,
			"x": -186.53397399243374,
			"y": 395.73367182928564,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"width": 74.03996276855469,
			"height": 25,
			"seed": 1526974982,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"boundElements": [
				{
					"id": "u6EqJcClvZqhFzK5gUG1-",
					"type": "arrow"
				}
			],
			"updated": 1701160848516,
			"link": null,
			"locked": false,
			"fontSize": 20,
			"fontFamily": 1,
			"text": "0X7c00",
			"rawText": "0X7c00",
			"textAlign": "left",
			"verticalAlign": "top",
			"containerId": null,
			"originalText": "0X7c00",
			"lineHeight": 1.25,
			"baseline": 17
		},
		{
			"id": "u6EqJcClvZqhFzK5gUG1-",
			"type": "arrow",
			"x": 818.9156209301436,
			"y": 572.8491033947904,
			"width": 943.0772159130371,
			"height": 161.02562537560107,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": {
				"type": 2
			},
			"seed": 2073623322,
			"version": 553,
			"versionNonce": 1503591514,
			"isDeleted": false,
			"boundElements": [
				{
					"type": "text",
					"id": "UFie4zz8"
				}
			],
			"updated": 1701160743968,
			"link": null,
			"locked": false,
			"points": [
				[
					0,
					0
				],
				[
					-382.0515435873159,
					-115.89740459735577
				],
				[
					-943.0772159130371,
					-161.02562537560107
				]
			],
			"lastCommittedPoint": [
				-850.2564415564907,
				44.10254845252405
			],
			"startBinding": {
				"elementId": "I1ihMEfF",
				"focus": 0.9738484851414658,
				"gap": 14.358943058894283
			},
			"endBinding": {
				"elementId": "YgEoam6l",
				"focus": 0.07712005192008989,
				"gap": 3.140414898212157
			},
			"startArrowhead": null,
			"endArrowhead": "arrow"
		},
		{
			"id": "UFie4zz8",
			"type": "text",
			"x": 429.33207966216366,
			"y": 439.45169879743463,
			"width": 15.063995361328125,
			"height": 35,
			"angle": 0,
			"strokeColor": "#e03131",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 369549062,
			"version": 7,
			"versionNonce": 955586522,
			"isDeleted": false,
			"boundElements": null,
			"updated": 1701160827862,
			"link": null,
			"locked": false,
			"text": "7",
			"rawText": "7",
			"fontSize": 28,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 24,
			"containerId": "u6EqJcClvZqhFzK5gUG1-",
			"originalText": "7",
			"lineHeight": 1.25
		},
		{
			"id": "0raY1djD",
			"type": "text",
			"x": -449.41668701171875,
			"y": -22.062461853027344,
			"width": 10,
			"height": 25,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 142124678,
			"version": 2,
			"versionNonce": 398238490,
			"isDeleted": true,
			"boundElements": null,
			"updated": 1701160856176,
			"link": null,
			"locked": false,
			"text": "",
			"rawText": "",
			"fontSize": 20,
			"fontFamily": 1,
			"textAlign": "center",
			"verticalAlign": "middle",
			"baseline": 17,
			"containerId": "V2dRdbDFhRi651-schvHa",
			"originalText": "",
			"lineHeight": 1.25
		},
		{
			"id": "Ffzhosq6",
			"type": "text",
			"x": -112.87957500092239,
			"y": 488.23371877940576,
			"width": 8,
			"height": 20,
			"angle": 0,
			"strokeColor": "#1e1e1e",
			"backgroundColor": "transparent",
			"fillStyle": "hachure",
			"strokeWidth": 0.5,
			"strokeStyle": "solid",
			"roughness": 1,
			"opacity": 100,
			"groupIds": [],
			"frameId": null,
			"roundness": null,
			"seed": 370627206,
			"version": 2,
			"versionNonce": 1278236058,
			"isDeleted": true,
			"boundElements": null,
			"updated": 1701160690803,
			"link": null,
			"locked": false,
			"text": "",
			"rawText": "",
			"fontSize": 16,
			"fontFamily": 1,
			"textAlign": "left",
			"verticalAlign": "top",
			"baseline": 14,
			"containerId": null,
			"originalText": "",
			"lineHeight": 1.25
		}
	],
	"appState": {
		"theme": "light",
		"viewBackgroundColor": "#ffffff",
		"currentItemStrokeColor": "#1e1e1e",
		"currentItemBackgroundColor": "transparent",
		"currentItemFillStyle": "hachure",
		"currentItemStrokeWidth": 0.5,
		"currentItemStrokeStyle": "solid",
		"currentItemRoughness": 1,
		"currentItemOpacity": 100,
		"currentItemFontFamily": 1,
		"currentItemFontSize": 20,
		"currentItemTextAlign": "left",
		"currentItemStartArrowhead": null,
		"currentItemEndArrowhead": "arrow",
		"scrollX": 915.379575000923,
		"scrollY": 728.4382855290512,
		"zoom": {
			"value": 0.5999999999999996
		},
		"currentItemRoundness": "round",
		"gridSize": null,
		"gridColor": {
			"Bold": "#C9C9C9FF",
			"Regular": "#EDEDEDFF"
		},
		"currentStrokeOptions": null,
		"previousGridSize": null,
		"frameRendering": {
			"enabled": true,
			"clip": true,
			"name": true,
			"outline": true
		}
	},
	"files": {}
}
```
%%